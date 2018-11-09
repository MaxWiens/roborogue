#include <stdio.h>
#include <conio.h> /* getch() and kbhit() */


int main(int argc, char const *argv[])
{
	while(1){
		if(kbhit()){
			char c = getch();
			if(c == '\n')
				printf("\n");
			else
				printf("%c", c);
		}
	};
	/*
	char c;

	for(;;){
		printf("hello\n");
		if(kbhit()){
			c = getch();d
			printf("%c\n", c);
		}
	}*/
	return 0;
}