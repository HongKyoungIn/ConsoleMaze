#pragma once

/* ▼▼▼▼▼ 함수 선언 ▼▼▼▼▼ */
void StartGame();
void FixedUpdate();
void Update();
void EndGame();
bool IsGameRun();
void GamePlay(); // 게임 시작
int LevelSuccess(); // 레벨 클리어 함수
int totalPlayTime = 0;
void AllCompleted(); // 모든 레벨 클리어 시 함수
/* ▲▲▲▲▲ 함수 선언 ▲▲▲▲▲ */