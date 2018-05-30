#include "Word.h"

void Word::printf() const//in xau chu s ra man hinh tai toa do coord
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << s;
    return;
}
void Word::clear() const//in xau clearS ra man hinh tai toa do coord, viec nay coi nhu xoa xau s khoi man hinh
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , ColorCode_Back);
    cout << s;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);
    return;
}
