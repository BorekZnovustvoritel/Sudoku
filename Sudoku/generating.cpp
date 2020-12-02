#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "gameFunctions.h"
#include "menuFunctions.h"
#include "otherFunctions.h"
#include "generating.h"
#include <time.h>


void mixRow(chmat matrix, int first, int second) //zmena radku v jednom tripletu
{
	char buffer;
	for (int n = 0; n < 9; n++)
	{
		buffer = matrix[second][n];
		matrix[second][n] = matrix[first][n];
		matrix[first][n] = buffer;
	}
}

void mixColumns(chmat matrix, int first, int second) //zmena sloupcu v jednom tripletu
{
	char buffer;
	for (int m = 0; m < 9; m++)
	{
		buffer = matrix[m][second];
		matrix[m][second] = matrix[m][first];
		matrix[m][first] = buffer;
	}
}

void swapNumbers(chmat matrix, char first, char second) //zamena devitic cisel (1 <-> 2 apod.)
{
	int firstcoords[18]; //bude drzet souradnice cisel, ktere chceme prohodit, souradnice drzime za sebou
	int i = 0; //promenna, drzi akt. pozici pro zapis do tabulky souradnic
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
		matrix[secondcoords[i]][secondcoords[i + 1]] = first; //prohozeni cisel
		matrix[firstcoords[i]][firstcoords[i + 1]] = second;
	}
}

void puncture(chmat matrix, int difficulty)  //derovani
{
	int m, n; //souradnice pro derovani
	int i = 0; //promenna, ktera urcuje, kolik der se ma udelat
	int Ematrix[9][9]; //pro pouziti funkci na kontrolu hraciho pole
	flushMatrix(Ematrix);
	int attempts = 0;
	printf("\nGenerating...\n");
	while (i < (15 + difficulty * 4) && attempts < MAX_ATTEMPTS) //kazdy obtiznostni bod prida 4 diry. 19 der je minimum. Pokud se dlouho nedari udelat dalsi diry, cyklus se ukonci
	{
		attempts++;
		m = rand() % 9;
		n = rand() % 9;
		if (matrix[m][n] != '0') //jen pokud uz neni vyderovano
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
				if(m<3) //prirazeni zacatku bunky pro funkci checkGrid
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
				attempts = 0; //reset pocitadla pokusu
			}
			else //ne, nebude jednoznacne
			{
				matrix[m][n] = buffer; //vratime hodnotu
			}
		}
	}
}

void mixAndClone(chmat Omatrix, chmat Gmatrix, int difficulty) //funkce volajici vyse definovane funkce ve spravnem poradi
{
	srand(time(NULL));
	int r, s, t, u;
	for (int i = 0; i < 50; i++)
	{
		r = rand() % 9; //cislo radku/sloupce
		if (r == 2 || r == 5 || r == 8) //r a s musi by ze stejneho tripletu
		{
			s = r - 2; //cislo radku/sloupce, se kterym se ma vymenit
		}
		else
		{
			s = r + 1;
		}
		mixRow(Omatrix, r, s);
		mixColumns(Omatrix, r, s);
		
		t = 1 + rand() % 9; //ktere cislo vymenime?
		do
		{
			u = 1 + rand() % 9; //s kterym?
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