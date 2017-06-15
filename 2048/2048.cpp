#pragma warning(disable : 4996)

#include<cstdio>
#include<Windows.h>
#include<conio.h>
#include<string>
#include<cstring>
#include<time.h>
using namespace std;

#define MAX_WINDOW_X 100
#define MAX_WINDOW_Y 30

#define FRAME_POS_X 4
#define FRAME_POS_Y 3
#define SCORE_FRAME_POS_X 40
#define SCORE_FRAME_POS_Y 8

#define BOARD_SIZE 4

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

const int PANEL_POS_X[BOARD_SIZE] = { FRAME_POS_X + 2, FRAME_POS_X + 8, FRAME_POS_X + 14, FRAME_POS_X + 20 };
const int PANEL_POS_Y[BOARD_SIZE] = { FRAME_POS_Y + 4, FRAME_POS_Y + 7, FRAME_POS_Y + 10, FRAME_POS_Y + 13 };
const int VALUE_POS_X[BOARD_SIZE] = { FRAME_POS_X + 4, FRAME_POS_X + 10, FRAME_POS_X + 16, FRAME_POS_X + 22 };
const int VALUE_POS_Y[BOARD_SIZE] = { FRAME_POS_Y + 5, FRAME_POS_Y + 8, FRAME_POS_Y + 11, FRAME_POS_Y + 14 };

int board[4][4] = {
	{ 0,0,0,0 },
	{ 1,0,4,0 },
	{ 0,2,0,0 },
	{ 0,0,0,8 }
};

int score;

inline void gotoxy(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void setcursortype(CURSOR_TYPE c) { //커서 표시를 바꿔주는 함수  
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
void setWindow() {
	system("mode con cols=MAX_WINDOW_X lines=MAX_WINDOW_Y");
	system("title 2048");
	system("cls");
}

void drawBackgroundFrame();
void drawBackgroundTitle(int x, int y);

void drawPanel(int x, int y, int value);
void drawEmptyPanel(int x, int y);
void drawBoard();

void drawScore(int x, int y);

void reset();
void newPanelNumber();
int getKey();

int main() {
	setcursortype(NOCURSOR);
	setWindow();

	reset();

	drawBoard();

	drawScore(SCORE_FRAME_POS_X, SCORE_FRAME_POS_Y);
	while (true) {
		if (getKey()) {
			
		}
		getch();
		newPanelNumber();
	}
}

void drawBackgroundFrame() {
	gotoxy(0, 0);
	string frame = "┌";
	for (int i = 0; i < MAX_WINDOW_X*0.5 - 2; ++i) {
		frame += "─";
	}
	frame += "┐\n";
	printf(frame.c_str());

	frame = "│";
	for (int i = 0; i < MAX_WINDOW_X - 4; ++i) {
		frame += " ";
	}
	frame += "│\n";
	for (int i = 0; i < MAX_WINDOW_Y - 2; ++i) {
		printf(frame.c_str());
	}

	frame = "└";
	for (int i = 0; i < MAX_WINDOW_X*0.5 - 2; ++i) {
		frame += "─";
	}
	frame += "┘";
	printf(frame.c_str());
}
void drawBackgroundTitle(int x, int y) {
	gotoxy(x + 6, y);
	printf("─┐┌┐││┌┐");
	gotoxy(x + 6, y + 1);
	printf("┌┘││└┤├┤");
	gotoxy(x + 6, y + 2);
	printf("└─└┘  │└┘");

	gotoxy(x, y + 3);
	printf("┌────────────┐");
	gotoxy(x, y + 4);
	printf("│                        │");
	gotoxy(x, y + 5);
	printf("│                        │");
	gotoxy(x, y + 6);
	printf("│                        │");
	gotoxy(x, y + 7);
	printf("│                        │");
	gotoxy(x, y + 8);
	printf("│                        │");
	gotoxy(x, y + 9);
	printf("│                        │");
	gotoxy(x, y + 10);
	printf("│                        │");
	gotoxy(x, y + 11);
	printf("│                        │");
	gotoxy(x, y + 12);
	printf("│                        │");
	gotoxy(x, y + 13);
	printf("│                        │");
	gotoxy(x, y + 14);
	printf("│                        │");
	gotoxy(x, y + 15);
	printf("│                        │");
	gotoxy(x, y + 16);
	printf("└────────────┘");
	gotoxy(x, y + 18);
	printf(" ◇ ←,→,↑,↓ : Move");
	gotoxy(x, y + 19);
	printf(" ◇ ESC : Quit");
	gotoxy(0, 0);
}

void clearPanel(int x, int y) {
	gotoxy(x, y);
	printf("      ");
	gotoxy(x, y + 1);
	printf("      ");
	gotoxy(x, y + 2);
	printf("      ");
}
void drawPanel(int x, int y, int value) {
	//clearPanel(x, y);
	gotoxy(x, y);
	printf("┌─┐");
	gotoxy(x, y + 1);
	printf("%6d", value);
	gotoxy(x, y + 2);
	printf("└─┘");
}
void drawEmptyPanel(int x, int y) {
	//clearPanel(x, y);
	gotoxy(x, y);
	printf("○");
}
void drawBoard() {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (board[i][j] == 0) {
				drawEmptyPanel(VALUE_POS_X[i], VALUE_POS_Y[j]);
			}
			else {
				drawPanel(PANEL_POS_X[i], PANEL_POS_Y[j], board[i][j]);
			}
		}
	}
}

void drawScore(int x, int y) {
	gotoxy(x, y);
	printf("┌────────────┐");
	gotoxy(x, y + 1);
	printf("│  Count : 0000000");
	gotoxy(x, y + 2);
	printf("│  Score : 0000000");
	gotoxy(x, y + 3);
	printf("└────────────┘");
}

void reset() {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			board[i][j] = 0;
		}
	}

	score = 0;

	drawBackgroundFrame();
	drawBackgroundTitle(FRAME_POS_X, FRAME_POS_Y);

	newPanelNumber();
	newPanelNumber();
}
void newPanelNumber() {
	int randomNumber = 0;
	int count = 0;
	int *pBoard[BOARD_SIZE * BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (board[i][j] == 0) {
				pBoard[count] = &board[i][j];
				++count;
			}
		}
	}
	
	srand(time(0));
	randomNumber = rand() % count;

	*pBoard[randomNumber] = 2;
	drawBoard();
	*pBoard[randomNumber] = 0;
	drawBoard();
	*pBoard[randomNumber] = 2;
	drawBoard();
}
int getKey() {
	int key = 0;

	key = getch();
	if (key == ESC) {
		exit(0);
	}
	if (key == 0xE0 || key == 0) {
		key = getch();

		switch (key) {
		case LEFT:
			break;
		case RIGHT:
			break;
		case UP:
			break;
		case DOWN:
			break;
		}
	}
	return 0;
}