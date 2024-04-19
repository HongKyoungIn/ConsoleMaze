#include "main.h"
#include "map.h"
#include "time.h"

using namespace std;

#define FINISH 4    // 도착 지점
#define PLAYER 20    // 플레이어
#define WALL 1    // 벽 - 플레이어가 막혀서 가지 못 하는 곳.
#define SPACE 0    // 빈 공간 - 즉 플레이어가 이동할 수 있는 곳.
#define RMS 25    // 부품 배열의 크기

int level = 1; // 현재 레벨
int NowLevel = 0;

void GamePlay() { // game.cpp에서 main() 정도의 역할
	myTime::InitTime();
	int PosX = 1,PosY = 1;    // 플레이어의 좌표
	NowLevel = level;
	char title[40] = {0};

	if(NowLevel == 4) { // 전부 다 클리어 했다면
		AllCompleted();
		return;
	}

	sprintf_s(title,"title 미로찾기 - %d단계",level);
	system(title);
	system("mode con: cols=100 lines=50");    // 50 * 50만큼 출력할 창
	SetMap();    // 자동 맵 생성

	while(NowLevel == level) {
		if(GetAsyncKeyState(VK_UP)) {
			PlayerMove(&PosX,&PosY,VK_UP);
		}
		else if(GetAsyncKeyState(VK_DOWN)) {
			PlayerMove(&PosX,&PosY,VK_DOWN);
		}
		else if(GetAsyncKeyState(VK_LEFT)) {
			PlayerMove(&PosX,&PosY,VK_LEFT);
		}
		else if(GetAsyncKeyState(VK_RIGHT)) {
			PlayerMove(&PosX,&PosY,VK_RIGHT);
		}

		PrintMap(PosX,PosY);
	}

	while(true) {
		switch(LevelSuccess()) {
			case 0:
				for(int i = 0; i < mapSize; i++) {
					delete[] map[i];
					delete[] backupMap[i];
				}
				delete[] map;
				delete[] backupMap;
				GamePlay();
				return;
				break;
			case 1:
				cls;
				break;
			case 2:
				exit(0);
				break;
		}
	}
	return;
}

void StartGame() {
    // 게임 시작
}

void ProcessInput() {
    // 키 입력 함수
}

void FixedUpdate() {

}

void Update() {

}

void EndGame() {

}

bool IsGameRun() {
    return true;
}