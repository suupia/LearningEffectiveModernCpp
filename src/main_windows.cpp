#ifdef _WIN32

#include <windows.h>

constexpr wchar_t kClassName[] = L"HelloWindowClass";
constexpr wchar_t kWindowTitle[] = L"Hello Window";
constexpr wchar_t kMessage[] = L"Hello World";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      RECT rect;
      GetClientRect(hwnd, &rect);
      SetBkMode(hdc, TRANSPARENT);
      DrawTextW(hdc, kMessage, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

      EndPaint(hwnd, &ps);
      return 0;
    }
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }

  return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
  WNDCLASSW wc{};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = kClassName;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

  RegisterClassW(&wc);

  HWND hwnd = CreateWindowExW(
      0,
      kClassName,
      kWindowTitle,
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      640,
      360,
      nullptr,
      nullptr,
      hInstance,
      nullptr);

  if (!hwnd) {
    return 1;
  }

  ShowWindow(hwnd, nCmdShow);

  MSG msg;
  while (GetMessageW(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  return static_cast<int>(msg.wParam);
}

#endif
