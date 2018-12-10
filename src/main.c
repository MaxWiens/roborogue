#include <stdio.h>
#include "util/bool.h"
#include "gui/frame.h"
#include <ncurses.h>
#include <stdlib.h>
#include<time.h>

//debug
#include "collections/linkedlist.h"
#include "dungeon/generate.h"
#include "dungeon/dungeon.h"
//end debug


#define DUNGEON_WIN_WIDTH 100
#define DUNGEON_WIN_HEIGHT 25

#define STATUS_WIN_WIDTH 100
#define STATUS_WIN_HEIGHT 5

#define INVENTORY_WIN_WIDTH 50
#define INVENTORY_WIN_HEIGHT 15

#define INFO_WIN_WIDTH 50
#define INFO_WIN_HEIGHT 15

/* IMPORTANT NOTE: For an ideal experience, this assumes the user's window
				   is at least 150 x 30. */

#define MAX_WIDTH 150
#define MAX_HEIGHT 30


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
	#define SCREEN_WIDTH 100
	#define SCREEN_HEIGHT 20
	const int SCREEN_HEIGHT_HALF = SCREEN_HEIGHT*0.5;
	const int SCREEN_WIDTH_HALF = SCREEN_WIDTH*0.5;
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


	/* Title Screen */
	WINDOW* title_win = newwin(MAX_HEIGHT, MAX_WIDTH, top_scr_offset, right_scr_offset);
	Frame* title_frame = new_frame(title_win, MAX_HEIGHT, MAX_WIDTH, top_scr_offset, right_scr_offset);

	keypad(title_win, true);
	bool start_menu = true;

	int splash_y = 5;
	while (start_menu){
		outline_frame(title_frame);
	 //  _____       _
	 // |  __ \     | |
	 // | |__) |___ | |__   ___  _ __ ___   __ _ _   _  ___
	 // |  _  // _ \| '_ \ / _ \| '__/ _ \ / _` | | | |/ _ \
	 // | | \ \ (_) | |_) | (_) | | | (_) | (_| | |_| |  __/
	 // |_|  \_\___/|_.__/ \___/|_|  \___/ \__, |\__,_|\___|
	 //                                     __/ |
	 //                                    |___/

	 	// print splash screen

		mvwprintw(title_frame->window, splash_y, 2,    " _____       _");
		mvwprintw(title_frame->window, splash_y+1, 2, "|  __ \\     | |");
		mvwprintw(title_frame->window, splash_y+2, 2, "| |__) |___ | |__   ___  _ __ ___   __ _ _   _  ___");
		mvwprintw(title_frame->window, splash_y+3, 2, "|  _  // _ \\| '_ \\ / _ \\| '__/ _ \\ / _` | | | |/ _ \\");
		mvwprintw(title_frame->window, splash_y+4, 2, "| | \\ \\ (_) | |_) | (_) | | | (_) | (_| | |_| |  __/");
		mvwprintw(title_frame->window, splash_y+5, 2, "|_|  \\_\\___/|_.__/ \\___/|_|  \\___/ \\__, |\\__,_|\\___|");
		mvwprintw(title_frame->window, splash_y+6, 2, "                                    __/ |           ");
		mvwprintw(title_frame->window, splash_y+7, 2, "                                   |___/            ");

		mvwprintw(title_frame->window, splash_y+10, 5, "Press [p] to begin.");

	 	int input = wgetch(title_win);
	 	switch (input) {
		 	case 'p':
		 		start_menu = false;
				clear_frame(title_frame);
				break;

	 	}
		wrefresh(title_win);
	}
	delwin(title_win);


	/* "Log-IN" screen. */
	/*char username[20]; // this shall be used to form the seed
	WINDOW* login_win = newwin(MAX_HEIGHT, MAX_WIDTH, top_scr_offset, right_scr_offset);
	Frame* login_frame = new_frame(login_win, MAX_HEIGHT, MAX_WIDTH, top_scr_offset, right_scr_offset);

	keypad(login_win, true);
	bool login_menu = true;

	int login_y = 10;
	// while (login_menu) {
	outline_frame(login_frame);

	mvwprintw(login_frame->window,login_y, 2, "Enter a seed: ");
	mvwprintw(login_frame->window,login_y+1, 2, "roboshell>");
	wrefresh(login_frame->window);

	nodelay(stdscr, true);
	wgetstr(login_frame->window, username);
	mvwprintw(login_frame->window, login_y+2, 2, "Welcome %s", username);
	wmove(login_frame->window, login_y+2, 20);

	clear_frame(login_frame);
	outline_frame(login_frame);
	wrefresh(login_frame->window);
	while (login_menu) {
		mvwprintw(login_frame->window, login_y, 2, "Press [p] to play.");

		int input  = wgetch(login_frame->window);
		switch (input) {
			case 'p':
				clear_frame(login_frame);
				login_menu = false;
				break;
			}
		wrefresh(login_frame->window);
		}

	delwin(login_win);*/

	// Leaving out "log in" system for now.


	// create windows
	WINDOW* dungeon_win = newwin(DUNGEON_WIN_HEIGHT, DUNGEON_WIN_WIDTH, top_scr_offset, right_scr_offset);
	WINDOW* status_win = newwin(STATUS_WIN_HEIGHT, STATUS_WIN_WIDTH, top_scr_offset + DUNGEON_WIN_HEIGHT, right_scr_offset);
	WINDOW* inventory_win = newwin(INVENTORY_WIN_HEIGHT, INVENTORY_WIN_WIDTH, top_scr_offset, right_scr_offset + DUNGEON_WIN_WIDTH);
	WINDOW* info_win = newwin(INFO_WIN_HEIGHT, INFO_WIN_WIDTH, top_scr_offset + INVENTORY_WIN_HEIGHT, right_scr_offset + STATUS_WIN_WIDTH);

	// create frames for the windows
	Frame* dungeon_frame = new_frame(dungeon_win, DUNGEON_WIN_HEIGHT, DUNGEON_WIN_WIDTH, top_scr_offset, right_scr_offset);
	Frame* status_frame = new_frame(status_win, STATUS_WIN_HEIGHT, STATUS_WIN_WIDTH, top_scr_offset + DUNGEON_WIN_HEIGHT, right_scr_offset);
	Frame* inventory_frame = new_frame(inventory_win, INVENTORY_WIN_HEIGHT, INVENTORY_WIN_WIDTH, top_scr_offset, right_scr_offset + DUNGEON_WIN_WIDTH);
	Frame* info_frame = new_frame(info_win, INFO_WIN_HEIGHT, INFO_WIN_WIDTH, top_scr_offset + INVENTORY_WIN_HEIGHT, right_scr_offset + STATUS_WIN_WIDTH);

	//debug
	srand(time(0));


	Dungeon* dungeon = generate(1);
	char arr[DUNGEON_HEIGHT][DUNGEON_WIDTH];

	print_dungeon(dungeon, arr);

	for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < DUNGEON_WIDTH; ++x) {
			mvwprintw(dungeon_win,y,x, "%c", arr[y][x]);
			wrefresh(dungeon_win);
		}
	}
	//end debug


	/* Game Logic */

	keypad(dungeon_win, true);
	bool exit = false;
	while(!exit){

		//outline every window frame
		outline_frame(dungeon_frame);
		outline_frame(status_frame);
		outline_frame(inventory_frame);
		outline_frame(info_frame);

		int input = wgetch(dungeon_win);

		switch(input){
			//escape is pressed
			case KEY_SLEFT:
			case KEY_BACKSPACE:

				print_center_frame(status_frame, "[Press backspace again to quit]");

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
