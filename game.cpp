#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <conio.h>

using namespace std;

const int nAnswers = 4;

void clrscr();
void gotoXY (int column, int line);
void TextColor (int color);
void createWordList(vector <string> &wordList, const string fileWord);
int chooseIntexValid(bool *wordsUsed, const int &nWords);
void createTheAnswer(int *theAnswer, int &correctAnswer, const int &randomIntex, const int &nWords);
char printfQuestion(const vector <string> &englishWordList, const vector <string> &vietnameseWordList, const int &randomIntex, const int *theAnswer);
void handl(const char &reply, const int &correctAnswer, int &yourPoint, int &wordsCanGuessed);
void handlWord(string &word);
void chen(string word, int dcs, int ccs, string out[]);
void xoanguoi(int i, int j, string out[]);
void chennguoi(int i, int j, string out[]);

int main()
{
	vector <string> englishWordList, vietnameseWordList;
	createWordList(englishWordList, "EnglishWordList.txt");
	createWordList(vietnameseWordList, "VietnameseWordList.txt");
	int nWords = vietnameseWordList.size();
    if(nWords != 0)
    {
		bool *wordsUsed;
		wordsUsed = new bool[nWords];
		int wordsCanGuessed = nWords, yourPoint = 0;
    	for(; ;)
		{
		    clrscr();
		    int roi = 0;
		    int randomIntex = chooseIntexValid(wordsUsed, nWords);
			int correctAnswer, theAnswer[nAnswers];
            createTheAnswer(theAnswer, correctAnswer, randomIntex, nWords);
            char reply = printfQuestion(englishWordList, vietnameseWordList, randomIntex, theAnswer);
			handl(reply, correctAnswer, yourPoint,wordsCanGuessed);
			if(wordsCanGuessed == 0)
			break;
		}
		delete wordsUsed;
		if(yourPoint == nWords)
		cout << "You win!";
	}
	else
	cout << "Error";
	return 0;
}

void handlWord(string &word)
{
    int space = 0;
    for(int i = 0;i < word.length();i ++)
    {
        if(word[i] == ' ')
        {
            space ++;
            if(space % 3 == 0)
                word[i] = '\n';
        }
    }
}

void createWordList(vector <string> &wordList, const string fileWord)
{
	ifstream file (fileWord.c_str());
	if(file.is_open())
	{
		string word;
		while(!file.eof())
		{
			getline(file, word);
			handlWord(word);
			wordList.push_back(word);
		}
	}
	file.close();
	return;
}

int chooseIntexValid(bool *wordsUsed, const int &nWords)
{
    srand(time(NULL));
    int randomIntex = rand() % nWords;
    while(wordsUsed[randomIntex] == true)
    randomIntex = rand() % nWords;
    wordsUsed[randomIntex] = true;
    return randomIntex;
}

void createTheAnswer(int *theAnswer, int &correctAnswer, const int &randomIntex, const int &nWords)
{
    srand(time(NULL));
    correctAnswer = rand() % nAnswers;
    theAnswer[correctAnswer] = randomIntex;
    for(int i = correctAnswer - 1;i >= 0;i --)
    {
        bool valueValid = true;
        int randomIntex = rand() % nWords;
        for(int j = correctAnswer;j > i;j --)
        if(randomIntex == theAnswer[j])
        {
            valueValid = false;
            break;
        }
        if(valueValid == true)
        theAnswer[i] = randomIntex;
        else
        i ++;
    }
    for(int i = correctAnswer + 1;i < nAnswers;i ++)
    {
        bool valueValid = true;
        int randomIntex = rand() % nWords;
        for(int j = 0;j < i;j ++)
        if(randomIntex == theAnswer[j])
        {
            valueValid = false;
            break;
        }
        if(valueValid == true)
        theAnswer[i] = randomIntex;
        else
        i --;
    }
    return;
}

char printfQuestion(const vector <string> &englishWordList, const vector <string> &vietnameseWordList, const int &randomIntex, const int *theAnswer)
{
    int line = 0;
    string out[25];
    for(int i = 0;i < 20;i ++)
        out[line] += " ";
    out[line ++] += englishWordList.at(randomIntex);
    line ++;
    ifstream file("hinh.txt");
    if(file.is_open())
    {
        string hinh;
        while(!file.eof())
        {
            getline(file, hinh);
            out[line ++] = hinh;
        }
    }
    out[line ++] = "____________________________________________________________";
    line ++;
    out [line ++] = "Nhap dap an cua ban: ";
    chen(vietnameseWordList.at(theAnswer[0]), 4, 1, out);
    chen(vietnameseWordList.at(theAnswer[1]), 4, 34, out);
    chen(vietnameseWordList.at(theAnswer[2]), 12, 1, out);
    chen(vietnameseWordList.at(theAnswer[3]), 12, 34, out);
    int roi = 0;
    while(roi != 12)
    {
        clrscr();
        xoanguoi(2 + roi, 24, out);
        chennguoi(3 + roi, 24, out);
        string manhinh;
        for(int i = 0;i < line;i ++)
            manhinh += out[i] + "\n";
            cout << manhinh;
            roi ++;
            if(kbhit())
                return getch();
            Sleep(1000);
    }
    if(roi == 12)
        return '\n';
}

void handl(const char &reply, const int &correctAnswer, int &yourPoint, int &wordsCanGuessed)
{
	if(reply - 'A' == correctAnswer
	|| reply - 'a' == correctAnswer)
    {
    	yourPoint ++;
    	wordsCanGuessed --;
    }
    else
    {
        cout << "You lose!" << endl;
        wordsCanGuessed = 0;
    }
    cout << endl;
    return;
}
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}
void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void TextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}

void chen(string word, int dcs, int ccs, string out[])
{
    int i = dcs, j = ccs;
    for(int k = 0;k < word.length();k ++)
    {
        if(word[k] == '\n')
        {
            i ++;
            j = ccs;
        }
        else
            out[i][j ++] = word[k];
    }
}
void chennguoi(int i, int j, string out[])
{
    out[i][j] = 2;
    out[i + 1][j] = '|';
    out[i + 2][j - 1] = '/';
    out[i + 2][j + 1] = '\\';
    out[i + 2][j] = '|';
    out[i + 3][j - 1] = '/';
    out[i + 3][j + 1] = '\\';
}
void xoanguoi(int i, int j, string out[])
{
    out[i][j] = ' ';
    out[i + 1][j] = ' ';
    out[i + 2][j - 1] = ' ';
    out[i + 2][j + 1] = ' ';
    out[i + 2][j] = ' ';
    out[i + 3][j - 1] = ' ';
    out[i + 3][j + 1] = ' ';
}
