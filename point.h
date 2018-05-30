#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <windows.h>

using namespace std;

//struct nay gom co cac truong: do dai cua ten thu gi do (diem, mang choi, ...), gia tri cua thu gi do (n), toa do cua thu do khi in ra man hinh (coord)
struct point
{
    public:
    string s;
    int n;
    COORD coord;
    void print(const int colorName, const int colorN) const;
};

#endif
