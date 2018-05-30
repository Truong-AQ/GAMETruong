#ifndef HANDLGAME_H
#define HANDLGAME_H

//xu li dap an ma nguoi choi nhap vao
void handl(point &score, point &heart, const char &correctAnswer, const char &reply, int &cumulativePoint, int &timeQuestion, const int &rhythmPlay, const int &pointToConvertHeart);
void handlGameOver(const point &score, const point &heart);//xu li khi tro choi ket thuc
void handlWinGame(const int &winScore);

#endif
