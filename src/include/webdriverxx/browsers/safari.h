#ifndef WEBDRIVERXX_BROWSERS_SAFARI_H
#define WEBDRIVERXX_BROWSERS_SAFARI_H

#include "../capabilities.h"

namespace webdriverxx {
	
struct SafariOptions : JsonObject {
	WEBDRIVERXX_PROPERTIES_BEGIN(SafariOptions)
	WEBDRIVERXX_PROPERTY(CleanSession, "cleanSession", bool)
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
	WEBDRIVERXX_PROPERTY(SafariOptions, "safari.options", SafariOptions)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
