#ifndef TEVENTDATA_H
#define TEVENTDATA_H

namespace StateMachine {
   /*!
    * \brief Базовый класс данных, передаваемых в событии для машины состояний
    */
   class TEventData
   {
      public:
         /*!
          * \brief Чисто виртуальный конструктор
          */
         virtual ~TEventData() = default;
   };

} // StateMachine

#endif //TEVENTDATA_H
