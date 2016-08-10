#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define rowSize 17
#define columnSize 33

char field[rowSize][columnSize];

FILE *fp;

void mainMenu();
int playGame();
void instructions();
void createField();
void inGameScore(int score, int dead);
void printField();
void saveScore(int score);
void viewScores();
void deleteScores();

int main()
{
	char menuChoice = '2';
	while (1)
	{
		mainMenu();
		if (menuChoice < 49 || menuChoice > 53)
			printf("\n\n\t\t\t\t ERROR: Wrong input. Try again.\n");
		menuChoice = getch();
		switch (menuChoice)
		{
		case '1':	playGame();			break;
		case '2':	instructions();		break;
		case '3':	viewScores();		break;
		case '4':	deleteScores();		break;
		case '5':	return 0;			break;
		default:	system("cls");		break;
		}
	}
}

void mainMenu()
{
	system("cls");
	printf("\n\n\t\t\t\t ------------------------------------- ");
	printf("\n\t\t\t\t|              GAME MENU              |");
	printf("\n\t\t\t\t|-------------------------------------|");
	printf("\n\t\t\t\t|                                     |");
	printf("\n\t\t\t\t| [1] Play Game                       |");
	printf("\n\t\t\t\t| [2] Instructions                    |");
	printf("\n\t\t\t\t| [3] View Scores                     |");
	printf("\n\t\t\t\t| [4] Delete Scores                   |");
	printf("\n\t\t\t\t| [5] Exit                            |");
	printf("\n\t\t\t\t|                                     |");
	printf("\n\t\t\t\t ------------------------------------- ");

}

void instructions()
{
	system("cls");
	printf("\n\n\t\t\t\t ------------------------------------- ");
	printf("\n\t\t\t\t|             INSTRUCTIONS            | ");
	printf("\n\t\t\t\t|-------------------------------------|");
	printf("\n\t\t\t\t|                                     |");
	printf("\n\t\t\t\t| -> Eat worms to increase score      |");
	printf("\n\t\t\t\t| -> Don't eat yellow snow            |");
	printf("\n\t\t\t\t| -> Use W,A,S,D keys to play         |");
	printf("\n\t\t\t\t| -> Snake dies if you hit the wall   |");
	printf("\n\t\t\t\t|    or if it bites itself            |");
	printf("\n\t\t\t\t|                                     |");
	printf("\n\t\t\t\t ------------------------------------- \n\n\t\t\t\t");
	system("Pause");
}

void inGameScore(int score, int dead)
{
	printf("\n");
	printf("\n\t\t SCORE: %d\t\t      %s", score, dead == 1 ? "GAME OVER" : " ");
	printf("\n\t\t -----------");
	printf("\n\n\t\t");
}

void saveScore(int score)
{
	fflush(stdin);
	char name[10];
	printf("Enter nickname: ");
	fgets(name, 10, stdin);
	strtok(name, "\n");
	fp = fopen("C:/Users/Ferhat/Documents/Visual Studio 2013/Projects/Special/Snake/scores.txt", "a");
	fprintf(fp, "%s: %d\n", name, score);
	fclose(fp);
}

void viewScores()
{
	system("cls");
	int c;
	fp = fopen("C:/Users/Ferhat/Documents/Visual Studio 2013/Projects/Special/Snake/scores.txt", "r");
	// Algorithm to read a character from the txt file, and print it right after reading
	if (fp) {
		while ((c = getc(fp)) != EOF)
			putchar(c);
		fclose(fp);
	}
	system("Pause");
	system("cls");
}

void deleteScores()
{
	system("cls");
	fp = fopen("C:/Users/Ferhat/Documents/Visual Studio 2013/Projects/Special/Snake/scores.txt", "w");
	fclose(fp);
	printf("Scores successfully erased.\n");
	system("Pause");
	system("cls");
}

void createField()
{
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < columnSize; j++)
		{
			if (i == 0 && j == 0) // top left corner
				field[i][j] = 254;// 201;
			else if (i == 0 && j == columnSize - 1) // top right corner
				field[i][j] = 254; //187;
			else if (i == rowSize - 1 && j == 0) // bottom left corner
				field[i][j] = 254;// 200;
			else if (i == rowSize - 1 && j == columnSize - 1) // bottom right corner
				field[i][j] = 254; // 188;
			else if (i == 0 || i == rowSize - 1) // top and bottom row
				field[i][j] = 254; // 205;
			else if (j == 0 || j == columnSize - 1) // sides
				field[i][j] = 254; // 186;
			else
				field[i][j] = ' ';
		}
	}
}

