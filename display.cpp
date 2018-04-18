#include "Word.h"
#include "display.h"
#include "color.h"
#include <conio.h>

void introduce()//gioi thieu ten va luat choi
{
    int tSleep = 200;
    //gioi thieu ten tro choi
    Word nameGame = {"TEST ENGLISH", {34, 8}};
    nameGame.createClearS();//tao xau xoa cua ten tro choi
    //hieu ung lam in ra tung chu cua ten tro choi ra man hinh
    for(int i = 0;i < nameGame.lenS;i ++)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), nameGame.coord);
            cout << nameGame.s.substr(0, i + 1);
            Sleep(tSleep);
        }
        Word instruction = {"Nhan phim bat ky de tiep tuc", {27, 12}};//chi dan cua tro choi
        instruction.createClearS();
        instruction.printf();
        while(1)//doi nguoi dung nhap phim thi tro choi tiep tuc
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , rand() % nColors);//tao hieu ung mau cho ten tro choi nhap nhay
            nameGame.printf();
            if(kbhit())
            {
                nameGame.clear();//xoa ten tro choi khoi man hinh
                instruction.clear();//xoa chi dan
                if(getch() == 224)//bat phim ki tu dac biet
                    getch();
                break;
            }
            Sleep(tSleep);
        }
        //gioi thieu luat choi tro choi
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , ColorCode_Yellow);//in luat choi ra man hinh voi mau vang
        Word laws[] =
        {
            {"Tro choi yeu cau ban doan nghia mot tu tieng anh", {10, 7}},
            {"Co tat ca 4 phuong an dung la A, B ,C, D cho ban lua chon", {10, 8}},
            {"Hay chon dap an dung trong so do, va ket qua doc tu ban phim", {10, 9}},
            {"Ban can dat duoc 100 diem de hoan thanh tro choi nay", {10, 10},},
            {"An phim bat ki de tro choi duoc bat dau", {10, 11}}
        };//cac luat choi
        int nLaws = sizeof(laws) / sizeof(Word);//tinh toan so luat choi
        for(int i = 0;i < nLaws;i ++)
            laws[i].createClearS();
    for(int i = 0;i < nLaws;i ++)//in luat choi ra man hinh
    {
    	Sleep(tSleep);
    	laws[i].printf();
	}
    while(1)//doi nguoi dung nhap 1 phim de tro choi tiep tuc
    {
        if(kbhit())
        {
            if(getch() == 224)//ki tu dac biet
                    getch();
            for(int i = 0;i < nLaws;i ++)//xoa cac luat choi khoi man hinh
                laws[i].clear();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);//doi mau cua chu sang mau tu dong
            return;
        }
    }
}
void printfBoard(const int &nAnswers)//in ra man hinh cac phan hien thi co ban cua tro choi
{
	//in hinh chu nhat chua cac cau tra loi ben trong
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , ColorCode_Cyan);//in cac hinh chu nhat bang mau cyan
    int nTriangle  = nAnswers;//so hinh chu nhat bang so dap an, trong tro nay mac dinh la 4 dap an
    string triangle[] =
    {
        "ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿",
        "³               ³",
        "³               ³",
        "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ"
    };//hinh chu nhat co chieu dai 17, chieu rong 4
    int heightTriangle = sizeof(triangle) / sizeof(string);//tinh toan chieu rong hinh chu nhat
    COORD coordTriangle[] = {{18, 6}, {42, 6}, {18, 12}, {42, 12}};//toa do cua 4 hinh chu nhat
    for(int i = 0;i < nTriangle;i ++)//in tung hinh chu nhat ra man hinh
    {
        for(int j = 0;j < heightTriangle;j ++)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordTriangle[i]);
            cout << triangle[j];
            coordTriangle[i].Y ++;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);//chuyen ve mau tu dong de in cac dap an
    Word nameAnswer[nAnswers] =
    {
        {"A.", {19, 5}},
        {"B.", {43, 5}},
        {"C.", {19, 11}},
        {"D.", {43, 11}}
    };//ten cac dap an va cac toa do cua dap an
    for(int i = 0;i < nAnswers;i ++)//in dap an ra man hinh
    nameAnswer[i].printf();
    //in tuong (gioi han cua vung choi tro choi va vung in diem va mang song)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , ColorCode_Blue);//tuong mau blue
    Word wall = {"³", {60, 0}};
    for(int i = 0;i < consoleHeight;i ++)//in tuong ngan cach giua man hinh cau hoi va man hinh diem, mang choi
    {
        wall.printf();
        wall.coord.Y ++;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);//chuyen mau ve tu dong de in ten cia dong chet (gioi han thoi gian cua\
    tro choi), se thay khi choi tro choi
    Word nameLineDead = {"LINE DEAD", {34, 17}};
    nameLineDead.printf();
    return;
}
void toBootSecond(const int n)//khoi dong n giay truoc khi tro choi bat dau
{
    int tSleep = 1000;//thoi gian ngu 1 s
    Word wordBegin = {"GO!", {38, 11}};//tu de bat dau cuoc choi
    wordBegin.createClearS();
    for(int i = n;i > 0;i --)//in tung giay ..., 3, 2, 1 ra man hinh
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), wordBegin.coord);
        cout << i;
        Sleep(tSleep);
    }
    wordBegin.printf();//in tu GO! de tro choi bat dau
    Sleep(tSleep);
    wordBegin.clear();//xoa tu GO! khoi man hinh
    return;
}
