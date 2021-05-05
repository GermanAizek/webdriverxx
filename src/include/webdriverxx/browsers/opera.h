#ifndef WEBDRIVERXX_BROWSERS_OPERA_H
#define WEBDRIVERXX_BROWSERS_OPERA_H

#include "../capabilities.h"

namespace webdriverxx {


struct OperaOptions : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(OperaOptions)
	WEBDRIVERXX_PROPERTY(Args,                      "args",             std::vector<std::string>)
	WEBDRIVERXX_PROPERTY(Binary,                    "binary",           std::string)
	WEBDRIVERXX_PROPERTY(Extensions,                "extensions",       std::vector<std::string>)
	WEBDRIVERXX_PROPERTY(LocalState,                "localState",       JsonObject)
	WEBDRIVERXX_PROPERTY(Prefs,                     "prefs",            JsonObject)
	WEBDRIVERXX_PROPERTY(Detach,                    "detach",           bool)
	WEBDRIVERXX_PROPERTY(DebuggerAddress,           "debuggerAddress",  std::string)
	WEBDRIVERXX_PROPERTY(ExcludeSwitches,           "excludeSwitches",  std::vector<std::string>)
	WEBDRIVERXX_PROPERTY(MinidumpPath,              "minidumpPath",     std::string)
	WEBDRIVERXX_PROPERTIES_END()
};

struct Opera : Capabilities { // copyable
	Opera(const Capabilities& defaults = Capabilities())
		: Capabilities(defaults) {
		SetBrowserName(browser::Opera);
		SetVersion("");
		SetPlatform(platform::Any);
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(Opera)
	WEBDRIVERXX_PROPERTY(OperaOptions,         "ms:edgeOptions",                               OperaOptions)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
