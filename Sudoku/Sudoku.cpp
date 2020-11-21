#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "gameFunctions.h"
#include "otherFunctions.h"

typedef char chmat[9][9];

int main()
{
    showConsoleCursor(FALSE);
    char addr[NAMELENGTH + 15]; //celkova adresa pro ukladani 
    char name[NAMELENGTH + 1]; // cast, kterou zadava uzivatel
    char folderaddr[14] = "Playgrounds\\"; //defaultni adresar pro ukladani her
    char names[NAMENUM][NAMELENGTH + 1]; //matice obsahujici nazvy rozehranych her pro quick load

    chmat Omatrix, Gmatrix; //Omatrix - original, udava, ktere hodnoty nelze zmenit, Gmatrix - herni, obsahuje vsechny hodnoty
 
    int canContinue = 0; //drzi binarni hodnotu, ktera rika, jestli ma program v pameti nejakou rozehranou hru, tuto hodnotu zmeni na kladnou hodnotu otevreni hry, dohrani hry ji zmeni na nulu. Vytvareni layoutu ji zmeni na nulu vzdy
    char row[6] = { ' ', ' ','>',' ',' ',' ' }; //vychozi oznaceny radek v menu je Start a new game (index 2)
    unsigned int rownum = 2; //drzi index oznaceneho radku v menu
    
    int leave = 0; //preruseni cyklu, zmeni se pry vyberu radku Exit v menu
    unsigned int key; //drzi int hodnotu stisknute klavesy

    if (getQuickLoadMenuData(names)) //nacitame nazvy poslednich nekolika ulozenych souboru
    {
        printf("Error: 'DATA\\DATA' is missing.\nPress any key to continue.");
        getch();
    }

    while (!leave)
    {
        printMenu(row, rownum, canContinue);
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
            switch (key) //jakou klavesu uzivatel stisknul? Zajimaji nas jen nektere
            {
            case 72: //up
                if (rownum != (2 - 2*canContinue)) //pokud jsme nahore, nemuzeme vyse, canContinue vyjadruje nactenou herni matici v pameti
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
                    { //tato zavorka je jen kvuli inicializaci promenne. Nesmi byt ve switch case
                        int hasDupes = 0;
                        system("cls");
                        printf("Please, enter a name of this session. Maximal length is %d symbols.\n", NAMELENGTH);
                        showConsoleCursor(TRUE);
                        scanf_s("%s", name, NAMELENGTH + 1);
                        showConsoleCursor(FALSE);
                        mergeaddr(folderaddr, name, addr);
                        savematrix(Omatrix, Gmatrix, addr);
                        for (int i = 1; i < NAMENUM - 1; i++) //zkoumame, jestli jemno neni jiz obsazene, pokud je, soubor se sice prepie, ale seznam ulozenych her neobsahuje duplikaty
                        {
                            if (!strcmp(name, names[i])) //pokud jsou jmena stejna
                            {
                                hasDupes = 1;
                            }
                        }
                        if (!hasDupes)
                        {
                            for (int i = NAMENUM - 1; i > 1; i--) //posouvame ulozene nazvy o jeden dale
                            {
                                strcpy_s(names[i], NAMELENGTH + 1, names[i - 1]);
                            }
                            strcpy_s(names[1], NAMELENGTH + 1, name); //ulozime novy nazev na prvni pozici
                        }
                        FILE* data;
                        if (!fopen_s(&data, "DATA\\DATA", "w")) //zapiseme vse do souboru
                        {
                            for (int i = 0; i < NAMENUM; i++)
                            {
                                fprintf(data, "%s\n", names[i]);
                            }
                            fclose(data);
                        }
                        break;

                    }

                case 2: //Start a new game
                    { //tato zavorka je jen kvuli inicializaci promenne. Nesmi byt ve switch case
                        char addr2[] = "DATA\\000.txt"; //defaultni soubor
                        system("cls");
                        if (loadMatrix(Omatrix, Gmatrix, addr2, &canContinue) == 0)
                        {
                            play(Omatrix, Gmatrix, 1, &canContinue);
                        }
                        else
                        {
                            printf("Error: '%s' is missing.\nPress any key to continue.", addr2);
                            getch();
                            showConsoleCursor(FALSE);
                        }
                        break;
                    }

                case 3: //Load a saved game
                    { //tato zavorka je jen kvuli inicializaci promenne. Nesmi byt ve switch case
                        system("cls");
                        int option = loadGameMenu(names);
                        switch (option)
                        {
                        case 0: //vlastni pojmenovany soubor
                            printf("\nEnter the name of the save file:\n");
                            showConsoleCursor(TRUE);
                            scanf_s("%s", name, NAMELENGTH + 1);
                            mergeaddr(folderaddr, name, addr);
                            break;
                        case 1: //cache
                            strcpy_s(name, NAMELENGTH + 1, names[0]);
                            mergeaddr("DATA\\", name, addr);
                            break;
                        case -1: //esc, chceme pryc
                            break;
                        default: //vsechny ostatni soubory
                            strcpy_s(name, NAMELENGTH + 1, names[option - 1]);
                            mergeaddr(folderaddr, name, addr);
                        }
                        system("cls");
                        if (option >= 0)
                        {
                            int status = loadMatrix(Omatrix, Gmatrix, addr, &canContinue);  //podarilo se hraci pole uspesne nacist? 0 = ano, -1 = spatny format, jine hodnoty = error
                            if (status == 0)
                            {
                                play(Omatrix, Gmatrix, 1, &canContinue);
                            }
                            else if (status == 1)
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
                        }
                    }
                    break;


                case 4: //Create a new layout
                    chmat nulMatrix;
                    for (int m = 0; m < 9; m++) //vytvoreni nulove matice, do ktere bude hrac vkladat hodnoty
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
                        printf("Please, name this layout. Maximal length is %d symbols.\n", NAMELENGTH);
                        scanf_s("%s", name, NAMELENGTH + 1);
                        mergeaddr(folderaddr, name, addr);
                        savematrix(Gmatrix, Gmatrix, addr); //uklada do obou matic to, co bylo zadano jako layout. Timto se z hodnot stanou nemenna cisla
                        for (int i = NAMENUM - 1; i > 1; i--) //posouvame ulozene nazvy o jeden dale
                        {
                            strcpy_s(names[i], NAMELENGTH + 1, names[i - 1]);
                        }
                        strcpy_s(names[1], NAMELENGTH + 1, name); //ulozime novy nazev na prvni pozici
                        FILE* data;
                        if (!fopen_s(&data, "DATA\\DATA", "w")) //zapiseme vse do souboru
                        {
                            for (int i = 0; i < NAMENUM; i++)
                            {
                                fprintf(data, "%s\n", names[i]);
                            }
                            fclose(data);
                        }
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
    }
    if (canContinue) //ukladani cache
    {
        if (!getQuickLoadMenuData(names)) //nalezeni nazvu souboru pro ukladani cache (inicializace names[0])
        {
            mergeaddr("DATA\\", names[0], addr);
            savematrix(Omatrix, Gmatrix, addr);
            return 1; // cache se zmenila => return value main() = 1
        }
    }
    return 0;
}