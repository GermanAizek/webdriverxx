#include "webdriverxx.h"

using namespace webdriverxx;

int main()
{
  WebDriver browser = Start(Firefox());
  browser.Navigate("https://duckduckgo.org");
  Element elem = browser.FindElement(ByCss("input[name=q]"));
  elem.SendKeys("sha512 helloworld");
  elem.Submit();
  getchar();

  return 0;
}
