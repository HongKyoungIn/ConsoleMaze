#include "main.h"
#include "map.h"
#include "time.h"

using namespace std;

#define FINISH 4    // ���� ����
#define PLAYER 20    // �÷��̾�
#define WALL 1    // �� - �÷��̾ ������ ���� �� �ϴ� ��.
#define SPACE 0    // �� ���� - �� �÷��̾ �̵��� �� �ִ� ��.
#define RMS 25    // ��ǰ �迭�� ũ��

int level = 1; // ���� ����
int NowLevel = 0;

void GamePlay() { // game.cpp���� main() ������ ����
	myTime::InitTime();
	int PosX = 1,PosY = 1;    // �÷��̾��� ��ǥ
	NowLevel = level;
	char title[40] = {0};

	if(NowLevel == 4) { // ���� �� Ŭ���� �ߴٸ�
		AllCompleted();
		return;
	}

	sprintf_s(title,"title �̷�ã�� - %d�ܰ�",level);
	system(title);
	system("mode con: cols=100 lines=50");    // 50 * 50��ŭ ����� â
	SetMap();    // �ڵ� �� ����

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
    // ���� ����
}

void ProcessInput() {
    // Ű �Է� �Լ�
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