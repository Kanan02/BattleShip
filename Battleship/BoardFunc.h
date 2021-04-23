#pragma once
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "Ships.h"
using namespace std;
const int SIDE = 10;
const char isWATER = 247; 
const char isHIT = 'X';
const char isSHIP = 'S';
const char isMISS = '0';
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
struct COMPUTER {
    char VISIBLE_BOARD[SIDE][SIDE];
    char REAL_BOARD[SIDE][SIDE];
};
/******FUNCTIONS FOR MOVEMENT*********/
void GoRight(char BOARD[][SIDE], int& i,int&j) {
    swap(BOARD[i][j], BOARD[i][j + 1]);
    j++;
}
void GoLeft(char BOARD[][SIDE], int& i,int& j) {
    swap(BOARD[i][j], BOARD[i][j - 1]);
    j--;
}
void GoUp(char BOARD[][SIDE], int& i, int& j) {
    swap(BOARD[i][j], BOARD[i-1][j]);
    i--;
}
void GoDown(char BOARD[][SIDE], int& i, int& j) {
    swap(BOARD[i][j], BOARD[i + 1][j]);
    i++;
}
/************************************/


/***************CHECK THE WIN****************/
bool win(char BOARD[SIDE][SIDE]) {
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++) {
            if (BOARD[i][j] == isSHIP) {
                return false;
            }
        }
    }
    return true;
}
/***************************************/


