#pragma once

/* ▼▼▼▼▼ 헤더 선언 ▼▼▼▼▼ */
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <time.h>    // 랜덤을 사용하려면 현재 시간을 시드로 넘겨주기 위함!
/* ▲▲▲▲▲ 헤더 선언 ▲▲▲▲▲ */

/* ▼▼▼▼▼ define 선언 ▼▼▼▼▼ */
#define pause system("pause > nul")
#define cls system("cls")
/* ▲▲▲▲▲ define 선언 ▲▲▲▲▲ */

/* ▼▼▼▼▼ 함수 선언 ▼▼▼▼▼ */
void SetColor(int color);
void CursorView(char show);
void gotoxy(int x,int y);
void StartGame();
bool IsGameRun();
void ProcessInput();
void FixeUpdate();
void Update();
void EndGame();
/* ▲▲▲▲▲ 함수 선언 ▲▲▲▲▲ */