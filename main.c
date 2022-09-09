#include <windows.h>
#include <stdlib.h>

unsigned int global_running = 1;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		case WM_DESTROY:
		{
			global_running = 0;
			PostQuitMessage(0);
		} break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
		} break;

		default:
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		} break;
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow) {
	WNDCLASS WindowClass = {0};
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.hInstance = instance;
	WindowClass.lpszClassName = "test";
	if(RegisterClassA(&WindowClass)) {

		HWND Window = CreateWindowEx(
			0, 
			WindowClass.lpszClassName, 
			"data structures",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			instance,
			0);

		if(Window) {
			HDC device_context = GetDC(Window);
			ShowWindow(Window, cmdShow);

			while(global_running) {
				MSG msg = {0};
				while(GetMessage(&msg, NULL, 0, 0) > 0) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}

    return 0;
}