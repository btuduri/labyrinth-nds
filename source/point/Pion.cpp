#include <PA9.h>
#include "Pion.h"
#include "../gfx/pion.c"
#include "../gfx/pion.pal.c"

namespace point {
	 // sprite position
	s32 theX;
	s32 theY;

	Pion::Pion(void) {
		// sprite init
		PA_LoadSpritePal(0, // Screen
				0, // Palette number
				(void*)pion_Pal);	// Palette name
						
		PA_CreateSprite(0, // Screen
				0, // Sprite number
				(void*)pion_Sprite, // Sprite name
				OBJ_SIZE_16X16, // Sprite size
				1, // 256 color mode
				0, // Sprite palette number
				50, 50); // X and Y position on the screen

	}

	Pion::~Pion(void) {
		PA_DeleteSprite(0, 0);
	}

	void Pion::move(int x, int y) {
		theX = x;
		theY = y;
		PA_SetSpriteXY(0,0,theX,theY);
	}

	int Pion::getSize() {
		return 16;
	}
}

