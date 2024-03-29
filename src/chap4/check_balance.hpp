// 4.1
// Implement a function to check if a tree is balanced.
//

#ifndef _CHAP4_CHECK_TREE_BALANCE_HPP_
#define _CHAP4_CHECK_TREE_BALANCE_HPP_

#include "ww_tree.hpp"

// Return tree's height if tree is balanced; return -1 if not balanced.
template<typename T>
int check_tree_balance_and_height(typename ww::BinaryTree<T>::Node* root)
{
    if (NULL == root)
        return 0;
        
    int left_height = check_tree_balance_and_height<T>(root->left);
    if (left_height == -1)
        return -1;
        
    int right_height = check_tree_balance_and_height<T>(root->right);
    if (right_height == -1)
        return -1;
    
    int height_diff = left_height - right_height;
    if (std::abs(height_diff) > 1)
        return -1;
    return (height_diff > 0 ? left_height : right_height) + 1;
}

template<typename T>
bool is_tree_balanced(typename ww::BinaryTree<T>::Node* root)
{
    return check_tree_balance_and_height<T>(root) != -1;
}



#endif

