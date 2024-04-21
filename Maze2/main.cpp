#include "main.h"
#include "time.h"
#include "map.h"
#include "ConsoleRenderer.h"

using namespace std;

#define FINISH 4    // 도착 지점
#define PLAYER 20    // 플레이어
#define WALL 1    // 벽 - 플레이어가 막혀서 가지 못 하는 곳.
#define SPACE 0    // 빈 공간 - 즉 플레이어가 이동할 수 있는 곳.
#define RMS 25    // 부품 배열의 크기

void GamePlay(); // 게임 시작
void SetMap(); // 맵 생성
int** RollingArray(int MapArr[25][25],int num,int block); // 배열 회전
void PrintMap(int PosX,int PosY); // 플레이어 기준으로 맵을 보여주는 함수(카메라)
void PlayerMove(int* PosX,int* PosY,int Key); // 플레이어 이동하는 함수
void LevelSuccess(); // 레벨 클리어 함수
int totalPlayTime = 0;
void AllCompleted(); // 모든 레벨 클리어 시 함수
void ProcessInput();
void Render();

const char* pMap[] = {"  ", "■"}; // 맵을 프린트할 때 사용한다.
int** map;
int mapSize;
int** backupMap;
int level = 1; // 현재 레벨
int startTime = 0; // 플레이 시작 시간 기록
int timer = 0; // 플레이 끝낸 시간 기록
int Record[10] = {0};
int NowLevel = 0;
int PosX = 1,PosY = 1;

void Render() {
	PrintMap(PosX, PosY);
	ConsoleRenderer::ScreenFlipping();
	ConsoleRenderer::ScreenClear();
}

void ProcessInput() {
	if(1) {
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
	}
}

void GamePlay() {
	char title[40] = {0};

	sprintf_s(title,"title 미로찾기 - %d단계",level);
	system(title);
	system("mode con: cols=100 lines=50");    // 50 * 50만큼 출력할 창
}

void SetMap() {
	mapSize = level * 100;

	// 맵을 2차원 배열로 동적할당
	map = new int* [mapSize];

	// 각각의 인덱스에 선언하고자 하는 배열의 크기만큼을 가르키게 함
	for(int i = 0; i < mapSize; i++) {
		map[i] = new int[mapSize];
	}

	// 동적할당 된 맵을 전부 빈 공간으로 초기화 시켜줌
	for(int i = 0; i < mapSize; i++) {
		for(int j = 0; j < mapSize; j++) {
			map[i][j] = SPACE;
		}
	}

	int num = mapSize / RMS;

	for(int i = 0; i < num; i++) {
		for(int j = 0; j < num; j++) {
			srand((unsigned)time(NULL));
			// int **arr = RollingArray(RandomMap[0~2 중 하나], 0~3 중 하나,  (처음 시작부분 또는 마지막 위치인가?) ? 맞다 = 0 : 아니면 = 0~5 숫자 중 하나);
			int** arr = RollingArray(RandomMap[rand() % 3],rand() % 4,((i == 0 && j == 0) || (i == num - 1 && j == num - 1)) ? 0 : (rand() % 6));

			// 선택된 패턴(arr)을 map 배열의 해당 위치에 복사합니다.
			for(int AH = RMS * i,height = 0; height < RMS; height++,AH++) {
				for(int AW = RMS * j,width = 0; width < RMS; width++,AW++) {
					map[AH][AW] = arr[height][width];
				}
			}
		}
	}

	// 맨 끝 부분 벽으로 채우기
	for(int i = 0; i < mapSize; i++) {
		map[i][0] = WALL;
		map[0][i] = WALL;
		map[i][mapSize - 1] = WALL;
		map[mapSize - 1][i] = WALL;
	}

	map[mapSize - 2][mapSize - 2] = FINISH; // 도착 지점
	map[1][1] = PLAYER; // 플레이어 시작 위치


	// 아이템 같은 이벤트를 처리할 때 사용하기 위한 backupMap
	// 미로를 탈출 했을 때 이벤트로 처리하기 위해 사용
	backupMap = new int* [mapSize];

	for(int i = 0; i < mapSize; i++) {
		backupMap[i] = new int[mapSize];
	}

	for(int i = 0; i < mapSize; i++) {
		for(int j = 0; j < mapSize; j++) {
			backupMap[i][j] = map[i][j];
		}
	}
}

// 25 * 25 배열을 회전시키는 함수
int** RollingArray(int MapArr[25][25],int num,int block) {

	int** arr;
	arr = new int* [RMS];
	for(int i = 0; i < RMS; i++) {
		arr[i] = new int[RMS];
	}


	for(int i = 0; i < num; i++) {
		for(int j = 0; j < RMS; j++) {
			for(int k1 = RMS - 1,k2 = 0; k2 < RMS; k1--,k2++) {
				arr[j][k2] = MapArr[k1][j];
			}
		}
	}
	// MapArr를 arr에 그대로 복사합니다. 이는 회전하지 않고 원본 배열을 반환해야 할 경우를 처리합니다.
	if(num == 0) {
		for(int i = 0; i < RMS; i++) {
			for(int j = 0; j < RMS; j++) {
				arr[i][j] = MapArr[i][j];
			}
		}
	}

	return arr;
}

