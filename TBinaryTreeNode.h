#ifndef TNODE_H
#define TNODE_H
#include <string>
#include <nlohmann/json.hpp>

#include "DataTypes.h"

namespace BinarySearchTree
{
   /*!
    * \brief Класс узла бинарного дерева
    * В качестве данных хранит строку
    */
   class TBinaryTreeNode
   {
      public:
         /*!
          * \brief Конструктор узла
          * При создании узел является листом
          * Определяет указатели на потомков как nullptr
          * \param content Строка по адресу - данные узла
          */
         TBinaryTreeNode(const std::string &content )
            {
               this->content = content;

               isLeaf = true;
               pLeftChild = nullptr;
               pRightChild = nullptr;
            }

         /*!
          * \brief Возвращает представление поддерева в json
          * Обходит потомков рекурсивным путём
          * \return Объект json - представление поддерева
          */
         nlohmann::json getJsonView()
         {
            if ( isLeaf )
            {
               return nlohmann::json
               {
                  {"content", content},
                     {"leftChild", ""},
                  {"rightChild", ""}
               };
            }

            return nlohmann::json
            {
               {"content", content},
               {"leftChild", pLeftChild->getJsonView()},
               {"rightChild", pRightChild->getJsonView()},
            };
         }

         /*!
          * \brief Деструктор, рекурсивно удаляет всё поддерево
          */
         ~TBinaryTreeNode();

         TBinaryTreeNode* pLeftChild; //!< Указатель на левый узел-поддерево

         TBinaryTreeNode* pRightChild; //!< Указатель на правый узел-поддерево

         BOOL isLeaf; //!< Булево значение, является ли узел листом (не имеет поддеревьев)

         std::string content; //!< Данные узла
   };
}

#endif //TNODE_H