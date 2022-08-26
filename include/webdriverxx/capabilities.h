#ifndef WEBDRIVERXX_CAPABILITIES_H
#define WEBDRIVERXX_CAPABILITIES_H

#include "conversions.h"
#include "picojson.h"
#include <string>

namespace webdriverxx {

namespace browser {
typedef std::string Value;
typedef const char* const ConstValue;
ConstValue Chrome           = "chrome";
ConstValue Edge             = "MicrosoftEdge";
ConstValue Firefox          = "firefox";
ConstValue HtmlUnit         = "htmlunit";
ConstValue InternetExplorer = "internet explorer";
ConstValue IPad             = "iPad";
ConstValue IPhone           = "iPhone";
ConstValue Opera            = "opera";
ConstValue Safari           = "safari";
ConstValue WebKitGTK        = "MiniBrowser";
ConstValue Mock             = "mock";
ConstValue PhantomJS        = "phantomjs";
} // namespace browser

namespace platform {
typedef std::string Value;
typedef const char* const ConstValue;
ConstValue Any              = "ANY";
ConstValue Windows          = "WINDOWS";
ConstValue Xp               = "XP";
ConstValue Nt               = "NT";
ConstValue Mac              = "MAC";
ConstValue Linux            = "LINUX";
ConstValue Unix             = "UNIX";
ConstValue Android          = "ANDROID";
ConstValue Darwin           = "DARWIN";
ConstValue Java             = "JAVA";
} // namespace platform

namespace unexpected_alert_behaviour {
typedef std::string Value;
typedef const char* const ConstValue;
ConstValue Ignore           = "ignore";
ConstValue Accept           = "accept";
ConstValue Dismiss          = "dismiss";
ConstValue AcceptAndNotify  = "accept and notify";
ConstValue DismissAndNotify = "dismiss and notify";
} // namespace unexpected_alert_behaviour

namespace page_load_strategy {
typedef std::string Value;
typedef const char* const ConstValue;
ConstValue Default          = "default";
ConstValue Normal           = "normal";
ConstValue Eager            = "eager";
ConstValue None             = "none";
} // namespace page_load_strategy

namespace proxy_type {
typedef std::string Value;
typedef const char* const ConstValue;
ConstValue Direct           = "DIRECT";         // Direct connection, no proxy (default on Windows).
ConstValue Manual           = "MANUAL";         // Manual proxy settings (e.g., for httpProxy).
ConstValue Pac              = "PAC";            // Proxy autoconfiguration from URL.
ConstValue Autodetect       = "AUTODETECT";     // Proxy autodetection (presumably with WPAD).
ConstValue System           = "SYSTEM";         // Use system settings (default on Linux).
} // namespace proxy_type

#define WEBDRIVERXX_PROPERTIES_BEGIN(this_class) typedef this_class This;
#define WEBDRIVERXX_PROPERTIES_END()

#define WEBDRIVERXX_PROPERTY_RONLY(name, id, type) \
	inline type Get##name() const { return GetOptional<type>(id); } \
	inline bool Has##name() { return Has(id); }

#define WEBDRIVERXX_PROPERTY(name, id, type) \
	WEBDRIVERXX_PROPERTY_RONLY(name, id, type) \
	inline This& Set##name(const type& value) { Set(id, value); return *this; }

struct Proxy : JsonObject { // copyable
	WEBDRIVERXX_PROPERTIES_BEGIN(Proxy)
	WEBDRIVERXX_PROPERTY(ProxyType, "proxyType", proxy_type::Value)
	WEBDRIVERXX_PROPERTIES_END()
};

struct DirectConnection : Proxy { // copyable
	DirectConnection() { SetProxyType(proxy_type::Direct); }
};

struct AutodetectProxy : Proxy { // copyable
	AutodetectProxy() { SetProxyType(proxy_type::Autodetect); }
};

struct SystemProxy : Proxy { // copyable
	SystemProxy() { SetProxyType(proxy_type::System); }
};

struct AutomaticProxyFromUrl : Proxy { // copyable
	explicit AutomaticProxyFromUrl(const std::string& url) {
		SetProxyType(proxy_type::Pac);
		SetAutoconfigUrl(url);
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(AutomaticProxyFromUrl)
	WEBDRIVERXX_PROPERTY(AutoconfigUrl, "proxyAutoconfigUrl", std::string)
	WEBDRIVERXX_PROPERTIES_END()
};

struct ManualProxy : Proxy { // copyable
	ManualProxy() { SetProxyType(proxy_type::Manual); }

