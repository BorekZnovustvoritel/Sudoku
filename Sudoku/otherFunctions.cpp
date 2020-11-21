#include <stdio.h>
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

int loadMatrix(chmat Omatrix, chmat Gmatrix, const char* addr, int* ptr) //Nahraje hraci pole ze souboru do matic. Omatrix drzi neprepsatelne hodnoty, Gmatrix drzi pevne i uzivatelske hodnoty, addr je nazev souboru a ptr je adresa, do ktere vkladame canContinue z funkce main()
{
    char chr;
    int err;
    FILE* inputFile;
    if ((err = fopen_s(&inputFile, addr, "r")) == 0) //pokud nevyhodi otevirani souboru error
    {
        int i = 0; //promenne pro prochazeni pole
        int j = 0;
        err = 1; //predpokladame, ze matice neni spravne naformatovana
        while ((chr = getc(inputFile)) != EOF) //dokud nejsme na konci souboru
        {
            if (isdigit(chr) != 0)
            {
                if (i < 9)
                {
                    Omatrix[i][j] = chr; //prvnich 81  cisel je nahrano do pevne matice
                    if (i == 8 && j == 8) 
                    {
                        err = -1; //return hodnota vystupu pri zaplneni jen jedne matice, tento stav umi program opravit
                    }
                }
                else
                {
                    Gmatrix[i - 9][j] = chr; //dalsich 81 cisel se nahraje do matice, se kterou hrac interaguje
                    err = 1; //zaplnila se 1 matice, druha neni zcela zaplnena (spatne naformatovana matice)
                }
                if (j == 8) 
                {
                    i++;
                    j = 0;
                    if (i == 18) //bereme jen 162 symbolu. i se prepne pri poslednim symbolu na hodnotu 18, j na nulu
                    {
                        err = 0; //jen pokud se zaplni obe matice, chceme pokracovat
                        *ptr = 1; //canContinue = 1 (zobrazi se v menu moznost se hrou pokracovat, nebo ji ulozit)
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
    if (err == -1) //jen jedna matice (Omatrix) je cela zaplnena
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                Gmatrix[i][j] = Omatrix[i][j];
            }
        }
        err = 0;
        *ptr = 1;
    }
    return err;
}

int savematrix(chmat Omatrix, chmat Gmatrix, char* addr) //ulozi obe matice (pevnou i hracskou) do souboru s nazvem nahranym v promenne addr
{
    int err;
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

int checkarr(char arr[9]) //pruchod devitice znaku
{
    for (int m = 0; m < 8; m++)
    {
        for (int i = m + 1; i < 9; i++)
        {
            if (arr[i] == arr[m] && arr[i] != '0') //pokud obsahuje 2 stejne nenulove hodnoty, je to chybny sloupec
            {
                return 1;
            }
        }
    }
    return 0;
}

void flushMatrix(int Ematrix[9][9])  //vynulovani matice po minulem tahu
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Ematrix[i][j] = 0;
        }
    }
}

void checkColumn(chmat Gmatrix, int Ematrix[9][9], int n) //funkce pro overovani spravnosti vsech hodnot ve sloupci
{
    char arr[9];
    for (int m = 0; m < 9; m++)
    {
        arr[m] = Gmatrix[m][n];
    }
    if (checkarr(arr))
    {
        for (int m = 0; m < 9; m++)
        {
            Ematrix[m][n] = 1;
        }
    }
}

void checkcolumns(chmat Gmatrix, int Ematrix[9][9]) //volani checkColumn pro kazdy sloupec
{
    for (int n = 0; n < 9; n++)
    {
        checkColumn(Gmatrix, Ematrix, n);
    }
}

void checkRow(chmat Gmatrix, int Ematrix[9][9], int m) //funkce pro overovani spravnosti vsech hodnot v radku
{
    char arr[9];
    for (int n = 0; n < 9; n++)
    {
        arr[n] = Gmatrix[m][n];
    }
    if (checkarr(arr))
    {
        for (int n = 0; n < 9; n++)
        {
            Ematrix[m][n] = 1;
        }
    }
}

