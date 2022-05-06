#include <ncurses.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <locale.h>
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
	WINDOW *main_win;
	int xpos, ypos, xsize, ysize;
	char ch;
	setlocale(LC_ALL, "");
	initscr();

	cbreak();
	noecho();
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	printw("\n\tCentipede\n\tken kanekis favourite...");

	refresh();

	ysize = 17;
	xsize = 32;

	//game arena is 15x15 dots

	ypos = (LINES - ysize) / 2;
	xpos = (COLS - xsize) / 2;
	curs_set(0);

	int NewGame = 1;

	while(NewGame == 1)//create new game if game ends and user wants a new game in a loop
	{

	//-------------	Create new window for game
		WINDOW *game_arena;
		game_arena = newwin(ysize, xsize, ypos, xpos);
		box(game_arena, 0 , 0);	
		wrefresh(game_arena);

	//-------------	Game is running
		int GameState = 1; //setup for loop
		int y = 7;
		int x = 7;
		char direction = 'u';
		int length = 4; //initial lenght of centipede
		int genfood = 1; //generate food
		string score;

	//------------ create 2D vector and generate objects from tile class
		vector<vector <int> > sv
		{
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		};
		if(sv[y][x] <= 0)
		{
			sv[y][x] = 1;
		}
	//-------------	Start actual game
		while(GameState == 1)
		{
			switch(getch())
			{
				case 'q': GameState = 0; break; //stop game if q is pressed
				
				//vim keys
			//	case 'k': direction = 'u'; break;
			//	case 'j': direction = 'd'; break;
			//	case 'h': direction = 'l'; break;
			//	case 'l': direction = 'r'; break;
				//normal keys
				case 'w': direction = 'u'; break;
				case 's': direction = 'd'; break;
				case 'a': direction = 'l'; break;
				case 'd': direction = 'r'; break;
			}

			switch(direction)
			{
				case 'u': y--; break;
				case 'd': y++; break;
				case 'l': x--; break;
				case 'r': x++; break;
			}
		//-------------	Check for wall collision
			if((x <= -1) || (x >= 15) || (y <= -1) || (y >= 15))
			{
				GameState = 0; //crashed into wall, game over
				break;
			}
		//-------------	Crawl forward
			switch(sv[y][x])
			{
				case 0: sv[y][x] = 1; break; //nothing got eaten/coast is clear
				case -1: sv[y][x] = 1; length++; genfood = 1; break;
				default: GameState = 0; //you ate urself lol
			}
			score.assign("Score: ");
			score.append(to_string(length - 4));
			score.append("   ");
			move(ypos-1,xpos);
			printw(score.c_str());
			for( int i = 0; i < sv.size(); i++ )
			{
				for( int j = 0; j < sv.size(); j++ )
				{
					wmove(game_arena, i+1, (j*2)+1 );
					if(sv[i][j] == 0)
					{
						wprintw(game_arena, "  ");
					}
					else if(sv[i][j] >= length)
					{
						sv[i][j] = 0;
						wprintw(game_arena, "ZZ");
					}
					else if(sv[i][j] == -1)
					{
						//wprintw(game_arena, "\u98df");
						wprintw(game_arena, "FF");
					}
					else
					{
						sv[i][j]++;
						//wprintw(game_arena, "\u53e3");
						wprintw(game_arena, "SS");
					}
				}
			}
			while(genfood == 1)
			{
				srand(time(0));
				int a, b;
				a = rand()%14;
				b = rand()%14;

				     if( sv[a][b] == 0 ){ sv[a][b] = -1; genfood = 0; }
				else if( sv[b][a] == 0 ){ sv[b][a] = -1; genfood = 0; }
				else if( sv[a][a] == 0 ){ sv[a][a] = -1; genfood = 0; }
				else if( sv[b][b] == 0 ){ sv[b][b] = -1; genfood = 0; }
			}

			wrefresh(game_arena);
			napms(400-length);
		}
	//-------------	Remove window for game and open dialoge
		delwin(game_arena);
		move(2,3);
		printw("New Game?[y/n]                 ");
		NewGame = 2; //unset
		refresh();
		nodelay(stdscr, FALSE);
		while(NewGame == 2)
		{
			ch = getch();
			switch(ch)
			{
				case 'y': NewGame = 1; nodelay(stdscr, TRUE); move(2,3); printw("You sure like centipedes :D"); refresh(); break;
				case 'n': NewGame = 0; break; //this will break the loop and exit the program
			}
		}
	}
	curs_set(1);
	endwin();

	return 0;
}
