#ifndef WEBDRIVERXX_BROWSERS_FIREFOX_H
#define WEBDRIVERXX_BROWSERS_FIREFOX_H

#include "../capabilities.h"

namespace webdriverxx {
	
struct FirefoxProfile : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(FirefoxProfile)
	WEBDRIVERXX_PROPERTY(AcceptUntrustedCerts,  "webdriver_accept_untrusted_certs",  bool)
	WEBDRIVERXX_PROPERTY(AssumeUntrustedIssuer, "webdriver_assume_untrusted_issuer", bool)
	WEBDRIVERXX_PROPERTY(LogDriver,             "webdriver.log.driver",              log_level::Value)
	WEBDRIVERXX_PROPERTY(LogFile,               "webdriver.log.file",                std::string)
	WEBDRIVERXX_PROPERTY(LoadStrategy,          "webdriver.load.strategy",           std::string)
	WEBDRIVERXX_PROPERTY(LogFile,               "webdriver_firefox_port",            int) // default 7055
	WEBDRIVERXX_PROPERTIES_END()
};

struct Firefox : Capabilities { // copyable
	Firefox(const Capabilities& defaults = Capabilities())
		: Capabilities(defaults) {
		SetBrowserName(browser::Firefox);
		SetVersion("");
		SetPlatform(platform::Any);
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(Firefox)
	// Profile is a profile folder, zipped and base64 encoded.
	// base64 string FirefoxProfile : JsonObject
	WEBDRIVERXX_PROPERTY(Profile,             "firefox_profile",     std::string)
	WEBDRIVERXX_PROPERTY(LoggingPrefs,        "loggingPrefs",        LoggingPrefs)
	WEBDRIVERXX_PROPERTY(FirefoxBinary,       "firefox_binary",      std::string)
	WEBDRIVERXX_PROPERTY(PageLoadingStrategy, "pageLoadingStrategy", std::string)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
