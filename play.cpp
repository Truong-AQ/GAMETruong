#include "color.h"
#include <cstdlib>
#include <vector>
#include "Word.h"
#include <conio.h>

using namespace std;

void createTheAnswer(int theAnswers[], const int &nWords, const int &nAnswers)//tao ra cac gia tri so la vi tri cua cac cau tra loi trong danh sach vietnameseWordList
{
    for(int i = 0;i < nAnswers;i ++)//tao ra tung dap an mot, bat dau tu dap an thu nhat (theAnswers[0])
    {
        bool valueValid = true;//mot bien de kiem tra xem gia tri nay co hop ly khong de con luu vao lam gia tri cho theAnswers[i]
        int indexRandom = rand() % nWords;//gia tri sinh ra ngau nhien
        for(int j = 0;j < i;j ++)//kiem tra cac dap an truoc do co dap an nao trung dap an nay khong (do cac dap an khac nhau)
            if(indexRandom == theAnswers[j])//neu xuat hien thi gia tri sinh ra nay khong hop le
        {
            valueValid = false;
            break;
        }
        if(valueValid == true)//neu gia tri hop le, cho no vao lam dap an theAnswers[i]
            theAnswers[i] = indexRandom;
        else//neu gia tri khong hop le, tao lai gia tri do de luu vao theAnswers[i]
            i --;
    }
    return;
}
//in tu tieng anh la tu hoi va cac cau tra loi
void printfQuestion(const int theAnswers[], const int &nAnswers, const vector <Word> &vietnameseWordList, const vector <Word> &englishWordList, const char &correctAnswer)
{
    static int mid = 38;//toa do x giua hai hinh chu nhat, dung de in cau hoi vua man hinh voi cac dap an tra loi
    static COORD answers[] = {{19, 7}, {43, 7}, {19, 13}, {43, 13}};//toa do de in cac cau tra loi cho tu hoi
    Word question = englishWordList.at(theAnswers[correctAnswer - 'A']);
    question.coord.X = mid - question.lenS / 2;
    question.coord.Y = 3;
    question.printf();//in cau hoi
    //in cac cau tra loi voi chu la mau do cho dep
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , ColorCode_Red);
    for(int i = 0;i < nAnswers;i ++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), answers[i]);
        cout << vietnameseWordList.at(theAnswers[i]).s;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);//chuyen mau ve tu dong
    return;
}

char read(const int &timeQuestion)//doc dap an vao
{
    char noReply = 2;//nguoi choi khong tra loi, thi mac dinh dap an tra loi la ki tu 2 do nguoi choi khong nhap duoc ki tu nay
    Word lineDead = {"ÄÄÄÄÄÄÄÄÄ", {34, 16}};
    lineDead.printf();//in dong de tuong trung cho gioi han thoi gian choi
    static int limRight = 41, limLeft = 35, mid = (limLeft + limRight) / 2;//dieu khien cai mat cuoi di chuyen tren man hinh nen can cac gia tri nay:\
    cai mat cuoi se di chuyen nam trong hai gioi han trai (limLeft) va gioi han phai (limRight), giua (mid) de xac dinh trang thai cua cai mat cuoi luc dau\
    la di chuyen sang trai hay phai
    Word man = {" ", {rand() % limRight + 1, 6}};//tao toa do ngau nhien cho mat cuoi
    man.s[0] = 2;//hinh cai mat cuoi
    string state = "RIGHT";//trang thai luc dau la ben phai
    while(man.coord.X < limLeft)//neu toa do x cua cai mat cuoi khong nam trong hai gioi 2han thi phai dieu chinh lai
        man.coord.X = rand() % limRight + 1;
        if(man.coord.X >= mid)//neu toa do x cua cai mat cuoi lon hon giua (mid) thi chuyen trang thai di chuyen cua cai mat cuoi sang ben trai
            state == "LEFT";
    while(man.coord.Y <= lineDead.coord.Y)//khi cai mat cuoi chua cham vao dong chet (lineDead)
    {
        man.printf();//in cai mat cuoi
        if(man.coord.X == limLeft)//neu mat cuoi cham gioi han trai thi trang thai tiep theo phai la phai
            state = "RIGHT";
        else if(man.coord.X == limRight)//neu mat cuoi cham gioi han phai thi trang thai tiep theo phai la trai
            state ="LEFT";
            if(kbhit())//neu co phim nhap vao, tuc nguoi choi da tra loi, thi tra ve gia tri da nhap vao
            {
                char reply;
                reply = getch();
                reply = toupper(reply);//chuyen tra loi cua nguoi choi sang chu hoa
                if(reply == -32)//xu li cac ki tu dac biet
                    getch();
                man.clear();//xoa cai mat cuoi
                return reply;//tra ve ki tu
            }
            Sleep(timeQuestion);//giua moi lan cai mat cuoi di chuyen la mot khoang thoi gian
            man.clear();//xoa cai mat cuoi nay di de in tiep cac mat cuoi o vi tri ke tiep
            //tuy theo trang thai cai mat cuoi thi tinh toan toa do tiep theo cua cai mat cuoi
            if(state == "RIGHT")
            man.coord.X ++;
            else if(state == "LEFT")
            man.coord.X --;
            man.coord.Y ++;
    }
    return noReply;//neu nguoi choi khong tra loi kip thi tra ve gia tri nay
}
//xoa tu hoi va cac cau tra loi
void clearQuestion(const int theAnswers[], const int &nAnswers, const vector <Word> &vietnameseWordList, const vector <Word> &englishWordList, const char &correctAnswer)
{
    static int mid = 38;//toa do x giua hai hinh chu nhat, dung de in cau hoi vua man hinh voi cac dap an tra loi
    static COORD answers[] = {{19, 7}, {43, 7}, {19, 13}, {43, 13}};//toa do cua cac cau tra loi
    Word question = englishWordList.at(theAnswers[correctAnswer - 'A']);
    question.coord.X = mid - question.lenS / 2;
    question.coord.Y = 3;
    question.clear();//xoa cau hoi
    //xoa cac cau tra loi
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , ColorCode_Back);
    for(int i = 0;i < nAnswers;i ++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), answers[i]);
        cout << vietnameseWordList.at(theAnswers[i]).s;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);
    return;
}
