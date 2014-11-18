#include <windows.h>
#include "HL3Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	//Win32Window* window = new Win32Window(hInstance, hPrevInstance, szCmdLine, iCmdShow);
	HL3Game* game = new HL3Game();
	game->Start();
}