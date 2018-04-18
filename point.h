#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <windows.h>

using namespace std;

//class nay gom co cac truong: do dai cua ten thu gi do (diem, mang choi, ...), gia tri cua thu gi do (n), toa do cua thu do khi in ra man hinh (coord)
class point
{
    public:
    string s;
    int n;
    COORD coord;
    void print(const int colorName, const int colorN) const;
};

#endif
