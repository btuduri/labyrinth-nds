#include "Level.h"
#include <PA9.h>
#include "../gfx/PAGfx.h"

namespace level {
	int theWallTile;
	int theWinTile;
	int theMapSize;
	short* theMap;
	s32 scrollx = 0; 
	s32 scrolly = 0;

	Level::Level(PAGfx_struct* aBackground, int aWallTile, int aWinTile) {
		theMap = (short*)aBackground->Map;
		theMapSize = aBackground->Info[1];
		theWallTile = aWallTile;
		theWinTile = aWinTile;
	}

	Level::~Level(void) {
	}

	int Level::wallCollision(s32 x, s32 y, int size) {
		return collisionWith(x, y, theWallTile, size);
	}

	int Level::winCollision(s32 x, s32 y, int size) {
		return collisionWith(x, y, theWinTile, size);
	}

	void Level::scroll(s32 x) {
		if (scrollx < theMapSize-256) {
			s32 inc = (6*x)/256;
			if (inc < 1) inc = 1;

			scrollx += inc;
			PA_LargeScrollX(0, 3, scrollx);
		}
	}

	void Level::reset() {
		scrollx = 0;
		PA_LargeScrollX(0, 3, scrollx);
	}

	int Level::collisionLeft(s32 x, s32 y, int aTile, int size) {
		s32 ax = scrollx + x - size/2;
		s32 ay = scrolly + y;
		return (getTileAt(ax, ay) == aTile);
	}

	int Level::collisionRight(s32 x, s32 y, int aTile, int size) {
		s32 ax = scrollx + x + size/2;
		s32 ay = scrolly + y;
		return (getTileAt(ax, ay) == aTile);
	}

	int Level::collisionTop(s32 x, s32 y, int aTile, int size) {
		s32 ax = scrollx + x;
		s32 ay = scrolly + y - size/2;
		return (getTileAt(ax, ay) == aTile);
	}

	int Level::collisionBottom(s32 x, s32 y, int aTile, int size) {
		s32 ax = scrollx + x;
		s32 ay = scrolly + y + size/2;
		return (getTileAt(ax, ay) == aTile);
	}

	int Level::collisionWith(s32 x, s32 y, int aTile, int size) {
		return (collisionLeft(x, y, aTile, size) || collisionRight(x, y, aTile, size) || collisionTop(x, y, aTile, size) || collisionBottom(x, y, aTile, size));
	}

	int Level::getTileAt(s32 x, s32 y) {
		return theMap[( (y>>3) * (theMapSize>>3) ) + (x>>3)];
	}
}