	WEBDRIVERXX_PROPERTIES_BEGIN(ManualProxy)
	WEBDRIVERXX_PROPERTY(NoProxyFor, "noProxy", std::string)
	WEBDRIVERXX_PROPERTIES_END()
};

struct FtpProxy : ManualProxy { // copyable
	explicit FtpProxy(const std::string& address) { SetProxyAddress(address); }

	WEBDRIVERXX_PROPERTIES_BEGIN(FtpProxy)
	WEBDRIVERXX_PROPERTY(ProxyAddress, "ftpProxy", std::string)
	WEBDRIVERXX_PROPERTIES_END()
};

struct HttpProxy : ManualProxy { // copyable
	explicit HttpProxy(const std::string& address, const std::string& username = "", const std::string& password = "") {
		if (!username.empty()) {
			if (!password.empty()) {
				// TODO: create tunnel and connect
				SetProxyAddress(address + '@' + username + ':' + password);
			} else {
				SetProxyAddress(address + '@' + username + ':'); // pass empty
			}
		}
		else {
			SetProxyAddress(address);
		}
	}

	HttpProxy& SetUsername(const std::string& username) {
		SetProxyAddress(GetProxyAddress() + "@" + username + ":"); // pass empty
		return *this;
	}

	HttpProxy& SetPassword(const std::string& password) {
		SetProxyAddress(GetProxyAddress() + password); // pass empty
		return *this;
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(HttpProxy)
	WEBDRIVERXX_PROPERTY(ProxyAddress, "httpProxy", std::string)
	WEBDRIVERXX_PROPERTIES_END()
};

struct SslProxy : ManualProxy { // copyable
	explicit SslProxy(const std::string& address, const std::string& username = "", const std::string& password = "") {
		if (!username.empty()) {
			if (!password.empty()) {
				// TODO: create tunnel and connect
				SetProxyAddress(address + '@' + username + ':' + password);
			} else {
				SetProxyAddress(address + '@' + username + ':'); // pass empty
			}
		}
		else {
			SetProxyAddress(address);
		}
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(SslProxy)
	WEBDRIVERXX_PROPERTY(ProxyAddress, "sslProxy", std::string)
	WEBDRIVERXX_PROPERTIES_END()
};

struct SocksProxy : ManualProxy { // copyable
	explicit SocksProxy(const std::string& address) { SetProxyAddress(address); SetProxyVersion(5); }

	WEBDRIVERXX_PROPERTIES_BEGIN(SocksProxy)
	WEBDRIVERXX_PROPERTY(ProxyAddress, "socksProxy", std::string)
	WEBDRIVERXX_PROPERTY(Username, "socksUsername", std::string)
	WEBDRIVERXX_PROPERTY(Password, "socksPassword", std::string)
	WEBDRIVERXX_PROPERTY(ProxyVersion, "socksVersion", int) // [4,5]
	WEBDRIVERXX_PROPERTIES_END()
};

namespace log_level {
typedef std::string Value;
typedef const char* const ConstValue;
ConstValue Trace           = "trace";
ConstValue Debug           = "debug";
ConstValue Config          = "config";
ConstValue Info            = "info";
ConstValue Warn            = "warn";
ConstValue Error           = "error";
ConstValue Fatal           = "fatal";
ConstValue Default         = "default";
} // namespace log_level

struct LoggingPrefs : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(LoggingPrefs)
	WEBDRIVERXX_PROPERTY(DriverLogLevel, "driver",  log_level::Value)
	WEBDRIVERXX_PROPERTY(ServerLogLevel, "server",  log_level::Value)
	WEBDRIVERXX_PROPERTY(BrowserLogLevel, "browser", log_level::Value)
	WEBDRIVERXX_PROPERTIES_END()
};

// List of keys and values indicating features that server can or should provide.
struct Capabilities : JsonObject { // copyable
	Capabilities() {}
	explicit Capabilities(const picojson::object& object) : JsonObject(object) {}

