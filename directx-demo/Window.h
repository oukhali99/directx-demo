#pragma once
#include "Includes.h"

class Window {
public:
	Window(HINSTANCE hInstance, int nCmdshow);
	Window(HINSTANCE hInstance, HWND parentHWnd, int nCmdshow);
	Window(const Window& otherWindow) = delete;
	Window operator=(const Window& otherWindow) = delete;
	~Window();
	bool Init();
private:
	HWND parentHWnd;
	int nCmdShow;

	class WindowClass {
	public:
		WindowClass(HINSTANCE hInstance, LPCWSTR className);
		~WindowClass();
		WindowClass(const WindowClass& other) = delete;
		WindowClass operator=(const WindowClass& other) = delete;

		HINSTANCE GetHInstance() {
			return hInstance;
		}
		WNDCLASS GetWndClass() {
			return wndClass;
		}
		LPCWSTR GetClassName() {
			return className;
		}

	private:
		HINSTANCE hInstance;
		WNDCLASS wndClass;
		LPCWSTR className;
	};

	WindowClass windowClass;
};
