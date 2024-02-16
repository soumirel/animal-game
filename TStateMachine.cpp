#include "TStateMachine.h"
#include "TState.h"

namespace StateMachine
{
   TStateMachine::TStateMachine()
   {
      isEventGenerated = false;
      pNewState = nullptr;
      pCurrentState = nullptr;
      pStartState = nullptr;
      pEventData = nullptr;
      isRunning = false;
   }

   void TStateMachine::run()
   {
      isRunning = true;
      externalEvent(pStartState, nullptr);
   }

   void TStateMachine::externalEvent(TState* newState, TEventData* pEventData)
   {
      {
         internalEvent(newState, pEventData);

         stateEngine();
      }
   }

   void TStateMachine::internalEvent(TState* newState, TEventData* pEventData)
   {
      this->pEventData = pEventData;
      isEventGenerated = true;
      this->pNewState = newState;
   }

   void TStateMachine::stateEngine()
   {
      while (isEventGenerated)
      {
         isEventGenerated = false;

         if (pNewState != pCurrentState)
         {
            if (pCurrentState != nullptr)
            {
               pCurrentState->exit();
            }

            pCurrentState = pNewState;
            pNewState = nullptr;

            pCurrentState->enter();
         }
         else
         {
            pCurrentState->update();
         }

         pEventData = nullptr;
      }
   }

   void TStateMachine::update(TEventData* pEventData)
   {
      externalEvent(pCurrentState, pEventData);
   }

   BOOL TStateMachine::getIsRunning() const
   {
      return isRunning;
   }
} // StateMachine