	// Hardcoded capabilities are here just to add some sugar.
	// If a capability is not listed below use Get/Set/Has public members.

	WEBDRIVERXX_PROPERTIES_BEGIN(Capabilities)
	// Used by the selenium server for browser selection
	WEBDRIVERXX_PROPERTY(BrowserName, "browserName", browser::Value)
	WEBDRIVERXX_PROPERTY(Version, "browserVersion", std::string)
	WEBDRIVERXX_PROPERTY(Platform, "platformName", platform::Value)
	
	// Read-only capabilities
	WEBDRIVERXX_PROPERTY_RONLY(HandlesAlerts, "handlesAlerts", bool)
	WEBDRIVERXX_PROPERTY_RONLY(CssSelectorsEnabled, "cssSelectorsEnabled", bool)

	// Read-write capabilities
	WEBDRIVERXX_PROPERTY(JavascriptEnabled, "javascriptEnabled", bool)
	WEBDRIVERXX_PROPERTY(DatabaseEnabled, "databaseEnabled", bool)
	WEBDRIVERXX_PROPERTY(LocationContextEnabled, "locationContextEnabled", bool)
	WEBDRIVERXX_PROPERTY(ApplicationCacheEnabled, "applicationCacheEnabled", bool)
	WEBDRIVERXX_PROPERTY(BrowserConnectionEnabled, "browserConnectionEnabled", bool)
	WEBDRIVERXX_PROPERTY(WebStorageEnabled, "webStorageEnabled", bool)
	WEBDRIVERXX_PROPERTY(AcceptSslCerts, "acceptSslCerts", bool)
	WEBDRIVERXX_PROPERTY(Rotatable, "rotatable", bool)
	WEBDRIVERXX_PROPERTY(NativeEvents, "nativeEvents", bool)
	WEBDRIVERXX_PROPERTY(Proxy, "proxy", Proxy)
	WEBDRIVERXX_PROPERTY(UnexpectedAlertBehaviour, "unexpectedAlertBehaviour", unexpected_alert_behaviour::Value)
	WEBDRIVERXX_PROPERTY(ElementScrollBehavior, "elementScrollBehavior", int)

	// RemoteWebDriver specific
	WEBDRIVERXX_PROPERTY(SessionId, "webdriver.remote.sessionid", std::string)
	WEBDRIVERXX_PROPERTY(QuietExceptions, "webdriver.remote.quietExceptions", bool)
	
	// Grid-specific
	WEBDRIVERXX_PROPERTY(Path, "path", std::string)
	WEBDRIVERXX_PROPERTY(SeleniumProtocol, "seleniumProtocol", std::string)
	WEBDRIVERXX_PROPERTY(MaxInstances, "maxInstances", int)
	WEBDRIVERXX_PROPERTY(Environment, "environment", std::string)

	// Firefox-specific
	WEBDRIVERXX_PROPERTY(AcceptInsecureCerts, "acceptInsecureCerts", bool)
	
	WEBDRIVERXX_PROPERTIES_END()
};

inline
void CustomFromJson(const picojson::value& value, Capabilities& result) {
	WEBDRIVERXX_CHECK(value.is<picojson::object>(), "Capabilities is not an object");
	result = Capabilities(value.get<picojson::object>());
}

} // namespace webdriverxx

#endif
