cmake_minimum_required(VERSION 3.28)
project(TheAnimalGame)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(TheAnimalGame main.cpp
        TBinaryTreeNode.h
        TStateMachine.cpp
        TStateMachine.h
        TState.cpp
        TState.h
        TEventData.h
        DataTypes.h
        TGameStateMachine.cpp
        TGameStateMachine.h
        TGameStateMachine.h
        TGameEventData.h
        TGame.cpp
        TGame.h
        TGameConfig.h
        TGameStateMachineConfig.h
)

target_link_libraries(TheAnimalGame PRIVATE nlohmann_json::nlohmann_json)