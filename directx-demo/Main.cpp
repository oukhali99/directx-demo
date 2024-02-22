#include "Includes.h"
#include "Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int nCmdshow) {
	Window window(hInstance, nCmdshow);
	window.Init();

	MSG message;
	BOOL result = GetMessage(&message, nullptr, 0, 0);
	while (result) {
		TranslateMessage(&message);
		DispatchMessage(&message);

		result = GetMessage(&message, nullptr, 0, 0);
	}

	if (result == -1) {
		return -1;
	}

	return message.wParam;
}
