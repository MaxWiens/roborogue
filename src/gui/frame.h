#ifndef frame_h
#define frame_h

#include <ncurses.h>

typedef struct Frame
{
    WINDOW* window; // the ncurses window pointer
    int height;
    int width;
    int x; // x position of the frame, including offset
    int y; // y position of the frame, including offset
}Frame;


Frame* new_frame(WINDOW* window, int h, int w, int y, int x);
void outline_frame(Frame* frame);
//void refresh_borders(Frame* frames[]);
// (currently broken.)
void print_center_frame(Frame* frame, char* message);
void clear_frame(Frame* frame);


#endif
