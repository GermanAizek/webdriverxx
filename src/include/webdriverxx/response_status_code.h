#ifndef WEBDRIVERXX_RESPONSE_STATUS_CODE_H
#define WEBDRIVERXX_RESPONSE_STATUS_CODE_H

namespace webdriverxx {
namespace response_status_code {

enum Value {
	kSuccess = 0,
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
	kInvalidCoordinates,
	kInvalidSessionId,
	kNoSuchCookie = 62,
	kUnableToCaptureScreen = 63,
	kElementClickIntercepted = 64,
	kUnknownMethod,
	kMethodNotAllowed = 405
};

inline
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
	std::cout << driver.GetWindows()[0].GetHandle();\n\
		";
	// TODO: Add more info excepts
	case kInvalidCookieDomain: return "An illegal attempt was made to set a cookie under a different domain than the current page.";
	case kUnableToSetCookie: return "A request to set a cookie's value could not be satisfied.";
	case kUnexpectedAlertOpen: return "A modal dialog was open, blocking this operation";
	case kNoAlertOpenError: return "An attempt was made to operate on a modal dialog when one was not open.";
	case kScriptTimeout: return "A script did not complete before its timeout expired.";
	case kInvalidElementCoordinates: return "The coordinates provided to an interactions operation are invalid.";
	case kIMENotAvailable: return "IME was not available.";
	case kIMEEngineActivationFailed: return "An IME engine could not be started.";
	case kInvalidSelector: return "Argument was an invalid selector (e.g. XPath/CSS).";
	case kSessionNotCreatedException: return "A new session could not be created.";
	case kMoveTargetOutOfBounds: return "Target provided for a move action is out of bounds.";
	case kInvalidXPathSelector: return "";
	case kInvalidXPathSelectorReturnTyper: return "";
	case kElementNotInteractable: return "";
	case kInsecureCertificate: return "";
	// TODO: find out the switch-case value
	//case kInvalidArgument: return "";
	case kInvalidCoordinates: return "";
	case kInvalidSessionId: return "";
	//case kNoSuchCookie: return "";
	//case kUnableToCaptureScreen: return "";
	case kElementClickIntercepted: return "";
	case kUnknownMethod: return "";
	case kMethodNotAllowed: return "";
	}
	return "Unknown";
}

} // namespace response_status_code
} // namespace webdriverxx

#endif
