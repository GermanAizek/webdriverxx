#ifndef WEBDRIVERXX_BROWSERS_SAFARI_H
#define WEBDRIVERXX_BROWSERS_SAFARI_H

#include "../capabilities.h"

namespace webdriverxx {
	
struct SafariOptions : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(SafariOptions)
	WEBDRIVERXX_PROPERTY(CleanSession,            "cleanSession",                   bool)
	WEBDRIVERXX_PROPERTIES_END()
};

struct Safari : Capabilities { // copyable
	Safari(const Capabilities& defaults = Capabilities())
		: Capabilities(defaults) {
		SetBrowserName(browser::Safari);
		SetVersion("");
		SetPlatform(platform::Any);
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(Safari)
	WEBDRIVERXX_PROPERTY(SafariOptions,           "safari.options",                 SafariOptions)
	WEBDRIVERXX_PROPERTY(AutomaticInspection,     "safari:automaticInspection",     bool)
	WEBDRIVERXX_PROPERTY(AutomaticProfiling,      "safari:automaticProfiling",      bool)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
