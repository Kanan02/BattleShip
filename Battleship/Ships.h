#pragma once
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
using namespace std;
struct point {
	//A location on the grid defined
	//by X(horizontal) Y(vertical) coordinates
	int X;
	int Y;
};
enum DIRECTION { HORIZONTAL, VERTICAL,NONE };

struct SHIP {
	//Ship name
	string name;
	//Total points on the grid
	int length;
	//Coordinates of those points
	point p;
	point points[4];
	DIRECTION direction;
	int hits;
};


const int SHIP_TYPES = 10;
SHIP pc_ships[SHIP_TYPES],my_ships[SHIP_TYPES];
void LoadShips() {
	pc_ships[0].name = "Battleship"; pc_ships[0].length = 4;
	pc_ships[1].name = "Cruiser"; pc_ships[1].length = 3;
	pc_ships[2].name = "Cruiser"; pc_ships[2].length = 3;
	pc_ships[3].name = "Destroyer"; pc_ships[3].length = 2;
	pc_ships[4].name = "Destroyer"; pc_ships[4].length = 2;
	pc_ships[5].name = "Destroyer"; pc_ships[5].length = 2;
	pc_ships[6].name = "Boat"; pc_ships[6].length = 1;
	pc_ships[7].name = "Boat"; pc_ships[7].length = 1;
	pc_ships[8].name = "Boat"; pc_ships[8].length = 1;
	pc_ships[9].name = "Boat"; pc_ships[9].length = 1;

	my_ships[0].name = "Battleship"; my_ships[0].length = 4;
	my_ships[1].name = "Cruiser"; my_ships[1].length = 3;
	my_ships[2].name = "Cruiser"; my_ships[2].length = 3;
	my_ships[3].name = "Destroyer"; my_ships[3].length = 2;
	my_ships[4].name = "Destroyer"; my_ships[4].length = 2;
	my_ships[5].name = "Destroyer"; my_ships[5].length = 2;
	my_ships[6].name = "Boat"; my_ships[6].length = 1;
	my_ships[7].name = "Boat"; my_ships[7].length = 1;
	my_ships[8].name = "Boat"; my_ships[8].length = 1;
	my_ships[9].name = "Boat"; my_ships[9].length = 1;
	for (int i = 0; i < 10; i++)
	{
		my_ships[i].hits = 0;
		pc_ships[i].hits = 0;
	}
}
