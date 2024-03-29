#ifndef GAME_H
#define GAME_H

#include "TGameConfig.h"
#include "TGameStateMachine.h"

namespace GameLogic
{
   class TGame
   {
      public:
         /*!
          * \brief Конструктор, единственный
          * Устанавливает значение переменной о настройке в false
          * Создает экземпляр TGameStateMachine
          */
         TGame();

         ~TGame();

         /*!
          * \brief Настраивает машину состояний и бинарное дерево прогресса игры
          * Устанавливает значение переменной о настройке в true
          * Вызов метода необходим для дальнейшей работы
          * \param gameConfig Объект конфигурации, необходимый для настройки
          */
         void setUp(const TGameConfig& gameConfig );

         /*!
          * \brief Запускает игровой цикл
          * \return Успешность выполнения запуска
          * Возвращает true при успешном запуске игрового цикла
          * Возвращает false в случае, если не была произведена настройка
          * (вызов метода setUp(TGameConfig&)
          */
         BOOL start() const;

      private:

         TGameConfig gameConfig; //!< Кэшированный объект конфигурации

         TGameStateMachine* pGameStateMachine; //!< Указатель на машину состояний игры

         BOOL isSetUp; //!< Булево значение, обозначающее, настроен ли объект для запуска

         /*!
          * \brief Запуск игрового цикла
          * Тело цикла запрашивает пользовательский ввод для произведения игры
          * Выполняется, пока машина состояний считается запущеной
          * После завершения игрового цикла в случае неодходимости сохраняет игровой процесс
          */
         void startGameLoop() const;

         /*!
          * \brief Настройка машины состояний игры
          * Считывает файл конфигурации машины состояний, десериализует его и передаёт машине состояний игры
          */
         void setUpStateMachine() const;

         /*!
          * \brief Настройка бинарного дерева - прогресса игры
          * Считывает файл конфигурации прогресса игры, десериализиует его и передаёт машине состояний игры
          */
         void setUpBinaryTree();

         /*!
          * \brief Сохранения прогресса игры после завершения игрового цикла
          * Сериализует бинарное дерево и записывает в файл конфигурации бинарного дерева
          */
         void saveGameProgress() const;

         /*!
          * \brief Десериализация бинарного дерева из объекта json
          * Рекурсивно обходит объект json
          * \param j Ссылка на объект json, куда десериализовывается дерево
          * \return Указатель на бинарное дерево (корень) прогресса игры
          */
         TBinaryTreeNode* deserializeTree( nlohmann::json& j );
   };
}

#endif //GAME_H
