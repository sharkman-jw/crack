// 4.6
// Design an algorithm and write code to find the first common ancestor
// of two nodes in a binary tree Avoid storing additional nodes in a data
// structure   NOTE: This is not necessarily a binary search tree

#ifndef _CHAP4_6_LEAST_COMMON_ANCESTOR_H_
#define _CHAP4_6_LEAST_COMMON_ANCESTOR_H_

#include "ww_tree.hpp"

template <typename T>
typename ww::BinaryTree<T>::Node*
get_first_common_ancestor(typename ww::BinaryTree<T>::Node* root,
    typename ww::BinaryTree<T>::Node* node1,
    typename ww::BinaryTree<T>::Node* node2)
{
    if (root == NULL)
        return NULL;
        
    size_t count = 0;
    
    typename ww::BinaryTree<T>::Node* l_result =
        get_first_common_ancestor<T>(root->left, node1, node2);
    if (l_result != NULL)
        ++ count;
    typename ww::BinaryTree<T>::Node* r_result =
        get_first_common_ancestor<T>(root->right, node1, node2);
    if (r_result != NULL)
        ++ count;
    typename ww::BinaryTree<T>::Node* self_result = NULL;
    if (root == node1)
    {
        self_result = root;
        ++ count;
    }
    if (root == node2)
    {
        self_result = root;
        ++ count;
    }
    
    if (count > 1)
        return root;
    
    return l_result == NULL ?
        (r_result == NULL ? self_result : r_result) : l_result;
}

#endif
