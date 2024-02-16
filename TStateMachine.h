#ifndef TSTATEMACHINE_H
#define TSTATEMACHINE_H
#include "DataTypes.h"
#include "TEventData.h"

namespace StateMachine
{
   class TState;

   /*!
    * \brief Базовый чисто виртуальный класс машины состояний
    * Используется для создания наследников - конкретных машин состояний
    * с конкретными состояниями и дополнительной логикой
    */
   class TStateMachine
   {
      public:

         /*!
          * \brief Конструктор
          * Иннициализирует указатели на состояния в nullptr
          * Иннициализирует переменную о генерации события в false
          * Иннициализирует переменную о запущенности машины в false
          */
         TStateMachine();

         virtual ~TStateMachine() = default;

         /*!
          * \brief Запуск машины
          * Вызывает метод внешнего события для перехода в стартовое состояния
          * Иннициализирует переменную о запущенности машины в true
          */
         void run();

         /*!
          * \brief Обновление машины состояний
          * Необходимо к вызову для передачи данных внешнего события
          * \param pEventData
          */
         void update(TEventData* pEventData = nullptr);


         /*!
          * \brief Геттер поля о запущенности машины
          * \return Булево значение - информация, запущена ли машина
          * true - машина запущено и находится в каком-то состоянии
          * false - машина не запущена и не находится в любом из состояний
          */
         BOOL getIsRunning() const;

      protected:

         TEventData* pEventData; //!< Кэшированный указатель на данные события

         TState* pCurrentState; //!< Укзаатель на текущее состояние
         TState* pNewState; //!< Укзаатель на состояние, в которое требуется перейти
         TState* pStartState; //!< Укзаатель на стартовое состояние. При запуске машины переход в это состояние

         BOOL isEventGenerated; //!< Булево значение - было ли сгенерировано событие. Необходимо для метода stateEngene

         BOOL isRunning; //!< Булево значение - запущена ли машина

         /*!
          * \brief Генерация события, вызов которого иннициирован вне машины состояний
          * Генерирует внутреннее событие
          * Запускает "движок состояний" - stateEngene()
          * \param newState Указатель на состояние, в которое требуется перейти
          * \param pEventData Указатель на данные события
          */
         void externalEvent(TState* newState, TEventData* pEventData = nullptr);

         /*!
          * \brief Генерация события, вызов которого иннициирован машиной состояний или её состояниями
          * Необходим для состояний
          * При помощи генерации такого события состояние сигнализирует о необходимости перехода в другое состояние
          * Вызов продолжает работу "движка состояний"
          * \param newState Указатель на состояние, в которое требуется перейти
          * \param pEventData Указатель на данные события
          */
         void internalEvent(TState* newState, TEventData* pEventData = nullptr);

         /*!
          * \brief Движок для работы состояний
          * Вызывает методы состояний enter(), update(), exit()
          */
         void stateEngine();
   };
} // StateMachine

#endif // TSTATEMACHINE_H