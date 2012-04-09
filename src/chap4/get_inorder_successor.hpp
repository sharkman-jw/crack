// 4.5
// Write an algorithm to find the ‘next’ node (i e , in-order successor)
// of a given node in a binary search tree where each node has a link to
// its parent

#ifndef _CHAP4_5_GET_INORDER_SUCCSSOR_H_
#define _CHAP4_5_GET_INORDER_SUCCSSOR_H_

#include "ww_tree.hpp"

template <typename T>
typename ww::BinaryTree<T>::NodeWithParent*
get_inorder_successor(typename ww::BinaryTree<T>::NodeWithParent* node)
{
    if (NULL == node)
        return NULL;
    
    // No right leg: go up until we're on the left of a node,
    // then that node is the succesor
    if (node->right == NULL)
    {
        typename ww::BinaryTree<T>::NodeWithParent* candidate = node->parent;
        typename ww::BinaryTree<T>::NodeWithParent* temp = node;
        while (candidate != NULL && candidate->left != temp)
        {
            temp = candidate;
            candidate = candidate->parent;
        }
        return candidate;
    }
    else // Has right leg: get min of right
    {
        typename ww::BinaryTree<T>::NodeWithParent* rightmin = node->right_node();
        while (rightmin->left != NULL)
            rightmin = rightmin->left_node();
        return rightmin;
    }
}

#endif
