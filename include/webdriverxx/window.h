#ifndef WEBDRIVERXX_WINDOW_H
#define WEBDRIVERXX_WINDOW_H

#include "types.h"
#include "conversions.h"
#include "detail/resource.h"
#include <string>

namespace webdriverxx {

class Window { // copyable
public:
	Window(const std::string& handle, const detail::Shared<detail::Resource>& resource)
		: handle_(handle)
		, resource_(resource)
	{}

	~Window() {
		delete this;
	}

	inline
	void close() const {
		this->~Window();
	}

	inline
	std::string GetHandle() const {
		return handle_;
	}

	inline
	Size GetSize() const {
		return resource_->GetValue<Size>("size");
	}

	inline
	const Window& SetSize(const Size& size) const {
		resource_->PostValue("size", size);
		return *this;
	}

	inline
	Rect GetRect() const {
		return resource_->GetValue<Rect>("rect");
	}

	inline
	const Window& SetRect(const Rect& rect) const {
		resource_->PostValue("rect", JsonObject()
							 //.Set("rect", ToJson(rect)));
							 .Set("x", rect.x)
							 .Set("y", rect.y)
							 .Set("width", rect.width)
							 .Set("height", rect.height));
		return *this;
	}

	inline
	Point GetPosition() const {
		return resource_->GetValue<Point>("position");
	}

	inline
	const Window& SetPosition(const Point& position) const {
		resource_->PostValue("position", position);
		return *this;
	}

	inline
	const Window& Maximize() const {
		resource_->Post("maximize");
		return *this;
	}

	inline
	const Window& Minimize() const {
		resource_->Post("minimize");
		return *this;
	}

	inline
	const Window& Fullscreen() const {
		resource_->Post("fullscreen");
		return *this;
	}

private:
	std::string handle_;
	detail::Shared<detail::Resource> resource_;
};

} // namespace webdriverxx

#endif
