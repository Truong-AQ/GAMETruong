#ifndef PLAY_H
#define PLAY_H

//tao ra cac gia tri so la vi tri cua cac cau tra loi trong danh sach vietnameseWordList
void createTheAnswer(int theAnswers[], const int &nWords, const int &nAnswers);
void printfQuestion(const int theAnswers[], const int &nAnswers, const vector <Word> &vietnameseWordList, const vector <Word> &englishWordList, const char &correctAnswer);
//in tu tieng anh la tu hoi va cac cau tra loi
char read(const int &timeQuestion);//doc dap an vao
//xoa tu hoi va cac cau tra loi
void clearQuestion(const int theAnswers[], const int &nAnswers, const vector <Word> &vietnameseWordList, const vector <Word> &englishWordList, const char &correctAnswer);

#endif
