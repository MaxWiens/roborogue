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

Frame* new_frame(WINDOW* window, int h, int w, int x, int y);
void outline_frame(Frame* frame, Frame* overlay, char* c);
void print_center_frame(Frame* frame, char* message);
void clear_frame(Frame* frame);

/*
    alert_to_window
    Window* window: a window pointer to which we will alert the message
    int y: y position relative to window
    int x: x position relative to window
*/

#endif
