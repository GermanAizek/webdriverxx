#ifndef WEBDRIVERXX_BROWSERS_OPERA_H
#define WEBDRIVERXX_BROWSERS_OPERA_H

#include "../capabilities.h"

namespace webdriverxx {

struct Opera : Capabilities { // copyable
	Opera(const Capabilities& defaults = Capabilities())
		: Capabilities(defaults) {
		SetBrowserName(browser::Opera);
		SetVersion("");
		SetPlatform(platform::Any);
	}

	WEBDRIVERXX_PROPERTIES_BEGIN(Opera)
	// Profile is a profile folder, zipped and base64 encoded.
	// TODO: add OperaProfile
	WEBDRIVERXX_PROPERTIES_END()
};

} // namespace webdriverxx

#endif
