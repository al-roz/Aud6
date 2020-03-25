#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>


int MyIsDigit(char c)
{
	if (((int)c >= 48 && (int)c <= 57) || ((int)c >= 43 && (int)c <= 46))
		return 1; else  return 0;
}


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

int PasChek(char* s, int size)
{
	if (size < 8)return 0;
	int num = 0;
	int ch = 0;
	for (int i = 1; i < size; i++)
		if (MyIsDigit(s[i]) == 1) num++; else ch++;
	if (num == 0 || ch == 0) return 0;
	return 1;
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
		flag = PasChek(password,size);
		if (flag == 1) break;
		printf("Bad password\n");
		line++;
		//PrintPas(password,size);
	}
	printf("Good password");

}