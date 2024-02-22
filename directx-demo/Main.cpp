#include <Windows.h>
#include <string>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE: {
			if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hwnd);
			}
			// Else: User canceled. Do nothing.
			return 0;
		}			
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int nCmdshow) {
	wchar_t className[] = L"Some Class Name";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = className;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);
	
	HWND hWnd = CreateWindowExW(
		0,
		className,
		L"Window Title",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1280, 720,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL)
	{
		return 0;
	}

	ShowWindow(hWnd, nCmdshow);

	MSG message;
	while (GetMessageA(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}
