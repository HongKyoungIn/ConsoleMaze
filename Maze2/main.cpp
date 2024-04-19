#include "main.h"
#include "time.h"
#include "gameManager.h"
#include "InputSystem.h"

int main() {
    myTime::InitTime();

    StartGame();

    while(IsGameRun()) {
        myTime::UpdateTime();

        ProcessInput();

        FixedUpdate();

        Update();
    }

    EndGame();

    return 0;
}