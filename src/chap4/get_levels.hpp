// 4.4
// Given a binary search tree, design an algorithm which creates a linked
// list of all the nodes at each depth (i e , if you have a tree with
// depth D, you’ll have D linked lists)

#ifndef _CHAP4_4_GET_LEVELS_H_
#define _CHAP4_4_GET_LEVELS_H_

#include <vector>
#include <list>

#include "ww_tree.hpp"

template <typename T>
void get_levels(typename ww::BinaryTree<T>::Node* root,
    std::vector<std::list<typename ww::BinaryTree<T>::Node*> >& levels)
{
    levels.clear();
    if (NULL == root)
        return;
    
    std::queue<typename ww::BinaryTree<T>::Node*> nodes;
    nodes.push(root);
    nodes.push(NULL);
    typename ww::BinaryTree<T>::Node* node = NULL;
    std::list<typename ww::BinaryTree<T>::Node*> level;
    while (!nodes.empty())
    {
        node = nodes.front();
        nodes.pop();
        if (NULL == node) // End of level
        {
            // Finish current level
            levels.push_back(level);
            level.clear();
            
            if (nodes.empty()) // End of all
                break;
            
            // Insert another end marker
            nodes.push(NULL);
        }
        else
        {
            level.push_back(node);
            if (node->left != NULL)
                nodes.push(node->left);
            if (node->right != NULL)
                nodes.push(node->right);
        }
    }
}

#endif
