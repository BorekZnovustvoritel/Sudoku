#pragma once

#define getch() _getch()

void showConsoleCursor(bool showFlag); //Funkce z navodoveho souboru, skryva nebo ukazuje kurzor
int loadMatrix(char Omatrix[9][9], char Gmatrix[9][9], char* addr, int* ptr); //Nacteni hraciho pole
int savematrix(char Omatrix[9][9], char Gmatrix[9][9], char* addr); //Ulozi referencni i hracskou matici do souboru s nazvem, kterym nahrajeme do parametru addr
void checkrow(char Gmatrix[9][9], int Ematrix[9][9]); //Oznacuje do Ematrix (matice chyb v reseni sudoku) spatne radky
void checkcolumn(char Gmatrix[9][9], int Ematrix[9][9]); //Oznacuje do Ematrix spatne sloupce
void checkgrid(char Gmatrix[9][9], int Ematrix[9][9], int gridrow, int gridcolumn); //Oznacuje do Ematrix spatne vyplneno podmatice. gridrow a gridcolumn oznacuji pocatecni pozici teto podmatice v hlavni matici
int shouldBeColoured(int i, int j);
char* mergeaddr(char* folderaddr, char* addr, char* ans);