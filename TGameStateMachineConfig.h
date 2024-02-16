#ifndef TGAMESTATEMACHINECONFIG_H
#define TGAMESTATEMACHINECONFIG_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <nlohmann/detail/macro_scope.hpp>

namespace GameLogic
{
   using std::string;

   /*!
    * \brief Структура данных конфигурации машины состояний игры
    * Содержит реплики машины состояний
    */
   struct TGameStateMachineConfig
   {
      string greetingPhrase; //!< Строка Реплика преветствия
      string playInvitationPhrase; //!< Строка Реплика приглашения к игре
      std::vector<string> positiveAnswers; //!< Вектор положительных ответов
      string gameVictoryPhrase; //!< Строка Реплика победы игры
      string userVictoryPhrase; //!< Строка Реплика победы игрока
      string trainingDataRequestPhrase; //!< Строка Реплика запроса об обучении игры
      string guessedAnimalRequestPhrase; //!< Строка Реплика запроса загаданного животного
      string newFeatureRequestPhrase; //!< Строка Реплика запроса различающего качества животного
      string afterMemorizingPhrase; //!< Строка Реплика после обучения игры
      string guessPrefix; //!< Строка Префикс реплики угадывания
      string guessPostfix; //!< Строка Постфикс реплики угадывания
      string saveGameProgressSuggestionPhrase; //!< Строка Реплика предложения о сохранении прогресса
      string goodbyePhrase; //!< Строка Реплика прощания

      /*!
       * Макрос библиотеки nlomann json для создания методов
       * сериализации и десериализации для структуры в json
       */

      NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TGameStateMachineConfig, greetingPhrase, playInvitationPhrase,
                                         positiveAnswers, gameVictoryPhrase, userVictoryPhrase,
                                         trainingDataRequestPhrase, guessedAnimalRequestPhrase,
                                         newFeatureRequestPhrase, afterMemorizingPhrase, guessPrefix, guessPostfix,
                                         saveGameProgressSuggestionPhrase,
                                         goodbyePhrase);
   };
} // GameLogic

#endif //TGAMESTATEMACHINECONFIG_H
