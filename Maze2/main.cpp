#include "main.h"
#include "time.h"
#include "game.h"

int main() {
    global::time::InitTime();

    StartGame();

    while(IsGameRun()) {
        global::time::UpdateTime();

        ProcessInput();

        FixeUpdate();

        Update();

        PrintCountsPerSecond();
    }

    EndGame();

    return 0;
}