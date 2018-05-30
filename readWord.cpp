#include <vector>
#include <fstream>
#include "Word.h"

using namespace std;

void createWordList(vector <Word> &wordList, const string nameFile)//tao danh sach tu tu tep ten la nameFile, doc va luu no vao vector wordList
{
    ifstream file(nameFile.c_str());//doc file chua danh sach tu
    if(file.is_open())//neu file mo
    {
        Word word;
        while(!file.eof())
        {
            getline(file, word.s);//doc tung tu mot
            word.lenS = word.s.length();
            wordList.push_back(word);//them tu vao danh sach tu
        }
    }
    file.close();//dong file
    return;
}
