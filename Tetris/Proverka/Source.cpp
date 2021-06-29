#include < iostream>
#include<time.h>
#include<stdlib.h>
#include <Windows.h> 
#include<conio.h>
#include"windows.h"
#include <fstream>


using namespace std;
bool gameover;
bool forrandom;
const int width = 10;
const int higth = 20;
const char WidthSym = 186;
const char HigthSym = 205;
const unsigned char squard = 254;
int arr[21][12];
int nextfigure[2][4];
int random;
int nextrandom;
int check;
int score = 0;
char* username = new char[32];
int readscorearr[10] = { 0,0,0,0,0,0,0,0,0,0 };
char** nicknames = new char* [10];
int figurenumb;
int turnamount;
int squard1x, squard1y, squard2x, squard2y, squard3x, squard3y, squard4x, squard4y;
int nextsquard1x, nextsquard1y, nextsquard2x, nextsquard2y, nextsquard3x, nextsquard3y, nextsquard4x, nextsquard4y;
enum Control { STOP = 0, RIGHT , LEFT , DROPPING , RESET , TURN , PAUSE  };
Control click;

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}


void Setup() {
	PlaySound(TEXT("game.wav"), NULL, SND_LOOP | SND_ASYNC);
	random = rand() % 7 + 1;
	nextrandom = rand() % 7 + 1;
	gameover = false;
	forrandom = true;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 12; j++) {
			if (j == 0 || j == 11) {
				arr[i][j] = 2;
			}
			else arr[i][j] = 0;
		}
	}
	
	for (int i = 20; i < 21; i++) {
		for (int j = 0; j < 12; j++) {
			arr[i][j] = 2;
		}
	}



	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			nextfigure[i][j] = 0;
		}
	}
}




void DrowTopLine() {
	gotoxy(50, 10);
	for (int i = 0; i < width + 2; i++) {
		cout << HigthSym;
		
	}
	cout << endl;
}

void DrowMainField() {
	for (int i = 0; i < higth; i++) {
		gotoxy(50, (i+11));
		for (int j = -1; j < width + 2; j++) {
			if (j == -1 || j == width+1) {
				cout << WidthSym;
			}
			if (j >= 1) {
				if (arr[i][j] == 1 || arr[i][j] == 2) {
					cout << squard;
				}
				if (arr[i][j] == 0) {
					cout << ' ';
				}
			}
		}
		cout << endl;
	}
}

void DrowBottomLine() {
	gotoxy(50, 31);
	for (int i = 0; i < width + 2; i++) {

		cout << HigthSym;
	}
	cout << endl;
}

void DrowScore() {
	gotoxy(50, 32);
	cout << "Score: " << score;
	cout << endl << endl;
}

void DrowArrWithNumbers() {
	for (int i = 0; i < 21; i++) {
		gotoxy(100, i+11);
		for (int j = 0; j < 12; j++) {
			cout << arr[i][j] << " ";
		}
		
	}
}

void DrowMeansSym() {
	int i = 0;
	gotoxy(70, i+11);
	i++;
	cout << "A - left shift" << endl;
	gotoxy(70, i + 11);
	i++;
	cout << "D - right shift" << endl;
	gotoxy(70, i + 11);
	i++;
	cout << "W - turn " << endl;
	gotoxy(70, i + 11);
	i++;
	cout << "SPACE - figure reset" << endl;
	gotoxy(70, i + 11);
	i++;
	cout << "P - pause " << endl;
	gotoxy(70, i + 11);
	i++;
	cout << "R - reset" << endl;
	gotoxy(70, i + 11);
	i++;
	cout << "Esc - game over" << endl;


}

void DrowNextFigure() {
	gotoxy(70, 21);
	cout << "Next Figure: ";
	gotoxy(70, 22);
	for (int i = 0; i <6; i++) {
		cout << HigthSym;

	}
	cout << endl;

	for (int i = 0; i < 2; i++) {
		gotoxy(70, (i + 23));
		for (int j = -1; j < 5; j++) {
			if (j == -1 || j == 4) {
				cout << WidthSym;
			}
			if (j >= 0) {
				if (nextfigure[i][j] == 1) {
					cout << squard;
				}
				if (nextfigure[i][j] == 0) {
					cout << ' ';
				}
			}
		}
		cout << endl;
	}

	gotoxy(70, 25);
	for (int i = 0; i < 6; i++) {

		cout << HigthSym;
	}
	cout << endl;
}

