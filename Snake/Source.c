#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>

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

int main()
{
	char menuChoice = '2';
	while (1)
	{
		mainMenu();
		if (menuChoice < 49 || menuChoice > 52)
			printf("\n\n\t\t\t\t ERROR: Wrong input. Try again.\n");
		menuChoice = getch();
		switch (menuChoice)
		{
		case '1':	playGame();			break;
		case '2':	instructions();		break;
		case '3':	viewScores();		break;
		case '4':	return 0;			break;
		default :	system("cls");		break;
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
	printf("\n\t\t\t\t| [3] View scores                     |");
	printf("\n\t\t\t\t| [4] Exit                            |");
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
	printf("\n\t\t SCORE: %d\t\t      %s", score, dead==1 ? "GAME OVER" : " ");
	printf("\n\t\t -----------");
	printf("\n\n\t\t");
}

void saveScore(int score)
{
	fflush(stdin);
	char name[10];
	char *pos;
	printf("Enter nickname: ");
	fgets(name, 10, stdin);
	if ((pos = strchr(name, '\n')) != NULL)
		*pos = '\0';
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
			// snake
			field[rowSize/2][columnSize/2] = 248;
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
	snakeY[0] = rowSize / 2;
	int snakeBody = 6;
	int dead = 0;
	int move = 0;

	int wormX[500];
	int wormY[500];
	int indexWorm = 0;

	char prevControl;
	char control = 'w';

	time_t t;
	srand((unsigned)time(&t));
	createField();

	while (dead==0)
	{
		system("cls");
		inGameScore(score, dead);
		printField();
		// snake body follows snake head x,y
		for (int i = 1; i <= snakeBody; i++)
		{
			snakeY[i] = snakeY[i - 1];
			snakeX[i] = snakeX[i - 1];
		}

		if (_kbhit())
		{
			prevControl = control;
			control = _getch();

			if (control == 'w' || control == 'W')		snakeY[0]--;
			if (control == 's' || control == 'S')		snakeY[0]++;	
			if (control == 'a' || control == 'A')		snakeX[0]--;
			if (control == 'd' || control == 'D')		snakeX[0]++;
			if (control == 27)  return 0;
			/*
			// Movement restrictions
			if (control == 'w' && prevControl == 's' || control == 'W' && prevControl == 'S')	control = prevControl;
			if (control == 's' && prevControl == 'w' || control == 'S' && prevControl == 'W')	control = prevControl;
			if (control == 'a' && prevControl == 'd' || control == 'A' && prevControl == 'D')	control = prevControl;
			if (control == 'd' && prevControl == 'a' || control == 'D' && prevControl == 'A')	control = prevControl;

			// Disabling other keys
			if (control != 'w' && control != 'W' && 
				control != 'a' && control != 'A' && 
				control != 's' && control != 'S' &&
				control != 'd' && control != 'D' &&
				control != 27) control = prevControl;
			*/
		}
		else
		{
			if (control == 'w' || control == 'W')		snakeY[0]--;
			if (control == 's' || control == 'S')		snakeY[0]++;
			if (control == 'a' || control == 'A')		snakeX[0]--;
			if (control == 'd' || control == 'D')		snakeX[0]++;
			if (control == 27)	return 0;
		}


		// create snake head
		field[snakeY[0]][snakeX[0]] = 248;
		// create snake body
		for (int i = 1; i <= snakeBody; i++)
		{
			field[snakeY[i]][snakeX[i]] = '*';
		}	
		// wipe snake body trace
		field[snakeY[snakeBody]][snakeX[snakeBody]] = ' ';

		// generate worms every 10 moves/screen blinks
		wormY[indexWorm] = 1 + (rand() % (rowSize    - 2));
		wormX[indexWorm] = 1 + (rand() % (columnSize - 2));
		if (move % 20 == 0)
		{
			field[wormY[indexWorm]][wormX[indexWorm]] = '~';
			indexWorm++;
		}

		// increase score and snakebody when snake eats a worm
		for (int i = 0; i <= indexWorm; i++)
		if (snakeY[0] == wormY[i] && snakeX[0] == wormX[i])
		{
			score++;
			snakeBody++;
			// new body instance follows last body instance
			snakeY[snakeBody] = snakeY[snakeBody - 1];
			snakeX[snakeBody] = snakeX[snakeBody - 1];
		}
		// death conditions
		if (snakeY[0] == 0)						dead = 1;
		else if (snakeY[0] == rowSize - 1)		dead = 1;
		if (snakeX[0] == 0)						dead = 1;
		else if (snakeX[0] == columnSize - 1)	dead = 1;

		move++;		
		Sleep(100);
	}
	system("cls"); 
	inGameScore(score, dead);
	printField();
	saveScore(score);
	printf("\n\t\t");
	system("Pause");
	return 0;
}