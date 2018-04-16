#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <ncurses.h>
#include <utility>
#include <limits>
#include <vector>
#include <queue>
#include <set>
#include "splash.h"
#include "inheritance.h"
using namespace std;

class Fire; 

const unsigned char GRASS = ','; //Grass, the bassline plant, fills open spots
const unsigned char WALL = '#';  //A wall space; impassable
const unsigned char WATER = '~'; //Water, cannot burn
const unsigned char TREE = 'T';  //A tree, burns longer than grass
const unsigned char BUSH = '*';  //A bush, doesn't bun as long as a tree, plus high chance to ignite **maybe causes spaces around it to immidiatley combust
const unsigned char FIRE = 'F';  //Fire, ignites the spaces around it and burns for a limited amount of time
const unsigned char ASH = '.';   //What remains when a fire goes out

//Globals holding game state
int SIZE_X,SIZE_Y; //Dimensions of the world
int cursor_x, cursor_y; //Cursor for drawing stuff
unsigned char* world; //A character array holding our world
vector<Fire> ff;
int ash_count = 0;
int tree_count = 0;
int bush_count = 0;
bool game_on; //Holds if the simulation is running

const unsigned int MIN_SIZE = 8; //Minimum size of the world
const unsigned int TIMEOUT = 300; //Milliseconds to wait for a getch to finish
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;

//2D to 1D array mapping
//NOTE: creates a circular array
//For example, access the world location (3,2) like this:
//  world[index(3,2)]
int index(int i, int j) {
	while (i < 0) i+=SIZE_X;
	while (j < 0) j+=SIZE_Y;
	if (i >= SIZE_X) i %= SIZE_X;
	if (j >= SIZE_Y) j %= SIZE_Y;
	return (i*SIZE_Y+j);
}

class Fire {
	public:
		Fire () {}
		Fire (int new_x, int new_y) : x(new_x), y(new_y) {}
		int x = 0, y = 0; //Location
		int chance; //chance each frame to spread
		int spread_radius = 1; //Fire can only spread to an adjacent square
		int burntime = 10;
		bool out = false;
		void think() { //AI For fire
				if (out) return;
				int new_x = x + (rand() % (1 + spread_radius * 2)) - spread_radius; //Between -1 and +1 offset
				int new_y = y + (rand() % (1 + spread_radius * 2)) - spread_radius; //Between -1 and +1 offset

				//three different checks for the plant that is burning
				if (world[index(new_x,new_y)] == GRASS) {
					chance = 20;
					if (rand() % 100 < chance) {
						world[index(new_x,new_y)] = FIRE; //Mark the spot on the map
						ff.push_back(Fire(new_x,new_y)); //Add fire to the fire vector
						burntime = 10;
					}
				}
				if (world[index(new_x,new_y)] == TREE) {
					chance = 50;
					if (rand() % 100 < chance) {
						world[index(new_x,new_y)] = FIRE;
						ff.push_back(Fire(new_x,new_y));
						burntime = 20;
						tree_count --;
					}
				}
				if (world[index(new_x,new_y)] == BUSH) {
	                chance = 40;
					if (rand() % 100 < chance) {
						world[index(new_x,new_y)] = FIRE;
						ff.push_back(Fire(new_x,new_y));
						burntime = 15;
						bush_count --;
					}
				}

				burntime--;

				if (burntime < 0) { //see if fire is out
					out = true;
					return;
				}
		}

};

//Builds an empty world with walls on the edges and open squares in the middle
//Randomly populate it with trees, bushes, fires.
const int TREE_PERCENTAGE = 10;
const int BUSH_PERCENTAGE = 5;
const int FIRE_PERCENTAGE = 2;
void reset_world() {
	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
			if (i == 0 || j == 0 || i == SIZE_X - 1 || j == SIZE_Y - 1) //Is edge
				world[index(i,j)] = WALL;
			else
				world[index(i,j)] = GRASS;
			//Put a lake in the center
			if ( (i == SIZE_X / 2 || i == SIZE_X/2 - 1 || i == SIZE_X/2 + 1) &&
					(j == SIZE_Y / 2 || j == SIZE_Y/2 - 1 || j == SIZE_Y/2 + 1) )
				world[index(i,j)] = WATER;

			//Now populate it with stuff
			if (world[index(i,j)] == GRASS && rand() % 100 < TREE_PERCENTAGE) {
				world[index(i,j)] = TREE;
				tree_count++;
			}
			else if (world[index(i,j)] == GRASS && rand() % 100 < BUSH_PERCENTAGE) {
				world[index(i,j)] = BUSH;
				bush_count++;
			}
			else if (world[index(i,j)] == GRASS && rand() % 100 < FIRE_PERCENTAGE) {
				world[index(i,j)] = FIRE;
				ff.push_back(Fire(i,j));
			}
		}
	}
}

//Prints the entire world, bolding the square the cursor is on
void print_world() {
	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
			if (i == cursor_x && j == cursor_y)
				attron(A_UNDERLINE | A_BOLD);
			int color = 1; 
			if (world[index(i,j)] == WALL)
				color = 6;
			else if (world[index(i,j)] == GRASS)
				color = 4;
			else if (world[index(i,j)] == WATER)
				color = 2;
			else if (world[index(i,j)] == TREE)
				color = 3;
			else if (world[index(i,j)] == BUSH)
				color = 3;
			else if (world[index(i,j)] == FIRE)
				color = 5;
			attron(COLOR_PAIR(color));
			mvaddch(i,j,world[index(i,j)]);
			attroff(COLOR_PAIR(color));
			attroff(A_UNDERLINE | A_BOLD);
		}
	}
}

