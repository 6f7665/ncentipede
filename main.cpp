#include <ncurses.h>
#include <string>
#include <vector>


using namespace std;

int main(int argc, char** argv)
{
	WINDOW *main_win;
	int xpos, ypos, xsize, ysize;
	char ch;
	initscr();

	printw("\n\tCaterpillar\n\t\tken kanekis favourite...");
	refresh();

	ysize = 17;
	xsize = 32;

	ypos = (LINES - ysize) / 2;
	xpos = (COLS - xsize) / 2;
	curs_set(0);
	WINDOW *game_arena;
	game_arena = newwin(ysize, xsize, ypos, xpos);
	box(game_arena, 0 , 0);

	wrefresh(game_arena);

	ch = getch();
	delwin(game_arena);
	curs_set(1);
	endwin();

	return 0;
}