void checkrows(chmat Gmatrix, int Ematrix[9][9]) //volani checkRow pro kazdy radek
{
    for (int m = 0; m < 9; m++)
    {
        checkRow(Gmatrix, Ematrix, m);
    }
}

void checkGrid(chmat Gmatrix, int Ematrix[9][9], int gridrow, int gridcolumn) //funkce pro overovani spravnosti vsech hodnot v podmatici 3x3, gridrow a gridcolumn jsou promenne oznacujici souradnice prvni hodnoty podmatice v hlavni matici
{ 
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
    if (checkarr(grid))
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

void checkgrids(chmat Gmatrix, int Ematrix[9][9]) //volani chackgrid nad vsemi podmaticemi
{
    for (int callgridrow = 0; callgridrow < 7; callgridrow += 3)
    {
        for (int callgridcolumn = 0; callgridcolumn < 7; callgridcolumn += 3)
        {
            checkGrid(Gmatrix, Ematrix, callgridrow, callgridcolumn);
        }
    }
}

int shouldBeColoured(int i, int j) //Oznacuje souradnice, ktere maji mit sachovnicove podbarveni. Vraci 1, pokud jsou souradnice urceny k podbarveni
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

char* mergeaddr(const char* folderaddr, const char* addr, char* ans) //spoji nazev souboru s adresarem, az pote se s adresou pracuje
{
    strcpy_s(ans, NAMELENGTH + 15, folderaddr);
    strcat_s(ans, NAMELENGTH + 15, addr);
    return ans;
}

int getQuickLoadMenuData(char names[NAMENUM][NAMELENGTH + 1]) //Otevre a extrahuje ulozena data ze souboru DATA\DATA
{
    int numOfNames = 0;
    FILE* data;
    if (!fopen_s(&data, "DATA\\DATA", "r"))
    {
        char chr;
        int i = 0;
        while ((chr = getc(data)) != EOF && numOfNames < NAMENUM)
        {
            if (chr != '\n')
            {
                names[numOfNames][i] = chr;
                i++;
            }
            else
            {
                names[numOfNames][i] = '\0';
                numOfNames++;
                i = 0;
            }
        }
        fclose(data);
        int emptyNames = NAMENUM - numOfNames; //pokud v souboru neni dost souboru k zobrazeni, nazev se vyplni prazdnym retezcem
        for (int i = 0; i < emptyNames; i++)
        {
            names[NAMENUM - 1 - i][0] = '\0';
        }
        return 0;
    }
    else
    {
        return 1;
    }
}

int loadGameMenu(char names[NAMENUM][NAMELENGTH + 1]) //Zobrazuje menu, ktere se zobrazi po otevreni moznosti Load a saved game
{
    char row[NAMENUM + 1];
    row[0] = '>';
    for (int i = 1; i < (NAMENUM + 1); i++)
    {
        row[i] = ' ';
    }
    int leave = 0;
    char key;
    int option = 0;
    while (!leave)
    {
        system("cls");
        printf("\n\tLoad a saved game\n");
        printf("\t%c Manually insert name\n", row[0]); 
        for (int i = 1; i < (NAMENUM + 1); i++)
        {
            printf("\t%c %s\n", row[i], names[i-1]);
        }
        key = getch();
        if (key == 0 || key == 0xE0) //zbaveni se prazdnych inputu
        {
            key = getch();
        }
        else
        {
            switch (key)
            {
                case 72: //up
                    if (option != 0)
                    {
                        row[option] = ' ';
                        option -= 1;
                        row[option] = '>';
                    }
                    break;
                case 80: //down
                    if (option != NAMENUM)
                    {
                        row[option] = ' ';
                        option += 1;
                        row[option] = '>';
                    }
                    break;
                case 13: //enter                 
                    leave = 1;
                    break;
                case 27: //esc
                    return -1;
                    break;
            }
        }
    }
    return option;
}