/****************GAME FUNCTIONS(HITS,SHOTS AND MISSES)***************************/
void create_random_point(char BOARD[][SIDE],int& i, int& j) {
    srand(time(NULL));
    while (true) {
        i = rand() % 10;
        j = rand() % 10;
        if(BOARD[i][j]==isWATER||BOARD[i][j]==isSHIP)break;
    }
}
void MakeMissesAroundShip(char BOARD[][SIDE], SHIP ship, int i, int j) {
    if (ship.direction == HORIZONTAL) {
        for (int k = 0; k < ship.length; k++)
        {
            if(ship.points[k].Y+1<=9)BOARD[ship.points[k].Y+1][ship.points[k].X ]=isMISS;
            if (ship.points[k].Y - 1 >= 0)BOARD[ship.points[k].Y-1][ship.points[k].X]=isMISS;
        }
        if (ship.points[0].X - 1 >= 0)BOARD[ship.points[0].Y][ship.points[0].X - 1]=isMISS;
        if (ship.points[0].X - 1 >= 0&&ship.points[0].Y - 1>=0)BOARD[ship.points[0].Y - 1][ship.points[0].X - 1] = isMISS;
        if (ship.points[0].X - 1 >= 0 && ship.points[0].Y + 1 <=9)BOARD[ship.points[0].Y + 1][ship.points[0].X - 1] = isMISS;

        if (ship.points[ship.length - 1].X + 1 <= 9)BOARD[ship.points[ship.length - 1].Y][ship.points[ship.length - 1].X + 1] = isMISS;
        if (ship.points[ship.length - 1].X + 1 <= 9&&ship.points[ship.length-1].Y-1>=0)BOARD[ship.points[ship.length - 1].Y - 1][ship.points[ship.length - 1].X + 1] = isMISS;
        if (ship.points[ship.length - 1].X + 1 <= 9 && ship.points[ship.length - 1].Y + 1 <= 9)BOARD[ship.points[ship.length - 1].Y + 1][ship.points[ship.length - 1].X + 1] = isMISS;
    }
    else if (ship.direction == VERTICAL) {
        for (int k = 0; k < ship.length; k++)
        {
            if (ship.points[k].X + 1 <= 9)BOARD[ship.points[k].Y][ship.points[k].X+1] = isMISS;
            if (ship.points[k].X - 1 >= 0)BOARD[ship.points[k].Y][ship.points[k].X-1] = isMISS;
        }
        if (ship.points[0].Y - 1 >= 0)BOARD[ship.points[0].Y-1][ship.points[0].X] = isMISS;
        if (ship.points[0].Y - 1 >= 0 && ship.points[0].X - 1 >= 0)BOARD[ship.points[0].Y - 1][ship.points[0].X - 1] = isMISS;
        if (ship.points[0].Y - 1 >= 0 && ship.points[0].X + 1 <= 9)BOARD[ship.points[0].Y - 1][ship.points[0].X + 1] = isMISS;

        if (ship.points[ship.length - 1].Y + 1 <= 9)BOARD[ship.points[ship.length - 1].Y + 1][ship.points[ship.length - 1].X] = isMISS;
        if (ship.points[ship.length - 1].Y + 1 <= 9 && ship.points[ship.length - 1].X - 1 >= 0)BOARD[ship.points[ship.length - 1].Y + 1][ship.points[ship.length - 1].X - 1] = isMISS;
        if (ship.points[ship.length - 1].Y + 1 <= 9 && ship.points[ship.length - 1].X + 1 <= 9)BOARD[ship.points[ship.length - 1].Y + 1][ship.points[ship.length - 1].X + 1] = isMISS;

    }
    else {
        if (ship.points[0].X + 1 <= 9)BOARD[ship.points[0].Y][ship.points[0].X + 1] = isMISS;
        if (ship.points[0].X + 1 <= 9 && ship.points[0].Y + 1 <= 9)BOARD[ship.points[0].Y+1][ship.points[0].X + 1] = isMISS;
        if (ship.points[0].X + 1 <= 9 && ship.points[0].Y - 1 >= 0)BOARD[ship.points[0].Y-1][ship.points[0].X + 1] = isMISS;

        if (ship.points[0].X - 1 >= 0)BOARD[ship.points[0].Y][ship.points[0].X - 1] = isMISS;
        if (ship.points[0].X - 1 >= 0 && ship.points[0].Y + 1 <= 9)BOARD[ship.points[0].Y + 1][ship.points[0].X - 1] = isMISS;
        if (ship.points[0].X - 1 >= 0 && ship.points[0].Y - 1 >= 0)BOARD[ship.points[0].Y - 1][ship.points[0].X - 1] = isMISS;

        if (ship.points[0].Y + 1 <= 9)BOARD[ship.points[0].Y + 1][ship.points[0].X] = isMISS;
        if (ship.points[0].Y - 1 >= 0)BOARD[ship.points[0].Y - 1][ship.points[0].X] = isMISS;
    }
}
bool isDrawn(char BOARD[][SIDE], SHIP ships[], int i, int j) {
    for (int k = 0; k < SHIP_TYPES; k++)
    {
        for (int l = 0; l < ships[k].length; l++) {
            if (i == ships[k].points[l].Y && j == ships[k].points[l].X) {
                if (ships[k].hits == ships[k].length) {
                    MakeMissesAroundShip(BOARD, ships[k], i, j);
                    return true;
                }
            }
        }
    }
    return false;
}
void add_hit(SHIP ships[SHIP_TYPES],int i, int j) {
    for (int k = 0; k < SHIP_TYPES; k++)
    {
        
        for (int l = 0; l < ships[k].length;l++) {
            if (i ==ships[k].points[l].Y &&j==ships[k].points[l].X){
                ships[k].hits++;
                
                break;
            }
            

        }
        
        
    }
}
void RandomShot(char BOARD[][SIDE], bool& pc_turn) {
    int i, j;
    create_random_point(BOARD, i, j);

    if (BOARD[i][j] == isSHIP) {
        BOARD[i][j] = isHIT;
        add_hit(my_ships, i, j);
        pc_turn = true;
        if (win(BOARD)) {
            pc_turn = false;
        }
        
        if (isDrawn(BOARD, my_ships, i, j)) {
            
        }
        else {
            
        }
        
    }
    else if (BOARD[i][j] == isWATER) {
        BOARD[i][j] = isMISS;

        pc_turn = false;
    }

}
void SmartShot(char BOARD[][SIDE], bool& pc_turn, int& i, int& j) {
    if (BOARD[i][j] == isSHIP) {
        pc_turn = true;
        
        BOARD[i][j] = isHIT;
        add_hit(my_ships, i, j);
        if (win(BOARD)) {
            pc_turn = false;
        }
        if (isDrawn(BOARD, my_ships, i, j)) {

        }
        else {

        }
        
  
        for (int k = 0; k < SHIP_TYPES; k++)
        {
            if (!pc_turn) { break; }
            for (int l = 0; l < my_ships[k].length; l++) {
                if (i == my_ships[k].points[l].Y && j == my_ships[k].points[l].X) {
                    /******************************************/
                    if (my_ships[k].direction == VERTICAL) {
                        if (i + 1 <= 9 ) {
                            i = i + 1;
                        }
                        else if (i - 1 >= 0 ) {
                            i = i - 1;
                        }
                        else if (i + 2 <= 9 ) {
                            i = i + 2;
                        }
                        else if (i + 3 <= 9) {
                            i = i + 3;
                        }

                        else if (i - 2 >= 0 ) {
                            i = i - 2;
                        }
                        else if (i - 3 >= 0) {
                            i = i - 3;
                        }
                    }
                    else if (my_ships[k].direction == HORIZONTAL) {
                        if (j + 1 <= 9) {
                            j = j + 1;
                        }
                        else if (j - 1 >= 0 ) {
                            j=j-1;
                        }
                        else if (j + 2 <= 9 ) {
                            j = j + 2;
                        }

                        else if (j + 3 <= 9 ) {
                            j = j + 3;
                        }

                        else if (j - 2 >= 0 ) {
                            j = j - 2;
                        }

                        else if (j - 3 >= 0 ) {
                            j = j - 3;
                        }

                    }
                    else if (my_ships[k].direction == NONE) {
                        create_random_point(BOARD, i, j);
                    }

                }
                break;
            }
        }
    }
    else if (BOARD[i][j] == isWATER) {
        BOARD[i][j] = isMISS;
        create_random_point(BOARD, i, j);
        
        pc_turn = false;
    }
    else {
        create_random_point(BOARD, i, j);
        pc_turn = false;
        
    }
}
/************************************************************/

