#ifndef WEBDRIVERXX_DETAIL_HTTP_CLIENT_H
#define WEBDRIVERXX_DETAIL_HTTP_CLIENT_H

#include "types.h"
#include <string>

namespace webdriverxx {
namespace detail {

struct HttpResponse {
	HTTPCode http_code;
	std::string body;

	HttpResponse()
		: http_code(0L)
	{}
};

struct IHttpClient {
	virtual HttpResponse Get(const std::string& url) const = 0;
	virtual HttpResponse Delete(const std::string& url) const = 0;
	virtual HttpResponse Post(const std::string& url, const std::string& data) const = 0;
	virtual ~IHttpClient() {}
};

} // namespace detail
} // namespace webdriverxx

#endif
