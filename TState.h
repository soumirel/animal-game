#ifndef TSTATE_H
#define TSTATE_H
#include <functional>
#include <string>

namespace StateMachine
{
   class TStateMachine;

   /*!
    * \brief Класс состояния машины состояний
    * Используется классом TStateMachine и его наследниками
    * Содержит объекты std::function<void()> - действия состояния
    */
   class TState
   {
      public:

         using Action = std::function<void()>;

         /*!
          * \brief Конструктор
          * \param stateMachine Указатель на машину состояний, которая использует создаваемое состояние
          * \param name Строковое значение - имя состояния. Необходимо для отладки
          */
         TState(TStateMachine* stateMachine, const std::string& name);

         ~TState();

         Action enterAction; //!< Объект std::function<void()> - действие состояния при переходе в него
         Action updateAction; //!< Объект std::function<void()> - действие состояния при его обновлении
         Action exitAction; //!< Объект std::function<void()> - действие состояния при выходе из него

         /*!
          * \brief Вызов действия при переходе в состояние
          */
         void enter() const;

         /*!
          * \brief Вызов действия при обновлении состояния
          */
         void update() const;

         /*!
          * \brief Вызов действия при выходе из состояния
          */
         void exit() const;

      private:

         std::string name; //!< Строкове значение имени состояния, необходимо для отладки

         TStateMachine* stateMachine; //!< Указатель на машину состояний - владельца состояния
   };
}// StateMachine

#endif //TSTATE_H