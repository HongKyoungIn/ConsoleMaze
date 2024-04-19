#include "main.h"
#include "map.h"
#include "time.h"

using namespace std;

#define FINISH 4    // 도착 지점
#define PLAYER 20    // 플레이어
#define WALL 1    // 벽 - 플레이어가 막혀서 가지 못 하는 곳.
#define SPACE 0    // 빈 공간 - 즉 플레이어가 이동할 수 있는 곳.
#define RMS 25    // 부품 배열의 크기

void GamePlay(); // 게임 시작
void SetMap(); // 맵 생성
int** RollingArray(int MapArr[25][25],int num,int block); // 배열 회전
void PrintMap(int PosX,int PosY); // 플레이어 기준으로 맵을 보여주는 함수
void PlayerMove(int* PosX,int* PosY,int Key); // 플레이어 이동하는 함수
int LevelSuccess(); // 레벨 클리어 함수
int totalPlayTime = 0;
void AllCompleted(); // 모든 레벨 클리어 시 함수