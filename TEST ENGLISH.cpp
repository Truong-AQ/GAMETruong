#include <vector>
#include "Word.h"
#include "display.h"
#include "readWord.h"
#include "play.h"
#include "point.h"
#include "color.h"
#include <ctime>
#include "handlGame.h"

using namespace std;

int main()
{
    vector <Word> englishWordList, vietnameseWordList;//tao ra 2 vector chua cac tu tieng anh va tieng viet
    createWordList(englishWordList, "english.txt");// doc tu tieng anh tu english.txt
    createWordList(vietnameseWordList, "vietnam.txt");//doc tu tieng viet tu vietnam.txt
    const int nWords = englishWordList.size();//nWords la so luong tu trong danh sach
    if(nWords == 0)//trong file khong co tu hay khong doc duoc file thi ket thuc chuong trinh
        cout << "Error";
    else
    {
    	//cac gia tri quan trong cua tro choi gom co: diem (score), mang choi(heart), diem tich luy (cumalativePoint)\
		diem de chuyen doi (pointToConvertHeart, cu tich luy du 10 diem duoc tang len 1 mang)\
		thoi gian tra loi cau hoi (timeQuestion), nhip choi (rhythmPlay, dung de giam hay tang thoi gian choi), winScore (diem de thang tro choi)
    	int cumulativePoint = 0;
		const int pointToConvertHeart = 10, winScore = 100;
		int timeQuestion = 500;
    	const int nAnswers = 4, rhythmPlay = 100;
        point score = {"SCORE:", 0, {61, 2}}, heart = {" ", 3, {61, 0}};
        heart.s[0] = 3;//hinh trai tim the hien mang song
        introduce();//gioi thieu ten va luat choi
        //in cac phan hien thi co ban cua tro choi
        printfBoard(nAnswers);
        //in diem va mang choi
        score.print(ColorCode_Pink, ColorCode_Yellow);
        heart.print(ColorCode_Pink, ColorCode_Yellow);
        toBootSecond(3);//khoi dong 3 s truoc khi bat dau tro choi
        srand(time(NULL));//khoi tao bo so ngau nhien de tao ra cac cau tra loi ngau nhien
        while(1)//vong lap tro choi
        {
            int theAnswers[nAnswers];//mang luu cac cau tra loi, moi so tuong ung se la moi tu trong danh sach tu tieng viet
            createTheAnswer(theAnswers, nWords, nAnswers);//ham tao ra cac cau tra loi ngau nhien
            char correctAnswer = rand() % nAnswers + 'A';//lua chon dap an ngau nhien trong danh sach tu tieng viet => tu hoi se la tu tieng anh tuong ung
            printfQuestion(theAnswers, nAnswers, vietnameseWordList, englishWordList, correctAnswer);//in tu tieng anh hoi va cac tu tieng viet la cac cau tra loi
            char reply = read(timeQuestion);//doc lua chon cua nguoi choi
            handl(score, heart, correctAnswer, reply, cumulativePoint, timeQuestion, rhythmPlay, pointToConvertHeart);//ham xu ly xem nguoi choi tra loi dung hay sai
            score.print(ColorCode_Pink, ColorCode_Yellow);//in diem
            heart.print(ColorCode_Pink, ColorCode_Yellow);//in mang
            clearQuestion(theAnswers, nAnswers, vietnameseWordList, englishWordList, correctAnswer);//xoa cau hoi va cau tra loi
            if(score.n == winScore)//khi nguoi choi thang
            {
            	handlWinGame(winScore);//xu li khi nguoi choi thang cuoc
            	break;
			}
            if(heart.n == 0)//het mang, ket thuc tro choi
            {
                 handlGameOver(score, heart);//xu ly khi tro choi ket thuc
                 break;
            }
        }
    }
    return 0;
}
