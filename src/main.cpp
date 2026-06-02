int run_platform_app();

#ifdef _WIN32
#include <windows.h>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  return run_platform_app();
}
#else
int main() {
  return run_platform_app();
}
#endif
