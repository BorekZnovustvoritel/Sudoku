#include <stdio.h>
#include <errno.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "gameFunctions.h"
#include "otherFunctions.h"

#define NAMELENGTH 20

int main()
{
    char addr[35], name[21]; //celkova adresa pro ukladani / cast, kterou zadava uzivatel
    char folderaddr[] = "Playgrounds\\"; //defaultni adresar pro ukladani her
    char addr2[] = "Playgrounds\\000.txt"; //defaultni soubor
    char Omatrix[9][9], Gmatrix[9][9]; //Omatrix - original, udava, ktere hodnoty nelze zmenit, Gmatrix - herni, obsahuje vsechny hodnoty

    showConsoleCursor(FALSE);
    int canContinue = 0; //drzi binarni hodnotu, ktera rika, jestli ma program v pameti nejakou rozehranou hru, tuto hodnotu zmeni na kladnou hodnotu otevreni hry, dohrani hry ji zmeni na nulu. Vytvareni layoutu ji zmeni na nulu vzdy
    char row[6] = { ' ', ' ','>',' ',' ',' ' }; //vychozi oznaceny radek v menu je prvni (index 0)
    unsigned int rownum = 2; //drzi index oznaceneho radku v menu
    printMenu(row, rownum, canContinue);
    
    int leave = 0; //preruseni cyklu, zmeni se pry vyberu radku Exit v menu
    unsigned int key; //drzi int hodnotu stisknute klavesy
    int status; //podarilo se hraci pole uspesne nacist? 0 = ano, -1 = spatny format, jine hodnoty = error
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
                if (rownum != (2 - 2*canContinue)) //pokud jsme nahore, nemuzeme vyse, canContinue vyjadruje herni matici v¨pameti
                {
                    row[rownum - 1] = row[rownum];
                    row[rownum] = ' ';
                    --rownum;
                }
                break;
            case 80: //down
                if (rownum != 5)
                {
                    row[rownum + 1] = row[rownum];
                    row[rownum] = ' ';
                    ++rownum;
                }
                break;
            case 13: //enter
                switch (rownum) //####### tento switch ovlada hlavni menu #######
                {


                case 0: //continue
                    play(Omatrix, Gmatrix, 1, &canContinue);

                    if (canContinue == 0) //pokud hru dokoncime, musime presunout kurzor hlavniho menu, jinak by zmizel
                    {
                        row[0] = ' ';
                        row[2] = '>';
                        rownum = 2;
                    }
                    break;


                case 1: //Save the current game
                    system("cls");
                    
                    if (canContinue == 0)
                    {
                        printf("There is no initiated game available.\nPress any key to continue.");
                        getch();
                    }
                    else
                    {
                        printf("Please, enter a name of this session. Maximal length is 20 symbols.\n");
                        scanf_s("%s", &name, NAMELENGTH);
                        mergeaddr(folderaddr, name, addr);
                        savematrix(Omatrix, Gmatrix, addr);
                    }
                    break;


                case 2: //Start a new game
                    system("cls");
                    if (loadMatrix(Omatrix, Gmatrix, addr2, &canContinue) == 0)
                    {
                        play(Omatrix, Gmatrix, 1, &canContinue);
                    }
                    else
                    {
                        printf("Please copy the thext file named '%s' into the 'Playgrounds' folder.\nPress any key to continue.", addr);
                        getch();
                        showConsoleCursor(FALSE);
                    }
                    break;


                case 3: //Load a saved game
                    system("cls");
                    printf("Enter the name of the save file:\n");
                    showConsoleCursor(TRUE);
                    scanf_s("%s", &name, NAMELENGTH);
                    mergeaddr(folderaddr, name, addr);
                    status = loadMatrix(Omatrix, Gmatrix, addr, &canContinue);
                    if (status == 0)
                    {
                        play(Omatrix, Gmatrix, 1, &canContinue);
                    }
                    else if (status == -1)
                    {
                        printf("\nThe file '%s' is not formatted properly.\nPlease read the user's manual.\nPress any key to continue.", name);
                        getch();
                    }
                    else
                    {
                        printf("\nThe file '%s' was not found.\nPress any key to continue.", name);
                        getch();
                    }
                    showConsoleCursor(FALSE);
                    break;


                case 4: //Create a new layout
                    char nulMatrix[9][9];
                    for (int m = 0; m < 9; m++)
                    {
                        for (int n = 0; n < 9; n++)
                        {
                            nulMatrix[m][n] = '0';
                            Gmatrix[m][n] = '0';
                        }
                    }
                    if(play(nulMatrix, Gmatrix, 2, &canContinue) == 1)
                    {
                        system("cls");
                        showConsoleCursor(TRUE);
                        printf("Please, name this layout. Maximal length is 20 symbols.\n");
                        scanf_s("%s", &name, NAMELENGTH);
                        mergeaddr(folderaddr, name, addr);
                        savematrix(Gmatrix, Gmatrix, addr); //uklada do obou matic to, co bylo zadano jako layout. Timto se z hodnot stanou nemenna cisla
                        showConsoleCursor(FALSE);
                    }
                    for (int m = 0; m < 9; m++)
                    {
                        for (int n = 0; n < 9; n++)
                        {
                            Gmatrix[m][n] = '0';                           
                        }
                    }
                    break;


                case 5: //Exit
                    leave = 1;
                    break;
                }
            }
        }
        printMenu(row, rownum, canContinue);
    }
}