/***************PRINT AND INITIALIZE BOARDS*********************/
void ShowBoardByPosition(char board[][SIDE],HANDLE hConsole,COORD pos) {
    pos = { 50,3 };
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, 240);
    cout << "   ";
    for (int i = 0; i < SIDE; i++)
    {
        cout << i << " ";
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << endl;
    for (int i = 0; i < SIDE; i++)
    {
        pos = { 50,(short)i+4 };
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, 240);
        cout <<" "<< i << " ";
        SetConsoleTextAttribute(hConsole, 15);
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == isSHIP)SetConsoleTextAttribute(hConsole, 22);
            if (board[i][j] == isHIT)SetConsoleTextAttribute(hConsole, 28);
            if (board[i][j] == isMISS)SetConsoleTextAttribute(hConsole, 17);
            if (board[i][j] == isWATER)SetConsoleTextAttribute(hConsole, 25);
            cout << board[i][j] << " ";
            SetConsoleTextAttribute(hConsole, 15);

        }
        cout << endl;
    }
}
void ShowBoard(char board[][SIDE]) {
    cout << "     ";
    SetConsoleTextAttribute(hConsole, 240);
    cout << "   ";
    for (int i = 0; i < SIDE; i++)
    {
        cout <<i << " ";
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << endl;
    for (int i = 0; i < SIDE; i++)
    {
        
        cout << "     ";
        SetConsoleTextAttribute(hConsole, 240);
        cout<<" "<<i << " ";
        SetConsoleTextAttribute(hConsole, 15);
        for (int j = 0; j < SIDE; j++)
        {
            if(board[i][j]==isSHIP)SetConsoleTextAttribute(hConsole, 22);
            if (board[i][j] == isHIT)SetConsoleTextAttribute(hConsole, 28);
            if (board[i][j] == isMISS)SetConsoleTextAttribute(hConsole, 17);
            if (board[i][j] == isWATER)SetConsoleTextAttribute(hConsole, 25);
            if (board[i][j] == '?')SetConsoleTextAttribute(hConsole, 31);
            cout << board[i][j] << " ";
            SetConsoleTextAttribute(hConsole, 15);
        }
        cout << endl;
    }
}
void InitializeBoard(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {

            board[i][j] = isWATER;
        }
    }
}
/************************************************************/


