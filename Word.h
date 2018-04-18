#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <windows.h>

using namespace std;

//class Word gom xau chu s, do dai xau s (lenS), toa do cua xau s (coord) tren man hinh, va xau xoa clearS
class Word
{
    public:
    string s;
    COORD coord;
    int lenS;
    string clearS;//khi in ra xau clearS ra man hinh tai toa do xau s, coi nhu xau s da bi xoa khoi man hinh
    void createClearS();
    void printf() const;
    void clear() const;
};

#endif
