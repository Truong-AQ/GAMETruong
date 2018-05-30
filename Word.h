#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <windows.h>
#include "color.h"


using namespace std;

//struct Word gom xau chu s, do dai xau s (lenS), toa do cua xau s (coord) tren man hinh
struct Word
{
    string s;
    COORD coord;
    int lenS;
    void printf() const;
    void clear() const;
};

#endif
