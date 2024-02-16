#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include "TGame.h"
#include "TGameEventData.h"

namespace GameLogic
{
   TGame::TGame()
   {
      isSetUp = FALSE;
      pGameStateMachine = new TGameStateMachine();
   }

   TGame::~TGame()
   = default;

   void TGame::setUp(const TGameConfig& gameConfig)
   {
      this->gameConfig = gameConfig;

      setUpStateMachine();
      setUpBinaryTree();

      isSetUp = TRUE;
   }

   BOOL TGame::start() const
   {
      if ( isSetUp )
      {
         startGameLoop();
         return TRUE;
      }

      return FALSE;
   }

   void TGame::startGameLoop() const
   {
      pGameStateMachine->run();

      std::string input;
      auto* pGameEventData = new TGameEventData();
      while ( pGameStateMachine->getIsRunning() )
      {
         getline( std::cin, input );
         pGameEventData->message = input;
         pGameStateMachine->update( pGameEventData );
      }

      if ( pGameStateMachine->getIsNeedSaveProgress() )
      {
         saveGameProgress();
      }

      system( "pause" );
   }

   void TGame::setUpStateMachine() const
   {
      std::ifstream i(this->gameConfig.gsmConfigFileName);
      nlohmann::json gsmConfigJson;
      i >> gsmConfigJson;
      i.close();

      TGameStateMachineConfig gsmConfig;
      gsmConfig.from_json(gsmConfigJson, gsmConfig);

      pGameStateMachine->setConfig(gsmConfig);
   }

   void TGame::setUpBinaryTree()
   {
      nlohmann::json gameTreeJson;
      std::ifstream i(gameConfig.dataBaseFileName);
      i >> gameTreeJson;
      i.close();

      TBinaryTreeNode* pGameTree = deserializeTree( gameTreeJson );
      pGameStateMachine->setGameTree(pGameTree);
   }

   TBinaryTreeNode* TGame::deserializeTree( nlohmann::json& j )
   {
      auto* pNode = new TBinaryTreeNode( j.at( "content" ) );

      if ( j.at( "leftChild" ) != "" )
      {
         pNode->isLeaf = false;
         pNode->pLeftChild = deserializeTree(j.at( "leftChild" ));
         pNode->pRightChild = deserializeTree(j.at( "rightChild" ));
      }

      return pNode;
   }

   void TGame::saveGameProgress() const
   {
      auto gameTree = pGameStateMachine->getGameTree();
      auto gameTreeJson = gameTree->getJsonView();
      std::ofstream o(gameConfig.dataBaseFileName);
      o << gameTreeJson;
      o.close();
   }
} // GameLogic

