#ifndef TGAMESTATEMACHINE_H
#define TGAMESTATEMACHINE_H

#include "TBinaryTreeNode.h"
#include "TStateMachine.h"
#include "TGameStateMachineConfig.h"

namespace GameLogic
{
   using StateMachine::TStateMachine;
   using StateMachine::TState;
   using BinarySearchTree::TBinaryTreeNode;
   using std::string;

   /*!
    * \brief Класс машины состояний игры
    * Наследник базового класса машины состояний
    */
   class TGameStateMachine final : public TStateMachine
   {
      public:

         /*!
          * \brief Конструктор машины состояний
          * Иннициализирует указатели на узлы дерева игры
          * Иннициализирует укзатели - состояния машины
          * Иннициализирует действия состояний
          * Устанавливает переменную о необходимости сохранения прогресса в false
          */
         TGameStateMachine();

         /*!
          * \brief Сеттер объекта конфигурации
          * \param config Объект конфигурации
          */
         void setConfig( TGameStateMachineConfig config );

         /*!
          * \brief Геттер необходимости сохранения прогресса
          * \return Булево значение - Необходимость сохранения прогресса
          * true - необходимо сохранение прогресса
          * false - сохранение прогресса не требуется
          */
         BOOL getIsNeedSaveProgress() const;


         /*!
          * \brief Сеттер дерева игры
          * \param pTree Указатель на бинарное дерево игры (корень)
          */
         void setGameTree( TBinaryTreeNode* pTree );

         /*!
          * \brief Геттер бинарного дерева игры
          * \return Указатель на бинарное дерево игры
          * Нужен для получения изменённого дерева игры после самой игры
          * Возвращаемое значение используется для сериализации- сохранения прогресса
          */
         TBinaryTreeNode* getGameTree() const;

      private:

         TGameStateMachineConfig config; //!< Кэшированный объект конфигурации

         //! Объявление состояний машины
         TState* pWaitingNextRoundState; //!< Указатель на состояние Ожидание след.раунда игры
         TState* pAskingQuestionState; //!< Указатель на состояние Поиск и опрашивания игрока
         TState* pWaitingAnswerState; //!< Указатель на состояние Ожидание ответа на вопрос
         TState* pTryingGuessState; //!< Указатель на состояние Попытка угадывания
         TState* pWaitingGuessingResultState; //!< Указатель на состояние Ожидание результата догадки
         TState* pMemorizingState; //!< Указатель на состояние Запоминание новой информации
         TState* pFinishingGameState; //!< Указатель на состояние Завершение игры

         //! Дерево игры и указатели, используемые в раунде игры
         TBinaryTreeNode* pTree; //!< Указатель на бинарное дерево игры (корень)
         TBinaryTreeNode* pPreviousQuestionNode; //!< Указатель на предыдущий узел раунда
         TBinaryTreeNode* pCurrentQuestionNode; //!< Указатель на текущий узел раунда
         TBinaryTreeNode* pNewFeatureNode; //!< Указатель на новый узел с информацией о свойстве животного
         TBinaryTreeNode* pNewAnimalNode; //!< Указатель на новый узел с информацией о названии животного

         BOOL isNeedSaveProgress; //!< Булево значение - необходимость сохранения игры

         /*!
         * \brief Иннициализация действия состояний
         * Устанавливает лямбда-функции для действий состояний
         */
         void initializeStatesActions();

         /*!
          * \brief Иннициализация действий состояния Стартовое состояние
          */
         void initStartStateActions();

          /*!
          * \brief Иннициализация действий состояния Ожидание след.раунда
          */
         void initWaitingNextRoundStateActions();

         /*!
          * \brief Иннициализация действий состояния Опрашивание игрока
          */
         void initAskingQuestionStateActions();

         /*!
         * \brief Иннициализация действий состояния Попытка угадать
         */
         void initTryingGuessStateActions();

         /*!
         * \brief Иннициализация действий состояния Обучение
         */
         void initMemorizingStateActions();

         /*!
         * \brief Иннициализация действий состояния Окончание игры
         */
         void initFinishingGameStateActions();

         /*!
          * \brief Проверка ответа на положительный окрас
          * \param answer Строковое значение - проверяемый ответ
          * \return Булево значение, обозначающее окрас ответа
          * true - ответ положительный
          * false - ответ отрицательный
          */
         BOOL checkIsPositiveAnswer( const std::string &answer );
   };
}// GameLogic

#endif // TGAMESTATEMACHINE_H
