#include "GameTime.h"
#include "ConsoleRenderer.h"
#include "Map.h"

int PosX = 1, PosY = 1;    // �÷��̾��� ��ǥ

void StartGame() {
    // ���� �ʱ�ȭ �۾�
    system("mode con: cols=100 lines=50");    // 50 * 50��ŭ ����� â
    ConsoleRenderer::ScreenInit();
    SetMap();
}

bool IsGameRun() {
    // ������ ��� ���� ������ Ȯ��
    return true; // ���ǿ� ���� ����
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

    map[*PosY][*PosX] = PLAYER; // �� �κ��� �ּ� ó���� �����մϴ�.

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
    // ������ �������� ������Ʈ (���� ��� ��)
}

void Update() {
    // ���� ���� ������Ʈ
}

void Render() {
    int CameraPosX = 0,CameraPosY = 0;  // ī�޶� ��ǥ

    // PosX�� PosY ���� ���� ���� �����մϴ�.
    if(PosX < 25) {
        PosX = 0;  // ī�޶� ���� ���κ��� �ε����� ��
    }
    else if(PosX > mapSize - 26) {
        PosX = mapSize - 50;  // ī�޶� ������ ���κ��� �ε����� ��
    }
    else {
        PosX = PosX - 25;
    }

    if(PosY < 25) {
        PosY = 0;  // ī�޶� ���� ���κ��� �ε����� ��
    }
    else if(PosY > mapSize - 26) {
        PosY = mapSize - 50;  // ī�޶� �Ʒ��� ���κ��� �ε����� ��
    }
    else {
        PosY = PosY - 25;
    }

    // �ܼ� ȭ���� �ʱ�ȭ�մϴ�.
    ConsoleRenderer::ScreenClear();

    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 50; j++) {
            CameraPosX = PosX + j;
            CameraPosY = PosY + i;  // ī�޶�� ���� ��ǥ + ��µǴ� �ε�����.

            // �÷��̾� ��ġ�� ���
            if(map[CameraPosY][CameraPosX] == PLAYER) {
                ConsoleRenderer::ScreenSetString(j * 2,i,"��",FG_BLUE);
            }
            // �ǴϽ� ��ġ�� ���
            else if(map[CameraPosY][CameraPosX] == FINISH) {
                ConsoleRenderer::ScreenSetString(j * 2,i,"  ",FG_RED);
            }
            // �ٸ� ��ġ�� ���
            else {
                ConsoleRenderer::ScreenSetString(j * 2,i,pMap[map[CameraPosY][CameraPosX]],FG_WHITE);
            }
        }
    }

    // ���۸� �ø����Ͽ� ���� ������ �����մϴ�.
    ConsoleRenderer::ScreenFlipping();
}

void EndGame() {
    // ���� ���� �۾�
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
