#pragma once

#define getch() _getch()
#define NAMELENGTH 20

typedef char chmat[9][9];

void showConsoleCursor(bool showFlag); //Funkce z navodoveho souboru, skryva nebo ukazuje kurzor
int loadMatrix(chmat Omatrix, chmat Gmatrix, char* addr, int* ptr); //Nacteni hraciho pole
int savematrix(chmat Omatrix, chmat Gmatrix, char* addr); //Ulozi referencni i hracskou matici do souboru s nazvem, kterym nahrajeme do parametru addr
void checkrow(chmat Gmatrix, int Ematrix[9][9]); //Oznacuje do Ematrix (matice chyb v reseni sudoku) spatne radky
void checkcolumn(chmat Gmatrix, int Ematrix[9][9]); //Oznacuje do Ematrix spatne sloupce
void checkgrid(chmat Gmatrix, int Ematrix[9][9], int gridrow, int gridcolumn); //Oznacuje do Ematrix spatne vyplneno podmatice. gridrow a gridcolumn oznacuji pocatecni pozici teto podmatice v hlavni matici
int shouldBeColoured(int i, int j);
char* mergeaddr(char* folderaddr, char* addr, char* ans);