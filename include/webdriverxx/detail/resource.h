#ifndef WEBDRIVERXX_DETAIL_RESOURCE_H
#define WEBDRIVERXX_DETAIL_RESOURCE_H

#include "error_handling.h"
#include "http_client.h"
#include "shared.h"
#include "../conversions.h"
#include "../response_status_code.h"
#include "../picojson.h"

namespace webdriverxx {
namespace detail {

class Resource : public SharedObjectBase { // noncopyable
public:
	enum Ownership { IsOwner, IsObserver };

	Resource(
		const std::string& url,
		const Shared<IHttpClient>& http_client,
		Ownership mode = IsObserver
		)
		: http_client_(http_client)
		, url_(url)
		, ownership_(mode)
	{}

	Resource(
		const Shared<Resource>& parent,
		const std::string& name,
		Ownership mode = IsObserver
		)
		: http_client_(parent->http_client_)
		, parent_(parent)
		, url_(ConcatUrl(parent->url_, name))
		, ownership_(mode)
	{}

	virtual ~Resource() {
		try {
			if (ownership_ == IsOwner)
				DeleteResource();
		} catch (const std::exception&) {}
	}

	inline
	const std::string& GetUrl() const {
		return url_;
	}

	inline
	picojson::value Get(const std::string& command = std::string()) const {
		return Download(command, &IHttpClient::Get, "GET");
	}

	template<typename T>
	inline T GetValue(const std::string& command) const {
		WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
		return FromJson<T>(Get(command));
		WEBDRIVERXX_FUNCTION_CONTEXT_END_EX(detail::Fmt() <<
			"command: " << command
			)
	}

	inline
	std::string GetString(const std::string& command) const {
		return GetValue<std::string>(command);
	}

	inline
	bool GetBool(const std::string& command) const {
		return GetValue<bool>(command);
	}

	inline
	picojson::value Delete(const std::string& command = std::string()) const {
		return Download(command, &IHttpClient::Delete, "DELETE");
	}

	inline
	picojson::value Post(
		const std::string& command = std::string(),
		const picojson::value& upload_data = picojson::value()
		) const {
		return Upload(command, upload_data, &IHttpClient::Post, "POST");
	}

	template<typename T>
	inline picojson::value Post(
		const std::string& command,
		const std::string& arg_name,
		const T& arg_value
		) const {
		return Post(command, JsonObject().Set(arg_name, arg_value));
	}	

	template<typename T>
	inline picojson::value PostValue(const std::string& command, const T& value) const {
		WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
		return Post(command, ToJson(value));
		WEBDRIVERXX_FUNCTION_CONTEXT_END_EX(detail::Fmt() <<
			"command: " << command
			)
	}	

protected:
	inline
	virtual picojson::value TransformResponse(picojson::value& response) const {
		picojson::value result;
		response.get("value").swap(result);
		return result;
	}

	inline
	virtual void DeleteResource() {
		Delete();
	}

private:
	inline
	picojson::value Download(
		const std::string& command,
		HttpResponse (IHttpClient::* member)(const std::string& url) const,
		const char* request_type
		) const {
		WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
		return ProcessResponse((http_client_->*member)(
			ConcatUrl(url_, command)
			));
		WEBDRIVERXX_FUNCTION_CONTEXT_END_EX(Fmt()
			<< "request: " << request_type
			<< ", command: " << command
			<< ", resource: " << url_
			)
	}

	inline
	static std::string ToUploadData(const picojson::value& upload_data)
	{
		return upload_data.is<picojson::null>() ?
			std::string() : upload_data.serialize();
	}

	inline
	picojson::value Upload(
		const std::string& command,
		const picojson::value& upload_data,
		HttpResponse (IHttpClient::* member)(const std::string& url, const std::string& upload_data) const,
		const char* request_type
		) const {
		WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
		return ProcessResponse((http_client_->*member)(
			ConcatUrl(url_, command),
			ToUploadData(upload_data)
			));
		WEBDRIVERXX_FUNCTION_CONTEXT_END_EX(Fmt()
			<< "request: " << request_type
			<< ", command: " << command
			<< ", resource: " << url_
			<< ", data: " << ToUploadData(upload_data)
			)
	}

