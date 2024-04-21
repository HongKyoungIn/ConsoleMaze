#include "main.h"
#include "time.h"
#include "map.h"
#include "ConsoleRenderer.h"

using namespace std;

#define FINISH 4    // ���� ����
#define PLAYER 20    // �÷��̾�
#define WALL 1    // �� - �÷��̾ ������ ���� �� �ϴ� ��.
#define SPACE 0    // �� ���� - �� �÷��̾ �̵��� �� �ִ� ��.
#define RMS 25    // ��ǰ �迭�� ũ��

void GamePlay(); // ���� ����
void SetMap(); // �� ����
int** RollingArray(int MapArr[25][25],int num,int block); // �迭 ȸ��
void PrintMap(int PosX,int PosY); // �÷��̾� �������� ���� �����ִ� �Լ�(ī�޶�)
void PlayerMove(int* PosX,int* PosY,int Key); // �÷��̾� �̵��ϴ� �Լ�
void LevelSuccess(); // ���� Ŭ���� �Լ�
int totalPlayTime = 0;
void AllCompleted(); // ��� ���� Ŭ���� �� �Լ�
void ProcessInput();
void Render();

const char* pMap[] = {"  ", "��"}; // ���� ����Ʈ�� �� ����Ѵ�.
int** map;
int mapSize;
int** backupMap;
int level = 1; // ���� ����
int startTime = 0; // �÷��� ���� �ð� ���
int timer = 0; // �÷��� ���� �ð� ���
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

	sprintf_s(title,"title �̷�ã�� - %d�ܰ�",level);
	system(title);
	system("mode con: cols=100 lines=50");    // 50 * 50��ŭ ����� â
}

void SetMap() {
	mapSize = level * 100;

	// ���� 2���� �迭�� �����Ҵ�
	map = new int* [mapSize];

	// ������ �ε����� �����ϰ��� �ϴ� �迭�� ũ�⸸ŭ�� ����Ű�� ��
	for(int i = 0; i < mapSize; i++) {
		map[i] = new int[mapSize];
	}

	// �����Ҵ� �� ���� ���� �� �������� �ʱ�ȭ ������
	for(int i = 0; i < mapSize; i++) {
		for(int j = 0; j < mapSize; j++) {
			map[i][j] = SPACE;
		}
	}

	int num = mapSize / RMS;

	for(int i = 0; i < num; i++) {
		for(int j = 0; j < num; j++) {
			srand((unsigned)time(NULL));
			// int **arr = RollingArray(RandomMap[0~2 �� �ϳ�], 0~3 �� �ϳ�,  (ó�� ���ۺκ� �Ǵ� ������ ��ġ�ΰ�?) ? �´� = 0 : �ƴϸ� = 0~5 ���� �� �ϳ�);
			int** arr = RollingArray(RandomMap[rand() % 3],rand() % 4,((i == 0 && j == 0) || (i == num - 1 && j == num - 1)) ? 0 : (rand() % 6));

			// ���õ� ����(arr)�� map �迭�� �ش� ��ġ�� �����մϴ�.
			for(int AH = RMS * i,height = 0; height < RMS; height++,AH++) {
				for(int AW = RMS * j,width = 0; width < RMS; width++,AW++) {
					map[AH][AW] = arr[height][width];
				}
			}
		}
	}

	// �� �� �κ� ������ ä���
	for(int i = 0; i < mapSize; i++) {
		map[i][0] = WALL;
		map[0][i] = WALL;
		map[i][mapSize - 1] = WALL;
		map[mapSize - 1][i] = WALL;
	}

	map[mapSize - 2][mapSize - 2] = FINISH; // ���� ����
	map[1][1] = PLAYER; // �÷��̾� ���� ��ġ


	// ������ ���� �̺�Ʈ�� ó���� �� ����ϱ� ���� backupMap
	// �̷θ� Ż�� ���� �� �̺�Ʈ�� ó���ϱ� ���� ���
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

// 25 * 25 �迭�� ȸ����Ű�� �Լ�
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
	// MapArr�� arr�� �״�� �����մϴ�. �̴� ȸ������ �ʰ� ���� �迭�� ��ȯ�ؾ� �� ��츦 ó���մϴ�.
	if(num == 0) {
		for(int i = 0; i < RMS; i++) {
			for(int j = 0; j < RMS; j++) {
				arr[i][j] = MapArr[i][j];
			}
		}
	}

	return arr;
}

// ī�޶� ������� �� �Լ�
void PrintMap(int PosX, int PosY) {
	int CameraPosX = 0,CameraPosY = 0;    //ī�޶� ��ǥ

	//�����Ͱ� �ƴϱ� ������ Pos���� �ٲ㵵 ������.
	if(PosX < 25) {
		PosX = 0;   //ī�޶� ���� ���κ��� �ε����� ��
	}
	else if(PosX > mapSize - 26) {
		PosX = mapSize - 50;    //ī�޶� ������ ���κ��� �ε����� ��
	}
	else {
		PosX = PosX - 25;
	}

	if(PosY < 25) {
		PosY = 0;    //ī�޶� ���� ���κ��� �ε����� ��
	}
	else if(PosY > mapSize - 26) {
		PosY = mapSize - 50;    //ī�޶� �Ʒ��� ���κ��� �ε����� ��
	}
	else {
		PosY = PosY - 25;
	}

	for(int i = 0; i < 50; i++) {
		for(int j = 0; j < 50; j++) {
			CameraPosX = PosX + j;
			CameraPosY = PosY + i;  // ī�޶�� ���� ��ǥ + ��µǴ� �ε�����.
			gotoxy(j * 2,i);  // gotoxy�� �ֿܼ��� �Է��� ���̴� �״�� ���ָ� ��.
			if(map[CameraPosY][CameraPosX] == PLAYER) {  // �÷��̾ ���
				SetColor(10);
				ConsoleRenderer::ScreenSetString(CameraPosX,CameraPosY,"��",FG_BLUE);
				SetColor(15);
			}
			else if(map[CameraPosY][CameraPosX] == FINISH) {  // �ǴϽ� ��Ҹ� ���
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

// �÷��̾ �̵��� �� ����ϴ� �Լ�
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
	sprintf_s(title,"title %d�ܰ� ����!",level - 1);
	system(title);
	system("mode con: cols=60 lines=10");
	gotoxy(20,3); printf("�ҿ� �ð� % d�� % d��",(timer / 1000) / 60,(timer / 1000) % 60);

	for(int i = 0; i < mapSize; i++) {
		delete[] map[i];
		delete[] backupMap[i];
	}
	delete[] map;
	delete[] backupMap;
	
}

void AllCompleted() {
	cls;
	gotoxy(15,3); printf("�� �÷��� �ð� %d�� %d��",(totalPlayTime / 1000) / 60,(totalPlayTime / 1000) % 60);
	gotoxy(15,6); cout << "�����մϴ�!" << endl;
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