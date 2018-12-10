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

void outline_frame(Frame* frame)
{
    wborder(frame->window, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(frame->window);
}

/*
// Leaving here to come back to at some point.
void refresh_borders(Frame* frames[], int max_frame_count)
{
    for (int i = 0; i < max_frame_count; i++)
    {
        clear_frame(frames[i]);
        outline_frame(frames[i]);
    }
}
*/

void print_player_info(Frame* frame, char message[], int pos)
{
    // if (pos > frame->height) {
    //     wclear(frame->window)
    //     pos = 1;
    //     wrefresh(frame->window);
    // }

    mvwprintw(frame->window, pos, 1, message);
    wrefresh(frame->window);
    wmove(frame->window, pos, 1);
}

void print_center_frame(Frame* frame, char message[])
{
    mvwprintw(frame->window, frame->height *0.5, 2, message);
    wrefresh(frame->window);
}

void clear_frame(Frame* frame)
{
    wclear(frame->window);
    wrefresh(frame->window);
}