void DrowForClean() {
	for (int i = 0; i < 20; i++) {
		gotoxy(62, (i + 11));
		cout << " " << endl;
	}
}

void DrowForClean1() {
	for (int i = 0; i < 20; i++) {
		gotoxy(76, (i + 23));
		cout << " " << endl;
	}
}


void Drow() {
	Sleep(300);
	system("cls");
	gotoxy(2, 5);
	DrowTopLine();
	
	DrowMainField();
	DrowForClean();
	DrowBottomLine();
	
	DrowScore();

	DrowMeansSym();

	DrowNextFigure(); 
	DrowForClean1();

	DrowArrWithNumbers();
	
	

}





void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			click = LEFT;
			break;
		case 'A':
			click = LEFT;
			break;
		case 'd':
			click = RIGHT;
			break;
		case 'D':
			click = RIGHT;
			break;
		case 'w':
			click = TURN;
			break;
		case 'W':
			click = TURN;
			break;
		case 'p':
			click = PAUSE;
			break;
		case 'P':
			click = PAUSE;
			break;
		case 'r':
			click = RESET;
			break;
		case 'R':
			click = RESET;
			break;
		case 32:
			click = DROPPING;
			break;
		case 27:
			gameover = true;
			break;
			
		}
	}
	

}






void LogicForLeft() {
	if (arr[squard1y][squard1x - 1] != 2 && arr[squard2y][squard2x - 1] != 2 &&
		arr[squard3y][squard3x - 1] != 2 && arr[squard4y][squard4x - 1] != 2) {
		if (arr[squard1y][squard1x] != 2 && arr[squard2y][squard2x] != 2 &&
			arr[squard3y][squard3x] != 2 && arr[squard4y][squard4x] != 2) {

			arr[squard1y][squard1x] = 0;
			arr[squard2y][squard2x] = 0;
			arr[squard3y][squard3x] = 0;
			arr[squard4y][squard4x] = 0;

			squard1x -= 1;
			squard2x -= 1;
			squard3x -= 1;
			squard4x -= 1;

			arr[squard1y][squard1x] = 1;
			arr[squard2y][squard2x] = 1;
			arr[squard3y][squard3x] = 1;
			arr[squard4y][squard4x] = 1;

		}
	}
}

void LogicForRight() {
	if (arr[squard1y][squard1x + 1] != 2 && arr[squard2y][squard2x + 1] != 2 &&
		arr[squard3y][squard3x + 1] != 2 && arr[squard4y][squard4x + 1] != 2) {
		if (arr[squard1y][squard1x] != 2 && arr[squard2y][squard2x] != 2 &&
			arr[squard3y][squard3x] != 2 && arr[squard4y][squard4x] != 2) {

			arr[squard1y][squard1x] = 0;
			arr[squard2y][squard2x] = 0;
			arr[squard3y][squard3x] = 0;
			arr[squard4y][squard4x] = 0;

			squard1x += 1;
			squard2x += 1;
			squard3x += 1;
			squard4x += 1;

			arr[squard1y][squard1x] = 1;
			arr[squard2y][squard2x] = 1;
			arr[squard3y][squard3x] = 1;
			arr[squard4y][squard4x] = 1;

		}
	}
}

void LogicForReset() {
	gameover = false;
	forrandom = true;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 12; j++) {
			if (j == 0 || j == 11) {
				arr[i][j] = 2;
			}
			else arr[i][j] = 0;
		}
	}

	for (int i = 20; i < 21; i++) {
		for (int j = 0; j < 12; j++) {
			arr[i][j] = 2;
		}
	}
}

