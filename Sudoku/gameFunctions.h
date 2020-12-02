#pragma once

typedef char chmat[9][9];

void showConsoleCursor(bool showFlag); //Funkce z navodoveho souboru, skryva nebo ukazuje kurzor
void printMatrix(chmat Omatrix, chmat Gmatrix, int Ematrix[9][9]); //Tisk matice, upravena funkce z navodoveho souboru
void setCursorPosition(int x, int y); //Z navodoveho souboru
void move(char d, int* mActual, int* nActual); //Funkce z navodoveho souboru, slouzi k posouvani po hernim poli
int getvictory(chmat Gmatrix, int Ematrix[9][9]); //Hlida pravidla hry. Pokud je hraci pole zaplnene a bez chyb (Ematrix je matice nul), pak vrati hodnotu 1
void checkAndPrintMatrix(chmat Omatrix, chmat Gmatrix, int Ematrix[9][9], int mActual, int nActual); //Funkce ma za ukol pouze zkratit kod, ktery by se jinak opakoval. Vola nekolik ostatnich funkci v urcite sekvenci, sama je volana ve funkci play()
int play(chmat Omatrix, chmat Gmatrix, int gamemode, int* ptr); //Samotny herni mechanismus, vola ostatni funkce, je volana z menu()