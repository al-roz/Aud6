#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void PrintPas(char* s, int size)
{
	for (int i = 1; i < size; i++)
		printf("%c", s[i]);
}


int main()
{
	int flag = 0;
	int line = 0;
	int pos = 0;
	char password[21];
	while (flag != 1)
	{
		printf("Enter your prassword(max size 20)\n");
		line++;
		int size = 0;
		char x = ' ';
		while (size < 20 && x != '\r')
		{
			x = _getche();
			size++;			
			password[size] = x;
			if (x == '\b') size -= 2;
			gotoxy(size - 1 , line);
			if (x != '\r' && x != '\b') printf("*");
			if (x == '\b')
			{
				gotoxy(size, line);
				printf(" ");
				gotoxy(size, line);
			}
			
			//printf("%d\n", size);			
			if (size < 0) size = 1;
		}
		printf("\n");
		line++;
		//PrintPas(password,size);
	}

}