#include <webdriverxx/browsers/chrome.h>
#include <gtest/gtest.h>

namespace test {

using namespace webdriverxx;

TEST(Chrome, DefaultEmulateDeviceChrome) {
	chrome::MobileEmulation me;
	me.SetdeviceName(chrome::device::Get("Galaxy Note 3"));
	auto gc = Chrome();
	gc.SetMobileEmulation(me);
	ASSERT_EQ(gc.GetMobileEmulation().GetdeviceName(), me.GetdeviceName());
}

} // namespace test