#include <stdio.h>
#include <ncurses.h> /* getch() and kbhit() */


int main(int argc, char const *argv[])
{
	//initialises ncurses
	initscr();
	raw();
	noecho();

	const int SCREEN_WIDTH = 100;
	const int SCREEN_HEIGHT = 20;
	WINDOW* win = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
	keypad(win, true);

	int x = 0;
	int y = 0;
	bool exit = false;
	//WINDOW* win = newwin(SCREEN_HEIGHT,SCREEN_WIDTH, 10,10);
	while(!exit){
		int input = wgetch(win);
		switch(input){

			case KEY_UP:
				y = y-1;
				break;
			case KEY_DOWN:
				y = y+1;
				break;
			case KEY_LEFT:
				x = x-1;
				break;
			case KEY_RIGHT:
				x = x+1;
				break;

			case KEY_BACKSPACE: //escape is pressed
				mvwprintw(win, SCREEN_HEIGHT*0.5,SCREEN_WIDTH*0.5-14, "[Press backspace again to quit]");
				//wrefresh(win);
				if(wgetch(win) == KEY_BACKSPACE)
					exit = true;
				else
					wclear(win);
				break;
		}
		mvwprintw(win, y,x, "0");
		// refresh screen
		wrefresh(win);
	}



	//ends ncurses
	endwin();
	return 0;
}