#ifndef WEBDRIVERXX_DETAIL_HTTP_CONNECTION_H
#define WEBDRIVERXX_DETAIL_HTTP_CONNECTION_H

#include "http_client.h"
#include "http_request.h"
#include "error_handling.h"
#include "shared.h"
#include <curl/curl.h>

namespace webdriverxx {
namespace detail {

class HttpConnection // noncopyable
	: public IHttpClient
	, public SharedObjectBase
{
public:
	HttpConnection()
		: connection_(InitCurl())
	{}

	~HttpConnection() {
		curl_easy_cleanup(connection_);
	}

	inline
	HttpResponse Get(const std::string& url) const {
		return HttpGetRequest(connection_, url).Execute();
	}
	
	inline
	HttpResponse Delete(const std::string& url) const {
		return HttpDeleteRequest(connection_, url).Execute();
	}
	
	inline
	HttpResponse Post(
		const std::string& url,
		const std::string& upload_data
		) const {
		return HttpPostRequest(connection_, url, upload_data).Execute();
	}

private:
	static
	inline CURL* InitCurl() {
		CURL *const result = curl_easy_init();
		WEBDRIVERXX_CHECK(result, "Cannot initialize CURL");
		return result;
	}

private:
	CURL *const connection_;
};

} // namespace detail
} // namespace webdriverxx

#endif
