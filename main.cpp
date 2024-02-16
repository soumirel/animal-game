#include <fstream>
#include <iostream>
#include <nlohmann/json_fwd.hpp>

#include "TGame.h"

int main(int argc, char* argv[])
{
    system("chcp 65001");

    if (argc != 3)
    {
        std::cout << "Приложению требуется 2 аргумента:\nИмя файла конфгурации машины состояний игры (реплики)\nИмя файла конфигурации игрового дерева (прогресса)";
        return -1;
    }

    GameLogic::TGameConfig gameConfig
    {
        argv[1],
        argv[2]
    };

    auto* pGame = new GameLogic::TGame();

    pGame->setUp(gameConfig);
    pGame->start();

    return 0;
}
