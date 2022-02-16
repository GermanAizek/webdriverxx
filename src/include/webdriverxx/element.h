#ifndef WEBDRIVERXX_ELEMENT_H
#define WEBDRIVERXX_ELEMENT_H

#include "by.h"
#include "types.h"
#include "keys.h"
#include "detail/shared.h"
#include "detail/keyboard.h"
#include "detail/resource.h"
#include "detail/factories.h"
#include <string>
#include <vector>

namespace webdriverxx {

// An element from DOM
class Element { // copyable
private:
	bool w3c;
	detail::Resource& GetResource() const;
	detail::Keyboard GetKeyboard() const;

	std::string ref_;
	detail::Shared<detail::Resource> resource_;
	detail::Shared<detail::IFinderFactory> factory_;
public:
	Element();
	
	Element(
		const std::string& ref,
		const detail::Shared<detail::Resource>& resource,
		const detail::Shared<detail::IFinderFactory>& factory
		);

	std::string GetRef() const; // Returns ID that is used by Webdriver to identify elements

	bool IsDisplayed() const;
	bool IsEnabled() const;
	bool IsSelected() const;
	Point GetLocation() const;
	Point GetLocationInView() const;
	Size GetSize() const;
	Rect GetRect() const;
	std::string GetAttribute(const std::string& name) const;
	std::string GetCssProperty(const std::string& name) const;
	std::string GetAriaRole() const;
	std::string GetAriaLabel() const;
	std::string GetTagName() const;
	std::string GetText() const;

	Element FindElement(const By& by) const;
	std::vector<Element> FindElements(const By& by) const;

	const Element& Clear() const;
	const Element& Click() const;
	const Element& Submit() const;

	const Element& SendKeys(const std::string& keys) const;
	const Element& SendKeys(const Shortcut& shortcut) const;
	const Element& KeyDown(const std::string& keys) const;
	const Element& KeyUp(const std::string& keys) const;
	const Element& SendInput(const std::string& input) const;

	bool Equals(const Element& other) const;
	bool operator != (const Element& other) const;
	bool operator == (const Element& other) const;
	bool operator < (const Element& other) const;
};

} // namespace webdriverxx

#include "element.inl"

#endif
