#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

int x[4][4];
int a[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0 };

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void mixing()
{
	srand(time(0));

	for (int i = 0; i < 16; i++)
	{
		int s = a[i], j = rand() % 15;
		a[i] = a[j];
		a[j] = s;
	}
}

void transposition_parity(int zero_pos[])
{
	int N = 0, e;

	for (int i = 0; i < 16; i++)
	{
		if (a[i] != 0)
			for (int j = i + 1; j < 16; j++)
			{
				if (a[j] < a[i] && a[j] != 0)
					N++;
			}
		else
		{
			e = i / 4 + 1;
			zero_pos[0] = i / 4;
			zero_pos[1] = i % 4;
		}
	}

	if ((N + e) % 2)
		for (int i = 0; i < 16; i++)
			if (a[i] == 14)
				a[i] = 15;
			else if (a[i] == 15)
				a[i] = 14;

	for (int i = 0; i < 16; i++)
		x[i / 4][i % 4] = a[i];
}

void control(int z[], int i0, int j0)
{
	//z[0], z[1] - zero position
	//z[2] - counter steps
	if (_kbhit())
		switch (_getch())
		{
		case 72: //UP
		{
			if (i0 != 3)
			{
				x[i0][j0] = x[i0 + 1][j0];
				x[i0 + 1][j0] = 0;
				i0++;
				z[2]++;
			}
			break;
		}

		case 80: //DOWN
		{
			if (i0 != 0)
			{
				x[i0][j0] = x[i0 - 1][j0];
				x[i0 - 1][j0] = 0;
				i0--;
				z[2]++;
			}
			break;
		}

		case 77: //RIGHT
		{
			if (j0 != 0)
			{
				x[i0][j0] = x[i0][j0 - 1];
				x[i0][j0 - 1] = 0;
				j0--;
				z[2]++;
			}
			break;
		}

		case 75: //LEFT
		{
			if (j0 != 3)
			{
				x[i0][j0] = x[i0][j0 + 1];
				x[i0][j0 + 1] = 0;
				j0++;
				z[2]++;
			}
			break;
		}
		}
	z[0] = i0;
	z[1] = j0;
}

int puzzle_model(char mode[])
{
	if (mode[0] == '1')
		if (x[0][0] == 1 && x[0][1] == 2 && x[0][2] == 3 && x[0][3] == 4 && x[1][0] == 5 && x[1][1] == 6 && x[1][2] == 7 && x[1][3] == 8 && x[2][0] == 9 && x[2][1] == 10 && x[2][2] == 11 && x[2][3] == 12 && x[3][0] == 13 && x[3][1] == 14 && x[3][2] == 15 && x[3][3] == 0)
			return 1;
		else return 0;
	// STANDART MODEL

	if (mode[0] == '2')
		if (x[0][0] == 0 && x[0][1] == 15 && x[0][2] == 14 && x[0][3] == 13 && x[1][0] == 12 && x[1][1] == 11 && x[1][2] == 10 && x[1][3] == 9 && x[2][0] == 8 && x[2][1] == 7 && x[2][2] == 6 && x[2][3] == 5 && x[3][0] == 4 && x[3][1] == 3 && x[3][2] == 2 && x[3][3] == 1)
			return 1;
		else return 0;
	// MIRROR MODEL

	if (mode[0] == '3')
		if (x[0][0] == 7 && x[0][1] == 8 && x[0][2] == 9 && x[0][3] == 10 && x[1][0] == 6 && x[1][1] == 1 && x[1][2] == 2 && x[1][3] == 11 && x[2][0] == 5 && x[2][1] == 4 && x[2][2] == 3 && x[2][3] == 12 && x[3][0] == 0 && x[3][1] == 15 && x[3][2] == 14 && x[3][3] == 13)
			return 1;
		else return 0;
	//SPIRAL MODEL

	if (mode[0] == 27)
		return -1;
	//EXIT
}

void menu(char a[])
{
	do
	{
		system("cls");
		SetColor(15, 0);
		printf("///////////////////////////////////////////////////////////////////////////\n");
		printf("//                                                                       //\n");
		printf("//  Welcome to...                                                        //\n");
		printf("//                                                                       //\n");
		printf("//     11  55555     PPPPPP  UU  UU  ZZZZZZZ  ZZZZZZZ  LL      EEEEE     //\n");
		printf("//    111  55        PP  PP  UU  UU      ZZ       ZZ   LL      EE        //\n");
		printf("//     11  55555  =  PPPPPP  UU  UU    ZZZ      ZZZ    LL      EEEE      //\n");
		printf("//     11     55     PP      UU  UU   ZZ       ZZ      LL      EE        //\n");
		printf("//     11  55555     PP       UUUU   ZZZZZZZ  ZZZZZZZ  LLLLLL  EEEEE     //\n");
		printf("//                                                                       //\n//");
		SetColor(1, 0);
		printf("               STANDART(1)     MIRROR(2)       SPIRAL(3)");
		SetColor(15, 0);
		printf("               //\n//                                                                       //\n//");
		SetColor(10, 0);
		printf("               1  2  3  4    __ 15 14 13      7  8  9 10");
		SetColor(15, 0);
		printf("               //\n//");
		SetColor(10, 0);
		printf("               5  6  7  8    12 11 10  9      6  1  2 11");
		SetColor(15, 0);
		printf("               //\n//");
		SetColor(10, 0);
		printf("               9 10 11 12     8  7  6  5      5  4  3 12");
		SetColor(15, 0);
		printf("               //\n//");
		SetColor(10, 0);
		printf("              13 14 15 __     4  3  2  1     __ 15 14 13");
		SetColor(15, 0);
		printf("               //\n//                                                                       //\n//");
		SetColor(9, 0);
		printf("               PRESS ON THE GAME NUMBER(EXIT - 'ESCAPE')");
		SetColor(15, 0);
		printf("               //\n//                                                                       //\n");
		printf("///////////////////////////////////////////////////////////////////////////");
		if (!_kbhit())
			switch (_getch())
			{
			case '1':
			{
				a[0] = '1';
				break;
			}

			case '2':
			{
				a[0] = '2';
				break;
			}

			case '3':
			{
				a[0] = '3';
				break;
			}

			case 27:
			{
				a[0] = 27;
				break;
			}
			}
	} while (a[0] != '1' && a[0] != '2' && a[0] != '3' && a[0] != 27);
}

