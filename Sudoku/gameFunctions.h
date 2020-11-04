#pragma once

void printMatrix(char Omatrix[9][9], char Gmatrix[9][9], int Ematrix[9][9]); //Tisk matice, upravena funkce z navodoveho souboru
void setCursorPosition(int x, int y); //Z navodoveho souboru
void printPoint(char Gmatrix[9][9], int* mActual, int* nActual); //Upravena funkce z navodoveho souboru
void moveNumber(char Gmatrix[9][9], char d, int* mActual, int* nActual); //Funkce z navodoveho souboru, slouzi k posouvani po hernim poli
int getvictory(char Gmatrix[9][9], int Ematrix[9][9]); //Hlida pravidla hry. Pokud je hraci pole zaplnene a bez chyb (Ematrix je matice nul), pak vrati hodnotu 1
void checkAndPrintMatrix(char Omatrix[9][9], char Gmatrix[9][9], int Ematrix[9][9], int mActual, int nActual); //Funkce ma za ukol pouze zkratit kod, ktery by se jinak opakoval. Vola nekolik ostatnich funkci v urcite sekvenci, sama je volana ve funkci play()
void printMenu(char* row, unsigned int rownum, int canContinue); //Vykresli hlavni menu
void play(char Omatrix[9][9], char Gmatrix[9][9], int gamemode, int* ptr); //Samotny herni mechanismus, vola ostatni funkce, je volana z menu()