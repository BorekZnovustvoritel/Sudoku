#include <stdio.h>
#include <errno.h>
#include <windows.h>
#include <conio.h>
#include "gameFunctions.h"
#include "otherFunctions.h"
#include <ctype.h>

void showConsoleCursor(bool showFlag) //funkce z navodu, spousti se s parametrem TRUE/FALSE
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

int loadMatrix(char Omatrix[9][9], char Gmatrix[9][9], char* addr) //Nahraje hraci pole ze souboru do matic. Omatrix drzi neprepsatelne hodnoty, Gmatrix drzi pevne i uzivatelske hodnoty a addr je nazev souboru
{
    char chr;
    errno_t err;
    FILE* inputFile;
    if ((err = fopen_s(&inputFile, addr, "r")) == 0) //pokud nevyhodi otevirani souboru error
    {
        err = -1;
        int i = 0;
        int j = 0;
        while ((chr = getc(inputFile)) != EOF) //dokud nejsme na konci souboru
        {
            if (isdigit(chr) != 0)
            {
                if (i < 9)
                {
                    Omatrix[i][j] = chr; //prvnich 81  cisel je nahrano do pevne matice
                }
                else
                {
                    Gmatrix[i - 9][j] = chr; //dalsich 81 cisel se nahraje do matice, se kterou hrac interaguje
                }
                if (j == 8) 
                {
                    i++;
                    j = 0;
                    if (i == 18) //bereme jen 162 symbolu. i se prepne pri poslednim symbolu na hodnotu 18, j na nulu
                    {
                        err = 0; //jen pokud se zaplni obe matice, chceme pokracovat
                        break;
                    }
                }
                else
                {
                    j++;
                }
            }
        }
        fclose(inputFile);
    }
    return err;
}

int savematrix(char Omatrix[9][9], char Gmatrix[9][9], char* addr) //ulozi obe matice (pevnou i hracskou) do souboru s nazvem nahranym v promenne addr
{
    errno_t err;
    FILE* outputFile;
    if ((err = fopen_s(&outputFile, addr, "w")) == 0)
    {
        for (int m = 0; m < 9; m++)
        {
            for (int n = 0; n < 9; n++)
            {
                fprintf(outputFile, "%c", Omatrix[m][n]);
            }
            fprintf(outputFile, "\n");
        }
        for (int m = 0; m < 9; m++)
        {
            for (int n = 0; n < 9; n++)
            {
                fprintf(outputFile, "%c", Gmatrix[m][n]);
            }
            fprintf(outputFile, "\n");
        }
        fclose(outputFile);
    }
    return err;
}

void checkcolumn(char Gmatrix[9][9], int Ematrix[9][9]) //funkce pro overovani spravnosti vsech hodnot ve sloupci
{
    for (int i = 0; i < 9; i++) //vynulovani matice po minulem tahu
    {
        for (int j = 0; j < 9; j++)
        {
            Ematrix[i][j] = 0;
        }
    }
    for (int n = 0; n < 9; n++)
    {
        for (int m = 0; m < 8; m++)
        {
            for (int i = m + 1; i < 9; i++)
            {
                if (Gmatrix[i][n] == Gmatrix[m][n] && Gmatrix[i][n] != '0') //pokud sloupec obsahuje 2 stejne nenulove hodnoty, je to chybny sloupec
                {
                    for (int j = 0; j < 9; j++)
                    {
                        Ematrix[j][n] = 1;
                    }
                }
            }
        }
    }
}

void checkrow(char Gmatrix[9][9], int Ematrix[9][9]) //funkce pro overovani spravnosti vsech hodnot v radku
{
    for (int m = 0; m < 9; m++)
    {
        for (int n = 0; n < 8; n++)
        {
            for (int i = n + 1; i < 9; i++)
            {
                if (Gmatrix[m][i] == Gmatrix[m][n] && Gmatrix[m][i] != '0') //pokud sloupec obsahuje 2 stejne nenulove hodnoty, je to chybny radek
                {
                    for (int j = 0; j < 9; j++)
                    {
                        Ematrix[m][j] = 1;
                    }
                }
            }
        }
    }
}

void checkgrid(char Gmatrix[9][9], int Ematrix[9][9], int gridrow, int gridcolumn) //funkce pro overovani spravnosti vsech hodnot v podmatici 3x3, gridrow a gridcolumn jsou promenne oznacujici souradnice prvni hodnoty podmatice v hlavni matici
{ //gridrow a gridcolumn jsou v kodu volany pomoci vnoreneho cyklu for, projde tedy vsech 9 podmatic
    char grid[9]; //jednorozmerne pole je lehci na pruchodnost nez dvourozmerne, nahrajeme do nej hodnoty z podmatice
    int a = 0;
    for (int m = gridrow; m < gridrow + 3; m++)
    {
        for (int n = gridcolumn; n < gridcolumn + 3; n++)
        {
            grid[a] = Gmatrix[m][n];
            ++a;
        }
    }
    for (int i = 0; i < 8; i++) //pokud jsou mezi hodnotami 2 stejne nenulove, podmatice se oznaci jako chybna
    {
        for (int j = i + 1; j < 9; j++)
        {
            if (grid[i] == grid[j] && grid[i] != '0')
            {
                for (int m = gridrow; m < gridrow + 3; m++)
                {
                    for (int n = gridcolumn; n < gridcolumn + 3; n++)
                    {
                        Ematrix[m][n] = 1;
                    }
                }
            }
        }
    }
}

int shouldBeColoured(int i, int j)
{
    if (((i - 1 >= -1 && i - 1 <= 1) && (j - 1 >= -1 && j - 1 <= 1)) ||
        ((i - 1 >= -1 && i - 1 <= 1) && (j - 7 >= -1 && j - 7 <= 1)) ||
        ((i - 4 >= -1 && i - 4 <= 1) && (j - 4 >= -1 && j - 4 <= 1)) ||
        ((i - 7 >= -1 && i - 7 <= 1) && (j - 1 >= -1 && j - 1 <= 1)) ||
        ((i - 7 >= -1 && i - 7 <= 1) && (j - 7 >= -1 && j - 7 <= 1)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}