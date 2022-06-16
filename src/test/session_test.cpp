#include "environment.h"
#include <webdriverxx/session.h>
#include <gtest/gtest.h>
#include <algorithm>

namespace test {

	using namespace webdriverxx;

	class TestSession : public ::testing::Test {
	protected:
		TestSession() : driver(GetDriver()) {}

		void ReplaceSpoiledSession() {
			driver = GetFreshDriver();
		}

		WebDriver driver;
	};

	TEST_F(TestSession, GetsCapabilities)
	{
		Capabilities c = driver.GetCapabilities();
		ASSERT_TRUE(c.Has("browserName"));
		ASSERT_TRUE(c.Has("version"));
		ASSERT_TRUE(c.Has("platform"));
		ASSERT_NE("", c.GetBrowserName());
	}

	TEST_F(TestSession, StartsSecondBrowser) {
		WebDriver second = CreateDriver();
	}

	TEST_F(TestSession, GetsCurrentWindow) {
		driver.GetCurrentWindow();
	}

	TEST_F(TestSession, GetsWindowHandle) {
		ASSERT_NE("", driver.GetCurrentWindow().GetHandle());
	}

	TEST_F(TestSession, SetsFocusToWindow) {
		driver.SetFocusToWindow(driver.GetCurrentWindow().GetHandle());
	}

	TEST_F(TestSession, ClosesCurrentWindow) {
		driver.CloseCurrentWindow();
		ReplaceSpoiledSession();
	}

	TEST_F(TestSession, GetsWindowSize) {
		Window window = driver.GetCurrentWindow();
		window.GetSize();
	}

	TEST_F(TestSession, SetsWindowSize) {
		Window window = driver.GetCurrentWindow();
		Size size1;
		size1.width = 601;
		size1.height = 602;
		window.SetSize(size1);
		Size size2 = window.GetSize();
		ASSERT_EQ(601, size2.width);
		ASSERT_EQ(602, size2.height);
	}

	TEST_F(TestSession, GetsWindowPosition) {
		Window window = driver.GetCurrentWindow();
		window.GetPosition();
	}

	TEST_F(TestSession, SetsWindowPosition) {
		if (IsPhantomJS()) return;
		Window window = driver.GetCurrentWindow();
		Point position1;
		position1.x = 101;
		position1.y = 102;
		window.SetPosition(position1);
		Point position2 = window.GetPosition();
		ASSERT_EQ(101, position2.x);
		ASSERT_EQ(102, position2.y);
	}

	TEST_F(TestSession, CloseWindow) {
		Window window = driver.GetCurrentWindow();
		window.close();
	}

	TEST_F(TestSession, MaximizesWindow) {
		Window window = driver.GetCurrentWindow();
		window.Maximize();
	}

	TEST_F(TestSession, MinimizesWindow) {
		Window window = driver.GetCurrentWindow();
		window.Minimize();
	}

	TEST_F(TestSession, FullscreensWindow) {
		Window window = driver.GetCurrentWindow();
		window.Fullscreen();
	}

	TEST_F(TestSession, GetsWindows) {
		driver.GetWindows();
	}

	TEST_F(TestSession, Navigates) {
		std::string url = GetWebDriverUrl() + "status";
		driver.Navigate(url);
		ASSERT_EQ(url, driver.GetUrl());
	}

	TEST_F(TestSession, NavigatesToTestPage) {
		const std::string url = GetTestPageUrl("session.html");
		driver.Navigate(url);
		ASSERT_EQ(url, driver.GetUrl());
	}

	TEST_F(TestSession, GoesBack) {
		const std::string page1 = GetTestPageUrl("navigation1.html");
		const std::string page2 = GetTestPageUrl("navigation2.html");
		driver.Navigate(page1).Navigate(page2).Back();
		ASSERT_EQ(page1, driver.GetUrl());
	}

	TEST_F(TestSession, GoesForward) {
		const std::string page1 = GetTestPageUrl("navigation1.html");
		const std::string page2 = GetTestPageUrl("navigation2.html");
		driver.Navigate(page1).Navigate(page2).Back().Forward();
		ASSERT_EQ(page2, driver.GetUrl());
	}

	TEST_F(TestSession, DoesRefresh) {
		const std::string page = GetTestPageUrl("navigation1.html");
		driver.Navigate(page).FindElement(ByTag("input")).Click().SendKeys("abc");
		ASSERT_EQ("abc", driver.FindElement(ByTag("input")).GetAttribute("value"));
		driver.Refresh();
		ASSERT_EQ(page, driver.GetUrl());
		ASSERT_EQ("", driver.FindElement(ByTag("input")).GetAttribute("value"));
	}

