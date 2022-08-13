
#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <windows.h>
using namespace std;

//variables and functions
int a = 1, b = 10; //screen position
int row = 15;	   //getmaxx();
int column = 10;   //getmaxy();
int pi = 15;	   //getmaxx()-5;
int pj = 15;	   //getmaxy()/2;
int c = 0, oi, oj, n = 500;
int score = 0, life = 1, fi, fj, lvl = 0;
void draw();
void control();
void obstacles();
void fruit();
void GameEnd();
void cardraw(int x, int y);
void gotoxy(int x, int y);

//main
int main()
{
	char str[100], name[20], ch;
	FILE *fp;

//welcome screen
x:

	system("CLS");
	cout << "\n\n\t\t\t=======================\n";
	cout << "\t\t\t  Welcome to the Game";
	cout << "\n\t\t\t=======================\n";

	cout << "\t\t\t    ::MAIN MENU::\n";
	cout << "\n\t\t\t1. START GAME";
	cout << "\n\t\t\t2. LEADERBOARD";
	cout << "\n\t\t\t3. EXIT";
	cout << "\n\n\t\t\tSelect Your Option (1-3): ";
	cin >> ch;

	//MENU
	switch (ch)
	{
	case '1':
		break;
	case '2':
		fp = fopen("leaderboard.txt", "r");
		if (fp == NULL)
		{
			printf("\t\tFile not found\n");
		}
		else
		{
			system("CLS");
			c = fgetc(fp);
			gotoxy(0, 5);
			printf("Leaderboard:\n");
			while (c != EOF)
			{
				printf("%c", c);
				c = fgetc(fp);
			}
			fclose(fp);
		}
		exit(0);
	case '3':
		exit(0);
	default:
		printf("\n\t\tPLEASE ENTER A VALID NUMBER");

		_sleep(1500);
		goto x;
	}

	//TAKING NAME
	system("CLS");
	gotoxy(5, 5);
	printf("ENTER NAME : ");
	scanf("%s", name);
	int n = 250;
	FILE *fptr;

	//function call
	while (life)
	{
		draw();

		control();

		_sleep(n);
	}
	//gameover
	printf("\n\n\n\t\t*gameover*");
	getch();
	GameEnd();
	fptr = fopen("score.txt", "a");
	if (fptr == NULL)
	{
		printf("Error in file reading");
		return 0;
	}
	fprintf(fptr, name);
	printf("HIGHSCORES : \n");

	for (int i = 0; i != EOF; i++)
	{
		fgets(str, sizeof str, stdin);
		fputs(str, fptr);
	}

	fclose(fptr);

	getch();
	return 0;
}
void gotoxy(int x, int y)
{
	COORD c = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw()
{
	if (n % (row + 1) == 0)
	{
		obstacles();
		fruit();
	}
	else
	{
		oi++;
		fi++;
	}

	//game body
	int i, j;
	n++;
	//clrscr();
	system("CLS");
	a = 1, b = 10; //screen position
	for (i = 0; i <= row; i++)
	{
		if (oj == pj - 1 && (oi == pi))
		{
			life = 0;
		}
		if ((fj == pj - 1) && (fi == row))
		{
			score += 10;
			int pl = score % (row * 10);
			if (pl == 0)
			{
				n = n - 50;
				lvl++;
			}
		}
		gotoxy(b, a++);
		printf("|");
		for (j = 10; j <= column + 10; j++)
			if (i == pi && j == pj)
				cardraw(pj, pi);
			else if (i == oi && j == oj)
			{
				printf("&"); //obstacles(oj,oi);
			}
			else if (i == fi && j == fj)
				printf("#"); //fruit(fj,fi);
			else
			{
				printf(" ");
			}

		printf("|");

		printf("\n");
		c++;
	}

	//  Bottom of game
	printf("\n");
	printf("\n");
	printf("\t\tSCORE= %d  LIFE= %d  LEVEL= %d\n", score, life, lvl);
	printf("\t\tPRESS <-- OR --> TO MOVE OBJECT LEFT OR RIGHT \n");
	printf("\t\t&=Obstracle #=Gifts\n");
	printf("\t\tPRESS ESC TO EXIT\n");
}

//Movement of car
void control()
{
	if (kbhit())
	{
		char c = getch();
		switch (c)
		{
		case 75:
		{
			pj--;
			break;
		}
		case 77:
		{
			pj++;
			break;
		}
		case 27:
		{
			exit(0);
		}
		}
	}
}

//Car Structure
void cardraw(int x, int y)
{

	gotoxy(x, y);
	printf("*");
	gotoxy(x - 1, y + 1);
	printf("***");
	gotoxy(x - 1, y + 2);
	printf(" * ");
	gotoxy(x - 1, y + 3);
	printf("***");
}

//Scoring Obstacle
void fruit()
{
	fi = 0;
	fj = rand() % column + b + 1;
}

//Obstacle
void obstacles()
{
	oi = 0;
	oj = rand() % column + b + 1;
}

void GameEnd()
{
	system("CLS");
	gotoxy(b, a);
	int x = (rand() + 1) % 9;

	//Slogans
	switch (x)
	{
	case 1:
		cout << "GO GREEN! There is no Planet B" << endl;
		break;
	case 2:
		cout << "Plans to protect air and water, wilderness and wildlife are in fact plans to protect man" << endl;
		break;
	case 3:
		cout << "The future will either be green or not at all" << endl;
		break;
	case 4:
		cout << "Make earth a better place for your children" << endl;
		break;
	case 5:
		cout << "Sadly, its much easier to create a desert than a forest" << endl;
		break;
	case 6:
		cout << "Earth is all we have in common" << endl;
		break;
	case 7:
		cout << "The environment is where we all meet, where we all have a mutual interest, it is the one thing all of us share" << endl;
		break;
	case 8:
		cout << "Save nature or start producing oxygen" << endl;
		break;
	case 9:
		cout << "The Earth is a fine place and worth fighting for" << endl;
		break;
	default:
		cout << "The Earth is a fine place and worth fighting for" << endl;
	}
	getch();
}


// #include