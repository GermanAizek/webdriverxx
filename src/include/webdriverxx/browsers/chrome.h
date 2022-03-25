#ifndef WEBDRIVERXX_BROWSERS_CHROME_H
#define WEBDRIVERXX_BROWSERS_CHROME_H

#include "../capabilities.h"
#include <unordered_set>

namespace webdriverxx {
namespace chrome {
namespace device {
	std::unordered_set<std::string> deviceList {
		"BlackBerry Z30",
		"Blackberry PlayBook",
		"Galaxy Note 3",
		"Galaxy Note II",
		"Galaxy S III",
		"Kindle Fire HDX",
		"LG Optimus L70",
		"Laptop with HiDPI screen",
		"Laptop with MDPI screen",
		"Laptop with touch",
		"Microsoft Lumia 550",
		"Microsoft Lumia 950",
		"Moto G4",
		"Nexus 10",
		"Nexus 4",
		"Nexus 5",
		"Nexus 5X",
		"Nexus 6",
		"Nexus 6P",
		"Nexus 7",
		"Nokia Lumia 520",
		"Nokia N9",
		"iPad Mini",
		"iPhone 4",
		"JioPhone 2",
		"Galaxy S5",
		"Pixel 2",
		"Pixel 2 XL",
		"iPhone 5/SE",
		"iPhone 6/7/8",
		"iPhone 6/7/8 Plus",
		"iPhone X",
		"iPad",
		"iPad Pro",
		"Surface Duo",
		"Galaxy Fold"
	};

	std::string Get(const std::string& name) {
		auto pos = deviceList.find(name);
		if (pos != deviceList.end())
			return *pos;
		else
			return std::string();
	}
	
	struct deviceMetrics : JsonObject {
		WEBDRIVERXX_PROPERTIES_BEGIN(deviceMetrics)
		WEBDRIVERXX_PROPERTY(width,      "width",      int)
		WEBDRIVERXX_PROPERTY(height,     "height",     int)
		WEBDRIVERXX_PROPERTY(pixelRatio, "pixelRatio", float)
		WEBDRIVERXX_PROPERTY(touch,      "touch",      bool)
		WEBDRIVERXX_PROPERTIES_END()
	};
}

struct MobileEmulation : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(MobileEmulation)
	WEBDRIVERXX_PROPERTY(deviceName,    "deviceName",    std::string)
	WEBDRIVERXX_PROPERTY(userAgent,     "userAgent",     std::string)
	WEBDRIVERXX_PROPERTY(deviceMetrics, "deviceMetrics", device::deviceMetrics)
	WEBDRIVERXX_PROPERTIES_END()
};

struct PerfLoggingPrefs : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(PerfLoggingPrefs)
	WEBDRIVERXX_PROPERTY(EnableNetwork,                "enableNetwork",                bool)
	WEBDRIVERXX_PROPERTY(EnablePage,                   "enablePage",                   bool)
	WEBDRIVERXX_PROPERTY(EnableTimeline,               "enableTimeline",               bool)
	WEBDRIVERXX_PROPERTY(TraceCategories,              "traceCategories",              std::string)
	WEBDRIVERXX_PROPERTY(BufferUsageReportingInterval, "bufferUsageReportingInterval", int)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace chrome

struct ChromeOptions : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(ChromeOptions)
	WEBDRIVERXX_PROPERTY(Args,                      "args",             std::vector<std::string>)
	WEBDRIVERXX_PROPERTY(Binary,                    "binary",           std::string)
	// Each extension is a base64-encoded .crx file
	WEBDRIVERXX_PROPERTY(Extensions,                "extensions",       std::vector<std::string>)
	WEBDRIVERXX_PROPERTY(LocalState,                "localState",       JsonObject)
	WEBDRIVERXX_PROPERTY(Prefs,                     "prefs",            JsonObject)
	WEBDRIVERXX_PROPERTY(Detach,                    "detach",           bool)
	WEBDRIVERXX_PROPERTY(DebuggerAddress,           "debuggerAddress",  std::string)
	WEBDRIVERXX_PROPERTY(ExcludeSwitches,           "excludeSwitches",  std::vector<std::string>)
	WEBDRIVERXX_PROPERTY(MinidumpPath,              "minidumpPath",     std::string)
	WEBDRIVERXX_PROPERTY(MobileEmulation,           "mobileEmulation",  chrome::MobileEmulation)
	WEBDRIVERXX_PROPERTY(WindowTypes,               "windowTypes",      std::vector<std::string>)
	WEBDRIVERXX_PROPERTY(SpecCompliantProtocol,     "w3c",              bool)

	// Read-only capabilities
	WEBDRIVERXX_PROPERTY_RONLY(ChromeDriverVersion, "chrome.chromedriverVersion", std::string)
	WEBDRIVERXX_PROPERTY_RONLY(UserDataDir,         "userDataDir",                std::string)

	WEBDRIVERXX_PROPERTY(LoggingPrefs,              "loggingPrefs",     LoggingPrefs)
	WEBDRIVERXX_PROPERTIES_END()
};

struct Chrome : Capabilities { // copyable
	Chrome(const Capabilities& defaults = Capabilities())
		: Capabilities(defaults) {
		SetBrowserName(browser::Chrome);
		SetVersion(defaults.GetVersion());   // 加上这句就可以，BrowserName不能为空
		SetPlatform(platform::Any);
	}

	// See https://sites.google.com/a/chromium.org/chromedriver/capabilities for details
	WEBDRIVERXX_PROPERTIES_BEGIN(Chrome)
	WEBDRIVERXX_PROPERTY(ChromeOptions,             "goog:chromeOptions",                  ChromeOptions)
	WEBDRIVERXX_PROPERTY(PerfLoggingPrefs,          "goog:perfLoggingPrefs",               chrome::PerfLoggingPrefs)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
