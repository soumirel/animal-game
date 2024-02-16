#ifndef TGAMEEVENTDATA_H
#define TGAMEEVENTDATA_H

#include <string>

#include "TEventData.h"

namespace GameLogic
{
   /*!
    * \brief Класс данных, передаваемых в событиях машины состояний TGameStateMachine
    * Наследник базового класса данных событий, TEventData
    */
   class TGameEventData final : public StateMachine::TEventData
   {
      public:

         std::string message; //!< Передаваемое в событии сообщение машине состояний
   };
} // GameLogic

#endif //TGAMEEVENTDATA_H
