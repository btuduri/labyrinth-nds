//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .h, for easier inclusion in a project

#ifndef ALL_GFX_H
#define ALL_GFX_H

#ifndef PAGfx_struct
	typedef struct{
		void *Map;
		int MapSize;
		void *Tiles;
		int TileSize;
		void *Palette;
		int *Info;
} PAGfx_struct;
#endif

// Background files : 
extern const int level1_Info[3]; // BgMode, Width, Height
extern const unsigned short level1_Map[768] __attribute__ ((aligned (4))) ;
extern const unsigned char level1_Tiles[192] __attribute__ ((aligned (4))) ;
//extern PAGfx_struct level1; // background pointer

extern const int level2_Info[3]; // BgMode, Width, Height
extern const unsigned short level2_Map[3072] __attribute__ ((aligned (4))) ;
extern const unsigned char level2_Tiles[192] __attribute__ ((aligned (4))) ;
//extern PAGfx_struct level2; // background pointer

// Sprite files : 


// Palette files : 
extern const unsigned short level1_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short level2_Pal[3] __attribute__ ((aligned (4))) ;

#endif