	picojson::value ProcessResponse(
		const HttpResponse& http_response
		) const {
		WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
		WEBDRIVERXX_CHECK(
			static_cast<int32_t>(http_response.http_code / 100) != 4 && // is not 4xx
			http_response.http_code != 501,
			"HTTP code indicates that request is invalid");

		picojson::value response;
		std::string error_message;
		picojson::parse(response, http_response.body.begin(), http_response.body.end(), &error_message);

		WEBDRIVERXX_CHECK(error_message.empty(),
			Fmt() << "JSON parser error (" << error_message << ")"
			);

		WEBDRIVERXX_CHECK(response.is<picojson::object>(), "Server response is not an object");
		response_status_code::Value status;
		if (response.contains("status")) {
			if (response.get("status").is<double>()) {
				status = static_cast<response_status_code::Value>(static_cast<int>(response.get("status").get<double>()));
			}
		}

		WEBDRIVERXX_CHECK(response.contains("value"), "Server response has no member \"value\"");
		const auto& value = response.get("value");

		if (http_response.http_code == 500) { // Internal server error
			WEBDRIVERXX_CHECK(value.is<picojson::object>(), "Server returned HTTP code 500 and \"response.value\" is not an object");
			WEBDRIVERXX_CHECK(value.contains("message"), "Server response has no member \"value.message\"");
			WEBDRIVERXX_CHECK(value.get("message").is<std::string>(), "\"value.message\" is not a string");
			auto ss = Fmt();
			ss << "Server failed to execute command (" << "message: " << value.get("message").to_str();
			if (response.contains("status")) {
				ss << ", status: " << response_status_code::ToString(status) << ", status_code: " << status;
			}
			ss << ")";
			WEBDRIVERXX_THROW();
		}

		if (response.contains("status")) {
			WEBDRIVERXX_CHECK(status == response_status_code::kSuccess, "Non-zero response status code");
		}

		WEBDRIVERXX_CHECK(http_response.http_code == 200, "Unsupported HTTP code");

		return TransformResponse(response);
		WEBDRIVERXX_FUNCTION_CONTEXT_END_EX(Fmt()
			<< "HTTP code: " << http_response.http_code
			<< ", body: " << http_response.body
			)
	}

	static
	std::string ConcatUrl(const std::string& a, const std::string& b, const char delim = '/') {
		auto result = a.empty() ? b : a;
		if (!a.empty() && !b.empty()) {
			if (result[result.length()-1] != delim)
				result += delim;
			result.append(b[0] == delim ? b.begin() + 1 : b.begin(), b.end());
		}
		return result;
	}

private:
	const Shared<IHttpClient> http_client_;
	const Shared<Resource> parent_;
	const std::string url_;
	const Ownership ownership_;
};

class RootResource : public Resource { // noncopyable
public:
	RootResource(
		const std::string& url,
		const Shared<IHttpClient>& http_client
		)
		: Resource(url, http_client, IsObserver)
	{}

private:
	inline
	virtual picojson::value TransformResponse(picojson::value& response) const {
		picojson::value result;
		response.swap(result);
		return result;
	}
};

inline
Shared<Resource> MakeSubResource(
	const Shared<Resource>& parent,
	const std::string& subpath,
	Resource::Ownership mode = Resource::IsObserver
	) {
	return Shared<Resource>(new Resource(parent, subpath, mode));
}

inline
Shared<Resource> MakeSubResource(
	const Shared<Resource>& parent,
	const std::string& subpath1,
	const std::string& subpath2,
	Resource::Ownership mode = Resource::IsObserver
	) {
	return Shared<Resource>(new Resource(parent, subpath1 + "/" + subpath2, mode));
}

} // namespace detail
} // namespace webdriverxx

#endif