	TEST_F(TestSession, GetsPageSource) {
		driver.Navigate(GetTestPageUrl("session.html"));
		std::string source = driver.GetPageSource();
		ASSERT_NE(std::string::npos, source.find("<html"));
		ASSERT_NE(std::string::npos, source.find("</html>"));
	}

	TEST_F(TestSession, GetsPageTitle) {
		driver.Navigate(GetTestPageUrl("session.html"));
		ASSERT_EQ("Test title", driver.GetTitle());
	}

	TEST_F(TestSession, GetsScreenshot) {
		driver.Navigate(GetTestPageUrl("session.html"));
		ASSERT_TRUE(!driver.GetScreenshot().empty());
	}

	TEST_F(TestSession, GetsElementScreenshot) {
		const std::string page = GetTestPageUrl("navigation1.html");
		Element element = driver.Navigate(page).FindElement(ByTag("input"));
		ASSERT_TRUE(!driver.GetElementScreenshot(element).empty());
	}

	TEST_F(TestSession, SetsTimeouts) {
		driver.SetTimeoutMs(timeout::Implicit, 1000);
		driver.SetTimeoutMs(timeout::PageLoad, 1000);
		driver.SetTimeoutMs(timeout::Script, 1000);
	}

	TEST_F(TestSession, SetsAsyncScriptTimeout) {
		driver.SetAsyncScriptTimeoutMs(1000);
	}

	TEST_F(TestSession, SetsImplicitTimeout) {
		driver.SetImplicitTimeoutMs(1000);
	}

	TEST_F(TestSession, GetsActiveElement) {
		driver.Navigate(GetTestPageUrl("session.html"));
		Element e = driver.FindElement(ByTag("input"));
		e.Click();
		ASSERT_EQ(e, driver.GetActiveElement());
	}

	Cookie FindCookie(
		const std::vector<Cookie>& cookies,
		const std::string& name,
		const Cookie& default_value = Cookie()
	) {
		const auto it = std::find_if(cookies.begin(), cookies.end(),
			[&name](const Cookie& cookie) {
				return cookie.name == name;
			});
		return it != cookies.end() ? *it : default_value;
	}

	namespace webdriverxx {

		void PrintTo(const Cookie& c, ::std::ostream* os) {
			*os << ToJson(c).serialize();
		}

	} // namespace webdriverxx

	TEST_F(TestSession, SetsAndGetsCookies) {
		driver.Navigate(GetTestPageUrl("session.html"));
		driver.SetCookie(Cookie("name1", "value1")).SetCookie(Cookie("name2", "value2"));
		std::vector<Cookie> cookies = driver.GetCookies();
		ASSERT_TRUE(cookies.size() >= 2u);
		ASSERT_EQ("value1", FindCookie(cookies, "name1").value);
		ASSERT_EQ("value2", FindCookie(cookies, "name2").value);
	}

	TEST_F(TestSession, SetsAllFieldsOfACookie) {
		// const Cookie c1("name1", "value1", "/path1", "domain1.com", true, true, 123);
		const Cookie c1("name1", "value1", "/path1", "domain1.com", nullptr, true, 123);
		const Cookie c2("name2", "value2", "/path2", "domain2.com", false, false, 124);
		ASSERT_EQ(c1, FromJson<Cookie>(ToJson(c1)));
		ASSERT_EQ(c2, FromJson<Cookie>(ToJson(c2)));
	}

	TEST_F(TestSession, DeletesCookies) {
		driver.Navigate(GetTestPageUrl("session.html"));
		driver.SetCookie(Cookie("name1", "value1")).SetCookie(Cookie("name2", "value2"));
		driver.DeleteCookies();
		ASSERT_EQ(0u, driver.GetCookies().size());
	}

	TEST_F(TestSession, DeletesACookie) {
		driver.Navigate(GetTestPageUrl("session.html"));
		driver.SetCookie(Cookie("name1", "value1")).SetCookie(Cookie("name2", "value2"));
		driver.DeleteCookie("name1");
		std::vector<Cookie> cookies = driver.GetCookies();
		ASSERT_EQ("", FindCookie(cookies, "name1").value);
		ASSERT_EQ("value2", FindCookie(cookies, "name2").value);
	}

} // namespace test
