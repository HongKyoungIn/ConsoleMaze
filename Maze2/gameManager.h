#pragma once

/* ������ �Լ� ���� ������ */
void StartGame();
void FixedUpdate();
void Update();
void EndGame();
bool IsGameRun();
void GamePlay(); // ���� ����
int LevelSuccess(); // ���� Ŭ���� �Լ�
int totalPlayTime = 0;
void AllCompleted(); // ��� ���� Ŭ���� �� �Լ�
/* ������ �Լ� ���� ������ */