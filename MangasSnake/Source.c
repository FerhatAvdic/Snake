#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
void screen(void);
int main()
{
	printf("Use 2,4,6,8 to move around , dont bite yourself \n");
	printf("Press Enter to continue");
	_getch();
	screen();
	return 0;
}

void screen()
{
	int i, j, x1, y1, w, score, z;
	char m[20][20] = { " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " " };
	char s = '*';
	char h = '>';
	w = 3;
	char f = '8';
	char prevchoice = '6';
	char choice = '6';
	int x[80];
	int y[80];
	x[0] = 0;
	y[0] = 0;
	x1 = 5;
	y1 = 5;

	z = 250;

	score = 0;
	while (1)
	{

		for (i = w; i > 0; i--){
			x[i] = x[i - 1]; y[i] = y[i - 1];
			x[1] = x[0]; y[1] = y[0];
		}
		Sleep(250);
		if (_kbhit()){
			prevchoice = choice;
			choice = _getch();
			if (choice == '6') h = '>';
			if (choice == '4') h = '<';
			if (choice == '8') h = '^';
			if (choice == '2') h = 'v';


			if (choice == '6' && prevchoice == '4') choice = prevchoice;
			if (choice == '4' && prevchoice == '6') choice = prevchoice;
			if (choice == '8' && prevchoice == '2') choice = prevchoice;
			if (choice == '2' && prevchoice == '8') choice = prevchoice;
			if (choice != '8' && choice != '6' && choice != '4' && choice != '2') choice = prevchoice;
			if (choice == '6') { if (y[0] == 19) y[0] = 0; else y[0]++; }
			else if (choice == '4') { if (y[0] == 0) y[0] = 19; else y[0]--; }
			else if (choice == '8') { if (x[0] == 0) x[0] = 19; else x[0]--; }
			else if (choice == '2') { if (x[0] == 19) x[0] = 0; else x[0]++; }
		}
		else{
			if (choice == '6') { if (y[0] == 19) y[0] = 0; else y[0]++; }
			else if (choice == '4') { if (y[0] == 0) y[0] = 19; else y[0]--; }
			else if (choice == '8') { if (x[0] == 0) x[0] = 19; else x[0]--; }
			else if (choice == '2') { if (x[0] == 19) x[0] = 0; else x[0]++; }
		}
		m[x1][y1] = f;

		for (i = 0; i < w; i++)
		{
			if (i == 0) 
				m[x[i]][y[i]] = h;
			else 
				m[x[i]][y[i]] = s;

		}

		m[x[w - 1]][y[w - 1]] = ' ';

		system("cls");

		printf("\t**********\n\t*SCORE:%d*\n\t**********\n", score);
		printf("#----------------------------------------#\n");
		for (i = 0; i < 20; i++)
		{
			printf("|");

			for (j = 0; j < 20; j++)
			{

				printf("%c ", m[i][j]);
			}
			printf("|\n");
		}
		printf("#----------------------------------------#\n");
		if (m[x[0]][y[0]] == '*') { system("cls"); printf("GAME OVER!"); Sleep(2000); break; }
		
		if (x[0] == x1 && y[0] == y1) { w++; z--; score++; m[x[0]][y[0]] = ' '; x1 = rand() % 20; y1 = rand() % 20; }

	}



}