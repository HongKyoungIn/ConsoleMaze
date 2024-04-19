#pragma once

/* ▼▼▼▼▼ 헤더 선언 ▼▼▼▼▼ */
#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>
#include <iostream>
#include <malloc.h>    // 맵의 크기를 동기적으로 바꿔주기 위해 동적할당을 사용한다.
#include <time.h>    // 랜덤을 사용하려면 현재 시간을 시드로 넘겨주기 위함!
#include <process.h>
#include <conio.h>
#include <io.h>
#include <direct.h>
#include <setjmp.h>
/* ▲▲▲▲▲ 헤더 선언 ▲▲▲▲▲ */

/* ▼▼▼▼▼ define 선언 ▼▼▼▼▼ */
#define pause system("pause > nul")    // 그냥 내가 많이 쓰는 커맨드를 줄여준 것이다.
#define cls system("cls")
/* ▲▲▲▲▲ define 선언 ▲▲▲▲▲ */

/* ▼▼▼▼▼ 함수 선언 ▼▼▼▼▼ */
void SetColor(int color);
void CursorView(char show);
void gotoxy(int x,int y);
void GamePlay();
/* ▲▲▲▲▲ 함수 선언 ▲▲▲▲▲ */