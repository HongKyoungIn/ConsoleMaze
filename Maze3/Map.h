#pragma once

#include "Windows.h"
#include "time.h"

#define FINISH 4    // ���� ����
#define PLAYER 20    // �÷��̾�
#define WALL 1    // �� - �÷��̾ ������ ���� �� �ϴ� ��.
#define SPACE 0    // �� ���� - �� �÷��̾ �̵��� �� �ִ� ��.
#define RMS 25    // ��ǰ �迭�� ũ��

void SetMap();
int** RollingArray(int MapArr[25][25],int num,int block);

extern const char* pMap[]; // ���� ����Ʈ�� �� ����Ѵ�.
extern int** map;
extern int mapSize;
extern int** backupMap;
extern int level; // ���� ����