void board(int steps)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			if (x[i][j] == 0)
			{

				SetColor(0, 0);
				printf("%3i", x[i][j]);
			}
			else
			{
				SetColor(10, 0);
				printf("%3i", x[i][j]);
			}
		SetColor(15, 0);
		printf("\n//  ");
	}
	gotoxy(20, 2);
	SetColor(9, 0);
	printf("STEPS:  ");
	SetColor(15, 0);
	printf("%i", steps);
}

void frame()
{
	SetColor(15, 0);
	printf("///////////////////////////////////////////////////////////////////////////\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n//");
	SetColor(1, 0);
	printf("               STANDART(1)     MIRROR(2)       SPIRAL(3)");
	SetColor(15, 0);
	printf("               //\n//                                                                       //\n//");
	SetColor(10, 0);
	printf("               1  2  3  4    __ 15 14 13      7  8  9 10");
	SetColor(15, 0);
	printf("               //\n//");
	SetColor(10, 0);
	printf("               5  6  7  8    12 11 10  9      6  1  2 11");
	SetColor(15, 0);
	printf("               //\n//");
	SetColor(10, 0);
	printf("               9 10 11 12     8  7  6  5      5  4  3 12");
	SetColor(15, 0);
	printf("               //\n//");
	SetColor(10, 0);
	printf("              13 14 15 __     4  3  2  1     __ 15 14 13");
	SetColor(15, 0);
	printf("               //\n//                                                                       //\n//");
	printf("                                                         ");
	printf("              //\n//                                                                       //\n");
	printf("///////////////////////////////////////////////////////////////////////////");
}

void end_game(char ans[], int steps)
{
	SetColor(14, 0);
	printf("///////////////////////////////////////////////////////////////////////////\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//    EEEEE  NNN   NN  DDDDDD      GGGGGGG   AAAAAA   MM    MM  EEEEE    //\n");
	printf("//    EE     NNNN  NN  DD   DD     GG       AA    AA  MMM  MMM  EE       //\n");
	printf("//    EEEE   NN NN NN  DD   DD     GG  GGG  AA    AA  MM MM MM  EEEE     //\n");
	printf("//    EE     NN  NNNN  DD   DD     GG   GG  AAAAAAAA  MM    MM  EE       //\n");
	printf("//    EEEEE  NN   NNN  DDDDDD      GGGGGGG  AA    AA  MM    MM  EEEEE    //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n//");
	SetColor(9, 0);
	printf("                           %5i STEPS                                 ", steps);
	SetColor(14, 0);
	printf("//\n//                                                                       //\n//");
	SetColor(10, 0);
	printf("               'ENTER' - CONTINUE | 'ESCAPE' - EXIT                    ");
	SetColor(14, 0);
	printf("//\n//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("//                                                                       //\n");
	printf("///////////////////////////////////////////////////////////////////////////");
	if (!_kbhit())
		switch (_getch())
		{
		case 13://ENTER
		{
			ans[0] = 13;
			break;
		}

		case 27: //ESCAPE
		{
			ans[0] = 27;
			break;
		}
		}
}

int main()
{
	int z[3], i0, j0, steps = 0;
	char mode[1], ans[1];
	z[2] = 0;

	system("mode con cols=75 lines=20");

	do
	{
	   ///BEGIN///
		{
			ans[0] = 0;
			mixing();
			transposition_parity(z);
			menu(mode);
			system("cls");
		}
	   ///////////
		
		///GAME///
		{
			if (puzzle_model(mode) != -1)
		{
			frame();
			while (puzzle_model(mode) != 1)
			{
				gotoxy(4, 2);
				board(z[2]);
				_getch(); //PAUSE
				i0 = z[0];
				j0 = z[1];
				control(z, i0, j0);
			}
		}
			else
		{
			system("cls");
			return 0;
		}
			steps = z[2];
			z[2] = 0;
		}
		//////////
		
		////END////
		do
		{
			system("cls");
			end_game(ans, steps);
			z[2] = 0;
		} while (ans[0] != 27 && ans[0] != 13);
		///////////
		
	} while (ans[0] != 27);

	system("cls");
	return 0;
}