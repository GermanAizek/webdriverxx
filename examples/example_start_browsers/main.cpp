#include <webdriverxx/webdriverxx.h>

using namespace webdriverxx;

int main()
{
  WebDriver ff = Start(Firefox());

  WebDriver op = Start(Opera());

  WebDriver ph = Start(Phantom());

  WebDriver gc = Start(Chrome());

  WebDriver ie = Start(InternetExplorer());

  getchar();

  return 0;
}
