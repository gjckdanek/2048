#pragma warning(disable : 4996)

#include<cstdio>
#include<Windows.h>
#include<conio.h>
#include<string>
#include<cstring>
using namespace std;

#define MAX_WINDOW_X 100
#define MAX_WINDOW_Y 30

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

void gotoxy(int x, int y) {
	COORD pos = { x, y };
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

void drawBackgroundFrame() {
	gotoxy(0, 0);
	string frame = "┌";
	for (int i = 0; i < MAX_WINDOW_X*0.5 -2; ++i) {
		frame += "─";
	}
	frame += "┐\n";
	printf(frame.c_str());

	frame = "│";
	for (int i = 0; i < MAX_WINDOW_X -4; ++i) {
		frame += " ";
	}
	frame += "│\n";
	for (int i = 0; i < MAX_WINDOW_Y -2; ++i) {
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
void drawPanel(int x, int y) {
	gotoxy(x, y);
	printf("┌─┐");
	gotoxy(x, y + 2);
	printf("└─┘");
}
void drawEmptyPanel(int x, int y) {
	gotoxy(x, y);
	printf("○");
}

int getKey() {
	int key = 0;

	key = getch();
	if (key == ESC) {
		exit(0);
	}
	if (key == 0xE0 || key == 0) {
		key == getch();

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

int board[4][4] = {
	{ 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,0,0,0 }
};

int score;

int main() {
	setcursortype(NOCURSOR);
	setWindow();
	drawBackgroundFrame();
	drawBackgroundTitle(4, 3);
	drawPanel(6, 7);
	drawPanel(12, 7);
	drawPanel(18, 7);
	drawPanel(24, 7);
	drawPanel(6, 10);
	drawPanel(12, 10);
	drawPanel(18, 10);
	drawPanel(24, 10);
	drawPanel(6, 13);
	drawPanel(12, 13);
	drawPanel(18, 13);
	drawPanel(24, 13);
	drawPanel(6, 16);
	drawPanel(12, 16);
	drawPanel(18, 16);
	drawPanel(24, 16);

	drawEmptyPanel(8, 8);
	drawEmptyPanel(14, 8);
	drawEmptyPanel(20, 8);
	drawEmptyPanel(26, 8);
	drawEmptyPanel(8, 11);
	drawEmptyPanel(14, 11);
	drawEmptyPanel(20, 11);
	drawEmptyPanel(26, 11);
	drawEmptyPanel(8, 14);
	drawEmptyPanel(14, 14);
	drawEmptyPanel(20, 14);
	drawEmptyPanel(26, 14);
	drawEmptyPanel(8, 17);
	drawEmptyPanel(14, 17);
	drawEmptyPanel(20, 17);
	drawEmptyPanel(26, 17);

	while (true) {
		if (getKey()) {

		}
		getch();
	}
}