/**************PLACE THE SHIPS ON BOARDS***************************************/
bool isValid(SHIP ship,char BOARD[SIDE][SIDE]) {
    //check if the length is ok
    
    if (ship.direction == HORIZONTAL && ship.p.X + ship.length - 1 > 9)return false;
    else if (ship.direction == VERTICAL && ship.p.Y + ship.length - 1 > 9)return false;
    
    for (int i = 0; i < ship.length; i++)
    {
            if (ship.direction == HORIZONTAL) {
            //if the ship is inside other ship
            if (BOARD[ship.p.Y][ship.p.X + i] == isSHIP)return false;
            //if the ship is somewhere near
            if (BOARD[ship.p.Y + 1][ship.p.X + i] == isSHIP)return false;
            if (BOARD[ship.p.Y - 1][ship.p.X + i] == isSHIP)return false;
           
            if (ship.p.X > 0) {
                if (BOARD[ship.p.Y][ship.p.X - 1] == isSHIP)return false;
                if (BOARD[ship.p.Y - 1][ship.p.X - 1] == isSHIP)return false;
                if (BOARD[ship.p.Y + 1][ship.p.X - 1] == isSHIP)return false;
            }
            if (ship.p.X + ship.length <= 9) {
                if (BOARD[ship.p.Y][ship.p.X + ship.length] == isSHIP)return false;
                if (BOARD[ship.p.Y - 1][ship.p.X + ship.length] == isSHIP)return false;
                if (BOARD[ship.p.Y + 1][ship.p.X + ship.length] == isSHIP)return false;
            }
        }
        else if (ship.direction == VERTICAL) {
            //if the ship is inside other ship
            if (BOARD[ship.p.Y + i][ship.p.X] == isSHIP)return false;
            //if the ship is somewhere near
            if (BOARD[ship.p.Y + i][ship.p.X + 1] == isSHIP)return false;
            if (BOARD[ship.p.Y + i][ship.p.X - 1] == isSHIP)return false;
            
            if (ship.p.Y > 0) {
                if (BOARD[ship.p.Y - 1][ship.p.X] == isSHIP)return false;
                if (BOARD[ship.p.Y - 1][ship.p.X - 1] == isSHIP)return false;
                if (BOARD[ship.p.Y - 1][ship.p.X + 1] == isSHIP)return false;
            }
            if (ship.p.Y + ship.length <= 9) {
                if (BOARD[ship.p.Y + ship.length][ship.p.X - 1] == isSHIP)return false;
                if (BOARD[ship.p.Y + ship.length][ship.p.X + 1] == isSHIP)return false;
                if (BOARD[ship.p.Y + ship.length][ship.p.X] == isSHIP)return false;
            }
        }
        else {
            if (BOARD[ship.p.Y][ship.p.X] == isSHIP)return false;
            if (ship.p.Y < 9)if (BOARD[ship.p.Y + 1][ship.p.X] == isSHIP)return false;
            if (ship.p.X < 9)if (BOARD[ship.p.Y][ship.p.X + 1] == isSHIP)return false;
            if (ship.p.X > 0)if (BOARD[ship.p.Y][ship.p.X - 1] == isSHIP)return false;
            
            if (ship.p.Y > 0)if (BOARD[ship.p.Y-1][ship.p.X] == isSHIP)return false;
            if (ship.p.Y > 0 && ship.p.X>0)if (BOARD[ship.p.Y-1][ship.p.X-1] == isSHIP)return false;
            if (ship.p.Y > 0 && ship.p.X < 9)if (BOARD[ship.p.Y-1][ship.p.X+1] == isSHIP)return false;
            if (ship.p.Y <9 && ship.p.X <9)if (BOARD[ship.p.Y+1][ship.p.X+1] == isSHIP)return false;
            if (ship.p.Y <9 && ship.p.X > 0)if (BOARD[ship.p.Y+1][ship.p.X-1] == isSHIP)return false;
            
        }
    }
    return true;

    }
