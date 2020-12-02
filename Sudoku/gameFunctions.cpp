#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "gameFunctions.h"
#include "menuFunctions.h"
#include "otherFunctions.h"
#include "generating.h"


void showConsoleCursor(bool showFlag) //funkce z navodu, spousti se s parametrem TRUE/FALSE
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

//vypise Gmatrix, hodnoty shodne s Omatrix vybarvi zelene, hodnoty oznacene jako chybne (v Ematrix) podbarvi cervene, cast je prevzata z navodoveho souboru
void printMatrix(chmat Omatrix, chmat Gmatrix, int Ematrix[9][9])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    int stringSize = ((9 * 2) + 2) * 9;
    char* matrixString = new char[stringSize];

    printf("\n"); //kvuli nemu se k pozici kurzoru pricita +1
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    for (int i = 0; i < 9; i++)
    {
        printf(" |");
        for (int j = 0; j < 9; j++)
        {
            if (Gmatrix[i][j] == '0') //misto nuly se vypise prazdne pole
            {
                if (Ematrix[i][j] == 1) //chybne radky/sloupce/podmatice se podbarvi cervene (vcetne poli obsahujicich '0')
                {
                    SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
                }
                else if (shouldBeColoured(i, j) == 1) //podbarvene podmatice pro lepsi orientaci maji zelene pozadi
                {
                    SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY);
                }
                printf(" ");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                printf("|");
            }
            else
            {
                if (Gmatrix[i][j] != Omatrix[i][j]) //prepsatelna pole maji bily text, pokud nejsou v podbarvene podmatici
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
                    if (Ematrix[i][j] == 1)
                    {
                        SetConsoleTextAttribute(hConsole, BACKGROUND_RED); //hodnoty v oznacenych polich jsou cerne s cervenym pozadim
                    }
                    else if (shouldBeColoured(i, j) == 1) //podbarvene podmatice pro lepsi orientaci
                    {
                        SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY);
                    }
                }
                else //neprepsatelna pole maji modry text
                {
                    if (Ematrix[i][j] == 1)
                    {
                        SetConsoleTextAttribute(hConsole, BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); //hodnoty v oznacenych polich jsou modre s cervenym pozadim
                    }
                    else if (shouldBeColoured(i, j) == 1) //podbarvene podmatice pro lepsi orientaci
                    {
                        SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY| FOREGROUND_BLUE);
                    }
                    else
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    }
                }
                printf("%c", Gmatrix[i][j]);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN); //oddelovace
                printf("|");
            }
        }
        printf("\n");
    }
    SetConsoleTextAttribute(hConsole, saved_attributes); //resetovani konzole
}

void setCursorPosition(int x, int y) //Nastaveni kurzoru v konzoli na pozici x = sloupce, y = radky, funkce z navodoveho souboru
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    fflush(stdin);
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void move(char d, int* mActual, int* nActual) //funkce pro pohyb v hracim poli, funkce z navodoveho souboru, upravena
{
    if (d == 'u' && *mActual - 1 >= 0) {
        (*mActual)--;
        setCursorPosition(*nActual * 2 + 2, *mActual + 1);
    }

    if (d == 'd' && *mActual + 1 < 9) {
        (*mActual)++;
        setCursorPosition(*nActual * 2 + 2, *mActual + 1);
    }

    if (d == 'l' && *nActual - 1 >= 0) {
        (*nActual)--;
        setCursorPosition(*nActual * 2 + 2, *mActual + 1);
    }

    if (d == 'r' && *nActual + 1 < 9) {
        (*nActual)++;
        setCursorPosition(*nActual * 2 + 2, *mActual + 1);
    }
}

int getvictory(chmat Gmatrix, int Ematrix[9][9]) //pokud jsou vyplnene vsechny hodnoty hracske matice a neobsahuje zadne chyby, vrati funkce hodnotu 1
{
    int r = 1;
    for (int m = 0; m < 9; m++)
    {
        for (int n = 0; n < 9; n++)
        {
            if (Gmatrix[m][n] == '0' || Ematrix[m][n] == 1)
            {
                r = 0;
            }
        }
    }
    return r;
}

