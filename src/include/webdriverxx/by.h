#ifndef WEBDRIVERXX_BY_H
#define WEBDRIVERXX_BY_H

#include <string>
#include "types.h"

namespace webdriverxx {

class By { // copyable
public:
	By(const std::string& strategy, const std::string& value)
		: strategy_(strategy)
		, value_(value)
	{}

	inline
	const std::string& GetStrategy() const {
		return strategy_;
	}

	inline
	const std::string& GetValue() const {
		return value_;
	}

private:
	std::string strategy_;
	std::string value_;
};

inline
By ByCss(const std::string& value) {
	WEBDRIVERXX_ISEMPTY_THROW(value, "Cannot find elements when name CSS selector is null.");
	return By("css selector", value);
}

inline
By ByClass(const std::string& value) {
	WEBDRIVERXX_ISEMPTY_THROW(value, "Cannot find elements when the class name expression is null.");
	std::string selector = '.' + value;
	return ByCss(selector);
}

inline
By ById(const std::string& value) {
	WEBDRIVERXX_ISEMPTY_THROW(value, "Cannot find elements with a null id attribute.");
	std::string selector = "*[id=\"" + value + "\"]";
	return ByCss(selector);
}

inline
By ByName(const std::string& value) {
	WEBDRIVERXX_ISEMPTY_THROW(value, "Cannot find elements when name text is null.");
	std::string selector = "*[name=\"" + value + "\"]";
	return ByCss(selector);
}

inline
By ByLinkText(const std::string& value) {
	WEBDRIVERXX_ISEMPTY_THROW(value, "Cannot find elements when link text is null.");
	return By("link text", value);
}

inline
By ByPartialLinkText(const std::string& value) {
	WEBDRIVERXX_ISEMPTY_THROW(value, "Cannot find elements when partial link text is null.");
	return By("partial link text", value);
}

inline
By ByTag(const std::string& value) {
	WEBDRIVERXX_ISEMPTY_THROW(value, "Cannot find elements when name tag name is null.");
	return ByCss(value);
}

inline
By ByXPath(const std::string& value) {
	WEBDRIVERXX_ISEMPTY_THROW(value, "Cannot find elements when the XPath expression is null.");
	return By("xpath", value);
}

} // namespace webdriverxx

#endif
