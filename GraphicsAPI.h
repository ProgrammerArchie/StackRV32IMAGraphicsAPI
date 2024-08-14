#pragma once
#define COLUMNBYTE 0x8000003F
#define UPPERSCREENBYTE 0x80000040
#define UPPERMIDDLESCREENBYTE 0x80000041
#define LOWERMIDDLESCREENBYTE 0x80000042
#define LOWERSCREENBYTE 0x80000043
unsigned video_memory[31];
void write_to_column(unsigned char column_number, unsigned column_data) {
	unsigned char* columnaddress = (unsigned char*) COLUMNBYTE;
	if(column_number > 32) column_number = 32;
	*columnaddress = column_number;
	unsigned char* screenbyte = (unsigned char*) UPPERSCREENBYTE;
	*screenbyte = column_data >> 24;
	screenbyte = (unsigned char*) UPPERMIDDLESCREENBYTE;
	*screenbyte = (column_data >> 16) & 0xFF;
	screenbyte = (unsigned char*) LOWERMIDDLESCREENBYTE;
	*screenbyte = (column_data >> 8) & 0xFF;
	screenbyte = (unsigned char*) LOWERSCREENBYTE;
	*screenbyte = column_data & 0xFF;
	return;
}
void update_screen(void) {
	for (unsigned char i = 0; i < 31; ++i) write_to_column(i, video_memory[i]);
	return;
}
void draw_pixel(unsigned char x, unsigned char y) {
    video_memory[x] |= 1 << (y ^ 31);
}
void draw_line(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int j = y1;
    int i = x1;
    int e = dy - dx;
    int stepx = dx >= 0 ? 1 : -1;
    int stepy = dy >= 0 ? 1 : -1;
    if (dx >= dy) {
        for (i; i <= x2 - 1; i += stepx) {
            draw_pixel(i, j);
            if (e >= 0) {
                j += stepy;
                e -= dx;
            }
            e += dy;
        }
    }
    else {
        for (int j = y1; j <= y2 - 1; j += stepy) {
            draw_pixel(i, j);
            if (e >= 0) {
                i += stepx;
                e -= dy;
            }
            e += dx;
        }
    }
    return;
}
void draw_triangle(unsigned char x1, unsigned char x2, unsigned char x3, unsigned char y1, unsigned char y2, unsigned char y3) {
	draw_line(x1, y1, x2, y2);
	draw_line(x2, y2, x3, y3);
	draw_line(x1, y1, x3, y3);
	return;
}
