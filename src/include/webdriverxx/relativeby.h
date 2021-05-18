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
    WEBDRIVERXX_PROPERTY(Args,        "args",                  std::vector<Element>)
    WEBDRIVERXX_PROPERTIES_END()
};

class RelativeBy : public By { // copyable
public:
        /*
         * TODO: Construct no done
        RelativeBy(const JsonObject& root, std::vector<RelativeFilter> filters = {})
                : root_(root)
                , filters_(filters)
        {}
        */

        const RelativeBy& Above(const Element& elemlocator) {
                WEBDRIVERXX_ISEMPTY_THROW(elemlocator.GetRef(), "Element or locator must be given when calling above method");
                RelativeFilter filter;
                filter.SetKind("above")
                      .SetArgs({elemlocator});
                filters_.push_back(filter);
                return *this;
        }

private:
        std::string wrappedAtom_;
        JsonObject root_;
        std::vector<RelativeFilter> filters_;
};

} // namespace webdriverxx

#endif // RELATIVEBY_H
