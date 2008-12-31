#include "Game.h"
#include "level/Level.h"
#include "point/Pion.h"
#include "gfx/PAGfx.h"
#include "gfx/level0.c"
#include "gfx/level0.pal.c"
#include "gfx/level1.c"
#include "gfx/level1.pal.c"
#include "gfx/level2.c"
#include "gfx/level2.pal.c"
#include "gfx/level3.c"
#include "gfx/level3.pal.c"
#include <PA9.h>
#include <time.h>

using namespace level;
using namespace point;
	
	const int NB_LEVEL = 4;

	// current level
	int levelIndex = 0;
	Level* theCurrentLevel;

	// pion
	Pion *thePion;

	// for score compute
	int frame = 0;
	int startFrame;	
	float bestDuration[NB_LEVEL] = {0.0};
	int lostTime = 0;
	int winTime = 0;

	// game control
	int started = false;
	int finished = false;
	int lives = 3;

	Game::Game(void) {
		thePion = new Pion();

		levelIndex = 0;
		loadLevel();
	}

	Game::~Game(void)
	{
	}

	void Game::refresh() {
		frame++;

		if (Stylus.Newpress) {
			if (finished) {
				finished = false;
				
				lives = 3;
				thePion = new Pion();
				levelIndex = 0;
				loadLevel();
			} else if (PA_SpriteStylusOver(0)) {
				start();
			}
		}
		
		if (started) {
			// display current time
			displayCurrentScore();

			// user released stylus = loose
			if (Stylus.Released) {
				loose();
			}
			// wall collision = loose
			else if (theCurrentLevel->wallCollision(Stylus.X, Stylus.Y, thePion->getSize())) {
				loose();
			}
			// end door collision = win
			else if (theCurrentLevel->winCollision(Stylus.X, Stylus.Y, thePion->getSize())) {
				win();
			}
			// game is running
			else {
				PA_SetTextTileCol(1, 0);
				PA_OutputText(1, 0, 6, "--------------------------------");
				PA_OutputText(1, 0, 7, "|                              |");
				PA_OutputText(1, 0, 8, "|     Don't touch the walls    |");
				PA_OutputText(1, 0, 9, "|                              |");
				PA_OutputText(1, 0, 10, "--------------------------------");

				// move point
				s32 x = Stylus.X - thePion->getSize()/2;
				s32 y = Stylus.Y - thePion->getSize()/2;
				thePion->move(x, y);

				// Scrolling
				theCurrentLevel->scroll(x);
			}
		}
	}

	void Game::init() {
		PA_SetTextTileCol(1, 0);
		PA_OutputText(1, 0, 5, "    LEVEL %d ......... lives : %d", (levelIndex+1), lives );

		theCurrentLevel->reset();
		thePion->move(5, 20);
		
		started = false;
	}

	void Game::start() {
		startFrame = frame;
		started = true;
	}

	void Game::loadLevel() {
		if (levelIndex == 0) {
			PAGfx_struct level = {(void*)level0_Map, 768, (void*)level0_Tiles, 192, (void*)level0_Pal, (int*)level0_Info };
			theCurrentLevel = new Level(&level, 0, 2);
			PA_LoadPAGfxLargeBg(0, 3, level0);
		} else if (levelIndex == 2) {
			PAGfx_struct level = {(void*)level1_Map, 768, (void*)level1_Tiles, 192, (void*)level1_Pal, (int*)level1_Info };
			theCurrentLevel = new Level(&level, 0, 1);
			PA_LoadPAGfxLargeBg(0, 3, level1);
		} else if (levelIndex == 1) {
			PAGfx_struct level = {(void*)level2_Map, 3072, (void*)level2_Tiles, 192, (void*)level2_Pal, (int*)level2_Info };
			theCurrentLevel = new Level(&level, 0, 2);
			PA_LoadPAGfxLargeBg(0, 3, level2);
		} else if (levelIndex == 3) {
			PAGfx_struct level = {(void*)level3_Map, 3072, (void*)level3_Tiles, 192, (void*)level3_Pal, (int*)level3_Info };
			theCurrentLevel = new Level(&level, 0, 2);
			PA_LoadPAGfxLargeBg(0, 3, level3);
		}
		
		init();
	}

	void Game::loose() {
		PA_SetTextTileCol(1, 2);
		PA_OutputText(1, 0,  6, "--------------------------------");
		PA_OutputText(1, 0,  7, "|   ------------------------   |");
		PA_OutputText(1, 0,  8, "|   |   ---> LOOSER <---   |   |");
		PA_OutputText(1, 0,  9, "|   ------------------------   |");
		PA_OutputText(1, 0, 10, "--------------------------------");
		lostTime++;
		displayWinLost();
		lives--;

		// has live left ?
		if (lives < 0) {
			end(false);
		}
		else {// re-init level
			init();
		}
	}

	void Game::win() {
		PA_SetTextTileCol(1, 4);
		PA_OutputText(1, 0,  6, "--------------------------------");
		PA_OutputText(1, 0,  7, "|   ------------------------   |");
		PA_OutputText(1, 0,  8, "|   |   ---> WINNER <---   |   |");
		PA_OutputText(1, 0,  9, "|   ------------------------   |");
		PA_OutputText(1, 0, 10, "--------------------------------");
		winTime++;
		displayWinLost();

		// best score handling
		float duration = (frame - startFrame) / 60.0; // 60 FPS
		if (bestDuration[levelIndex] <= 0.0 || duration < bestDuration[levelIndex]) {
			bestDuration[levelIndex] = duration;
			displayBestScore();
		}
		
		levelIndex++;
		if (levelIndex >= NB_LEVEL) {
			end(true);
		} else {
			loadLevel();
		}
	}

	void Game::end(int win) {
		started = false;
		finished = true;
		PA_ResetBgSysScreen(0);
		delete thePion;

		PA_InitText(0, 3);
		PA_SetTextTileCol(0, 4);
		if (win) {
			PA_OutputText(0, 0, 8, "          YOU WON GAME         ");
		} else {
			PA_OutputText(0, 0, 8, "          YOU LOST GAME         ");
		}
		
		PA_SetTextTileCol(0, 1);
		PA_OutputText(0, 0, 9, "         Touch to restart         ");
		
		PA_SetTextTileCol(1, 0);
		PA_OutputText(1, 0, 5, "           ");
	}

	void Game::displayCurrentScore() {
		PA_SetTextTileCol(1, 5);
		float duration = (frame - startFrame) / 60.0; // 60 FPS
		PA_OutputText(1, 0, 11, "%f1 secondes", duration);
	}

	void Game::displayBestScore() {
		PA_SetTextTileCol(1, 6);
		int line = 15;
		PA_OutputText(1, 0, line, "BEST SCORES :");
		for (int i = 0 ; i < NB_LEVEL ; i++) {
			if (bestDuration[i] > 0.0) {
				line++;
				PA_OutputText(1, 0, line, "-> LEVEL %d : %f1 secondes", i+1, bestDuration[i]);
			}
		}
	}

	void Game::displayWinLost() {
		PA_SetTextTileCol(1, 0);
		PA_OutputText(1, 1, 21, "Lost : %d          Win : %d", lostTime, winTime);
	}
