# animal-game

<h2>Сторонние пакеты</h2>
<h3>Для сборки требуются сторонние пакеты:</h3>
nlohmann-json

<h2>Аргументы</h2>
<h3>Для запуска требуется передать два аргумента:</h3>
Имя файла конфигурации реплик<br>
Имя файла конфигурации прогресса<br>

<h2>Файлы конфигурации</h2>
<h3>Файл конфигурации машины состояний игры</h3>
Формат - json. В файле конфигурации находятся реплики игры.<br>
Шаблон:<br>
{<br>
<t></t>"afterMemorizingPhrase": "...",<br>
  "gameVictoryPhrase": "...",<br>
  "greetingPhrase": "...",<br>
  "guessPostfix": "...",<br>
  "guessPrefix": "... ",<br>
  "guessedAnimalRequestPhrase": "...",<br>
  "newFeatureRequestPhrase": "...",<br>
  "playInvitationPhrase": "...",<br>
  "positiveAnswers": [<br>
    "...",<br>
  ],<br>
  "trainingDataRequestPhrase": "...",<br>
  "userVictoryPhrase": "...",<br>
  "saveGameProgressSuggestionPhrase": "...",<br>
  "goodbyePhrase": "..."<br>
}<br>
<br>
<h3>Файл конфигурации прогресса игры - бинарного дерева</h3>
Формат - json. В файле конфигурации находится прогресс
Шаблон:<br>
{<br>
  "content" : "..."<br>
  "leftChild" : ""<br>
  "rightChild" : ""<br>
}<br>
<br>
Шаблон рекурсивный, у единицы узла три поля - content, leftChild, rightChild.<br>
Значения leftChild и rightChild - новый объект шаблона.<br>
В случае отсутствия потомков значения - пустые строки.<br>

<h2>Готовая конфигурация</h2>
В папке config находятся 3 файла с готовой конфигурацией

<h3>gsmConfig.json</h3>
Готовая конфигурация реплик
<h3>progressConfig.json</h3>
Готовый прогресс игры с несколькими признаками и животными
<h3>emptyProgressConfig.json</h3>

Пустой прогресс игры с одним начальным вариантом ответа
