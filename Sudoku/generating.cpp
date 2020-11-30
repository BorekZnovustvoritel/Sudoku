#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "gameFunctions.h"
#include "otherFunctions.h"
#include "generating.h"
#include <time.h>

void mixRow(chmat matrix, int first, int second)
{
	char buffer;
	for (int n = 0; n < 9; n++)
	{
		buffer = matrix[second][n];
		matrix[second][n] = matrix[first][n];
		matrix[first][n] = buffer;
	}
}

void mixColumns(chmat matrix, int first, int second)
{
	char buffer;
	for (int m = 0; m < 9; m++)
	{
		buffer = matrix[m][second];
		matrix[m][second] = matrix[m][first];
		matrix[m][first] = buffer;
	}
}

void swapNumbers(chmat matrix, char first, char second)
{
	int firstcoords[18];
	int i = 0;
	int secondcoords[18];
	int j = 0;
	for (int m = 0; m < 9; m++)
	{
		for (int n = 0; n < 9; n++)
		{
			if (matrix[m][n] == second)
			{
				secondcoords[i++] = m;
				secondcoords[i++] = n;
			}
			if (matrix[m][n] == first)
			{
				firstcoords[j++] = m;
				firstcoords[j++] = n;
			}
		}
	}
	for (int i = 0; i < 18; i += 2)
	{
		matrix[secondcoords[i]][secondcoords[i + 1]] = first;
		matrix[firstcoords[i]][firstcoords[i + 1]] = second;
	}
}

void puncture(chmat matrix, int difficulty)
{
	int m;
	int n;
	int i = 0;
	int Ematrix[9][9];
	flushMatrix(Ematrix);
	int attempts = 0;
	printf("\nGenerating...\n");
	while (i < (15 + difficulty * 4) && attempts < 1000000)
	{
		attempts++;
		m = (rand() * 100) % 9;
		n = (rand() * 100) % 9;
		if (matrix[m][n] != '0')
		{
			int numOfFails = 0;
			char buffer = matrix[m][n];
			Ematrix[m][n] = 0;
			for (char j = '1'; j <= '9'; j++) //pokud odebereme toto cislo, bude reseni jednoznacne?
			{
				matrix[m][n] = j;
				checkRow(matrix, Ematrix, m);
				checkColumn(matrix, Ematrix, n);
				int startgridM, startgridN;
				if(m<3) //prirazeni zacatku bunky
				{
					startgridM = 0;
				}
				else if (m < 6)
				{
					startgridM = 3;
				}
				else
				{
					startgridM = 6;
				}
				if (n < 3)
				{
					startgridN = 0;
				}
				else if (n < 6)
				{
					startgridN = 3;
				}
				else
				{
					startgridN = 6;
				}
				checkGrid(matrix, Ematrix, startgridM, startgridN);
				if (Ematrix[m][n] == 1)
				{
					numOfFails++;
				}
				Ematrix[m][n] = 0;
			}
			if (numOfFails == 8) //ano, bude jednoznacne
			{
				matrix[m][n] = '0';
				i++; //vyderovanych mist
				attempts = 0;
			}
			else //ne, nebude jednoznacne
			{
				matrix[m][n] = buffer;
			}
		}
	}
}

void mixAndClone(chmat Omatrix, chmat Gmatrix, int difficulty)
{
	srand(time(NULL));
	int r, s, t, u;
	for (int i = 0; i < 50; i++)
	{
		r = (rand() * 100) % 9; //cislo radku/sloupce
		if (r == 2 || r == 5 || r == 8)
		{
			s = r - 2; //cislo radku/sloupce, se kterym se ma vymenit
		}
		else
		{
			s = r + 1;
		}
		mixRow(Omatrix, r, s);
		mixColumns(Omatrix, r, s);
		
		t = 1 + (rand() * 100) % 9; //ktere cislo vymenime?
		do
		{
			u = 1 + (rand() * 100) % 9; //s kterym?
		} while (u == t);
		swapNumbers(Omatrix, '0' + t, '0' + u);
	}
	puncture(Omatrix, difficulty);

	for (int m = 0; m < 9; m++) //kopirovani, at je reference i hracske pole stejne
	{
		for (int n = 0; n < 9; n++)
		{
			Gmatrix[m][n] = Omatrix[m][n];
		}
	}
}