#ifndef WEBDRIVERXX_RESPONSE_STATUS_CODE_H
#define WEBDRIVERXX_RESPONSE_STATUS_CODE_H

namespace webdriverxx {
namespace response_status_code {

enum Value {
	kSuccess = 0,
	kNoSuchDriver = 6,
	kNoSuchElement = 7,
	kNoSuchFrame = 8,
	kUnknownCommand = 9,
	kStaleElementReference = 10,
	kElementNotVisible = 11,
	kInvalidElementState = 12,
	kUnknownError = 13,
	kElementIsNotSelectable = 15,
	kJavaScriptError = 17,
	kXPathLookupError = 19,
	kTimeout = 21,
	kNoSuchWindow = 23,
	kInvalidCookieDomain = 24,
	kUnableToSetCookie = 25,
	kUnexpectedAlertOpen = 26,
	kNoAlertOpenError = 27,
	kScriptTimeout = 28,
	kInvalidElementCoordinates = 29,
	kIMENotAvailable = 30,
	kIMEEngineActivationFailed = 31,
	kInvalidSelector = 32,
	kSessionNotCreatedException = 33,
	kMoveTargetOutOfBounds = 34,
	kInvalidXPathSelector = 51,
	kInvalidXPathSelectorReturnTyper = 52,
	kElementNotInteractable = 60,
	kInsecureCertificate,
	kInvalidArgument = 61,
	kInvalidCoordinates = Value::kInvalidElementCoordinates,
	kInvalidSessionId = Value::kNoSuchDriver,
	kNoSuchCookie = 62,
	kUnableToCaptureScreen = 63,
	kElementClickIntercepted = 64,
	kUnknownMethod = Value::kUnknownCommand,
	kMethodNotAllowed = 405
};

const char* ToString(Value code) {
	switch(code) {
	case kSuccess:
		return "";
	case kNoSuchElement:
		return "\
Thrown when element could not be found.\n\
If you encounter this exception, you may want to check the following:\n\
	* Check your selector used in your driver.FindElement(By...(...))\n\
	* Element may not yet be on the screen at the time of the find operation,\n\
	  (webpage is still loading) see WaitForValue(...)\n\
	  for how to write a wait wrapper to wait for an element to appear.\
	";
	case kNoSuchFrame:
		return "Thrown when frame target to be switched doesn't exist.";
	case kUnknownCommand:
		return "The requested resource could not be found, or a request was received using an HTTP method that is not supported by the mapped resource.";
	case kStaleElementReference:
		return "\
Thrown when a reference to an element is now \"stale\".\n\n\
Stale means the element no longer appears on the DOM of the page.\n\n\n\
Possible causes of StaleElementReferenceException include, but not limited to:\n\
	* You are no longer on the same page, or the page may have refreshed since the element\n\
	  was located.\n\
	* The element may have been removed and re-added to the screen, since it was located.\n\
	  Such as an element being relocated.\n\
	  This can happen typically with a javascript framework when values are updated and the\n\
	  node is rebuilt.\n\
	* Element may have been inside an iframe or another context which was refreshed.\
	";
	case kElementNotVisible:
		return "\
Thrown when an element is present on the DOM, but\n\
it is not visible, and so is not able to be interacted with.\n\n\
Most commonly encountered when trying to click or read text\n\
of an element that is hidden from view.\
	";
	case kInvalidElementState:
		return "\
Thrown when a command could not be completed because the element is in an invalid state.\n\n\
This can be caused by attempting to clear an element that isn't both editable and resettable.\
		";
	case kUnknownError:
		return "An unknown server-side error occurred while processing the command.";
	case kElementIsNotSelectable:
		return "\
Thrown when trying to select an unselectable element.\n\n\
For example, selecting a 'script' element.\
		";
	case kJavaScriptError:
		return "An error occurred while executing JavaScript supplied by the user.";
	case kXPathLookupError:
		return "An error occurred while searching for an element by XPath.";
	case kTimeout:
		return "Thrown when a command does not complete in enough time.";
	case kNoSuchWindow:
		return "\
Thrown when window target to be switched doesn't exist.\n\n\
To find the current set of active window handles, you can get a list\n\
of the active window handles in the following way:\n\n\
	std::cout << driver.GetWindows()[0].GetHandle();\
		";
	case kInvalidCookieDomain:
		return "\
Thrown when attempting to add a cookie under a different domain\n\
than the current URL.\
		";
	case kUnableToSetCookie:
		return "Thrown when a driver fails to set a cookie.";
	case kUnexpectedAlertOpen:
		return "\
Thrown when an unexpected alert has appeared.\n\n\
Usually raised when  an unexpected modal is blocking the webdriver from executing\n\
commands.\
		";
	case kScriptTimeout:
		return "Thrown when a command does not complete in enough time.";
	case kInvalidElementCoordinates:
		return "The coordinates provided to an interaction's operation are invalid.";
	case kIMENotAvailable:
		return "\
Thrown when IME support is not available. This exception is thrown for every IME-related\n\
method call if IME support is not available on the machine.\
		";
	case kIMEEngineActivationFailed:
		return "Thrown when activating an IME engine has failed.";
	case kInvalidSelector:
		return "\
Thrown when the selector which is used to find an element does not return\n\
a WebElement. Currently this only happens when the selector is an xpath\n\
expression and it is either syntactically invalid (i.e. it is not a\n\
xpath expression) or the expression does not select WebElements\n\
(e.g. \"count(//input)\").\
		";
		// TODO: Replace except info python code to cpp
	case kSessionNotCreatedException:
		return "A new session could not be created.";
	case kMoveTargetOutOfBounds:
		return "\
Thrown when the target provided to the `ActionsChains` move()\n\
method is invalid, i.e. out of document.\
		";
	case kInvalidXPathSelector:
		return "\
Thrown when the selector which is used to find an element does not return\n\
a WebElement. Currently this only happens when the selector is an xpath\n\
expression and it is either syntactically invalid (i.e. it is not a\n\
xpath expression) or the expression does not select WebElements\n\
(e.g. \"count(//input)\").\
		";
	case kInvalidXPathSelectorReturnTyper:
		return "\
Thrown when the selector which is used to find an element does not return\n\
a WebElement. Currently this only happens when the selector is an xpath\n\
expression and it is either syntactically invalid (i.e. it is not a\n\
xpath expression) or the expression does not select WebElements\n\
(e.g. \"count(//input)\").\
		";
	case kElementNotInteractable:
		return "\
Thrown when an element is present in the DOM but interactions\n\
with that element will hit another element due to paint order.\
		";
	case kInsecureCertificate:
		return "\
Navigation caused the user agent to hit a certificate warning, which is usually the result\n\
of an expired or invalid TLS certificate.\
		";
	// TODO: find out the switch-case value
	//case kInvalidArgument:
	//	return "The arguments passed to a command are either invalid or malformed.";
		//case kInvalidCoordinates:
		//	return "The coordinates provided to an interaction's operation are invalid.";
	case kInvalidSessionId:
		return "\
Occurs if the given session id is not in the list of active sessions, meaning the session\n\
either does not exist or that it's not active.\
		";
	//case kNoSuchCookie:
	//	return "\
//No cookie matching the given path name was found amongst the associated cookies of the\n\
//current browsing context's active document.\
//		";
	//case kUnableToCaptureScreen:
	//	return "A screen capture was made impossible.";
	case kElementClickIntercepted:
		return "\
The Element Click command could not be completed because the element receiving the events\n\
is obscuring the element that was requested to be clicked.\
		";
		//case kUnknownMethod:
		//	return "The requested command matched a known URL but did not match any methods for that URL.";
	//case kMethodNotAllowed:
	//	return "";
	}
	return "Unknown";
}

} // namespace response_status_code
} // namespace webdriverxx

#endif
