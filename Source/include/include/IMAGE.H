/*
 *  Image.H
 *
 *  Created on: Oct 23, 2022
 *  Author: SAK-007
 *
 *
 *  Contains: Box,Sprite,Lines,ScreenMode,etc.
 *
 */



#include <STDLIB.H>
#include <STDIO.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <LIBGS.H>
#include <LIBETC.H>
#include <LIBSPU.H>
#include <SYS/TYPES.H>


#define OT_LENGTH 1
#define PACKETMAX 300




typedef struct {
	RECT rect;
	RECT crect;
	GsIMAGE tim_data;
	GsSPRITE sprite;
} Image;


GsOT 		  OrderingTable[2];
short 		  CurrentBuffer;


Image createImage(unsigned char imageData[]) {


	Image image;
	GsGetTimInfo ((u_long *)(imageData+4),&image.tim_data);


	image.rect.x = image.tim_data.px;            	// tim start X coord to put image data in frame buffer
	image.rect.y = image.tim_data.py;            	// tim start Y coord to put image data in frame buffer
	image.rect.w = image.tim_data.pw;            	// data width
	image.rect.h = image.tim_data.ph;            	// data height
	LoadImage(&image.rect, image.tim_data.pixel);

	// Load the CLUT into the frame buffer
	image.crect.x = image.tim_data.cx;            	// x pos to put CLUT in frame buffer
	image.crect.y = image.tim_data.cy;           	// y pos to put CLUT in frame buffer
	image.crect.w = image.tim_data.cw;            	// width of CLUT
	image.crect.h = image.tim_data.ch;            	// height of CLUT
	LoadImage(&image.crect, image.tim_data.clut);

	// Initialize sprite
	image.sprite.attribute = 0x1000000; 			// (0x1 = 8-bit, 0x2 = 16-bit)
	image.sprite.x = 0;                         	// draw at x coord
	image.sprite.y = 0;                          	// draw at y coord
	image.sprite.w = image.tim_data.pw * 2;         // width of sprite
	image.sprite.h = image.tim_data.ph;             // height of sprite

	image.sprite.tpage = GetTPage(
			1,   								// 0=4-bit, 1=8-bit, 2=16-bit
			1,   								// semitransparency rate
			image.tim_data.px, 						// framebuffer pixel x
			image.tim_data.py  						// framebuffer pixel y
	);

	image.sprite.r = 128;							// color red blend
	image.sprite.g = 128;							// color green blend
	image.sprite.b = 128;							// color blue blend
	image.sprite.u=(image.tim_data.px - 320) * 2;   // position within timfile for sprite
	image.sprite.v=image.tim_data.py;				// position within timfile for sprite
	image.sprite.cx = image.tim_data.cx;            // CLUT location x
	image.sprite.cy = image.tim_data.cy;            // CLUT location y
	image.sprite.mx = 0;                            // rotation x coord
	image.sprite.my = 0;                            // rotation y coord
	image.sprite.scalex = ONE;                      // scale x (ONE = 100%)
	image.sprite.scaley = ONE;                      // scale y (ONE = 100%)
	image.sprite.rotate = 0;                        // rotation

	return image;
}

Image moveImage(Image image, int x, int y) {
	image.sprite.x = x;
	image.sprite.y = y;
	return image;
}


void drawImage(Image image) {
	CurrentBuffer = GsGetActiveBuff();
	GsSortSprite(&image.sprite, &OrderingTable[CurrentBuffer], 0);
}

