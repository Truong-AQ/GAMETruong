#include "point.h"
#include "color.h"
#include "Word.h"
#include <conio.h>
#include <fstream>

//xu li dap an ma nguoi choi nhap vao
void handl(point &score, point &heart, const char &correctAnswer, const char &reply, int &cumulativePoint, int &timeQuestion, const int &rhythmPlay, const int &pointToConvertHeart)
{
    char noReply = 2;//day mac dinh la ki tu tra ve khi nguoi choi khong nhap dap an tu ban phim
    if(reply == correctAnswer)//cau tra loi cua nguoi choi dung
    {
        score.n ++;//tang diem
        cumulativePoint ++;//so diem tich luy tang them 1 diem
        if(cumulativePoint == pointToConvertHeart)//neu du diem tich luy, chuyen so diem do thanh mang song
        {
            cumulativePoint = 0;
            heart.n ++;
            timeQuestion -= rhythmPlay;//giam thoi gian choi de tang do kho
        }
    }
    else//neu cau tra loi cua nguoi choi sai
    {
        heart.n --;//mat mot mang
        if(reply == noReply)//neu nguoi choi khong nhap dap an thi tang thoi gian choi (co the do thoi gian choi qua nhanh)
            timeQuestion += rhythmPlay;
        Word advice = {"Wrong! Right answer is ", {18, 19}};//loi khuyen de thong bao dap an dung
        Word instruction = {"An phim bat ky de tiep tuc", {18, 20}};//chi dan cho nguoi choi de tiep tuc tro choi
        //tao xau xoa cua hai tu nay
        advice.createClearS();
        instruction.createClearS();
        advice.printf();//in loi thong bao
        cout << correctAnswer;//in dap an dung
        instruction.printf();//in chi dan
        while(1)//doi nguoi dung nhap 1 phim de tiep tuc tro choi
        {
            if(kbhit())
            {
                if(getch() == 224)//bat phim ki tu dac biet
                    getch();
                advice.clear();//xoa loi khuyen
                cout << " ";//in them mot khoang trang de xoa dap an vua thong bao la dung
                instruction.clear();//xoa chi dan
                break;
            }
        }
    }
    return;
}
//xu li khi tro choi ket thuc
void handlGameOver(const point &score, const point &heart)
{
	    system("cls");//xoa man hinh
        int tSleep = 300;
        Word nameEnd = {"GAME OVER!", {35, 8}};//hien ra khi tro choi ket thuc, game over
        nameEnd.lenS = nameEnd.s.length();//tinh do dai tu game over
        ifstream file("best.txt");//file luu diem cao nhat cua tro choi
        int maxScore;//diem cao nhat
        file >> maxScore;//doc diem tu file
        file.close();//dong file
        if(maxScore < score.n)//neu so diem nguoi choi vuot qua so diem dat cao nhat truoc do thi thay so diem cao nhat doc tu file bang so diem do\
        roi luu vao file so diem do
        {
            ofstream file("best.txt");
            file << score.n;
            maxScore = score.n;
            file.close();//dong file
        }
        point yourScore = {"Diem cua ban:", score.n, {32, 12}};//diem cua khi nguoi choi choi tro choi
        point bestScore = {"Diem cao nhat:", maxScore, {32, 14}};//diem cao nhat cua nguoi choi
        for(int i = 0;i < nameEnd.lenS;i ++)//tao hieu ung in ra chu game over (in tung tu mot den het) cho dep
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), nameEnd.coord);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , rand() % nColors);
            cout << nameEnd.s.substr(0, i + 1);
            Sleep(tSleep);
        }
        //in diem nguoi choi choi duoc va diem cao nhat nguoi choi choi duoc ra man hinh
        yourScore.print(ColorCode_White, ColorCode_Yellow);
        bestScore.print(ColorCode_White, ColorCode_Yellow);
        while(1)//doi nguoi choi nhap phim thi dung chuong trinh
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , rand() % nColors);//tao mau nhap nhay cho chu game over
            nameEnd.printf();//in ra chu game over
            Sleep(tSleep);
            if(kbhit())
                break;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);//chuyen ve mau tu dong
        return;
}
void handlWinGame(const int &winScore)
{
	system("cls");//xoa man hinh
	ofstream file("best.txt");
	file << winScore;//luu diem tuyet doi vao file best.txt (file chua diem cao nhat cua nguoi choi)
	file.close();
	int tSleep = 500, nFireWorks;
	Word fireWorks[] = //phao hoa
	{
		{"\\\\\\\\\\/////",{35, 7}},
		{"\\\\\\\\////",{36, 8}},
		{"\\\\\\///",{37, 9}},
		{"\\\\//",{38, 10}},
		{"\\/",{39, 11}},
		{"||",{39, 12}}
	};
	nFireWorks = sizeof(fireWorks) / sizeof(Word);//tinh so luong phao hoa
	for(int i = 0;i < nFireWorks;i ++)
	fireWorks[i].createClearS();//xau xoa cua phao hoa
	Word nameWin = {"CONGRATULATIONS! You win", {28, 5}};//loi chuc mung chien thang
	nameWin.createClearS();
	while(1)
	{
		for(int i = 0;i < nFireWorks;i ++)
		fireWorks[i].clear();//xoa phao hoa
		nameWin.clear();//xoa loi chuc mung
		//in phao hoa va loi chuc mung, cho giong voi phao hoa that thi phai in tung cai mot
		for(int i = nFireWorks - 1;i >= 0;i --)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , rand() % nColors);//in phao hoa nhieu mau
			fireWorks[i].printf();
			Sleep(tSleep);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , rand() % nColors);
		nameWin.printf();
		Sleep(tSleep);
		if(kbhit())//phat hien co nut nhap vao thi tro choi ket thuc
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);//chuyen ve mau tu dong
			return;
		}
	}
}
