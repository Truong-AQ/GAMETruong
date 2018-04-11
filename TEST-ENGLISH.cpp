#include <iostream>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <ctime>

#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7
#define nColors                 16
#define consoleWidth            80
#define consoleHeight           25

int timeQuestion = 500;
const int rhythmPlay = 100;
const int nAnswers = 4;
int cumulativePoint = 0;
const int pointToConvertHeart = 10;

using namespace std;

class Word
{
    public:
    string s;
    COORD coord;
    int lenS;
    string clearS;
    void createClearS()
    {
        lenS = s.length();
        clearS = string(lenS, ' ');
        return;
    }
    void printf()
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
        cout << s;
        return;
    }
    void clear()
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
        cout << clearS;
        return;
    }
};
class point
{
    public:
    string s;
    int n;
    COORD coord;
    void print(int colorName, int colorN)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , colorName);
        cout << s << " ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , colorN);
        cout << n;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);
        return;
    }
};

void introduce();
void printfBoard();
void toBootSecond(int n);
void createWordList(vector <Word> &wordList, string nameFile);//
void createTheAnswer(int theAnswers[], const int &nWords);
void printfQuestion(int theAnswers[], vector <Word> &vietnameseWordList, vector <Word> &englishWordList, char &correctAnswer);
char read();
void clearQuestion(int theAnswers[], vector <Word> &vietnameseWordList, vector <Word> &englishWordList, char &correctAnswer);
void handl(point &score, point &heart, char &correctAnswer, char &reply);
void gameOver(point &score, point &heart);

int main()
{
    vector <Word> englishWordList, vietnameseWordList;
    createWordList(englishWordList, "english.txt");
    createWordList(vietnameseWordList, "vietnam.txt");
    int nWords = englishWordList.size();
    if(nWords == 0)
        cout << "Error";
    else
    {
        point score = {"SCORE:", 0, {61, 2}}, heart = {" ", 3, {61, 0}};
        heart.s[0] = 3;
        introduce();
        printfBoard();
        score.print(ColorCode_Pink, ColorCode_Yellow);
        heart.print(ColorCode_Pink, ColorCode_Yellow);
        toBootSecond(3);
        srand(time(NULL));
        while(1)
        {
             int theAnswers[nAnswers];
             createTheAnswer(theAnswers, nWords);
             char correctAnswer = rand() % nAnswers + 'A';
             printfQuestion(theAnswers, vietnameseWordList, englishWordList, correctAnswer);
             char reply = read();
             handl(score, heart, correctAnswer, reply);
             score.print(ColorCode_Pink, ColorCode_Yellow);
             heart.print(ColorCode_Pink, ColorCode_Yellow);
             clearQuestion(theAnswers, vietnameseWordList, englishWordList, correctAnswer);
             if(heart.n == 0)
             {
                 gameOver(score, heart);
                 break;
             }
        }
    }
    return 0;
}

