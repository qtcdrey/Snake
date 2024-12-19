#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;

// height and width for border on the game
const int width = 80;
const int height = 20;

// coordinate for snake head (x-axis and y-axis)
int headX,headY;

// coordinate for food snake 
int fruitX,fruitY;

// score for the player
int playerScore;

// coordinate for snake tail (x-axis and y-axis)
int snakeTailX[100],snakeTailY[100];

// length for snake tail
int snakeTailLen;

// direction for snake
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

// varibale direction for snake
snakesDirection sDir;

// boolean (true of false) for checking the game is over or not
bool isGameOver; 

//this are prototype for a function following:
void GameRender(string playerName);
void GameInit();
void scratch();
void UpdateGame();
int SetDifficulty();
void UserInput();

int main() {
	string playerName;
	cout << "Enter your name: ";
	cin >> playerName;
	int dfc = SetDifficulty();
	
	GameInit();
	while (!isGameOver) {
		GameRender(playerName);
		UserInput();
		UpdateGame();
		Sleep(dfc);
	}
	//getch();
	return 0;
}

void scratch() {
	for ( int i = 0; i <= 256; i++ ) {
		printf("%i  =   %c\n\n",i,i);
	}
}

void GameInit() {
	isGameOver = false;
	sDir = STOP;
	headX = width / 2; 
	headY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	playerScore = 0;
}

// this is draw a snake game 
void GameRender(string playerName) {
	
	system("cls"); // for clearing the recently console
	
	// Creating top walls width
	for ( int i = 0; i < width + 2; i++ ) 
		putchar(220);
	printf("\n");
		
	for ( int i = 0; i < height; i++ ) {
		for ( int j = 0; j <= width ; j++ ) {
			if ( j == 0 || j == width )
				putchar(219);
			if ( i == headY && j == headX )
				putchar(254);		
			else if ( i == fruitY && j == fruitX ) 
				putchar(249);
			else {
				bool prTail = false;
				for ( int k = 0; k < snakeTailLen; k++ ) {
					if ( snakeTailX[k] == j && snakeTailY[k] == i ) {
						putchar(254);
						prTail = true;
					}	
				}
				if (!prTail) 
				putchar(' ');
			}
		}
		printf("\n");
	}
	for ( int i = 0; i < width + 2; i++ ) 
		putchar(223);
	printf("\n");
	
	cout << playerName << "'s Score: " << playerScore << endl;
}

void UpdateGame() {
	int prevx = snakeTailX[0];
	int prevy = snakeTailY[0];
	int prev2X,prev2Y;
	snakeTailX[0] = headX;
	snakeTailY[0] = headY;
	
	for ( int i = 1; i < snakeTailLen; i++ ) {
		prev2X = snakeTailX[i];
		prev2Y = snakeTailY[i];
		snakeTailX[i] = prevx;
		snakeTailY[i] = prevy;
		prevx = prev2X;
		prevy = prev2Y;	 
	}
	
	switch (sDir) {
		case LEFT:
			headX--;
			break;
		case RIGHT:
			headX++;
			break;
		case UP:
			headY--;
			break;
		case DOWN:
			headY++;
			break;			
	}
	
	if ( headX >= width || headX < 0 || headY >= height || headY < 0  	)
		isGameOver = true;
	for ( int i = 0; i < snakeTailLen; i++ ) {
		if ( snakeTailX[i] == headX && snakeTailY[i] == headY ) {
			isGameOver = true;
		}
	}
	if ( headX == fruitX && headY == fruitY ) {
		playerScore += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		snakeTailLen++;
	}	
}

int SetDifficulty() {
	int dfc;
	char choice = '2';
	puts("SET DIFFICULTY:\n1] Easy\n2] Meduim\n3] Hard");
	choice = getche();
	
	switch (choice) {
		case '1':
			dfc = 50;
			break;
		case '2':
			dfc = 100;
			break;
		case '3':
			dfc = 150;
			break;
		default:
			dfc = 100;
			break;	 
	}
	return dfc;
}

void UserInput() {
	if ( _kbhit() ) {
		switch (_getch()) {
			case 75:
				sDir = LEFT;
				break;
			case 77:
				sDir = RIGHT;
				break;
			case 72:
				sDir = UP;
				break;
			case 80:
				sDir = DOWN;
				break;
			case 'x':
				isGameOver = true;
				break;			
		}
	}
}