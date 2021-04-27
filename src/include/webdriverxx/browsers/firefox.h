#ifndef WEBDRIVERXX_BROWSERS_FIREFOX_H
#define WEBDRIVERXX_BROWSERS_FIREFOX_H

#include "../capabilities.h"

namespace webdriverxx {

// TODO: this is dont written
class FirefoxBinary {
public:
	FirefoxBinary(const std::string& path = nullptr, const std::string& logfile = nullptr) {
		startcmd_ = path;
		if (!logfile.empty()) {
			logfile_ = logfile;
		} else {
			std::ofstream devnull_log("/dev/null", std::ofstream::binary);
			logfile_ = devnull_log;
			//std::streambuf* strm_buffer = std::cout.rdbuf();
			//std::cout.rdbuf(file.rdbuf());
		}
	}
private:
	std::string startcmd_;
	std::string logfile_;
	std::string commandline_;
	std::string platform_;
	std::string enviroment_;
};

struct Options : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(Options)
	//WEBDRIVERXX_PROPERTY(FirefoxBinary,         "binary",                    FirefoxBinary)
	WEBDRIVERXX_PROPERTY(FirefoxPreferences,    "prefs",                     std::vector<std::string>)
	WEBDRIVERXX_PROPERTY(FirefoxProfile,        "profile",                   std::string)
	WEBDRIVERXX_PROPERTY(FirefoxProxy,          "proxy",                     Proxy)
	WEBDRIVERXX_PROPERTY(FirefoxLogFile,        "log",                       std::string)
	WEBDRIVERXX_PROPERTIES_END()
};
	
// FIXME: Deprecated FirefoxProfile
struct FirefoxProfile : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(FirefoxProfile)
	WEBDRIVERXX_PROPERTY(AcceptUntrustedCerts,  "webdriver_accept_untrusted_certs",  bool)
	WEBDRIVERXX_PROPERTY(AssumeUntrustedIssuer, "webdriver_assume_untrusted_issuer", bool)
	WEBDRIVERXX_PROPERTY(LogDriver,             "webdriver.log.driver",              log_level::Value)
	WEBDRIVERXX_PROPERTY(FirefoxLogFile,        "webdriver.log.file",                std::string)
	WEBDRIVERXX_PROPERTY(LoadStrategy,          "webdriver.load.strategy",           std::string)
	WEBDRIVERXX_PROPERTY(Port,               "webdriver_firefox_port",            int) // default 7055
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
	WEBDRIVERXX_PROPERTY(FirefoxProfile,      "firefox_profile",     std::string)
	WEBDRIVERXX_PROPERTY(LoggingPrefs,        "loggingPrefs",        LoggingPrefs)
	WEBDRIVERXX_PROPERTY(FirefoxBinary,       "firefox_binary",      std::string)
	WEBDRIVERXX_PROPERTY(PageLoadingStrategy, "pageLoadingStrategy", std::string)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
