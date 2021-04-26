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

	const std::string& GetStrategy() const {
		return strategy_;
	}

	const std::string& GetValue() const {
		return value_;
	}

private:
	std::string strategy_;
	std::string value_;
};

inline By ByCss(const std::string& value) {
	return By("css selector", value);
}

inline By ByClass(const std::string& value) {
	std::string selector = '.' + value;
	return ByCss(selector);
}

inline By ById(const std::string& value) {
	std::string selector = "*[id=\"" + value + "\"]";
	return ByCss(selector);
}

inline By ByName(const std::string& value) {
	std::string selector = "*[name=\"" + value + "\"]";
	return ByCss(selector);
}

inline By ByLinkText(const std::string& value) {
	return By("link text", value);
}

inline By ByPartialLinkText(const std::string& value) {
	return By("partial link text", value);
}

inline By ByTag(const std::string& value) {
	return ByCss(value);
}

inline By ByXPath(const std::string& value) {
	return By("xpath", value);
}

} // namespace webdriverxx

#endif
