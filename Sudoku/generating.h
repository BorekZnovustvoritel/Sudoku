#pragma once

#define MAX_ATTEMPTS 1000000

typedef char chmat[9][9];

void mixRow(chmat matrix, int first, int second); //zmena radku v jednom tripletu
void mixColumns(chmat matrix, int first, int second); //zmena sloupcu v jednom tripletu
void swapNumbers(chmat matrix, char first, char second); //zamena devitic cisel (1 <-> 2 apod.)
void puncture(chmat matrix, int difficulty); //derovani
void mixAndClone(chmat Omatrix, chmat Gmatrix, int difficulty); //funkce volajici vyse zminene funkce ve spravnem poradi