void printField()
{
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < columnSize; j++)
		{
			printf(" %c", field[i][j]);
		}
		printf("\n\t\t");
	}
}

int playGame()
{
	system("cls");
	int score = 0;

	int snakeX[500];
	int snakeY[500];
	snakeX[0] = columnSize / 2;
	snakeY[0] = rowSize / 2 + 1;
	int snakeBody = 2;
	int dead = 0;
	int move = 0;

	int wormX;
	int wormY;

	int i; // just a loop control variable initialized

	// variable to store control keys
	char prevControl;
	char control = 'w';

	// generate random seed
	time_t t;
	srand((unsigned)time(&t));

	createField();

	// generate first worm
	wormY = 1 + (rand() % (rowSize - 2));
	wormX = 1 + (rand() % (columnSize - 2));

	while (dead == 0)
	{
		// snake body follows snake head x,y
		for (i = snakeBody; i > 0; i--)
		{
			snakeY[i] = snakeY[i - 1];
			snakeX[i] = snakeX[i - 1];
		}

		Sleep(100);
		if (_kbhit())
		{
			prevControl = control;
			control = _getch();

			if (control == 'w' || control == 'W') snakeY[0]--;
			if (control == 's' || control == 'S') snakeY[0]++;
			if (control == 'a' || control == 'A') snakeX[0]--;
			if (control == 'd' || control == 'D') snakeX[0]++;
			if (control == 27) return 0;

			// Movement restrictions
			if (control == 'w' && prevControl == 's' || control == 'W' && prevControl == 'S') control = prevControl;
			if (control == 's' && prevControl == 'w' || control == 'S' && prevControl == 'W') control = prevControl;
			if (control == 'a' && prevControl == 'd' || control == 'A' && prevControl == 'D') control = prevControl;
			if (control == 'd' && prevControl == 'a' || control == 'D' && prevControl == 'A') control = prevControl;

			// Disabling other keys
			if (control != 'w' && control != 'W' &&
				control != 'a' && control != 'A' &&
				control != 's' && control != 'S' &&
				control != 'd' && control != 'D' &&
				control != 27) control = prevControl;
		}
		else
		{
			if (control == 'w' || control == 'W') snakeY[0]--;
			if (control == 's' || control == 'S') snakeY[0]++;
			if (control == 'a' || control == 'A') snakeX[0]--;
			if (control == 'd' || control == 'D') snakeX[0]++;
			if (control == 27) return 0;
		}

		// create snake body
		for (i = 1; i < snakeBody; i++)
			field[snakeY[i]][snakeX[i]] = '*';
		// create worm
		field[wormY][wormX] = '~';
		// create snake head
		field[snakeY[0]][snakeX[0]] = 248;

		system("cls");
		inGameScore(score, dead);
		printField();

		// wipe body trace
		field[snakeY[snakeBody - 1]][snakeX[snakeBody - 1]] = ' ';

		// increase score and snake when snake eats worms
		if (snakeY[0] == wormY && snakeX[0] == wormX)
		{
			snakeBody++;
			score++;
			// generate worm
			wormY = 1 + (rand() % (rowSize - 2));
			wormX = 1 + (rand() % (columnSize - 2));
		}

		// death conditions
		// hit the wall
		if (snakeY[0] == 0) dead = 1;
		else if (snakeY[0] == rowSize - 1) dead = 1;
		if (snakeX[0] == 0) dead = 1;
		else if (snakeX[0] == columnSize - 1) dead = 1;
		// bite itself
		for (i = 1; i < snakeBody; i++)
		if (snakeY[0] == snakeY[i + 1] && snakeX[0] == snakeX[i + 1])	dead = 1;

		move++;


	}
	system("cls");
	inGameScore(score, dead);
	printField();
	saveScore(score);
	printf("\n\t\t");
	system("Pause");
	return 0;
}