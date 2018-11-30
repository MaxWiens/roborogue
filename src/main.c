#include <stdio.h>
#include "util/bool.h"
#include "gui/frame.h"
#include <ncurses.h>

#define DUNGEON_WIN_WIDTH 100
#define DUNGEON_WIN_HEIGHT 25
// #define DUNGEON_WIN_WIDTH 101
// #define DUNGEON_WIN_HEIGHT 26

#define STATUS_WIN_WIDTH 100
#define STATUS_WIN_HEIGHT 5
// #define STATUS_WIN_WIDTH 101
// #define STATUS_WIN_HEIGHT 6

#define INVENTORY_WIN_WIDTH 50
#define INVENTORY_WIN_HEIGHT 15
// #define INVENTORY_WIN_WIDTH 51
// #define INVENTORY_WIN_HEIGHT 16

#define INFO_WIN_WIDTH 50
#define INFO_WIN_HEIGHT 15
// #define INFO_WIN_WIDTH 51
// #define INFO_WIN_HEIGHT 16


#define MAX_WIDTH 150
#define MAX_HEIGHT 30
// TOTALS:
// WIDTH: 150
// HEIGHT: 30

/* GENERAL GUI LAYOUT:
##############################
#                #           #
#    dungeon     # inventory #
#                #           #
#                # # # # # # #
# # # # # # # #  # info      #
#   status       #           #
############################## */


int main(int argc, char const *argv[])
{
	//initialises ncurses
	initscr();
	raw();
	noecho();

	/* WINDOW COMPOSITION */

	// get total window height to center the screen (if possible)
	int max_scr_y = 0, max_scr_x = 0;
	getmaxyx(stdscr, max_scr_y, max_scr_x);

	// calculate offsets
	int right_scr_offset = 0;
	if (max_scr_x > MAX_WIDTH) {
		right_scr_offset = (max_scr_x - MAX_WIDTH) / 2;
	}

	int top_scr_offset = 0;
	if (max_scr_y > MAX_HEIGHT) {
		top_scr_offset = (max_scr_y - MAX_HEIGHT) / 2;
	}

	// create windows
	WINDOW* dungeon_win = newwin(DUNGEON_WIN_HEIGHT, DUNGEON_WIN_WIDTH, top_scr_offset, right_scr_offset);
	WINDOW* status_win = newwin(STATUS_WIN_HEIGHT, STATUS_WIN_WIDTH, top_scr_offset + DUNGEON_WIN_HEIGHT, right_scr_offset);
	WINDOW* inventory_win = newwin(INVENTORY_WIN_HEIGHT, INVENTORY_WIN_WIDTH, top_scr_offset, right_scr_offset + DUNGEON_WIN_WIDTH);
	WINDOW* info_win = newwin(INFO_WIN_HEIGHT, INFO_WIN_WIDTH, top_scr_offset + INVENTORY_WIN_HEIGHT, right_scr_offset + STATUS_WIN_WIDTH);

	// add 3 to height and width to account for padding due to the
	WINDOW* overlay_win = newwin(MAX_HEIGHT + 3, MAX_WIDTH + 3, top_scr_offset, right_scr_offset);

	// create frames for the windows
	Frame* dungeon_frame = new_frame(dungeon_win, DUNGEON_WIN_HEIGHT, DUNGEON_WIN_WIDTH, top_scr_offset, right_scr_offset);
	Frame* status_frame = new_frame(status_win, STATUS_WIN_HEIGHT, STATUS_WIN_WIDTH, top_scr_offset + DUNGEON_WIN_HEIGHT, right_scr_offset);
	Frame* inventory_frame = new_frame(inventory_win, INVENTORY_WIN_HEIGHT, INVENTORY_WIN_WIDTH, top_scr_offset, right_scr_offset + DUNGEON_WIN_WIDTH);
	Frame* info_frame = new_frame(info_win, INFO_WIN_HEIGHT, INFO_WIN_WIDTH, top_scr_offset + INVENTORY_WIN_HEIGHT, right_scr_offset + STATUS_WIN_WIDTH);

	Frame* overlay_frame = new_frame(overlay_win, MAX_HEIGHT, MAX_WIDTH, top_scr_offset, right_scr_offset);


	//outline every frame
	outline_frame(dungeon_frame, overlay_frame, "*");
	outline_frame(status_frame, overlay_frame, "*");
	outline_frame(inventory_frame, overlay_frame, "*");
	outline_frame(info_frame, overlay_frame, "*");
	//manually refresh the overlay frame, because we should only outline everything one time.
	wrefresh(overlay_frame->window);

	keypad(dungeon_win, true);

	// game logic
	bool exit = false;
	while(!exit){
		int input = wgetch(dungeon_win);
		switch(input){
			//escape is pressed
			case KEY_SLEFT:
			case KEY_BACKSPACE:

				// mvwprintw(status_frame->window, 0,STATUS_WIN_WIDTH *0.5-15, "[Press backspace again to quit]");
				// wrefresh(status_frame->window);

				print_center_frame(status_frame, "[Press backspace again to quit]");
				outline_frame(status_frame, overlay_frame, "*");

				int key = wgetch(dungeon_win);
				if(key == KEY_BACKSPACE || key == KEY_SLEFT)
					exit = true;

				clear_frame(status_frame);
				break;
		}
		// refresh screen
		wrefresh(dungeon_win);
	}
	//ends ncurses
	endwin();
	return 0;
}
