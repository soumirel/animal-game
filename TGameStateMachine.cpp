#include <iostream>
#include <utility>

#include "TGameStateMachine.h"
#include "TGameEventData.h"
#include "TState.h"

namespace GameLogic
{
   using namespace std;

   TGameStateMachine::TGameStateMachine()
   {
      pCurrentQuestionNode = nullptr;
      pPreviousQuestionNode = nullptr;
      pNewFeatureNode = nullptr;
      pNewAnimalNode = nullptr;

      isNeedSaveProgress = FALSE;

      pStartState = new TState(this, "StartState");
      pWaitingNextRoundState = new TState(this, "WaitingNextRound");
      pAskingQuestionState = new TState(this, "AskingQuestion");
      pWaitingAnswerState = new TState(this, "WaitingAnswer");
      pTryingGuessState = new TState(this, "TryingGuess");
      pWaitingGuessingResultState = new TState(this, "WaitingGuessingResult");
      pMemorizingState = new TState(this, "Memorizing");
      pFinishingGameState = new TState(this, "FinishingGame");

      initializeStatesActions();
   }

   void TGameStateMachine::setConfig( TGameStateMachineConfig config )
   {
      this->config = std::move( config );
   }

   BOOL TGameStateMachine::getIsNeedSaveProgress() const
   {
      return isNeedSaveProgress;
   }

   void TGameStateMachine::setGameTree( TBinaryTreeNode *pTree )
   {
      this->pTree = pTree;
   }

   TBinaryTreeNode* TGameStateMachine::getGameTree() const
   {
      return pTree;
   }

   void TGameStateMachine::initStartStateActions()
   {
      //! Иннициализация входного действия
      pStartState->enterAction = [&]
      {
         cout << config.greetingPhrase << "\n";
         internalEvent(pWaitingNextRoundState, nullptr);
      };
   }

   void TGameStateMachine::initWaitingNextRoundStateActions()
   {
      //! Иннициализация входного действия
      pWaitingNextRoundState->enterAction = [&]
      {
         std::cout << config.playInvitationPhrase << "\n";
      };

      //! Иннициализация действия обновления
      pWaitingNextRoundState->updateAction = [&]
      {
         if ( auto* pGameEventData = dynamic_cast<TGameEventData*>( pEventData ) )
         {
            if ( checkIsPositiveAnswer(pGameEventData->message) )
            {
               internalEvent( pAskingQuestionState, nullptr ) ;
            }
            else
            {
               internalEvent(pFinishingGameState, nullptr);
            }
         }
      };
   }

   void TGameStateMachine::initAskingQuestionStateActions()
   {
      //! Иннициализация входного действия
      pAskingQuestionState->enterAction = [&]
      {
         pCurrentQuestionNode = pTree;
         if ( pCurrentQuestionNode->isLeaf )
         {
            internalEvent( pTryingGuessState, nullptr );
         }
         else
         {
            pCurrentQuestionNode = pTree;
            cout << config.guessPrefix << pCurrentQuestionNode->content << config.guessPostfix << "\n";
         }
      };

      //! Иннициализация действия обновления
      pAskingQuestionState->updateAction = [&]
      {
         if ( auto* pGameEventData = dynamic_cast<TGameEventData*>( pEventData ) )
         {
            pPreviousQuestionNode = pCurrentQuestionNode;
            if ( checkIsPositiveAnswer(pGameEventData->message) )
            {
               pCurrentQuestionNode = pCurrentQuestionNode->pRightChild;
            }
            else
            {
               pCurrentQuestionNode = pCurrentQuestionNode->pLeftChild;
            }
            if ( pCurrentQuestionNode->isLeaf )
            {
               internalEvent( pTryingGuessState, nullptr );
            }
            else
            {
               cout << config.guessPrefix << pCurrentQuestionNode->content << config.guessPostfix << '\n';
            }
         }
      };
   }

   void TGameStateMachine::initTryingGuessStateActions()
   {
      //! Иннициализация входного действия
      pTryingGuessState->enterAction = [&]
      {
         cout << config.guessPrefix << pCurrentQuestionNode->content << config.guessPostfix << "\n";
      };

      //! Иннициализация действия обновления
      pTryingGuessState->updateAction = [&]
      {
         if ( auto* pGameEventData = dynamic_cast<TGameEventData*>( pEventData ) )
         {
            if ( checkIsPositiveAnswer(pGameEventData->message) )
            {
               cout << config.gameVictoryPhrase << "\n";
               internalEvent( pWaitingNextRoundState, nullptr );
            }
            else
            {
               cout << config.userVictoryPhrase << "\n";
               internalEvent( pMemorizingState );
            }
         }
      };
   }

   void TGameStateMachine::initMemorizingStateActions()
   {
      //! Иннициализация входного действия
      pMemorizingState->enterAction = [&]
      {
         cout << config.trainingDataRequestPhrase << "\n";
         cout << config.guessedAnimalRequestPhrase << "\n";
      };

      //! Иннициализация действия обновления
      pMemorizingState->updateAction = [&]
      {
         if ( auto* pGameEventData = dynamic_cast<TGameEventData*>( pEventData ) )
         {
            if ( pNewAnimalNode == nullptr )
            {
               cout << config.newFeatureRequestPhrase << "\n";
               pNewAnimalNode = new TBinaryTreeNode( pGameEventData->message );
            }
            else
            {
               pNewFeatureNode = new TBinaryTreeNode( pGameEventData->message );
               pNewFeatureNode->pLeftChild = pCurrentQuestionNode;
               pNewFeatureNode->pRightChild = pNewAnimalNode;
               pNewFeatureNode->isLeaf = false;

               internalEvent( pWaitingNextRoundState );
            }
         }
      };

      //! Иннициализация действия выхода
      pMemorizingState->exitAction = [&]
      {
         if ( pCurrentQuestionNode == pTree )
         {
            pTree = pNewFeatureNode;
         }
         else
         {
            if ( pPreviousQuestionNode->pLeftChild == pCurrentQuestionNode )
               pPreviousQuestionNode->pLeftChild = pNewFeatureNode;
            else
               pPreviousQuestionNode->pRightChild = pNewFeatureNode;
         }

         pNewAnimalNode = nullptr;
         pNewFeatureNode = nullptr;

         cout << config.afterMemorizingPhrase << "\n";
      };
   }

   void TGameStateMachine::initFinishingGameStateActions()
   {
      //! Иннициализация входного действия
      pFinishingGameState->enterAction = [&]
      {
         cout << config.saveGameProgressSuggestionPhrase << "\n";
      };

      //! Иннициализация действия обновления
      pFinishingGameState->updateAction = [&]
      {
         if ( auto* pGameEventData = dynamic_cast<TGameEventData*>( pEventData ) )
            if ( checkIsPositiveAnswer( pGameEventData->message ) )
               isNeedSaveProgress = true;

         cout << config.goodbyePhrase << "\n";
         isRunning = false;
      };
   }

   void TGameStateMachine::initializeStatesActions()
   {
      initStartStateActions();

      initWaitingNextRoundStateActions();

      initAskingQuestionStateActions();

      initTryingGuessStateActions();

      initMemorizingStateActions();

      initFinishingGameStateActions();
   }

   BOOL TGameStateMachine::checkIsPositiveAnswer(const std::string &answer)
   {
      return find(config.positiveAnswers.begin(), config.positiveAnswers.end(), answer ) != config.positiveAnswers.end();
   }
} // GameLogic