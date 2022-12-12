#ifndef constants_h
#define constants_h


#include <STDLIB.H>
#include <STDIO.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <LIBGS.H>
#include <LIBETC.H>
#include <LIBSPU.H>
#include <LIBDS.H>
#include <STRINGS.H>
#include <SYS/TYPES.H>

unsigned long __ramsize =   0x00200000; // 2 Megabytes of RAM
unsigned long __stacksize = 0x00004000; // 16 Kilobytes of Stack


#define OT_LENGTH 1
#define PACKETMAX 300
#define TYPE_LINE 0
#define TYPE_BOX 1
#define SCREEN_MODE_PAL 0
#define SCREEN_MODE_NTSC 1
#define DEBUG 0
#define ROT_ONE 4096
#define Sprite GsSPRITE

typedef struct {
	int r;
	int g;
	int b;
} Color;




Color* 		  systemBackgroundColor;
GsOT 		  orderingTable[2];
short 		  currentBuffer;


void sprite_create(unsigned char imageData[], int x, int y, GsSPRITE **sprite) {

	// Initialize image
	GsIMAGE* tim_data;
	RECT* rect;
	RECT* crect;
	tim_data = malloc3(sizeof(GsIMAGE));
	GsGetTimInfo ((u_long *)(imageData+4),tim_data);
	rect = malloc3(sizeof(RECT));
	crect = malloc3(sizeof(RECT));

	// Load the image into the GPU memory (frame buffer)
	rect->x = tim_data->px; // x position of image in frame buffer
	rect->y = tim_data->py; // y position of image in frame buffer
	rect->w = tim_data->pw; // width in frame buffer
	rect->h = tim_data->ph; // height in frame buffer
	printf("Framebuffer info {x=%d, y=%d, w=%d, h=%d}\n", rect->x, rect->y, rect->w, rect->h);
	LoadImage(rect, tim_data->pixel);

	// Load the color lookup table (CLUT) into the GPU memory (frame buffer)
	crect->x = tim_data->cx; // x position of CLUT in frame buffer
	crect->y = tim_data->cy; // y position of CLUT in frame buffer
	crect->w = tim_data->cw; // width of CLUT in frame buffer
	crect->h = tim_data->ch; // height of CLUT in frame buffer
	printf("CLUT info {x=%d, y=%d, w=%d, h=%d}\n", crect->x, crect->y, crect->w, crect->h);
	LoadImage(crect, tim_data->clut);

	// Initialize sprite (see GSSprite at PSYQ/DOCS/LIBREF.PDF)
	*sprite = malloc3(sizeof(GsSPRITE));
	(*sprite) -> attribute = 0x0000000;
	(*sprite) -> x = x;
	(*sprite) -> y = y;
	(*sprite) -> w = tim_data->pw * 4;
	(*sprite) -> h = tim_data->ph;
	(*sprite) -> tpage = GetTPage(
			0, 		 // 0=4-bit, 1=8-bit, 2=16-bit
			1,       // semitransparency rate
			rect->x, // framebuffer x position of image
			rect->y  // framebuffer y position of image
	);
	(*sprite)->r = 128;  						// Color red blend
	(*sprite)->g = 128;  						// Color green blend
	(*sprite)->b = 128;  						// Color blue blend
	(*sprite)->u = (tim_data->px * 4) % 256;	// Position within tpage for sprite (0-256)
	(*sprite)->v = (tim_data->py % 256);		// Position within tpage for sprite (0-256)
	(*sprite)->cx = tim_data->cx;               // CLUT location x
	(*sprite)->cy = tim_data->cy;               // CLUT location y
	(*sprite)->rotate = ROT_ONE * 0;            // Rotation, ROT_ONE * (0 to 360) 
	(*sprite)->mx = 0;                          // Rotation x coord
	(*sprite)->my = 0;                          // Rotation y coord
	(*sprite)->scalex = ONE * 1;				// Sprite scale (width)
	(*sprite)->scaley = ONE * 1;				// Sprite scale (height)

	// Clean up
	free3(rect);
	free3(crect);
	free3(tim_data);
}

void sprite_set_rotation(Sprite* sprite, int rotation) {
	sprite -> rotate = ROT_ONE * rotation;
}

void sprite_set_middle(Sprite* sprite, int relative_x, int relative_y) {
	sprite->mx = relative_x;
	sprite->my = relative_y;
}

void sprite_set_position(Sprite* sprite, int x, int y) {
	sprite->x = x;
	sprite->y = y;
} 

void sprite_set_blend_color(Sprite* sprite, Color* color) {
	sprite -> r = color->r;
	sprite -> g = color->g;
	sprite -> b = color->b;
}

void sprite_set_blend_rgb(Sprite* sprite, int r, int g, int b) {
	sprite -> r = r;
	sprite -> g = g;
	sprite -> b = b;
}

void color_create(int r, int g, int b, Color** color) {
	*color = malloc(sizeof(Color));
	(*color) -> r = r;
	(*color) -> g = g;
	(*color) -> b = b;
}





void draw_sprite(Sprite *sprite) {
	currentBuffer = GsGetActiveBuff();
	GsSortSprite(sprite, &orderingTable[currentBuffer], 0);
}








#endif