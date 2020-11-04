#include <stdio.h>
#include <errno.h>
#include <windows.h>
#include <conio.h>
#include "gameFunctions.h"
#include "otherFunctions.h"

int main()
{
    char addr[8] = "000.txt"; //defaultni soubor pri spusteni nove hry
    char Omatrix[9][9], Gmatrix[9][9]; //Omatrix - original, udava, ktere hodnoty nelze zmenit, Gmatrix - herni, obsahuje vsechny hodnoty

    showConsoleCursor(FALSE);
    char row[5] = { '>',' ',' ',' ',' ' }; //vychozi oznaceny radek v menu je prvni (index 0)
    unsigned int rownum = 0; //drzi index oznaceneho radku v menu
    printMenu(row, rownum);
    
    int leave = 0; //preruseni cyklu, zmeni se pry vyberu radku Exit v menu
    unsigned int key; //drzi int hodnotu stisknute klavesy
    int status;
    while (!leave)
    {
        key = getch();
        if (key == 0 || key == 0xE0) //zbaveni se prazdnych inputu
        {
            key = getch();
        }
        if (key == 27) //esc, ukonci program stejne jako Exit
        {
            leave = 1;
        }
        else
        {
            switch (key) //jakou klavesu uzivatel zmackl? Zajimaji nas jen nektere
            {
            case 72: //up
                if (rownum != 0)
                {
                    row[rownum - 1] = row[rownum];
                    row[rownum] = ' ';
                    --rownum;
                }
                break;
            case 80: //down
                if (rownum != 4)
                {
                    row[rownum + 1] = row[rownum];
                    row[rownum] = ' ';
                    ++rownum;
                }
                break;
            case 13: //enter
                switch (rownum) //####### tento switch ovlada hlavni menu #######
                {
                case 0: //Start a new game
                    system("cls");
                    if (loadMatrix(Omatrix, Gmatrix, addr) == 0)
                    {
                        play(Omatrix, Gmatrix, 1);
                    }
                    else
                    {
                        printf("Please copy the thext file named '%s' into the game folder.\nPress any key to continue.", addr);
                        getch();
                        showConsoleCursor(FALSE);
                    }
                    break;


                case 1: //Load a saved game
                    system("cls");
                    char name1[21];
                    printf("Enter the name of the save file:\n");
                    showConsoleCursor(TRUE);
                    scanf_s("%s", name1, sizeof(name1));
                    status = loadMatrix(Omatrix, Gmatrix, name1);
                    if (status == 0)
                    {
                        play(Omatrix, Gmatrix, 1);
                    }
                    else if (status == -1)
                    {
                        printf("\nThe file '%s' is not formatted properly.\nPlease read the user's manual.\nPress any key to continue.", name1);
                        getch();
                    }
                    else
                    {
                        printf("\nThe file '%s' was not found.\nPress any key to continue.", name1);
                        getch();
                    }
                    showConsoleCursor(FALSE);
                    break;


                case 2: //Save the current game
                    system("cls");
                    char name2[21];
                    printf("Please, enter a name of this session. Maximal length is 20 symbols.\n");
                    scanf_s("%s", name2, sizeof(name2));
                    savematrix(Omatrix, Gmatrix, name2);
                    break;


                case 3: //Create a new layout
                    char nulMatrix[9][9];
                    for (int m = 0; m < 9; m++)
                    {
                        for (int n = 0; n < 9; n++)
                        {
                            nulMatrix[m][n] = '0';
                            Gmatrix[m][n] = '0';
                        }
                    }
                    play(nulMatrix, Gmatrix, 2);

                    break;


                case 4: //Exit
                    leave = 1;
                    break;
                }
            }
        }
        printMenu(row, rownum);
    }
}