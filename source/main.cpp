// PALib Template Application

// Includes
#include <PA9.h>       // Include for PA_Lib
#include "info/GameInfo.h"
#include "Game.h"

using namespace info;


int main() {
	// PA init
	PA_Init();
	PA_InitVBL();
	//

	// Game Info
	PA_InitText(1, 2);
	GameInfo *info = new GameInfo("First game from ", "Rasstone");
	PA_OutputText(1, 1, 2, "%s   %s", info->getName(), info->getCreator());
	
	// Game
	Game *game = new Game();

	// Infinite loop to keep the program running
	while (1) {
		// refresh game
		game->refresh();
		
		// wait next frame
		PA_WaitForVBL();
	}

	return 0;
}
