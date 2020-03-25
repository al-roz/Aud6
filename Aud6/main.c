#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <lm.h>
#include <LMaccess.h>

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

	/*
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
	*/


	LPUSER_INFO_1 pBuf = NULL;
	LPUSER_INFO_1 pTmpBuf;
	DWORD dwLevel = 1;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	DWORD i;
	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus;
	LPTSTR pszServerName = NULL;

	do
	{
		nStatus = NetUserEnum((LPCWSTR)pszServerName,
			dwLevel,
			FILTER_NORMAL_ACCOUNT,
			(LPBYTE*)&pBuf,
			dwPrefMaxLen,
			&dwEntriesRead,
			&dwTotalEntries,
			&dwResumeHandle);
		//
		// Если вызов выполнен успешно
		//
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			if ((pTmpBuf = pBuf) != NULL)
			{
				//
				// Цикл по записям.
				//
				for (i = 0; (i < dwEntriesRead); i++)
				{
					assert(pTmpBuf != NULL);

					if (pTmpBuf == NULL)
					{
						fprintf(stderr, "An access violation has occurred\n");
						break;
					}
					//
					// Вывод имени пользователя.
					//
					if (pTmpBuf->usri1_priv == USER_PRIV_USER) _wprintf_l(L"\t-- %s\n", "Russian", pTmpBuf->usri1_name);

					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}
		//
		// Otherwise, print the system error.
		//
		else
			fprintf(stderr, "A system error has occurred: %d\n", nStatus);
		//
		// Free the allocated buffer.
		//
		if (pBuf != NULL)
		{
			NetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	} while (nStatus == ERROR_MORE_DATA);

	if (pBuf != NULL)
		NetApiBufferFree(pBuf);

	//printf("sad");
}