void LogicForTurnFigure(){

	turnamount++;
	if (turnamount == 4) {
		turnamount = 0;
	}
	switch (figurenumb) {
	case 1:
		if (turnamount == 1) {
			if (arr[squard1y][squard1x + 1] != 2 && arr[squard2y][squard2x + 1] != 2
				&& arr[squard3y + 1][squard3x] != 2 && arr[squard4y + 1][squard4x - 2] != 2)
			{

				
					arr[squard1y][squard1x] = 0;
					arr[squard2y][squard2x] = 0;
					arr[squard3y][squard3x] = 0;
					arr[squard4y][squard4x] = 0;
					squard1x += 1;
					squard2x += 1;          //   k
					squard3y += 1;         //    k
					squard4x -= 2;        //   k k
					squard4y += 1;
					arr[squard1y][squard1x] = 1;
					arr[squard2y][squard2x] = 1;
					arr[squard3y][squard3x] = 1;
					arr[squard4y][squard4x] = 1;
				
			}
		}

		else if (turnamount == 2) {
			if (arr[squard1y][squard1x-1] != 2 && arr[squard2y-1][squard2x] != 2
				&& arr[squard3y-2][squard3x+1] != 2 && arr[squard4y-1][squard4x+2] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1x -= 1;
				squard2y -= 1;
				squard3x += 1;          // k k k
				squard3y -= 2;         //      k
				squard4x += 2;
				squard4y -= 1;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 3) {
			if (arr[squard1y][squard1x+1] != 2 && arr[squard2y][squard2x-1] != 2
				&& arr[squard3y+1][squard3x-2] != 2 && arr[squard4y+1][squard4x-2] != 2) 
			{
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1x += 1;
				squard2x -= 1;
				squard3x -= 2;          // k 
				squard3y += 1;         //  k
				squard4x -= 2;        //   k k
				squard4y += 1;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 0) {
			if (arr[squard1y][squard1x-1] != 2 && arr[squard2y+1][squard2x] != 2
				&& arr[squard3y][squard3x+1] != 2 && arr[squard4y-1][squard4x+2] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1x -= 1;
				squard2y += 1;
				squard3x += 1;           // k   
				squard4x += 2;          //  k k k
				squard4y -= 1;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		break;
	case 2:

		if (turnamount == 1) {
			if (arr[squard1y-1][squard1x] != 2 && arr[squard2y-1][squard2x] != 2
				&& arr[squard3y][squard3x-1] != 2 && arr[squard4y+2][squard4x-1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1y -= 1;
				squard2y -= 1;
				squard3x -= 1;
				squard4x -= 1;
				squard4y += 2;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 2) {
			if (arr[squard1y+1][squard1x] != 2 && arr[squard2y][squard2x-2] != 2
				&& arr[squard3y-1][squard3x] != 2 && arr[squard4y-2][squard4x+1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1y += 1;
				squard2x -= 1;
				squard3y -= 1;
				squard4x += 1;
				squard4y -= 2;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 3) {
			if (arr[squard1y-1][squard1x] != 2 && arr[squard2y+1][squard2x] != 2
				&& arr[squard3y+2][squard3x-1] != 2 && arr[squard4y+2][squard4x-1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1y -= 1;
				squard2y += 1;
				squard3x -= 1;
				squard3y += 2;
				squard4x -= 1;
				squard4y += 2;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 0) {
			if (arr[squard1y+1][squard1x] != 2 && arr[squard2y][squard2x+1] != 2
				&& arr[squard3y-1][squard3x+2] != 2 && arr[squard4y-2][squard4x+1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1y += 1;
				squard2x += 1;
				squard3x += 2;
				squard3y -= 1;
				squard4x += 1;
				squard4y -= 2;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		break;
	case 3:
		if (turnamount == 1) {
			if (arr[squard1y][squard1x] != 2 && arr[squard2y-1][squard2x] != 2
				&& arr[squard3y+1][squard3x] != 2 && arr[squard4y+1][squard4x-1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard2y -= 1;
				squard3y += 1;
				squard4x -= 1;
				squard4y += 1;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 2) {
			if (arr[squard1y-1][squard1x] != 2 && arr[squard2y][squard2x] != 2
				&& arr[squard3y][squard3x] != 2 && arr[squard4y-2][squard4x+1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1y -= 1;
				squard4x += 1;
				squard4y -= 2;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 3) {
			if (arr[squard1y][squard1x+1] != 2 && arr[squard2y+1][squard2x] != 2
				&& arr[squard3y][squard3x+1] != 2 && arr[squard4y+2][squard4x-1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1x += 1;
				squard2y += 1;
				squard3x += 1;
				squard4x -= 1;
				squard4y += 2;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 0) {
			if (arr[squard1y+1][squard1x-1] != 2 && arr[squard2y][squard2x] != 2
				&& arr[squard3y-1][squard3x-1] != 2 && arr[squard4y-1][squard4x+1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1x -= 1;
				squard1y += 1;
				squard3x -= 1;
				squard3y -= 1;
				squard4x += 1;
				squard4y -= 1;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}
		break;
	case 4:

		if (turnamount == 1) {
			if (arr[squard1y-1][squard1x] != 2 && arr[squard2y][squard2x-1] != 2
				&& arr[squard3y+1][squard3x] != 2 && arr[squard4y+2][squard4x-1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1y -= 1;
				squard2x -= 1;
				squard3y += 1;
				squard4x -= 1;
				squard4y += 2;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 2) {
			if (arr[squard1y+1][squard1x] != 2 && arr[squard2y][squard2x+1] != 2
				&& arr[squard3y-1][squard3x] != 2 && arr[squard4y-2][squard4x+1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1y += 1;
				squard2x += 1;
				squard3y -= 1;
				squard4x += 1;
				squard4y -= 2;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
				turnamount = 0;
			}
		}

		break;
	case 5:
		if (turnamount == 1) {
			if (arr[squard1y+2][squard1x] != 2 && arr[squard2y+1][squard2x-1] != 2
				&& arr[squard3y][squard3x] != 2 && arr[squard4y-1][squard4x-1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1y += 2;
				squard2x -= 1;
				squard2y += 1;
				squard4x -= 1;
				squard4y -= 1;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 2) {
			if (arr[squard1y-2][squard1x] != 2 && arr[squard2y-1][squard2x+1] != 2
				&& arr[squard3y][squard3x] != 2 && arr[squard4y+1][squard4x+1] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1y -= 2;
				squard2x += 1;
				squard2y -= 1;
				squard4x += 1;
				squard4y += 1;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
				turnamount = 0;
			}
		}

		break;
	case 6:

		if (turnamount == 1) {
			if (arr[squard1y-1][squard1x+1] != 2 && arr[squard2y][squard2x] != 2
				&& arr[squard3y+1][squard3x-1] != 2 && arr[squard4y+2][squard4x-2] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1x += 1;
				squard1y -= 1;
				squard3x -= 1;
				squard3y += 1;
				squard4x -= 2;
				squard4y += 2;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
			}
		}

		else if (turnamount == 2) {
			if (arr[squard1y+1][squard1x-1] != 2 && arr[squard2y][squard2x] != 2
				&& arr[squard3y-1][squard3x+1] != 2 && arr[squard4y-2][squard4x+2] != 2) {
				arr[squard1y][squard1x] = 0;
				arr[squard2y][squard2x] = 0;
				arr[squard3y][squard3x] = 0;
				arr[squard4y][squard4x] = 0;
				squard1x -= 1;
				squard1y += 1;
				squard3x += 1;
				squard3y -= 1;
				squard4x += 2;
				squard4y -= 2;
				arr[squard1y][squard1x] = 1;
				arr[squard2y][squard2x] = 1;
				arr[squard3y][squard3x] = 1;
				arr[squard4y][squard4x] = 1;
				turnamount = 0;
			}
		}

		break;
}


}

void LogicForDropFigure() {
	bool checkwhile = true;
	while (checkwhile){
		if (arr[squard1y + 1][squard1x] == 2 || arr[squard2y + 1][squard2x] == 2 || arr[squard3y + 1][squard3x] == 2 || arr[squard4y + 1][squard4x] == 2) {
			arr[squard1y][squard1x] = 2;
			arr[squard2y][squard2x] = 2;
			arr[squard3y][squard3x] = 2;
			arr[squard4y][squard4x] = 2;
			checkwhile = false;
			forrandom = true;
		}
		else {
			arr[squard1y][squard1x] = 0;
			arr[squard2y][squard2x] = 0;
			arr[squard3y][squard3x] = 0;
			arr[squard4y][squard4x] = 0;
			squard1y += 1;
			squard2y += 1;
			squard3y += 1;
			squard4y += 1;
			arr[squard1y][squard1x] = 1;
			arr[squard2y][squard2x] = 1;
			arr[squard3y][squard3x] = 1;
			arr[squard4y][squard4x] = 1;
		}

	}


}

void LogicForClick() {
	switch (click)
	{
	case LEFT:
		LogicForLeft();
		break;
	case RIGHT:
		LogicForRight();
		break;
	case TURN:
		LogicForTurnFigure();
		break;
	case DROPPING:
		LogicForDropFigure();
		break;
	case RESET:
		LogicForReset();
		score = 0;
		break;
	case PAUSE:
		system("pause");
		break;
	

	}
	click = STOP;
}

void LogicForCreatNextFigure() {
	nextfigure[nextsquard1y][nextsquard1x] = 0;
	nextfigure[nextsquard2y][nextsquard2x] = 0;
	nextfigure[nextsquard3y][nextsquard3x] = 0;
	nextfigure[nextsquard4y][nextsquard4x] = 0;

	switch (nextrandom) {
	case 1:
		nextsquard1x = 0;
		nextsquard1y = 0;
		nextsquard2x = 0;
		nextsquard2y = 1;
		nextsquard3x = 1;   // k
		nextsquard3y = 1;   // k k k
		nextsquard4x = 2;
		nextsquard4y = 1;
		break;
	case 2:
		nextsquard1x =0;
		nextsquard1y = 1;
		nextsquard2x = 1;
		nextsquard2y = 1;
		nextsquard3x = 2;   //     k
		nextsquard3y = 1;   // k k k 
		nextsquard4x = 2;
		nextsquard4y = 0;

		break;
	case 3:
		nextsquard1x = 0;
		nextsquard1y = 1;
		nextsquard2x = 1;
		nextsquard2y = 1;
		nextsquard3x = 1;  //   k
		nextsquard3y = 0;  // k k k
		nextsquard4x = 2;
		nextsquard4y = 1;

		break;
	case 4:
		nextsquard1x = 0;
		nextsquard1y = 1;
		nextsquard2x = 1;
		nextsquard2y = 1;
		nextsquard3x = 1;  //   k k
		nextsquard3y = 0; //  k k
		nextsquard4x = 2;
		nextsquard4y = 0;

		break;
	case 5:
		nextsquard1x = 0;
		nextsquard1y = 0;
		nextsquard2x = 1;
		nextsquard2y = 0;
		nextsquard3x = 1; //  k k
		nextsquard3y = 1; //    k k
		nextsquard4x = 2;
		nextsquard4y = 1;

		break;
	case 6:
		nextsquard1x = 0;
		nextsquard1y = 0;
		nextsquard2x = 1;
		nextsquard2y = 0;
		nextsquard3x = 2; // k k k k
		nextsquard3y = 0;
		nextsquard4x = 3;
		nextsquard4y = 0;

		break;
	case 7:
		nextsquard1x = 0;
		nextsquard1y = 0;
		nextsquard2x = 1;
		nextsquard2y = 0; // k k
		nextsquard3x = 0; // k k
		nextsquard3y = 1;
		nextsquard4x = 1;
		nextsquard4y = 1;

		break;

	}

	nextfigure[nextsquard1y][nextsquard1x] = 1;
	nextfigure[nextsquard2y][nextsquard2x] = 1;
	nextfigure[nextsquard3y][nextsquard3x] = 1;
	nextfigure[nextsquard4y][nextsquard4x] = 1;

}

void LogicForCreatFigure() {
	
	while (forrandom) {
		srand(time(NULL));
		turnamount = 0;
		switch (random) {
		case 1:
			squard1x = 4;
			squard1y = 0;
			squard2x = 4;
			squard2y = 1;
			squard3x = 5;   // k
			squard3y = 1;   // k k k
			squard4x = 6;
			squard4y = 1;
			figurenumb = 1;
			break;
		case 2:
			squard1x = 4;
			squard1y = 1;
			squard2x = 5;
			squard2y = 1;
			squard3x = 6;   //     k
			squard3y = 1;   // k k k 
			squard4x = 6;
			squard4y = 0;
			figurenumb = 2;
			break;
		case 3:
			squard1x = 4;
			squard1y = 1;
			squard2x = 5;
			squard2y = 1;
			squard3x = 5;  //   k
			squard3y = 0;  // k k k
			squard4x = 6;
			squard4y = 1;
			figurenumb = 3;
			break;
		case 4:
			squard1x = 4;
			squard1y = 1;
			squard2x = 5;
			squard2y = 1;
			squard3x = 5;  //   k k
			squard3y = 0; //  k k
			squard4x = 6;
			squard4y = 0;
			figurenumb = 4;
			break;
		case 5:
			squard1x = 4;
			squard1y = 0;
			squard2x = 5;
			squard2y = 0;
			squard3x = 5; //  k k
			squard3y = 1; //    k k
			squard4x = 6;
			squard4y = 1;
			figurenumb = 5;
			break;
		case 6:
			squard1x = 4;
			squard1y = 0;
			squard2x = 5;
			squard2y = 0;
			squard3x = 6; // k k k k
			squard3y = 0;
			squard4x = 7;
			squard4y = 0;
			figurenumb = 6;
			break;
		case 7:
			squard1x = 4;
			squard1y = 0;
			squard2x = 5;
			squard2y = 0; // k k
			squard3x = 4; // k k
			squard3y = 1;
			squard4x = 5;
			squard4y = 1;
			figurenumb = 7;
			break;

		}
		random = nextrandom;
		LogicForCreatNextFigure();
		nextrandom = rand() % 7 + 1;
		check = 0;
		score += 10;
		forrandom = false;
		if (arr[squard1y][squard1x] == 2 || arr[squard2y][squard2x] == 2
			|| arr[squard3y][squard3x] == 2 || arr[squard4y][squard4x] == 2) {
			gameover = true;
		}
	}
}

void LogicForMoveFigureDown() {
	if (check == 0) {
		arr[squard1y][squard1x] = 1;
		arr[squard2y][squard2x] = 1;
		arr[squard3y][squard3x] = 1;
		arr[squard4y][squard4x] = 1;
		
	}

	else if (check > 0) {
		arr[squard1y][squard1x] = 0;
		arr[squard2y][squard2x] = 0;
		arr[squard3y][squard3x] = 0;
		arr[squard4y][squard4x] = 0;
		squard1y += 1;
		squard2y += 1;
		squard3y += 1;
		squard4y += 1;
		arr[squard1y][squard1x] = 1;
		arr[squard2y][squard2x] = 1;
		arr[squard3y][squard3x] = 1;
		arr[squard4y][squard4x] = 1;
		
	}
	check++;
}

void LogicForFixFigure() {
	if (arr[squard1y + 1][squard1x] == 2 || arr[squard2y + 1][squard2x] == 2 || arr[squard3y + 1][squard3x] == 2 || arr[squard4y + 1][squard4x] == 2) {
		arr[squard1y][squard1x] = 2;
		arr[squard2y][squard2x] = 2;
		arr[squard3y][squard3x] = 2;
		arr[squard4y][squard4x] = 2;
		forrandom = true;
	}
}

void LogicForDelString() {
	for (int i = 0; i < 20; i++) {
		int checkfor2 = 0;
		for (int j = 1; j < 11; j++) {
			if (arr[i][j] == 2) {
				checkfor2++;
			}
		}
		if (checkfor2 == 10) {
			for (int l = 1; l < 11; l++) {
				arr[i][l] = 0;
			}

			for (int n = i; n > 0; n--) {
				for (int m = 1; m < 11; m++) {
					if (arr[n - 1][m] != 1) {
						arr[n][m] = arr[n - 1][m];
						arr[n - 1][m] = 0;
					}
				}
			}
			score += 100;
		}


	}
}

void Logic() {
	LogicForCreatFigure();

	LogicForMoveFigureDown();

	LogicForFixFigure();

	LogicForClick();

	LogicForFixFigure();
	

	LogicForDelString();
	
	

}



void ReadNickNames() {
	for (int i = 0; i < 10; i++) {
		nicknames[i] = new char[32];
	}

	ifstream ReadRecordsName;
	ReadRecordsName.open("RecordsNames.txt");
	for (int i = 0; i < 10;) {
		char* endcheck = new char[32];

		ReadRecordsName >> endcheck;

		if (!strcmp(endcheck, "$end") == 0) {
			nicknames[i] = endcheck;
			i++;
		}

	}

}

void WriteNickNames() {
	ofstream recordsNames;
	recordsNames.open("RecordsNames.txt", ios::trunc);
	if (recordsNames.is_open()) {
		for (int i = 0; i < 10; i++) {
			recordsNames << nicknames[i] << " $end" << endl;
		}
	}
	recordsNames.close();

}

void ReadScore() {
	ifstream ReadRecordsScores;

	ReadRecordsScores.open("RecordsScore.txt");

	for (int i = 0; i < 10; i++) {
		int endcheck;

		ReadRecordsScores >> endcheck;
		readscorearr[i] = endcheck;
	}

	ReadRecordsScores.close();

	cout << endl;


}

void WriteSocre() {


	int scorearr[10];
	for (int i = 0; i < 10; i++) {

		scorearr[i] = readscorearr[i];

	}

	ofstream recordsScores;
	recordsScores.open("RecordsScore.txt", ios::trunc);
	if (recordsScores.is_open()) {
		for (int i = 0; i < 10; i++) {
			recordsScores << scorearr[i] << " " << endl;
		}
	}
	recordsScores.close();
}

void AddNewRecords() {

	if (score > readscorearr[9]) {
		readscorearr[9] = score;
		for (int i = 0; i < 10; i++) {
			for (int j = 9; j > i; j--) {
				if (readscorearr[j] > readscorearr[j - 1]) {
					int swap = readscorearr[j - 1];
					readscorearr[j - 1] = readscorearr[j];
					readscorearr[j] = swap;
				}
			}
		}

		int rembindex = 0;
		for (int i = 0; i < 10; i++) {
			if (score == readscorearr[i]) {
				rembindex = i;
				break;
			}
		}


		for (int i = 9; i > rembindex; i--) {
			nicknames[i] = nicknames[i - 1];
		}
		nicknames[rembindex] = username;

	}





}


void Records() {
	ReadNickNames();
	ReadScore();
	AddNewRecords();
	WriteNickNames();
	WriteSocre();
}

void PrintRecordsInMenu() {
	ReadNickNames();
	ReadScore();
	int i = 0;
	for (; i < 10; i++) {
		gotoxy(70, i + 20);
		cout << i + 1 << ". " <<"\t"<< nicknames[i] << "........" << readscorearr[i] << endl;

	}
	gotoxy(70, i + 21);
	cout << "Press any key to return to the menu"<<endl<<endl<<endl<<endl<<endl<<endl;
	system("pause");
}


int main() {
	bool menuwork = true;

	COORD coord;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);

	while (menuwork) {
		int movebyY=0;
		PlaySound(TEXT("silent.wav"), NULL, SND_LOOP | SND_ASYNC);
		gotoxy(80, movebyY + 20);
		movebyY++;
		cout << "Menu:" << endl;
		gotoxy(80, movebyY + 20);
		movebyY++;
		cout << "1.Start" << endl;
		gotoxy(80, movebyY + 20);
		movebyY++;
		cout << "2.Records" << endl;
		int menu;
		gotoxy(80, movebyY + 20);
		movebyY++;
		cin >> menu;
		switch (menu) {
		case 1:
			system("cls");
			gotoxy(70, 20);
			cout << "Nick Name:";
			cin >> username;
			Setup();
			while (!gameover) {

				Drow();
				Input();
				Logic();
			}
			PlaySound(TEXT("gameover.wav"), NULL, SND_LOOP | SND_ASYNC);
			Records();
			system("cls");
			gotoxy(80, 20);
			cout << "GAME OVER";
			Sleep(2000);
			system("cls");
			break;
		case 2:
			system("cls");
			PrintRecordsInMenu();
			system("cls");
			break;
		}
	}
}
