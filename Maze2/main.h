#pragma once

/* ������ ��� ���� ������ */
#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>
#include <iostream>
#include <malloc.h>    // ���� ũ�⸦ ���������� �ٲ��ֱ� ���� �����Ҵ��� ����Ѵ�.
#include <time.h>    // ������ ����Ϸ��� ���� �ð��� �õ�� �Ѱ��ֱ� ����!
#include <process.h>
#include <conio.h>
#include <io.h>
#include <direct.h>
#include <setjmp.h>
/* ������ ��� ���� ������ */

/* ������ define ���� ������ */
#define pause system("pause > nul")    // �׳� ���� ���� ���� Ŀ�ǵ带 �ٿ��� ���̴�.
#define cls system("cls")
/* ������ define ���� ������ */

/* ������ �Լ� ���� ������ */
void SetColor(int color);
void CursorView(char show);
void gotoxy(int x,int y);
void GamePlay();
/* ������ �Լ� ���� ������ */