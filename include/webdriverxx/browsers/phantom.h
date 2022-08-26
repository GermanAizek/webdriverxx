#ifndef WEBDRIVERXX_BROWSERS_PHANTOM_H
#define WEBDRIVERXX_BROWSERS_PHANTOM_H

#include "../capabilities.h"

namespace webdriverxx {

struct PhantomJS : Capabilities { // copyable
    PhantomJS(const Capabilities& defaults = Capabilities())
		: Capabilities(defaults) {
		SetBrowserName(browser::PhantomJS);
		SetVersion("");
		SetPlatform(platform::Any);
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(PhantomJS)
	// Profile is a profile folder, zipped and base64 encoded.
	WEBDRIVERXX_PROPERTY(LoggingPrefs, "loggingPrefs", LoggingPrefs)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
