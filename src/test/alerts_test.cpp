#include "environment.h"
#include <webdriverxx/webdriver.h>
#include <gtest/gtest.h>

namespace test {

using namespace webdriverxx;

class TestAlerts : public ::testing::Test {
protected:
	static void SetUpTestCase() {
		GetDriver().Navigate(GetTestPageUrl("alerts.html"));
	}

	TestAlerts() : driver(GetDriver()) {}

	WebDriver driver;
};

TEST_F(TestAlerts, AcceptsAlert) {
	if (IsPhantomJS()) return;
	driver.Execute("alert('abc')");
	driver.AcceptAlert();
}

TEST_F(TestAlerts, DismissesAlert) {
	if (IsPhantomJS()) return;
	driver.Execute("alert('abc')");
	driver.DismissAlert();
}

TEST_F(TestAlerts, GetsAlertText) {
	if (IsPhantomJS()) return;
	driver.Execute("alert('abc')");
	ASSERT_EQ("abc", driver.GetAlertText());
	driver.DismissAlert();
}

TEST_F(TestAlerts, SendsKeysToAlert) {
	if (IsPhantomJS()) return;
	driver.Execute("result = prompt('abc')");
	driver.SendKeysToAlert("def");
	driver.AcceptAlert();
	ASSERT_EQ("def", driver.Eval<std::string>("return result"));
}

TEST_F(TestAlerts, DismissesSendedKeys) {
	if (IsPhantomJS()) return;
	driver.Execute("result = prompt('abc')");
	driver.SendKeysToAlert("def");
	driver.DismissAlert();
	ASSERT_FALSE(driver.Eval<bool>("return result"));
}

} // namespace test