void input_ship(SHIP& ship, char BOARD[SIDE][SIDE]) {
    if (ship.direction == HORIZONTAL) {

        for (int i = 0; i < ship.length; i++){
            
            BOARD[ship.p.Y][ship.p.X + i] = isSHIP;
            
            ship.points[i].X = ship.p.X + i;
            ship.points[i].Y = ship.p.Y ;
           
            }
        
        }
    else if (ship.direction == VERTICAL) {

        for (int i = 0; i < ship.length; i++)
        {
            
            BOARD[ship.p.Y + i][ship.p.X] = isSHIP;
            ship.points[i].X = ship.p.X;
            ship.points[i].Y = ship.p.Y + i;

        }
    }
    else if (ship.direction==NONE){
        BOARD[ship.p.Y][ship.p.X] = isSHIP;
        ship.points[0].X = ship.p.X;
        ship.points[0].Y = ship.p.Y;

    }
}
void PlaceRandomShips(char BOARD[][SIDE],SHIP ships[]) {
    srand(time(NULL));
    for (int i = 0; i < SHIP_TYPES; i++)
    {
        //Choose direction
        if (ships[i].length > 1) {
            int dir = rand() % 2;
            ships[i].direction = (DIRECTION)dir;

            ships[i].p.X = rand() % 10;
            ships[i].p.Y = rand() % 10;

            while (!isValid(ships[i], BOARD)) {
                int dir = rand() % 2;
                ships[i].direction = (DIRECTION)dir;
                ships[i].p.X = rand() % 10;
                ships[i].p.Y = rand() % 10;
            }
           
        }
        else {
            ships[i].direction = NONE;
            ships[i].p.X = rand() % 10;
            ships[i].p.Y = rand() % 10;
            while (!isValid(ships[i], BOARD)) {
                ships[i].p.X = rand() % 10;
                ships[i].p.Y = rand() % 10;
            }
        }
        input_ship(ships[i], BOARD);
    }
}

void PlaceMyRandomShips(char BOARD[][SIDE], SHIP ships[]) {
    srand(time(NULL));
    for (int i = 0; i < SHIP_TYPES; i++)
    {
        //Choose direction
        if (ships[i].length > 1) {
            int dir = rand() % 2;
            ships[i].direction = (DIRECTION)dir;

            ships[i].p.X = rand() % 10;
            ships[i].p.Y = rand() % 10;

            while (!isValid(ships[i], BOARD)) {
                int dir = rand() % 2;
                ships[i].direction = (DIRECTION)dir;
                ships[i].p.X = rand() % 10;
                ships[i].p.Y = rand() % 10;
            }

        }
        else {
            ships[i].direction = NONE;
            ships[i].p.X = rand() % 10;
            ships[i].p.Y = rand() % 10;
            while (!isValid(ships[i], BOARD)) {
                ships[i].p.X = rand() % 10;
                ships[i].p.Y = rand() % 10;
            }
        }
        input_ship(ships[i], BOARD);
    }
}
/*****************************************************************************/