int main()
{
	//Initialize random number generator
	srand(time(NULL));

	cout << "How big a world do you want? (Enter x size followed by y then hit return): ";
	cin >> SIZE_Y >> SIZE_X; //Everything is backwards (x and y) in NCURSES
	if (!cin || SIZE_X < MIN_SIZE || SIZE_Y < MIN_SIZE) {
		cout << "Error: world size must be at least " << MIN_SIZE << " in each dimension.\n";
		return 1;
	}

	//Set up NCURSES
	initscr();//Start curses mode
	start_color(); //Enable Colors if possible
	init_pair(1,COLOR_WHITE,COLOR_BLACK); //Set up some color pairs
	init_pair(2,COLOR_CYAN,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	init_pair(6,COLOR_MAGENTA,COLOR_BLACK);

	clear();
	noecho();
	cbreak();
	timeout(TIMEOUT); //Set a max delay for key entry

	//Splash Screen
	splash();
	timeout(TIMEOUT); //Set a max delay for key entry
	clear();

	world = new unsigned char[SIZE_X * SIZE_Y];
	reset_world();

	//MAIN LOOP
	int frame = 0;
	cursor_x = SIZE_X/2, cursor_y = SIZE_Y/2; //Cursor for drawing stuff
	game_on = false;
	while (true) {
		if (!game_on) 
			mvprintw(SIZE_X,0,"Design Mode - Game Paused                                        ");
		else
			mvprintw(SIZE_X,0,"Game Running. Fires: %i Trees: %i Bushes: %i Spots burned: %i  Frame: %i",ff.size(), tree_count, bush_count, ash_count, frame++);
		mvprintw(SIZE_X+1,0,"Use arrow keys to move the cursor around");
		mvprintw(SIZE_X+2,0,"Type Space to clear the square or set a wall");
		mvprintw(SIZE_X+3,0,"Type ~ to place a water");
		mvprintw(SIZE_X+4,0,"Type + to place a bush");
		mvprintw(SIZE_X+5,0,"Type T to place an Tree");
		mvprintw(SIZE_X+6,0,"Type F to place an ignition point");
		mvprintw(SIZE_X+7,0,"Type Enter to run or pause the game");
		mvprintw(SIZE_X+8,0,"Type Q to quit");
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') break;
		else if (ch == ' ' || ch == '#') {
			if (world[index(cursor_x,cursor_y)] == GRASS)
				world[index(cursor_x,cursor_y)] = WALL;
			else if (world[index(cursor_x,cursor_y)] == WALL)
				world[index(cursor_x,cursor_y)] = GRASS;
			//TODO: Be able to clear other things from the world
		}
		else if (ch == 'T' || ch == '1') {
			if (world[index(cursor_x,cursor_y)] == GRASS) {
				world[index(cursor_x,cursor_y)] = TREE;
				tree_count++;
			}
		}
		else if (ch == '=' || ch == '+') {
			if (world[index(cursor_x,cursor_y)] == GRASS) {
				world[index(cursor_x,cursor_y)] = BUSH;
				bush_count++;
			}
		}
		else if (ch == 'f' || ch == 'F') {
			if (world[index(cursor_x,cursor_y)] == GRASS) {
				world[index(cursor_x,cursor_y)] = FIRE;
				ff.push_back(Fire(cursor_x,cursor_y));
			}
		}
		else if (ch == '`' || ch == '~') {
			if (world[index(cursor_x,cursor_y)] == GRASS) {
				world[index(cursor_x,cursor_y)] = WATER;
			}
		}
		//Handle arrow keys, the NCURSES #defs don't work here for some reason
		//KEY_UP, for example, is set to 0403 (259), not 65
		else if (ch == RIGHT) { 
			cursor_y++;
			if (cursor_y >= SIZE_Y) cursor_y = SIZE_Y - 1; //Clamp value
		}
		else if (ch == LEFT) {
			cursor_y--;
			if (cursor_y < 0) cursor_y = 0; 
		}
		else if (ch == UP) { //Should be KEY_UP, grr
			cursor_x--;
			if (cursor_x < 0) cursor_x = 0;
		}
		else if (ch == DOWN) {
			cursor_x++;
			if (cursor_x >= SIZE_X) cursor_x = SIZE_X - 1; //Clamp value
		}
		else if (ch == ERR) { //No keystroke
			; //Do nothing
		} 
		else if (ch == '\n') {
			game_on = !game_on; //Pause or unpause the game
		}
		//else
		//mvprintw(SIZE_Y+5,0,"Unknown character: %i\n",ch);

		//Run the AI
		if (game_on) {
			for (Fire &h : ff) {
				h.think();
			}
		}
			//Clean up at most one corpse per frame, since the iterator goes invalid after erase
			//TODO: Fix this so it cleans up all corpses
			auto iter = ff.begin();
			while (iter != ff.end()) {
				if (iter->out) {
					world[index(iter->x,iter->y)] = ASH;
					ff.erase(iter);
					ash_count++;
					//iter = ff.begin();
		
				}
				iter++;
			}

		//Redraw the screen
		clear();
		print_world();
		refresh(); 
	}
	clear();
	print_world();
	refresh();
	wait_ticks(300000);
	endwin(); // End curses mode
	system("clear");

	return 0;

}
