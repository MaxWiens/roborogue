#include <stdio.h>
#include "util/bool.h"
#include <ncurses.h>


int main(int argc, char const *argv[])
{
	const int SCREEN_WIDTH = 100;
	const int SCREEN_HEIGHT = 20;
	const int SCREEN_HEIGHT_HALF = SCREEN_HEIGHT*0.5;
	const int SCREEN_WIDTH_HALF = SCREEN_WIDTH*0.5;
	//initialises ncurses
	initscr();
	raw();
	noecho();

	WINDOW* win = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
	keypad(win, true);
	WINDOW* messageBox = newwin(1, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	bool exit = false;
	while(!exit){
		int input = wgetch(win);
		switch(input){
			//escape is pressed
			case KEY_BACKSPACE:
				mvwprintw(messageBox, 0,SCREEN_WIDTH_HALF-15, "[Press backspace again to quit]");
				wrefresh(messageBox);

				if(wgetch(win) == KEY_BACKSPACE)
					exit = true;

				wclear(messageBox);
				wrefresh(messageBox);
				break;
		}
		// refresh screen
		wrefresh(win);
	}
	//ends ncurses
	endwin();
	return 0;
}