void introduce()
{
    int tSleep = 200;
    Word nameGame = {"TEST ENGLISH", {34, 8}};
    nameGame.createClearS();
    for(int i = 0;i < nameGame.lenS;i ++)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), nameGame.coord);
            cout << nameGame.s.substr(0, i + 1);
            Sleep(tSleep);
        }
        Word instruction = {"Nhan phim bat ky de tiep tuc", {27, 12}};
        instruction.createClearS();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);
        instruction.printf();
        while(1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , rand() % nColors);
            nameGame.printf();
            if(kbhit())
            {
                nameGame.clear();
                instruction.clear();
                if(getch() == 224)
                    getch();
                break;
            }
            Sleep(tSleep);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , ColorCode_Yellow);
        int nLaws = 4;
        Word laws[nLaws] =
        {
            {"Tro choi yeu cau ban doan nghia mot tu tieng anh", {10, 7}},
            {"Co tat ca 4 phuong an dung la A, B ,C, D cho ban lua chon", {10, 8}},
            {"Hay chon dap an dung trong so do", {10, 9}},
            {"Go phim bat ki de tro choi duoc bat dau", {10, 10}}
        };
        for(int i = 0;i < nLaws;i ++)
            laws[i].createClearS();
    for(int i = 0;i < nLaws;i ++)
    laws[i].printf();
    while(1)
    {
        if(kbhit())
        {
            if(getch() == 224)
                    getch();
            for(int i = 0;i < nLaws;i ++)
                laws[i].clear();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);
            return;
        }
    }
}
void createWordList(vector <Word> &wordList, string nameFile)
{
    ifstream file(nameFile.c_str());
    if(file.is_open())
    {
        Word word;
        while(!file.eof())
        {
            getline(file, word.s);
            word.createClearS();
            wordList.push_back(word);
        }
    }
    file.close();
    return;
}
void printfBoard()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , ColorCode_Cyan);
    int nTriangle  = nAnswers;
    string triangle[] =
    {
        "ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿",
        "³               ³",
        "³               ³",
        "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ"
    };
    int heightTriangle = sizeof(triangle) / sizeof(string);
    COORD coordTriangle[] = {{18, 6}, {42, 6}, {18, 12}, {42, 12}};
    for(int i = 0;i < nTriangle;i ++)
    {
        for(int j = 0;j < heightTriangle;j ++)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordTriangle[i]);
            cout << triangle[j];
            coordTriangle[i].Y ++;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);
    Word nameAnswer[nAnswers] =
    {
        {"A.", {19, 5}},
        {"B.", {43, 5}},
        {"C.", {19, 11}},
        {"D.", {43, 11}}
    };
    for(int i = 0;i < nAnswers;i ++)
    nameAnswer[i].printf();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , ColorCode_Blue);
    Word wall = {"³", {60, 0}};
    for(int i = 0;i < consoleHeight;i ++)
    {
        wall.printf();
        wall.coord.Y ++;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);
    Word nameLineDead = {"LINE DEAD", {34, 17}};
    nameLineDead.printf();
    return;
}
void createTheAnswer(int theAnswers[], const int &nWords)
{
    for(int i = 0;i < nAnswers;i ++)
    {
        bool valueValid = true;
        int indexRandom = rand() % nWords;
        for(int j = 0;j < i;j ++)
            if(indexRandom == theAnswers[j])
        {
            valueValid = false;
            break;
        }
        if(valueValid == true)
            theAnswers[i] = indexRandom;
        else
            i --;
    }
    return;
}
void printfQuestion(int theAnswers[], vector <Word> &vietnameseWordList, vector <Word> &englishWordList, char &correctAnswer)
{
    static int mid = 38;
    static COORD answers[] = {{19, 7}, {43, 7}, {19, 13}, {43, 13}};
    Word question = englishWordList.at(theAnswers[correctAnswer - 'A']);
    question.coord.X = mid - question.lenS / 2;
    question.coord.Y = 3;
    question.printf();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , ColorCode_Red);
    for(int i = 0;i < nAnswers;i ++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), answers[i]);
        cout << vietnameseWordList.at(theAnswers[i]).s;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);
    return;
}
void toBootSecond(int n)
{
    int tSleep = 1000;
    Word wordBegin = {"GO!", {38, 11}};
    wordBegin.createClearS();
    for(int i = n;i > 0;i --)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), wordBegin.coord);
        cout << i;
        Sleep(tSleep);
    }
    wordBegin.printf();
    Sleep(tSleep);
    wordBegin.clear();
    return;
}
char read()
{
    char noReply = ' ';
    Word lineDead = {"ÄÄÄÄÄÄÄÄÄ", {34, 16}};
    lineDead.printf();
    static int limRight = 41, limLeft = 35, mid = (limLeft + limRight) / 2;
    Word man = {" ", {rand() % limRight + 1, 6}};
    man.s[0] = 2;
    man.createClearS();
    string state = "RIGHT";
    while(man.coord.X < limLeft)
        man.coord.X = rand() % limRight + 1;
        if(man.coord.X >= mid)
            state == "LEFT";
    while(man.coord.Y <= lineDead.coord.Y)
    {
        man.printf();
        if(man.coord.X == limLeft)
            state = "RIGHT";
        else if(man.coord.X == limRight)
            state ="LEFT";
            if(kbhit())
            {
                char reply;
                reply = getch();
                if(reply == -32)
                    getch();
                man.clear();
                return reply;
            }
            Sleep(timeQuestion);
            man.clear();
            if(state == "RIGHT")
            man.coord.X ++;
            else if(state == "LEFT")
            man.coord.X --;
            man.coord.Y ++;
    }
    return noReply;
}
void clearQuestion(int theAnswers[], vector <Word> &vietnameseWordList, vector <Word> &englishWordList, char &correctAnswer)
{
    static int mid = 38;
    static COORD answers[] = {{19, 7}, {43, 7}, {19, 13}, {43, 13}};
    Word question = englishWordList.at(theAnswers[correctAnswer - 'A']);
    question.coord.X = mid - question.lenS / 2;
    question.coord.Y = 3;
    question.clear();
    for(int i = 0;i < nAnswers;i ++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), answers[i]);
        cout << vietnameseWordList.at(theAnswers[i]).clearS;
    }
    return;
}
void handl(point &score, point &heart, char &correctAnswer, char &reply)
{
    char noReply = ' ';
    reply = toupper(reply);
    if(reply == correctAnswer)
    {
        score.n ++;
        cumulativePoint ++;
        if(cumulativePoint == pointToConvertHeart)
        {
            cumulativePoint = 0;
            heart.n ++;
            timeQuestion -= rhythmPlay;
        }
    }
    else
    {
        heart.n --;
        if(reply == noReply)
            timeQuestion += rhythmPlay;
        Word advice = {"Wrong! Right answer is ", {18, 19}};
        Word instruction = {"An phim bat ky de tiep tuc", {18, 20}};
        advice.createClearS();
        instruction.createClearS();
        advice.printf();
        cout << correctAnswer;
        instruction.printf();
        while(1)
        {
            if(kbhit())
            {
                if(getch() == 224)
                    getch();
                advice.clear();
                cout << " ";
                instruction.clear();
                break;
            }
        }
    }
    return;
}
void gameOver(point &score, point &heart)
{
    COORD originalCoord = {0, 0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), originalCoord);
        cout << string(consoleWidth*consoleHeight, ' ');
        int tSleep = 300;
        Word nameEnd = {"GAME OVER!", {35, 8}};
        point yourScore = {"Diem cua ban:", score.n, {32, 12}};
        nameEnd.createClearS();
        for(int i = 0;i < nameEnd.lenS;i ++)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), nameEnd.coord);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , rand() % nColors);
            cout << nameEnd.s.substr(0, i + 1);
            Sleep(tSleep);
        }
        yourScore.print(ColorCode_White, ColorCode_Yellow);
        ifstream file("best.txt");
        int max;
        file >> max;
        file.close();
        if(max < score.n)
        {
            ofstream file("best.txt");
            file << score.n;
            max = score.n;
            file.close();
        }
        point bestScore = {"Diem cao nhat:", max, {32, 14}};
        bestScore.print(ColorCode_White, ColorCode_Yellow);
        while(1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , rand() % nColors);
            nameEnd.printf();
            Sleep(tSleep);
            if(kbhit())
                break;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , default_ColorCode);
        return;
}
