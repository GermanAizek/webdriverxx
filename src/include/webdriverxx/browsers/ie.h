#ifndef WEBDRIVERXX_BROWSERS_IE_H
#define WEBDRIVERXX_BROWSERS_IE_H

#include "../capabilities.h"

namespace webdriverxx {
namespace ie {

enum ElementScrollBehavior
{
	Default,
	Top,
	Bottom
};

} // namespace ie

struct IEOptions : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(IEOptions)
	WEBDRIVERXX_PROPERTY(SkipProtectedModeCheck,    "ignoreProtectedModeSettings",   bool)
	WEBDRIVERXX_PROPERTY(IgnoreZoomSetting,         "ignoreZoomSetting",             bool)
	WEBDRIVERXX_PROPERTY(InitialUrl,                "initialBrowserUrl",             std::string)
	WEBDRIVERXX_PROPERTY(EnablePersistentHover,     "enablePersistentHover",         bool)
	//WEBDRIVERXX_PROPERTY(EnableElementCacheCleanup, "enableElementCacheCleanup",     bool)
	// syntax error
	//WEBDRIVERXX_PROPERTY(ЕlementScrollBehavior,     "elementScrollBehavior",         ie::ElementScrollBehavior)
	WEBDRIVERXX_PROPERTY(RequireWindowFocus,        "requireWindowFocus",            bool)
	WEBDRIVERXX_PROPERTY(BrowserAttachTimeoutMs,    "browserAttachTimeout",          int)
	WEBDRIVERXX_PROPERTY(ForceCreateProcessApi,     "ie.forceCreateProcessApi",      bool)
	WEBDRIVERXX_PROPERTY(CommandLineSwitches,       "ie.browserCommandLineSwitches", std::string)
	WEBDRIVERXX_PROPERTY(UsePerProcessProxy,        "ie.usePerProcessProxy",         bool)
	WEBDRIVERXX_PROPERTY(EnsureCleanSession,        "ie.ensureCleanSession",         bool)
	WEBDRIVERXX_PROPERTY(ForceShellWindowsApi,      "ie.forceShellWindowsApi",       bool)
	WEBDRIVERXX_PROPERTY(FileUploadDialogTimeout,   "ie.fileUploadDialogTimeout",    bool)
	WEBDRIVERXX_PROPERTY(EnableFullPageScreenshot,  "ie.enableFullPageScreenshot",   bool)
	/*
	WEBDRIVERXX_PROPERTY(LogFile,                   "logFile",                       std::string)
	WEBDRIVERXX_PROPERTY(LogLevel,                  "logLevel",                      log_level::Value)
	WEBDRIVERXX_PROPERTY(Host,                      "host",                          std::string)
	WEBDRIVERXX_PROPERTY(ExtractPath,               "extractPath",                   std::string)
	WEBDRIVERXX_PROPERTY(Silent,                    "silent",                        bool)
	WEBDRIVERXX_PROPERTY(ProxyByServer,             "ie.setProxyByServer",           bool)
	*/
	WEBDRIVERXX_PROPERTIES_END()
};

struct InternetExplorer : Capabilities { // copyable
	InternetExplorer(const Capabilities& defaults = Capabilities())
		: Capabilities(defaults) {
		SetBrowserName(browser::InternetExplorer);
		SetVersion("");
		SetPlatform(platform::Any);
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(InternetExplorer)
	WEBDRIVERXX_PROPERTY(IEOptions,             "se:ieOptions",                  IEOptions)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
