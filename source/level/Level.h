#include <PA9.h>
#include "../gfx/PAGfx.h"

namespace level {
	class Level {
		public:
			Level(PAGfx_struct* aBackground, int aWallTile, int aWinTile);
			~Level(void);

			int wallCollision(s32 x, s32 y, int size);
			int winCollision(s32 x, s32 y, int size);
			void scroll(s32 x);
			void reset();

		private:
			int collisionLeft(s32 x, s32 y, int aTile, int size);
			int collisionRight(s32 x, s32 y, int aTile, int size);
			int collisionTop(s32 x, s32 y, int aTile, int size);
			int collisionBottom(s32 x, s32 y, int aTile, int size);
			int collisionWith(s32 x, s32 y, int aTile, int size);
			int getTileAt(s32 x, s32 y);
	};
}
