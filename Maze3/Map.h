#pragma once

#include "Windows.h"
#include "time.h"

#define FINISH 4    // 도착 지점
#define PLAYER 20    // 플레이어
#define WALL 1    // 벽 - 플레이어가 막혀서 가지 못 하는 곳.
#define SPACE 0    // 빈 공간 - 즉 플레이어가 이동할 수 있는 곳.
#define RMS 25    // 부품 배열의 크기

void SetMap();
int** RollingArray(int MapArr[25][25],int num,int block);

extern const char* pMap[]; // 맵을 프린트할 때 사용한다.
extern int** map;
extern int mapSize;
extern int** backupMap;
extern int level; // 현재 레벨