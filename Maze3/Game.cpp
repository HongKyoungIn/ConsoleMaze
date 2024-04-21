#include "GameTime.h"
#include "ConsoleRenderer.h"
#include "Map.h"

int PosX = 1, PosY = 1;    // 플레이어의 좌표

void StartGame() {
    // 게임 초기화 작업
    system("mode con: cols=100 lines=50");    // 50 * 50만큼 출력할 창
    ConsoleRenderer::ScreenInit();
    SetMap();
}

bool IsGameRun() {
    // 게임이 계속 실행 중인지 확인
    return true; // 조건에 따라 종료
}

void PlayerMove(int* PosX,int* PosY,int Key) {
    switch(Key) {
        case VK_UP:
            if(map[*PosY - 1][*PosX] != WALL) {
                map[*PosY][*PosX] = SPACE;
                *PosY -= 1;
            }
            break;

        case VK_DOWN:
            if(map[*PosY + 1][*PosX] != WALL) {
                map[*PosY][*PosX] = SPACE;
                *PosY += 1;
            }
            break;

        case VK_LEFT:
            if(map[*PosY][*PosX - 1] != WALL) {
                map[*PosY][*PosX] = SPACE;
                *PosX -= 1;
            }
            break;

        case VK_RIGHT:
            if(map[*PosY][*PosX + 1] != WALL) {
                map[*PosY][*PosX] = SPACE;
                *PosX += 1;
            }
            break;
    }

    map[*PosY][*PosX] = PLAYER; // 이 부분의 주석 처리를 해제합니다.

    if(backupMap[*PosY][*PosX] == FINISH) {
        level += 1;
    }
}

void ProcessInput() {
    if(GetAsyncKeyState(VK_UP) & 0x8000) {
        PlayerMove(&PosX,&PosY,VK_UP);
    }
    else if(GetAsyncKeyState(VK_DOWN) & 0x8000) {
        PlayerMove(&PosX,&PosY,VK_DOWN);
    }
    else if(GetAsyncKeyState(VK_LEFT) & 0x8000) {
        PlayerMove(&PosX,&PosY,VK_LEFT);
    }
    else if(GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        PlayerMove(&PosX,&PosY,VK_RIGHT);
    }
}

void FixedUpdate() {
    // 일정한 간격으로 업데이트 (물리 계산 등)
}

void Update() {
    // 게임 로직 업데이트
}

void Render() {
    int CameraPosX = 0,CameraPosY = 0;  // 카메라 좌표

    // PosX와 PosY 값을 범위 내로 조정합니다.
    if(PosX < 25) {
        PosX = 0;  // 카메라가 왼쪽 세로벽에 부딪혔을 때
    }
    else if(PosX > mapSize - 26) {
        PosX = mapSize - 50;  // 카메라가 오른쪽 세로벽에 부딪혔을 때
    }
    else {
        PosX = PosX - 25;
    }

    if(PosY < 25) {
        PosY = 0;  // 카메라가 위쪽 가로벽에 부딪혔을 때
    }
    else if(PosY > mapSize - 26) {
        PosY = mapSize - 50;  // 카메라가 아래쪽 가로벽에 부딪혔을 때
    }
    else {
        PosY = PosY - 25;
    }

    // 콘솔 화면을 초기화합니다.
    ConsoleRenderer::ScreenClear();

    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 50; j++) {
            CameraPosX = PosX + j;
            CameraPosY = PosY + i;  // 카메라는 현재 좌표 + 출력되는 인덱스다.

            // 플레이어 위치를 출력
            if(map[CameraPosY][CameraPosX] == PLAYER) {
                ConsoleRenderer::ScreenSetString(j * 2,i,"●",FG_BLUE);
            }
            // 피니시 위치를 출력
            else if(map[CameraPosY][CameraPosX] == FINISH) {
                ConsoleRenderer::ScreenSetString(j * 2,i,"  ",FG_RED);
            }
            // 다른 위치를 출력
            else {
                ConsoleRenderer::ScreenSetString(j * 2,i,pMap[map[CameraPosY][CameraPosX]],FG_WHITE);
            }
        }
    }

    // 버퍼를 플리핑하여 변경 사항을 적용합니다.
    ConsoleRenderer::ScreenFlipping();
}

void EndGame() {
    // 게임 종료 작업
}

int main() {
    GameTime::InitTime();
    StartGame();

    while(IsGameRun()) {
        GameTime::UpdateTime();
        ProcessInput();
        FixedUpdate();
        Update();
        Render();
    }

    EndGame();
    return 0;
}