// 카메라가 출력해줄 맵 함수
void PrintMap(int PosX, int PosY) {
	int CameraPosX = 0,CameraPosY = 0;    //카메라 좌표

	//포인터가 아니기 때문에 Pos값을 바꿔도 괜찮다.
	if(PosX < 25) {
		PosX = 0;   //카메라가 왼쪽 세로벽에 부딪혔을 때
	}
	else if(PosX > mapSize - 26) {
		PosX = mapSize - 50;    //카메라가 오른쪽 세로벽에 부딪혔을 때
	}
	else {
		PosX = PosX - 25;
	}

	if(PosY < 25) {
		PosY = 0;    //카메라가 위쪽 가로벽에 부딪혔을 때
	}
	else if(PosY > mapSize - 26) {
		PosY = mapSize - 50;    //카메라가 아래쪽 가로벽에 부딪혔을 때
	}
	else {
		PosY = PosY - 25;
	}

	for(int i = 0; i < 50; i++) {
		for(int j = 0; j < 50; j++) {
			CameraPosX = PosX + j;
			CameraPosY = PosY + i;  // 카메라는 현재 좌표 + 출력되는 인덱스다.
			gotoxy(j * 2,i);  // gotoxy는 콘솔에서 입력할 것이니 그대로 해주면 됨.
			if(map[CameraPosY][CameraPosX] == PLAYER) {  // 플레이어를 출력
				SetColor(10);
				ConsoleRenderer::ScreenSetString(CameraPosX,CameraPosY,"●",FG_BLUE);
				SetColor(15);
			}
			else if(map[CameraPosY][CameraPosX] == FINISH) {  // 피니시 장소를 출력
				SetColor(204);
				ConsoleRenderer::ScreenSetString(CameraPosX,CameraPosY,"  ",FG_RED);
				SetColor(15);
			}
			else {
				ConsoleRenderer::ScreenSetString(CameraPosX,CameraPosY,pMap[map[CameraPosY][CameraPosX]],FG_WHITE);
			}
		}
	}
	return;
}

// 플레이어가 이동할 때 사용하는 함수
void PlayerMove(int* PosX,int* PosY,int Key) {
	switch(Key) {
		case VK_UP:
			if(map[*PosY - 1][*PosX] != WALL) {
				map[*PosY][*PosX] = SPACE; *PosY -= 1;
			}
			break;

		case VK_DOWN:
			if(map[*PosY + 1][*PosX] != WALL) {
				map[*PosY][*PosX] = SPACE; *PosY += 1;
			}
			break;

		case VK_LEFT:
			if(map[*PosY][*PosX - 1] != WALL) {
				map[*PosY][*PosX] = SPACE; *PosX -= 1;
			}
			break;

		case VK_RIGHT:
			if(map[*PosY][*PosX + 1] != WALL) {
				map[*PosY][*PosX] = SPACE;
				*PosX += 1;
			}
			break;
	}

	map[*PosY][*PosX] = PLAYER;

	if(backupMap[*PosY][*PosX] == FINISH) {
		level += 1;
	}

	return;
}

void LevelSuccess(void) {
	timer = myTime::PlayTime();
	totalPlayTime += myTime::PlayTime();
	char title[40] = {0};
	sprintf_s(title,"title %d단계 성공!",level - 1);
	system(title);
	system("mode con: cols=60 lines=10");
	gotoxy(20,3); printf("소요 시간 % d분 % d초",(timer / 1000) / 60,(timer / 1000) % 60);

	for(int i = 0; i < mapSize; i++) {
		delete[] map[i];
		delete[] backupMap[i];
	}
	delete[] map;
	delete[] backupMap;
	
}

void AllCompleted() {
	cls;
	gotoxy(15,3); printf("총 플레이 시간 %d분 %d초",(totalPlayTime / 1000) / 60,(totalPlayTime / 1000) % 60);
	gotoxy(15,6); cout << "축하합니다!" << endl;
}

void StartGame() {
	ConsoleRenderer::ScreenInit();
	GamePlay();
	SetMap();
	Render();
}

void Update() {

}

bool IsGameRun() {
	return true;
}

void EndGame() {
	AllCompleted();
}

int main() {
    myTime::InitTime();

    StartGame();

    while(IsGameRun()) {
        myTime::UpdateTime();

        ProcessInput();

        // FixeUpdate();

        Update();

		Render();
    }

    EndGame();

    return 0;
}