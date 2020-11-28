#pragma once

typedef char chmat[9][9];

void mixRow(chmat matrix, int first, int second);
void mixColumns(chmat matrix, int first, int second);
void swapNumbers(chmat matrix, char first, char second);
void puncture(chmat matrix, int difficulty);
void mixAndClone(chmat Omatrix, chmat Gmatrix, int difficulty);