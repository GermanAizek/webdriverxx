#ifndef RELATIVEBY_H
#define RELATIVEBY_H

#include <string>
#include "types.h"
#include "conversions.h"
#include "element.h"

namespace webdriverxx {

struct RelativeFilter : JsonObject {
    WEBDRIVERXX_PROPERTIES_BEGIN(RelativeFilter)
    WEBDRIVERXX_PROPERTY(Kind,        "kind",                  std::string)
    WEBDRIVERXX_PROPERTY(Args,        "args",                  std::vector<Element>) // Element and int
    WEBDRIVERXX_PROPERTIES_END()
};

class RelativeBy : public By { // copyable
public:
	RelativeBy(const JsonObject& root, std::vector<RelativeFilter> filters = {})
		: root_(root)
		, filters_(filters)
		{}

        const RelativeBy& Above(const Element& elemlocator) {
                WEBDRIVERXX_ISEMPTY_THROW(elemlocator.GetRef(), "Element or locator must be given when calling above method");
                RelativeFilter filter;
                filter.SetKind("above")
                      .SetArgs({elemlocator});
                filters_.push_back(filter);
                return *this;
        }

        const RelativeBy& Below(const Element& elemlocator) {
                WEBDRIVERXX_ISEMPTY_THROW(elemlocator.GetRef(), "Element or locator must be given when calling above method");
                RelativeFilter filter;
                filter.SetKind("below")
                      .SetArgs({elemlocator});
                filters_.push_back(filter);
                return *this;
        }

        const RelativeBy& ToLeftOf(const Element& elemlocator) {
                WEBDRIVERXX_ISEMPTY_THROW(elemlocator.GetRef(), "Element or locator must be given when calling above method");
                RelativeFilter filter;
                filter.SetKind("left")
                      .SetArgs({elemlocator});
                filters_.push_back(filter);
                return *this;
        }

        const RelativeBy& ToRightOf(const Element& elemlocator) {
                WEBDRIVERXX_ISEMPTY_THROW(elemlocator.GetRef(), "Element or locator must be given when calling above method");
                RelativeFilter filter;
                filter.SetKind("right")
                      .SetArgs({elemlocator});
                filters_.push_back(filter);
                return *this;
        }

        // TODO:
        const RelativeBy& Near(int elemlocatorDistance) {
                //WEBDRIVERXX_ISEMPTY_THROW(elemlocatorDistance.GetRef(), "Element or locator or distance must be given when calling above method");
                RelativeFilter filter;
                filter.SetKind("near");
                      //.SetArgs({elemlocatorDistance});
                filters_.push_back(filter);
                return *this;
        }
private:
	std::string wrappedAtom_;
	JsonObject root_;
	std::vector<RelativeFilter> filters_;
};

void withTagName(const std::string& tagName) {
	WEBDRIVERXX_ISEMPTY_THROW(tagName, "tag_name can not be null");
	RelativeBy(JsonObject().Set("css selector", tagName));
}

} // namespace webdriverxx

#endif // RELATIVEBY_H
