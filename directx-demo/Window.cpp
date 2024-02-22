#include "Includes.h"
#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
		if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		// Else: User canceled. Do nothing.
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window(HINSTANCE hInstance, int nCmdshow)
	:
	Window(hInstance, nullptr, nCmdshow)
{}

Window::Window(HINSTANCE hInstance, HWND parentHWnd, int nCmdshow)
	:
	parentHWnd(parentHWnd),
	nCmdShow(nCmdshow),
	windowClass(hInstance, L"Some class name")
{}

bool Window::Init() {

	HWND hWnd = CreateWindowEx(
		0,
		windowClass.GetClassName(),
		L"Window Title",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1280, 720,
		parentHWnd,
		nullptr,
		windowClass.GetHInstance(),
		nullptr
	);

	if (hWnd == nullptr)
	{
		return false;
	}

	ShowWindow(hWnd, nCmdShow);

	return true;
}

Window::~Window() {
	UnregisterClass(windowClass.GetClassName(), windowClass.GetHInstance());
}

Window::WindowClass::WindowClass(HINSTANCE hInstance, LPCWSTR className)
	:
	hInstance(hInstance),
	className(className)
{
	wndClass.lpszClassName = className;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowProc;
	RegisterClass(&wndClass);
}

Window::WindowClass::~WindowClass() {
	UnregisterClass(className, hInstance);
}
