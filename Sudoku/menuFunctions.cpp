#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "gameFunctions.h"
#include "menuFunctions.h"
#include "otherFunctions.h"
#include "generating.h"


void printMenu(char* row, unsigned int rownum, int canContinue) //zobrazi hlavni menu podle parametru. row[] obsahuje kurzor ukazujici aktivni radek, rownum obsahuje cislo radku (zacinajici od nuly)
{
    system("cls");
    printf("\n\tSUDOKU\n\n");
    if (canContinue == 1)
    {
        printf("\t%c Continue\n\t%c Save the current game\n", row[0], row[1]);
    }
    printf("\t%c Start a new game\n\t%c Load a saved game\n\t%c Create a new layout\n\t%c Exit", row[2], row[3], row[4], row[5]);
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
            printf("\t%c %s\n", row[i], names[i - 1]);
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

int difficultyMenu() //zobrazeni pro nastaveni obtiznosti
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD saved_attributes;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    char key;
    int option = 1;
    int leave = 0;
    do
    {
        system("cls");
        printf("Select your difficulty using arrows < >.\nConfirm with Enter\n\n");
        printf("<");
        SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY);
        for (int i = 0; i < option; i++)
        {
            printf(" ");
        }
        SetConsoleTextAttribute(hConsole, saved_attributes);
        for (int i = option; i < 10; i++)
        {
            printf(" ");
        }
        printf(">");
        key = getch();
        if (key == 0 || key == 0xE0) //zbaveni se prazdnych inputu
        {
            key = getch();
        }
        else
        {
            switch (key)
            {
            case 75: //left
                if (option != 1)
                {
                    option--;
                }
                break;
            case 77: //right
                if (option != 10)
                {
                    option++;
                }
                break;
            case 13: //enter                 
                leave = 1;
                break;
            }
        }
    } while (!leave);
    return option;
}