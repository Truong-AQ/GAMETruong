#include <windows.h>
#include "point.h"
#include "color.h"

void point::print(const int colorName = default_ColorCode, const int colorN = default_ColorCode) const//in ra man hinh cho dep voi hai mau da chon, mot mau ten thu gi do, mot mau gia tri so thu gi do
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , colorName);//to mau cho ten
    cout << s << " ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , colorN);//to mau cho gia tri
    cout << n;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);//chuyen ve mau tu dong
    return;
}
