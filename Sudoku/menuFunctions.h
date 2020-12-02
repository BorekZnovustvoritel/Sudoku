#pragma once

#define NAMELENGTH 20
#define NAMENUM 6 //Pocet nazvu souboru, ktere se budou cist ze souboru DATA\DATA. Prvni je vzdy cache, takze se zobrazuje NAMENUM - 1 recentne ulozenych her

void printMenu(char* row, unsigned int rownum, int canContinue); //Vykresli hlavni menu
int getQuickLoadMenuData(char names[NAMENUM][NAMELENGTH + 1]); //Otevre a extrahuje ulozena data ze souboru DATA\DATA
int loadGameMenu(char names[NAMENUM][NAMELENGTH + 1]); //Zobrazuje menu, ktere se zobrazi po otevreni moznosti Load a saved game
int difficultyMenu(); //zobrazi nastaveni obtiznosti, vrati hodnotu