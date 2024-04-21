#include "GameTime.h"
#include "ConsoleRenderer.h"
#include "Map.h"
#include "stdio.h"

int PosX = 1, PosY = 1;    // �÷��̾��� ��ǥ
bool finish = false;
int timer = 0;

void StartGame() {
    // ���� �ʱ�ȭ �۾�
    
    system("mode con: cols=100 lines=50");    // 50 * 50��ŭ ����� â
    ConsoleRenderer::ScreenInit();
    SetMap();
}

bool IsGameRun() {
    // ������ ��� ���� ������ Ȯ��
    if(finish) {
        if(GetAsyncKeyState(VK_RETURN)) {
            return false;
        }
    }
    return true; // ���ǿ� ���� ����
}

// �÷��̾��� �̵� �Լ� ����
void PlayerMove(int* PosX,int* PosY,int Key) {
    int newPosX = *PosX;  // ���ο� ��ġ�� �ӽ� ������ ����
    int newPosY = *PosY;

    // �Է¿� ���� ���ο� ��ġ ���
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

    // ���ο� ��ġ�� ��ȿ�ϰ� ���� �ƴ��� Ȯ��
    if(newPosX >= 0 && newPosX < mapSize && newPosY >= 0 && newPosY < mapSize) {
        if(map[newPosY][newPosX] != WALL) {
            // �÷��̾� ��ġ�� ������Ʈ
            map[*PosY][*PosX] = SPACE;  // ���� ��ġ�� �� �������� ����
            *PosX = newPosX;
            *PosY = newPosY;
            map[*PosY][*PosX] = PLAYER;  // ���ο� ��ġ�� �÷��̾�� ����

            // ��ǥ���� ���� ���� Ȯ��
            
        }
    }
}

// �Է� ó�� �Լ� ����
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
    if(backupMap[PosY][PosX] == FINISH && finish == false) {
        /*ConsoleRenderer::ScreenInit();
        system("mode con: cols=60 lines=10");*/
        timer = GameTime::PlayTime();
        finish = true;
    }
}

void Render() {
    int cameraOffsetX = 0,cameraOffsetY = 0;

    // ȭ���� �ʱ�ȭ�մϴ�.
    ConsoleRenderer::ScreenClear();

    if(finish) {
        // ����ϰ��� �ϴ� ���ڿ��� ����ϴ�.
        char outputStr[50];
        sprintf_s(outputStr,"�ҿ� �ð� %d�� %d��",(timer / 1000) / 60,(timer / 1000) % 60);

        // `ConsoleRenderer::ScreenSetString` �Լ��� ����Ͽ� ���ڿ��� ������ ��ġ�� ����մϴ�.
        ConsoleRenderer::ScreenSetString(20,3,outputStr,FG_WHITE);
    }
    else {
        // ī�޶��� ���� ��ǥ�� �����մϴ�.
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

        // ȭ���� �������մϴ�.
        for(int i = 0; i < 50; i++) {
            for(int j = 0; j < 50; j++) {
                int renderX = j * 2;
                int renderY = i;
                int mapX = cameraOffsetX + j;
                int mapY = cameraOffsetY + i;

                // ���� ��ǥ�� �� ��Ҹ� Ȯ���Ͽ� �������մϴ�.
                if(map[mapY][mapX] == PLAYER) {
                    ConsoleRenderer::ScreenSetString(renderX,renderY,"��",FG_BLUE);
                }
                else if(map[mapY][mapX] == FINISH) {
                    ConsoleRenderer::ScreenSetString(renderX,renderY,"��",FG_RED);
                }
                else {
                    ConsoleRenderer::ScreenSetString(renderX,renderY,pMap[map[mapY][mapX]],FG_WHITE);
                }
            }
        }
    }
    // ȭ�� ���۸� �ø����մϴ�.
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
