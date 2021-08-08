#include "conversions.h"
#include "detail/error_handling.h"
#include "detail/types.h"

#if CXX17_2X
#include <filesystem>
#endif

namespace webdriverxx {

inline
Session::Session(const detail::Shared<detail::Resource>& resource)
	: resource_(resource)
	, factory_(new detail::SessionFactory(resource))
{}

inline
void Session::DeleteSession() const {
	resource_->Delete();
}

inline
Capabilities Session::GetCapabilities() const {
	return Capabilities(resource_->Get().get<picojson::object>());
}

inline
std::string Session::GetPageSource() const {
	return resource_->GetString("source");
}

inline
std::string Session::GetTitle() const {
	return resource_->GetString("title");
}

inline
std::string Session::GetUrl() const {
	return resource_->GetString("url");
}

inline
std::string Session::GetScreenshot() const {
	return resource_->GetString("screenshot");
}

inline
int Session::GetScreenshotAsFile(const std::string& filename) const {
	std::string name = filename;
	if (filename.find(".png") == std::string::npos) {
		name += ".png";
	}
	std::ofstream out(name, std::ios::binary);
	if (!out) return 1;
	out << b64decode(resource_->GetString("screenshot"));
	out.close();
	return 0;
}

// BUG: maybe GetRef() to str
inline
std::string Session::GetElementScreenshot(const Element& element) const {
	return resource_->GetString("element/" + element.GetRef() + "/screenshot");
}

inline
JsonObject Session::GetTimeoutMs() const {
	return resource_->GetValue<JsonObject>("timeouts");
}

inline
const Session& Session::SetTimeoutMs(timeout::Type type, int milliseconds) {
	resource_->Post("timeouts",
		JsonObject()
			.Set("type", type)
			.Set("ms", milliseconds)
		);
	return *this;
}

inline
const Session& Session::SetImplicitTimeoutMs(int milliseconds) {
	resource_->Post("timeouts/implicit_wait",
		JsonObject().Set("ms", milliseconds));
	return *this;
}

inline
const Session& Session::SetAsyncScriptTimeoutMs(int milliseconds) {
	resource_->Post("timeouts/async_script",
		JsonObject().Set("ms", milliseconds));
	return *this;
}

inline
Window Session::GetCurrentWindow() const {
	WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
	return MakeWindow(resource_->GetString("window_handle"));
	WEBDRIVERXX_FUNCTION_CONTEXT_END()
}

inline
const Session& Session::CloseCurrentWindow() const {
	resource_->Delete("window");
	return *this;
}

inline
const Session& Session::Navigate(const std::string& url) const {
	resource_->Post("url", "url", url);
	return *this;
}

inline
const Session& Session::Get(const std::string& url) const {
	return Navigate(url);
}

inline
const Session& Session::Forward() const {
	resource_->Post("forward");
	return *this;
}

inline
const Session& Session::Back() const {
	resource_->Post("back");
	return *this;
}

inline
const Session& Session::Refresh() const {
	resource_->Post("refresh");
	return *this;
}

inline
const Session& Session::Execute(const std::string& script, const JsArgs& args) const {
	InternalEvalJsonValue("execute", script, args);
	return *this;
}

template<typename T>
T Session::Eval(const std::string& script, const JsArgs& args) const {
	WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
	T result = T();
	InternalEval("execute", script, args, result);
	return result;
	WEBDRIVERXX_FUNCTION_CONTEXT_END_EX(detail::Fmt()
		<< "script: " << script
		)
}

inline
const Session& Session::ExecuteAsync(const std::string& script, const JsArgs& args) const {
	InternalEvalJsonValue("execute_async", script, args);
	return *this;
}

template<typename T>
T Session::EvalAsync(const std::string& script, const JsArgs& args) const {
	WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
	T result;
	InternalEval("execute_async", script, args, result);
	return result;
	WEBDRIVERXX_FUNCTION_CONTEXT_END_EX(detail::Fmt()
		<< "script: " << script
		)
}

inline
const Session& Session::SetFocusToWindow(const std::string& window_name_or_handle) const {
	resource_->Post("window", "name", window_name_or_handle);
	return *this;
}

inline
const Session& Session::SetFocusToWindow(const Window& window) const {
	SetFocusToWindow(window.GetHandle());
	return *this;
}

inline
const Session& Session::SetFocusToFrame(const Element& frame) const {
	return InternalSetFocusToFrame(ToJson(frame));
}

inline
const Session& Session::SetFocusToFrame(const std::string& id) const {
	return InternalSetFocusToFrame(ToJson(id));
}

inline
const Session& Session::SetFocusToFrame(int number) const {
	return InternalSetFocusToFrame(ToJson(number));
}

inline
const Session& Session::SetFocusToDefaultFrame() const {
	return InternalSetFocusToFrame(picojson::value());
}

inline
const Session& Session::SetFocusToParentFrame() const {
	resource_->Post("frame/parent");
	return *this;
}

inline
const Session& Session::InternalSetFocusToFrame(const picojson::value& id) const {
	resource_->Post("frame", JsonObject().Set("id", id));
	return *this;
}

inline
std::vector<Window> Session::GetWindows() const {
	WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
	const auto handles =
		FromJson<std::vector<std::string>>(
			resource_->Get("window_handles") // in W3C Get("window/handles")
			);

	std::vector<Window> result;
	result.reserve(handles.size());
	std::transform(handles.begin(), handles.end(), std::back_inserter(result),
		[this](const std::string& window_handle){
			return MakeWindow(window_handle);
		});
	return result;
	WEBDRIVERXX_FUNCTION_CONTEXT_END()
}

inline
Element Session::GetActiveElement() const {
	WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
	return factory_->MakeElement(FromJson<detail::ElementRef>(resource_->Post("element/active")).ref);
	WEBDRIVERXX_FUNCTION_CONTEXT_END()
}

inline
Element Session::FindElement(const By& by) const {
	return factory_->MakeFinder(resource_).FindElement(by);
}

inline
std::vector<Element> Session::FindElements(const By& by) const {
	return factory_->MakeFinder(resource_).FindElements(by);
}

inline
std::vector<Cookie> Session::GetCookies() const {
	WEBDRIVERXX_FUNCTION_CONTEXT_BEGIN()
	return FromJson<std::vector<Cookie>>(resource_->Get("cookie"));
	WEBDRIVERXX_FUNCTION_CONTEXT_END()
}

inline
const Session& Session::SetCookie(const Cookie& cookie) const {
	WEBDRIVERXX_ISEMPTY_THROW(cookie.name, "Cookie name cannot be null or empty string");
	WEBDRIVERXX_ISEMPTY_THROW(cookie.value, "Cookie value cannot be null");

	if (cookie.name.find(';') != std::string::npos) {
		WEBDRIVERXX_THROW(std::string("Cookie names cannot contain a ';': ") + cookie.name);
	}

	resource_->Post("cookie", JsonObject()
		.Set("cookie", ToJson(cookie)));
	return *this;
}

inline
const Session& Session::DeleteCookies() const {
	resource_->Delete("cookie");
	return *this;
}

inline
const Session& Session::DeleteCookie(const std::string& name) const {
	resource_->Delete(std::string("cookie/") + name);
	return *this;
}

inline
std::string Session::GetAlertText() const {
	return resource_->GetString("alert_text");
}

inline
const Session& Session::SendKeysToAlert(const std::string& text) const {
	resource_->Post("alert_text", "text", text);
	return *this;
}

inline
const Session& Session::AcceptAlert() const {
	resource_->Post("accept_alert");
	return *this;
}

inline
const Session& Session::DismissAlert() const {
	resource_->Post("dismiss_alert");
	return *this;
}

inline
const Session& Session::SendKeys(const std::string& keys) const {
	GetKeyboard().SendKeys(keys);
	return *this;
}

inline
const Session& Session::SendKeys(const Shortcut& shortcut) const {
	GetKeyboard().SendKeys(shortcut);
	return *this;
}

inline
const Session& Session::MoveToTopLeftOf(const Element& element, const Offset& offset) const {
	return InternalMoveTo(&element, &offset);
}

inline
const Session& Session::MoveToCenterOf(const Element& element) const {
	return InternalMoveTo(&element, nullptr);
}

inline
const Session& Session::MoveTo(const Offset& offset) const {
	return InternalMoveTo(nullptr, &offset);
}

inline
const Session& Session::InternalMoveTo(
	const Element* element,
	const Offset* offset
	) const {
	JsonObject args;
	if (element)
		args.Set("element", element->GetRef());
	if (offset) {
		args.Set("xoffset", offset->x);
		args.Set("yoffset", offset->y);
	}
	resource_->Post("moveto", args);
	return *this;
}

inline
const Session& Session::Click(mouse::Button button) const {
	return InternalMouseButtonCommand("click", button);
}

inline
const Session& Session::DoubleClick() const {
	resource_->Post("doubleclick");
	return *this;
}

inline
const Session& Session::ButtonDown(mouse::Button button) const {
	return InternalMouseButtonCommand("buttondown", button);
}

inline
const Session& Session::ButtonUp(mouse::Button button) const {
	return InternalMouseButtonCommand("buttonup", button);
}

inline
std::string Session::GetOrientation() const {
	return resource_->GetString("orientation");
}

inline
const Session& Session::SetOrientation(int value) const {
	const std::array<const char*, 2> allowed = {"LANDSCAPE", "PORTRAIT"};
	switch (value) {
	case 0:
	case 1:
		resource_->Post("orientation", "orientation", allowed[value]);
		break;
	default:
		throw WebDriverException("You can only set the orientation to 'LANDSCAPE' and 'PORTRAIT'");
		break;
	}
}

inline
const Session& Session::InternalMouseButtonCommand(const char* command, mouse::Button button) const {
	resource_->Post(command, "button", static_cast<int>(button));
	return *this;
}

inline
Window Session::MakeWindow(const std::string& handle) const {
	return Window(handle,
		detail::MakeSubResource(resource_, "window", handle)
		);
}

inline
detail::Keyboard Session::GetKeyboard() const
{
	return detail::Keyboard(resource_, "keys");
}

template<typename T>
void Session::InternalEval(const std::string& webdriver_command,
	const std::string& script, const JsArgs& args,
	T& result) const {
	result = FromJson<T>(InternalEvalJsonValue(webdriver_command, script, args));
}

inline
void Session::InternalEval(const std::string& webdriver_command,
	const std::string& script, const JsArgs& args,
	Element& result) const {
	detail::ElementRef element_ref;
	InternalEval(webdriver_command, script, args, element_ref);
	result = factory_->MakeElement(element_ref.ref);
}

inline
picojson::value Session::InternalEvalJsonValue(
	const std::string& webdriver_command,
	const std::string& script,
	const JsArgs& args
	) const {
	return resource_->Post(webdriver_command,
		JsonObject()
			.Set("script", script)
			.Set("args", args.args_)
		);
}

inline
picojson::value Session::PrintPage(
	const std::string& orientation,
	float scale,
	bool background,
	float page_width,
	float page_height,
	bool shrink_to_fit,
	std::vector<std::string> page_ranges,
	float margin_top,
	float margin_left,
	float margin_bottom,
	float margin_right
	) const {
	auto page = JsonObject()
			.Set("width", page_width)
			.Set("height", page_height);
	
	auto margin = JsonObject()
			.Set("top", margin_top)
			.Set("left", margin_left)
			.Set("bottom", margin_bottom)
			.Set("right", margin_right);
			
	return resource_->Post("print",
		JsonObject()
			.Set("orientation", orientation)
			.Set("scale", scale)
			.Set("background", background)
			.Set("page", page)
			.Set("margin", margin)
			.Set("shrinkToFit", shrink_to_fit)
			.Set("pageRanges", page_ranges)
		);
}

std::string char_to_string(char x[], int size_recv)
{
	int num_car = 0;
	int stop_while = size_recv;
	std::string output = "";

	while (stop_while > 0)
	{
		output += x[num_car];
		if (num_car < size_recv) { num_car++; }

		stop_while--;
	}

	return output;
}

// TODO: Make session install addon
inline
const Session& Session::InstallAddonFromFile(const std::string& path) const {
	if (path.empty()) {
		throw WebDriverException("Add-on file name must not be null or the empty string");
	}

#if CXX17_2X
	if (!std::filesystem::exists(path)) {
		throw WebDriverException("File " + path + " does not exist");
	}
#else
	std::ifstream exists(path);
	if (!exists.good()) {
		throw WebDriverException("File " + path + " does not exist");
	}
#endif

	//if (IsFirefox()) { // BUG: this is crashed
	FILE* file_input;
#if _MSC_VER
	fopen_s(&file_input, path.c_str(), "ab+");
#else
	file_input = fopen(path.c_str(), "ab+");
#endif
	char buff_read[1];
	if (file_input != NULL) {
		std::string b64data = "";
		while (fread(buff_read, sizeof(buff_read), 1, file_input)) {
			b64data += (buff_read, sizeof(buff_read));
			memset(buff_read, 0, sizeof(buff_read));
		}
		//std::cout << b64encode(b64data) << std::endl << std::endl;
		InstallAddon(b64data); // BUG: unknown freeze
		fclose(file_input);
	}
	return *this;
	//}
}

inline
const Session& Session::InstallAddon(const std::string& b64addon) const {
	if (b64addon.empty()) {
		throw WebDriverException("Base64 encoded add-on must not be null or the empty string");
	}
	resource_->Post("moz/addon/install", "addon", b64encode(b64addon));
	return *this;
}

inline
const Session& Session::UninstallAddon(const std::string& id) const {
	if (id.empty()) {
		throw WebDriverException("Base64 encoded add-on must not be null or the empty string");
	}
	resource_->Post("moz/addon/uninstall", "id", id);
	return *this;
}

inline
std::string Session::GetFullPageScreenshot() const {
	return b64decode(resource_->GetString("moz/screenshot/full"));
}

inline
const Session& Session::GetLog() const {
	resource_->Post("log");
	return *this;
}

} // namespace webdriverxx
