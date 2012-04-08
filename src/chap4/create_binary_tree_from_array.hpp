// 4.3
// Given a sorted array, write an algorithm to create a binary tree with
// minimal height.

#ifndef _CHAP4_3_CREATE_TREE_FROM_ARRAY_H_
#define _CHAP4_3_CREATE_TREE_FROM_ARRAY_H_

#include "ww_tree.hpp"

template <typename T>
typename ww::BinaryTree<T>::Node* 
create_binary_tree_from_array(T a[], size_t n, size_t spos=0)
{
    if (n == 0)
        return NULL;
    
    size_t root_pos = spos + n/2;
    typename ww::BinaryTree<T>::Node* root =
        new typename ww::BinaryTree<T>::Node(a[root_pos]);
    
    size_t left_n = root_pos - spos;
    size_t left_spos = spos;
    root->left = create_binary_tree_from_array(a, left_n, left_spos);
    
    size_t right_n = n - 1 - left_n;
    size_t right_spos = root_pos + 1;
    root->right = create_binary_tree_from_array(a, right_n, right_spos);
    
    return root;
}

#endif

