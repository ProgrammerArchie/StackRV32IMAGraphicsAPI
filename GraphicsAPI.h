#pragma once
unsigned video_memory[31];
void write_to_column(unsigned char column_number, unsigned column_data);
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