#include "GameTime.h"
#include "ConsoleRenderer.h"
#include "Map.h"
#include "stdio.h"

int PosX = 1, PosY = 1;    // 플레이어의 좌표
bool finish = false;
int timer = 0;

void StartGame() {
    // 게임 초기화 작업
    
    system("mode con: cols=100 lines=50");    // 50 * 50만큼 출력할 창
    ConsoleRenderer::ScreenInit();
    SetMap();
}

bool IsGameRun() {
    // 게임이 계속 실행 중인지 확인
    if(finish) {
        if(GetAsyncKeyState(VK_RETURN)) {
            return false;
        }
    }
    return true; // 조건에 따라 종료
}

// 플레이어의 이동 함수 수정
void PlayerMove(int* PosX,int* PosY,int Key) {
    int newPosX = *PosX;  // 새로운 위치를 임시 변수로 저장
    int newPosY = *PosY;

    // 입력에 따라 새로운 위치 계산
    switch(Key) {
        case VK_UP:
            newPosY -= 1;
            break;
        case VK_DOWN:
            newPosY += 1;
            break;
        case VK_LEFT:
            newPosX -= 1;
            break;
        case VK_RIGHT:
            newPosX += 1;
            break;
    }

    // 새로운 위치가 유효하고 벽이 아닌지 확인
    if(newPosX >= 0 && newPosX < mapSize && newPosY >= 0 && newPosY < mapSize) {
        if(map[newPosY][newPosX] != WALL) {
            // 플레이어 위치를 업데이트
            map[*PosY][*PosX] = SPACE;  // 이전 위치를 빈 공간으로 설정
            *PosX = newPosX;
            *PosY = newPosY;
            map[*PosY][*PosX] = PLAYER;  // 새로운 위치를 플레이어로 설정

            // 목표지점 도달 여부 확인
            
        }
    }
}

// 입력 처리 함수 수정
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
    if(backupMap[PosY][PosX] == FINISH && finish == false) {
        /*ConsoleRenderer::ScreenInit();
        system("mode con: cols=60 lines=10");*/
        timer = GameTime::PlayTime();
        finish = true;
    }
}

void Render() {
    int cameraOffsetX = 0,cameraOffsetY = 0;

    // 화면을 초기화합니다.
    ConsoleRenderer::ScreenClear();

    if(finish) {
        // 출력하고자 하는 문자열을 만듭니다.
        char outputStr[50];
        sprintf_s(outputStr,"소요 시간 %d분 %d초",(timer / 1000) / 60,(timer / 1000) % 60);

        // `ConsoleRenderer::ScreenSetString` 함수를 사용하여 문자열을 지정된 위치에 출력합니다.
        ConsoleRenderer::ScreenSetString(20,3,outputStr,FG_WHITE);
    }
    else {
        // 카메라의 시작 좌표를 조정합니다.
        if(PosX < 25) {
            cameraOffsetX = 0;
        }
        else if(PosX > mapSize - 25) {
            cameraOffsetX = mapSize - 50;
        }
        else {
            cameraOffsetX = PosX - 25;
        }

        if(PosY < 25) {
            cameraOffsetY = 0;
        }
        else if(PosY > mapSize - 25) {
            cameraOffsetY = mapSize - 50;
        }
        else {
            cameraOffsetY = PosY - 25;
        }

        // 화면을 렌더링합니다.
        for(int i = 0; i < 50; i++) {
            for(int j = 0; j < 50; j++) {
                int renderX = j * 2;
                int renderY = i;
                int mapX = cameraOffsetX + j;
                int mapY = cameraOffsetY + i;

                // 현재 좌표의 맵 요소를 확인하여 렌더링합니다.
                if(map[mapY][mapX] == PLAYER) {
                    ConsoleRenderer::ScreenSetString(renderX,renderY,"●",FG_BLUE);
                }
                else if(map[mapY][mapX] == FINISH) {
                    ConsoleRenderer::ScreenSetString(renderX,renderY,"■",FG_RED);
                }
                else {
                    ConsoleRenderer::ScreenSetString(renderX,renderY,pMap[map[mapY][mapX]],FG_WHITE);
                }
            }
        }
    }
    // 화면 버퍼를 플리핑합니다.
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
