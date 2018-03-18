#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream> 
#include <windows.h>

using namespace std;

void createWordList(vector <string> &wordList, const string fileWord);
int chooseIntexValid(bool *wordsUsed, const int &nWords);
void createTheAnswer(int *theAnswer, int &correctAnswer, const int &randomIntex, const int &nWords, const int &nAnswers);
void printfQuestion(const vector <string> &englishWordList, const vector <string> &vietnameseWordList, const int &randomIntex, const int *theAnswer, const int &nAnswers);
void readReply(char &reply);
void handl(const char &reply, const int &correctAnswer, int &yourPoint, int &wordsCanGuessed,int &nAnswers);

int main()
{
	vector <string> englishWordList, vietnameseWordList;
	createWordList(englishWordList, "EnglishWordList.txt");
	createWordList(vietnameseWordList, "VietnameseWordList.txt");
	int nWords = vietnameseWordList.size();
    if(nWords != 0)
    {
		int nAnswers = 4;
		bool *wordsUsed;
		wordsUsed = new bool[nWords];
		int wordsCanGuessed = nWords, yourPoint = 0;
    	for(; ;)
		{
		    int randomIntex = chooseIntexValid(wordsUsed, nWords);
			int correctAnswer, theAnswer[nAnswers];
            createTheAnswer(theAnswer, correctAnswer, randomIntex, nWords, nAnswers);
            printfQuestion(englishWordList, vietnameseWordList, randomIntex, theAnswer, nAnswers);
            char reply;
            readReply(reply); 
			handl(reply, correctAnswer, yourPoint,wordsCanGuessed, nAnswers);
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

void createWordList(vector <string> &wordList, const string fileWord)
{
	ifstream file (fileWord.c_str());
	if(file.is_open())
	{
		string word;
		while(!file.eof())
		{
			getline(file, word);
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
void createTheAnswer(int *theAnswer, int &correctAnswer, const int &randomIntex, const int &nWords, const int &nAnswers)
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

void printfQuestion(const vector <string> &englishWordList, const vector <string> &vietnameseWordList, const int &randomIntex, const int *theAnswer, const int &nAnswers)
{
    cout << englishWordList.at(randomIntex) << endl;
    for(int i = 0;i < nAnswers;i ++)
    cout << (char) (i + 'A') << ". " << vietnameseWordList.at(theAnswer[i]) << endl;
    return;
}
void readReply(char &reply)
{
    cin >> reply;
    return;
}
void handl(const char &reply, const int &correctAnswer, int &yourPoint, int &wordsCanGuessed,int &nAnswers)
{
	if(reply - 'A' == correctAnswer
	|| reply - 'a' == correctAnswer)
    {
    	yourPoint ++;
    	wordsCanGuessed --;
	    if(yourPoint % 10 == 0)
        nAnswers ++;
    }
    else
    {
        cout << "You lose!" << endl;
        wordsCanGuessed = 0;
    }
    cout << endl;
    return;
}
