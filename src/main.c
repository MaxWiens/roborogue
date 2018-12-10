#include <stdio.h>
#include "util/bool.h"
#include <ncurses.h>
#include <stdlib.h>
#include<time.h>

//debug
#include "collections/linkedlist.h"
#include "dungeon/generate.h"
#include "dungeon/dungeon.h"
//end debug

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

	WINDOW* win = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
	keypad(win, true);
	WINDOW* messageBox = newwin(1, SCREEN_WIDTH, SCREEN_HEIGHT, 0);




	//debug
	srand(time(0));


	Dungeon* dungeon = generate(1);
	char arr[DUNGEON_HEIGHT][DUNGEON_WIDTH];

	print_dungeon(dungeon, arr);

	for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < DUNGEON_WIDTH; ++x) {
			mvwprintw(win,y,x, "%c", arr[y][x]);
			wrefresh(win);
		}
	}
	//end debug




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