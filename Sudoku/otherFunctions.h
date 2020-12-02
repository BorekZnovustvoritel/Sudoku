#pragma once

#define getch() _getch()

typedef char chmat[9][9];

int loadMatrix(chmat Omatrix, chmat Gmatrix, const char* addr, int* ptr); //Nacteni hraciho pole
int savematrix(chmat Omatrix, chmat Gmatrix, char* addr); //Ulozi referencni i hracskou matici do souboru s nazvem, kterym nahrajeme do parametru addr
int checkarr(char arr[9]); //pruchod devitice znaku
void flushMatrix(int Ematrix[9][9]); //vynulovani matice po minulem tahu
void checkColumn(chmat Gmatrix, int Ematrix[9][9], int n); //funkce pro overovani spravnosti vsech hodnot ve sloupci
void checkcolumns(chmat Gmatrix, int Ematrix[9][9]); //Oznacuje do Ematrix spatne sloupce
void checkRow(chmat Gmatrix, int Ematrix[9][9], int m); //funkce pro overovani spravnosti vsech hodnot v radku
void checkrows(chmat Gmatrix, int Ematrix[9][9]); //Oznacuje do Ematrix (matice chyb v reseni sudoku) spatne radky
void checkGrid(chmat Gmatrix, int Ematrix[9][9], int gridrow, int gridcolumn); //Oznacuje do Ematrix spatne vyplneno podmatice.
void checkgrids(chmat Gmatrix, int Ematrix[9][9]); //volani chackgrid nad vsemi podmaticemi
int shouldBeColoured(int i, int j); //Oznacuje souradnice, ktere maji mit sachovnicove podbarveni
char* mergeaddr(const char* folderaddr, const char* addr, char* ans); //spoji nazev souboru s adresarem, az pote se s adresou pracuje