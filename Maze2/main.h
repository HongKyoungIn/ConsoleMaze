#pragma once

/* ������ ��� ���� ������ */
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <time.h>    // ������ ����Ϸ��� ���� �ð��� �õ�� �Ѱ��ֱ� ����!
/* ������ ��� ���� ������ */

/* ������ define ���� ������ */
#define pause system("pause > nul")
#define cls system("cls")
/* ������ define ���� ������ */

/* ������ �Լ� ���� ������ */
void SetColor(int color);
void CursorView(char show);
void gotoxy(int x,int y);
void StartGame();
bool IsGameRun();
void ProcessInput();
void FixeUpdate();
void Update();
void EndGame();
/* ������ �Լ� ���� ������ */