void checkAndPrintMatrix(chmat Omatrix, chmat Gmatrix, int Ematrix[9][9], int mActual, int nActual) //vola checkcolumns(), checkrows() a checkgrid() a printMatrix(), pokud bych nepouzil tuto funkci, cast kodu by se opakovala
{
    system("cls");
    flushMatrix(Ematrix);
    checkcolumns(Gmatrix, Ematrix);
    checkrows(Gmatrix, Ematrix);
    checkgrids(Gmatrix, Ematrix);
    printMatrix(Omatrix, Gmatrix, Ematrix);
    setCursorPosition(nActual * 2 + 2, mActual + 1);
}

int play(chmat Omatrix, chmat Gmatrix, int gamemode, int* ptr) //Herni mechanismus. Omatrix je reference, Gmatrix se zobrazuje. Pri vytvareni layoutu se funkce vola s gamemode hodnotou == 2, cast je prevzata z navodu
{
    int mActual = 0, nActual = 0; //ulozeni souradnic aktualniho prvku pro pouziti ve funkcich
    int Ematrix[9][9]; //Ematrix -E jako error, uklada chybne radky, sloupce a podmatice podle pravidel hry. Ty se pak podbarvuji cervene
    unsigned int key; //nahrava se do nej hodnota stisknute klavesy
    char direction; //vyuziva jej funkce move
    showConsoleCursor(TRUE);
    checkAndPrintMatrix(Omatrix, Gmatrix, Ematrix, mActual, nActual);
    while (getvictory(Gmatrix, Ematrix) != 1) //dokud neni hra vyhrana
    {
        key = getch();
        //Odstraneni prebytecnych znaku odesilanych pri stisku smerovych sipek
        if (key == 0 || key == 0xE0) {
            key = getch();
        }
        //ESC
        if (key == 27) {
            break;
        }
        switch (key)
        {
        case 72:
            //klavesa UP
            direction = 'u';
            move(direction, &mActual, &nActual);
            break;
        case 80:
            //klavesa DOWN
            direction = 'd';
            move(direction, &mActual, &nActual);
            break;
        case 75:
            //klavesa LEFT
            direction = 'l';
            move(direction, &mActual, &nActual);
            break;
        case 77:
            //klavesa RIGHT
            direction = 'r';
            move(direction, &mActual, &nActual);
            break;
        case 8:
            //klavesa Backspace, da se pomoci ni mazat (Ale stejnou funkci ma i '0')
            if (Omatrix[mActual][nActual] == '0')
            {
                Gmatrix[mActual][nActual] = '0';
            }
            checkAndPrintMatrix(Omatrix, Gmatrix, Ematrix, mActual, nActual);
            break;
        default:
            if (Omatrix[mActual][nActual] == '0' && (isdigit(key) != 0))
            {
                //printf("%c", key);
                Gmatrix[mActual][nActual] = key;
                checkAndPrintMatrix(Omatrix, Gmatrix, Ematrix, mActual, nActual);
            }
        }

    }
    if (getvictory(Gmatrix, Ematrix) == 1)
    {
        *ptr = 0;
        system("cls");
        printMatrix(Omatrix, Gmatrix, Ematrix);
        showConsoleCursor(FALSE);
        printf("Congratulation! You won!\nPress any key to return to the main menu."); //hlaska pri vyhre
        getch();
    }
    else
    {
        showConsoleCursor(FALSE); //co se ma stat, pokud je hra prerusena (automaticky hra vstoupi do menu)

        if (gamemode == 2) //pokud je zavolana v rezimu vytvareni layoutu
        {
            *ptr = 0;
            int checkerr = 0; //obsahuje layout chyby?
            for (int m = 0; m < 9; m++)
            {
                for (int n = 0; n < 9; n++)
                {
                    if (Ematrix[m][n] == 1)
                    {
                        checkerr = 1;
                    }
                }
            }
            if (checkerr == 1) //obsahuje chyby.
            {
                system("cls");
                printf("Unable to save a layout containing errors.\nPress any key to continue.");
                getch();
            }
            else //neobsahuje chyby.
            {
                return 1;
            }
        }
    }
    return 0;
}