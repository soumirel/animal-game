#include "TState.h"

namespace StateMachine
{
   TState::TState(TStateMachine* stateMachine, const std::string& name)
   {
      this->stateMachine = stateMachine;
      this->name = name;

      enterAction = nullptr;
      updateAction = nullptr;
      exitAction = nullptr;
   }

   TState::~TState()
   = default;

   void TState::enter() const
   {
      if (enterAction != nullptr)
      {
         enterAction();
      }
   }

   void TState::update() const
   {
      if (updateAction != nullptr)
      {
         updateAction();
      }
   }

   void TState::exit() const
   {
      {
         if (exitAction != nullptr)
         {
            exitAction();
         }
      }
   }
} // StateMachine