#include <windows.h>
#include "HL3Game.h"

int main() {
	//AllocConsole();
	//AttachConsole(GetCurrentProcessId());
	//freopen("CON", "w", stdout);

	HL3Game* game = new HL3Game();
	game->Start();
	return 0;
}