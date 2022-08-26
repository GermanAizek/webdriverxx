#ifndef WEBDRIVERXX_BROWSERS_PHANTOM_H
#define WEBDRIVERXX_BROWSERS_PHANTOM_H

#include "../capabilities.h"

namespace webdriverxx {

struct EdgeOptions : JsonObject {
        WEBDRIVERXX_PROPERTIES_BEGIN(EdgeOptions)
        WEBDRIVERXX_PROPERTY(EdgeChromium,        "ms:edgeChromium",                              bool)
        WEBDRIVERXX_PROPERTIES_END()
};

struct Edge : Capabilities { // copyable
    Edge(const Capabilities& defaults = Capabilities())
		: Capabilities(defaults) {
                SetBrowserName(browser::Edge);
		SetVersion("");
		SetPlatform(platform::Any);
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(Edge)
	WEBDRIVERXX_PROPERTY(EdgeOptions,         "ms:edgeOptions",                               EdgeOptions)
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
