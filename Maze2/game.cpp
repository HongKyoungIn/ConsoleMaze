#include "main.h"
#include "map.h"
#include "time.h"

using namespace std;

#define FINISH 4    // ���� ����
#define PLAYER 20    // �÷��̾�
#define WALL 1    // �� - �÷��̾ ������ ���� �� �ϴ� ��.
#define SPACE 0    // �� ���� - �� �÷��̾ �̵��� �� �ִ� ��.
#define RMS 25    // ��ǰ �迭�� ũ��

void GamePlay(); // ���� ����
void SetMap(); // �� ����
int** RollingArray(int MapArr[25][25],int num,int block); // �迭 ȸ��
void PrintMap(int PosX,int PosY); // �÷��̾� �������� ���� �����ִ� �Լ�
void PlayerMove(int* PosX,int* PosY,int Key); // �÷��̾� �̵��ϴ� �Լ�
int LevelSuccess(); // ���� Ŭ���� �Լ�
int totalPlayTime = 0;
void AllCompleted(); // ��� ���� Ŭ���� �� �Լ