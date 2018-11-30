#include <ncurses.h>
#include <stdlib.h>
#include "frame.h"

Frame* new_frame(WINDOW* window, int h, int w, int y, int x)
{
    Frame* frame = malloc(sizeof(Frame*));
    frame->window = window;
    frame->height = h;
    frame->width = w;
    frame->x = x;
    frame->y = y;

    return frame;
}

void outline_frame(Frame* frame, Frame* overlay, char* c)
{
    // for (int i = 0; i <= frame->height + 1; i++)
    // {
    //     for (int j = 0; j <= frame->width + 1; j++)
    //     {
    //          if (j == 0 || j == frame->width + 1) {
    //              mvwprintw(overlay->window, i, j, c);
    //          }
    //
    //          if (i == 0 || i == frame->height + 1) {
    //              mvwprintw(overlay->window, i, j, c);
    //          }
    //     }
    // }



    // wrefresh(overlay->window);

    WINDOW* win = overlay->window;

    // draw top border
    for (int n = 0; n <= frame->width; n++) {
        mvwprintw(win, -1, n, c);
    }
    
    // // draw bottom border
    // for (int n = 0; n < frame->width; n++) {
    //     mvwprintw(win, frame->height, n, c);
    // }
    //
    // // draw left border
    // for (int n = 0; n < frame->height; n++) {
    //     mvwprintw(win, n, 0, c);
    // }
    //
    // // draw right border
    // for (int n = 0; n < frame->height; n++) {
    //     mvwprintw(win, n, frame->width, c);
    // }

    // wrefresh(frame->window);
    // wrefresh(overlay->window);
}

void print_center_frame(Frame* frame, char message[])
{
    // wclear(frame->window);
    mvwprintw(frame->window, 0, frame->height * 0.5, message);
    wrefresh(frame->window);
}

void clear_frame(Frame* frame)
{
    wclear(frame->window);
    wrefresh(frame->window);
}
