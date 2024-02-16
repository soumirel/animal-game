#ifndef TGAMECONFIG_H
#define TGAMECONFIG_H
#include "TGameStateMachineConfig.h"

namespace GameLogic
{
   /*!
    * \brief Структура конфигурации объекта TGame
    * Содержит строковые значения - имена файлов конфигурации
    */
   struct TGameConfig
   {
      string gsmConfigFileName; //!< Имя файла конфиурации машины состояний игры

      string dataBaseFileName;//!< Имя файла конфиурации бинарного дерева прогресса игры
   };
} // GameLogic

#endif //TGAMECONFIG_H
