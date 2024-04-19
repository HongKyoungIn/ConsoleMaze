#include "main.h"
#include "time.h"
#include "Windows.h"

void mainPtr(void);

using namespace std;

int main() {
	int POS = 0;	// 0 - 새로 하기, 1 - 이어 하기, 2 - 랭킹 보기, 3 - 게임 종료
	CursorView(0);
	system("COLOR 0F");
	mainPtr();

	while(true) {
		if(myTime::shouldProcessInput()) {
			continue;
		}

		if(GetAsyncKeyState(VK_LEFT)) {
			if(POS == 0) POS = 3;
			else POS -= 1;
		}
		else if(GetAsyncKeyState(VK_RIGHT)) {
			if(POS == 3) POS = 0;
			else POS += 1;
		}
		else if(GetAsyncKeyState(VK_RETURN)) // 엔터를 눌렀을 때
			break;

		switch(POS) {
			case 0:
				SetColor(11);
				gotoxy(10, 4); printf("새로  하기");
				SetColor(15);
				gotoxy(35, 4); printf("이어  하기");
				gotoxy(60, 4); printf("랭킹  보기");
				gotoxy(85, 4); printf("게임  종료");
				break;
			case 1:
				gotoxy(10, 4); printf("새로  하기");
				SetColor(11);
				gotoxy(35, 4); printf("이어  하기");
				SetColor(15);
				gotoxy(60, 4); printf("랭킹  보기");
				gotoxy(85, 4); printf("게임  종료");
				break;
			case 2:
				gotoxy(10, 4); printf("새로  하기");
				gotoxy(35, 4); printf("이어  하기");
				SetColor(11);
				gotoxy(60, 4); printf("랭킹  보기");
				SetColor(15);
				gotoxy(85, 4); printf("게임  종료");
				break;
			case 3:
				gotoxy(10, 4); printf("새로  하기");
				gotoxy(35, 4); printf("이어  하기");
				gotoxy(60, 4); printf("랭킹  보기");
				SetColor(11);
				gotoxy(85, 4); printf("게임  종료");
				SetColor(15);
				break;
			default: break;
		}
		// Sleep(100);
	}
	cls;
	if(POS == 0) {
		GamePlay();
	}
	else if(POS == 1) {
		cout << "이어 하기를 눌렀습니다." << endl;
	}
	else if(POS == 2) {
		cout << "랭킹 보기를 눌렀습니다." << endl;
	}

	return 0;
}

void mainPtr(void) {
	system("mode con: cols=106 lines=9");   //참고로 cols 2단위가 특수문자 또는 한글 1글자다.
	system("title 미로찾기 - 메인");
	puts("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(10, 4); printf("새로  하기");
	gotoxy(35, 4); printf("이어  하기");
	gotoxy(60, 4); printf("랭킹  보기");
	gotoxy(85, 4); printf("게임  종료");
	return;
}