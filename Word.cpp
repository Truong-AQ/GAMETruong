#include "Word.h"

void Word::createClearS()//tao ra do dai xau s va xau xoa clearS
{
    lenS = s.length();//tinh do dai xau s
    clearS = string(lenS, ' ');//tao clearS co do dai bang s va toan ki tu trang
    return;
}
void Word::printf() const//in xau chu s ra man hinh tai toa do coord
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << s;
    return;
}
void Word::clear() const//in xau clearS ra man hinh tai toa do coord, viec nay coi nhu xoa xau s khoi man hinh
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << clearS;
    return;
}
