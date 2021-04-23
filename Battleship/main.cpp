#include <iostream>
#include <time.h>
#include "BoardFunc.h"
#include "Ships.h"
#include <Windows.h>
#include <cwchar>
#include <conio.h>
using namespace std;
char MY_BOARD[SIDE][SIDE];

void main() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	int pc_regime;
	int choice=1;
	bool quit = false;
	while (choice == 1){

		COMPUTER pc;
		LoadShips();
		InitializeBoard(MY_BOARD);
		InitializeBoard(pc.REAL_BOARD);
		InitializeBoard(pc.VISIBLE_BOARD);
		PlaceRandomShips(pc.REAL_BOARD, pc_ships);

		cout << "Welcome to the battleship!\n";
		cout << "1.New Game\t 2.Exit\n";
		cin >> choice;
		while (choice > 2 || choice < 1) {
			cout << "You can choose only 1 or 2!\n";
			cin >> choice;
		}
		system("cls");
		if(choice==1){
			bool game = true;
			cout << "Choose the regime you want to play.\n";
			cout << "1.Random pc shots\t2.Smart pc shots\n";
			cin >> pc_regime;
			while (pc_regime > 2 || pc_regime < 1) {
				cout << "You can choose only 1 or 2!\n";
				cin >> pc_regime;
			}
			system("cls");
			cout << "How do you want to place your ships:\n";
			cout << "1.Manually\t2.Randomly\n";
			int placement;
			cin >> placement;
			while (placement > 2 || placement < 1) {
				cout << "You can choose only 1 or 2!\n";
				cin >> placement;
			}
			system("cls");
			if (placement == 1) {
				for (int i = 0; i < SHIP_TYPES; i++)
				{
					if (my_ships[i].length > 1) {
						//Loop through each ship type to place
						ShowBoard(MY_BOARD);
						//give instructions
						cout << "\t-------------\n\t|INSTUCTIONS|\n\t-------------\n";
						cout << "You are about to place your ships.  Format should be:\n";
						cout << "Facing (0:horizontal,1:vertical), x (top-row) coords, y (left-side) coords\n";
						cout << "Example: 0 7 2 ,  This would place a ship beginning at x:7 y:2 going horizontal\n";
						cout << "-------------------------------------------------------------------------------\n";
						cout << "Ship #" << i + 1 << " to place: " << my_ships[i].name << " which has a length of " << my_ships[i].length << "\n";
						cout << "Where do you want it placed? ";
						int d;
						cin >> d >> my_ships[i].p.X >> my_ships[i].p.Y;

						my_ships[i].direction = (DIRECTION)d;

						while (!isValid(my_ships[i], MY_BOARD)) {
							cout << "Not Valid Input! Read the instruction and place the ship again.\n";
							cin >> d >> my_ships[i].p.X >> my_ships[i].p.Y;
							my_ships[i].direction = (DIRECTION)d;
						}
						system("cls");
						input_ship(my_ships[i], MY_BOARD);



					}
					else {
						ShowBoard(MY_BOARD);
						//give instructions
						cout << "\t-------------\n\t|INSTUCTIONS|\n\t-------------\n";
						cout << "Now only Boats left, their length is 1\n";
						SetConsoleTextAttribute(hConsole, 12);
						cout << "Warning! Now you should enter only coordinates (x, y).\n";
						SetConsoleTextAttribute(hConsole, 15);
						cout << "Example:7 2 ,  This would place a ship at x:7 y:2 going horizontal\n";
						cout << "-------------------------------------------------------------------------------\n";
						cout << "Ship #" << i + 1 << " to place: " << my_ships[i].name << " which has a length of " << my_ships[i].length << "\n";
						cout << "Where do you want it placed? ";
						cin >> my_ships[i].p.X >> my_ships[i].p.Y;
						my_ships[i].direction = NONE;
						while (!isValid(my_ships[i], MY_BOARD)) {
							cout << "Not Valid Input! Read the instruction and place the ship again.\n";
							cin >> my_ships[i].p.X >> my_ships[i].p.Y;
						}
						system("cls");
						input_ship(my_ships[i], MY_BOARD);
					}
				}
			}
			else if (placement == 2) {
				PlaceMyRandomShips(MY_BOARD, my_ships);
			}
			int i_pc, j_pc;
			create_random_point(MY_BOARD, i_pc, j_pc);
			int i = 0, j = 0;
			pc.VISIBLE_BOARD[0][0] = '?';
			while (game) {
				cout << "\tLet's Start the game!(press ENTER to attack position, use arrows to choose target,";
				SetConsoleTextAttribute(hConsole, 12);
				cout << "press 'q' to quit";

				SetConsoleTextAttribute(hConsole, 15);
				cout << ").\n\n";
				COORD pos = { 53,2 };
				int ch;

				pos = { 0,3 };
				cout << "          Computer's Board\n";

				SetConsoleCursorPosition(hConsole, pos);

				ShowBoard(pc.VISIBLE_BOARD);
				pos = { 53,2 };
				SetConsoleCursorPosition(hConsole, pos);
				cout << "  Your board\n";
				ShowBoardByPosition(MY_BOARD, hConsole, pos);
				if (win(MY_BOARD)) {
					SetConsoleTextAttribute(hConsole, 4);
					pos = { 28,15 };
					SetConsoleCursorPosition(hConsole, pos);
					cout << "Unfortunately you lost! Good luck next time!\n";
					Sleep(3000);
					system("cls");
					SetConsoleTextAttribute(hConsole, 15);
					break;
				}
				if (win(pc.REAL_BOARD)) {
					SetConsoleTextAttribute(hConsole, 2);
					pos = { 27,15 };
					SetConsoleCursorPosition(hConsole, pos);

					cout << "Congratulations! You won!\n";
					pos = { 35,16 };
					SetConsoleCursorPosition(hConsole, pos);
					cout << "Good Game!\n";
					Sleep(3000);
					system("cls");
					SetConsoleTextAttribute(hConsole, 15);
					break;
				}
				pos = { 0,3 };

				bool my_turn = true, pc_turn = true;
				do {
					ch = _getch();
					SetConsoleCursorPosition(hConsole, pos);

					if (ch == 77) {
						if (j < 9 && pc.VISIBLE_BOARD[i][j + 1] != '0' && pc.VISIBLE_BOARD[i][j + 1] != 'X') {

							GoRight(pc.VISIBLE_BOARD, i, j);
							ShowBoard(pc.VISIBLE_BOARD);
						}
						else if (j < 9 && (pc.VISIBLE_BOARD[i][j + 1] == '0' || pc.VISIBLE_BOARD[i][j + 1] == 'X')) {
							for (int k = 1; k < 10; k++)
							{
								if (j + k <= 9)if (pc.VISIBLE_BOARD[i][j + k] == isWATER) {
									swap(pc.VISIBLE_BOARD[i][j], pc.VISIBLE_BOARD[i][j + k]);
									j += k;
									ShowBoard(pc.VISIBLE_BOARD);
									break;
								}
							}
						}
					}
					if (ch == 75) {
						if (j != 0 && pc.VISIBLE_BOARD[i][j - 1] != '0' && pc.VISIBLE_BOARD[i][j - 1] != 'X') {
							GoLeft(pc.VISIBLE_BOARD, i, j);
							ShowBoard(pc.VISIBLE_BOARD);
						}
						else if (j > 0 && (pc.VISIBLE_BOARD[i][j - 1] == '0' || pc.VISIBLE_BOARD[i][j - 1] == 'X')) {
							for (int k = 1; k < 10; k++)
							{
								if (j - k >= 0 && pc.VISIBLE_BOARD[i][j - k] == isWATER) {
									swap(pc.VISIBLE_BOARD[i][j], pc.VISIBLE_BOARD[i][j - k]);
									j -= k;
									ShowBoard(pc.VISIBLE_BOARD);
									break;
								}
							}
						}
					}
					if (ch == 80) {
						if (i != 9 && pc.VISIBLE_BOARD[i + 1][j] != '0' && pc.VISIBLE_BOARD[i + 1][j] != 'X') {
							GoDown(pc.VISIBLE_BOARD, i, j);
							ShowBoard(pc.VISIBLE_BOARD);
						}
						else if (i < 9 && (pc.VISIBLE_BOARD[i + 1][j] == '0' || pc.VISIBLE_BOARD[i + 1][j] == 'X')) {
							for (int k = 1; k < 10; k++)
							{
								if (i + k <= 9 && pc.VISIBLE_BOARD[i + k][j] == isWATER) {
									swap(pc.VISIBLE_BOARD[i][j], pc.VISIBLE_BOARD[i + k][j]);
									i += k;
									ShowBoard(pc.VISIBLE_BOARD);
									break;
								}
							}
						}
					}
					if (ch == 72) {
						if (i != 0 && pc.VISIBLE_BOARD[i - 1][j] != '0' && pc.VISIBLE_BOARD[i - 1][j] != 'X') {
							GoUp(pc.VISIBLE_BOARD, i, j);
							ShowBoard(pc.VISIBLE_BOARD);
						}
						else if (j > 0 && (pc.VISIBLE_BOARD[i - 1][j] == '0' || pc.VISIBLE_BOARD[i - 1][j] == 'X')) {
							for (int k = 1; k < 10; k++)
							{
								if (i - k >= 0 && pc.VISIBLE_BOARD[i - k][j] == isWATER) {
									swap(pc.VISIBLE_BOARD[i][j], pc.VISIBLE_BOARD[i - k][j]);
									i -= k;
									ShowBoard(pc.VISIBLE_BOARD);
									break;
								}
							}
						}
					}
					if (ch == 13) {

						if (pc.REAL_BOARD[i][j] == isSHIP) {

							pc.VISIBLE_BOARD[i][j] = isHIT;
							pc.REAL_BOARD[i][j] = isHIT;
							add_hit(pc_ships, i, j);
							if (win(pc.REAL_BOARD)) {
								my_turn = false;
								pc_turn = false;
								break;
							}
							if (isDrawn(pc.VISIBLE_BOARD, pc_ships, i, j)) {
								pos = { 0,20 };
								SetConsoleCursorPosition(hConsole, pos);
								cout << "Ship is drown!  \n";

								pos = { 0,3 };
								SetConsoleCursorPosition(hConsole, pos);
							}
							else {
								pos = { 0,20 };
								SetConsoleCursorPosition(hConsole, pos);
								cout << "The ship is hit!\n";
								pos = { 0,3 };
								SetConsoleCursorPosition(hConsole, pos);
							}

						}
						else {
							pc.VISIBLE_BOARD[i][j] = isMISS;

							pc_turn = true;
							my_turn = false;
						}
						i = 0; j = 0;
						if (pc.VISIBLE_BOARD[i][j] == isMISS || pc.VISIBLE_BOARD[i][j] == isHIT) {
							for (int k = 0; k < 10; k++)
							{
								if (pc.VISIBLE_BOARD[i][j + k] != isMISS && pc.VISIBLE_BOARD[i][j + k] != isHIT) {
									j += k;
									break;
								}
								if (pc.VISIBLE_BOARD[i + k][j] != isMISS && pc.VISIBLE_BOARD[i + k][j] != isHIT) {
									i += k;
									break;
								}
								if (pc.VISIBLE_BOARD[i + k][j + k] != isMISS && pc.VISIBLE_BOARD[i + k][j + k] != isHIT) {
									i += k;
									j += k;
									break;
								}
								if (k == 9) {
									create_random_point(pc.VISIBLE_BOARD, i, j);
								}
							}

						}
						pc.VISIBLE_BOARD[i][j] = '?';

						ShowBoard(pc.VISIBLE_BOARD);
					}
					if (ch == 113) {
						quit = true;
						break;
					}
				}
				while (my_turn);
				if (quit) {
					SetConsoleTextAttribute(hConsole, 2);
					pos = { 28,15 };
					SetConsoleCursorPosition(hConsole, pos);
					cout << "Goodbye!";
					Sleep(2000);
					system("cls");
					SetConsoleTextAttribute(hConsole, 15);
					break; }
				if (pc_regime == 1) {

					while (pc_turn) {

						RandomShot(MY_BOARD, pc_turn);
					}
				}
				else if (pc_regime == 2) {
					while (pc_turn) {
						SmartShot(MY_BOARD, pc_turn, i_pc, j_pc);
					}
				}

				system("cls");
			}
		}
		else {
			cout << "\n\t\t\t\tGoodbye!\n";
			break;
		}
	}

}
