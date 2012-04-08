#ifndef _WW_TREE_H_
#define _WW_TREE_H_

#include <iostream>
#include <queue>
#include <stack>

namespace ww {

template<typename T>
class BinarySearchTree
{
public:
    typedef T key_type;

    struct Node
    {
        Node(const key_type& key_in) : key(key_in), left(NULL), right(NULL) {}
        key_type key;
        Node* left;
        Node* right;
    };

    BinarySearchTree() : root_(NULL) {}
    ~BinarySearchTree() 
    {
        clear();
    }

    void insert(const key_type& key)
    {
        if (NULL == root_)
        {
            root_ = new Node(key);
        }
        Node* node = root_;
        while (true)
        {
            if (key < node->key) // Pass to the left
            {
                if (NULL == node->left) // Found slot
                {
                    node->left = new Node(key);
                    break;
                }
                else
                    node = node->left; // Keep going
            }
            else if (key > node->key) // Pass to the right
            {
                if (NULL == node->right) // Found slot
                {
                    node->right = new Node(key);
                    break;
                }
                else
                    node = node->right; // Keep going
            }
            else // Equal to current node, skip inserting
            {
                break;
            }
        }
    }

    Node* find_node(const key_type& key)
    {
        Node* node = root_;
        while (node != NULL)
        {
            if (key < node->key)
            {
                node = node->left;
            }
            else if (key > node->key)
            {
                node = node->right;
            }
            else // Found it
            {
                break;
            }
        }
        return node;
    }

    void erase(const key_type& key)
    {
        // Find target node
        Node* node = root_;
        Node* parent = NULL;
        while (node != NULL)
        {
            if (key < node->key)
            {
                parent = node;
                node = node->left;
            }
            else if (key > node->key)
            {
                parent = node;
                node = node->right;
            }
            else
                break;
        }
        // Skip if not found
        if (NULL == node)
            return;
        delete_node(node, parent);
    }
    
    void clear()
    {
        if (NULL == root_)
            return;
        std::queue<Node*> nodes;
        nodes.push(root_);
        Node* node = NULL;
        while(!nodes.empty())
        {
            node = nodes.front();
            if (node->left != NULL)
                nodes.push(node->left);
            if (node->right != NULL)
                nodes.push(node->right);
            delete node;
            nodes.pop();
        }
        root_ = NULL;
    }

    void preorder_traversal(std::ostream& outs=std::cout) const
    {
        if (NULL == root_)
            return;
        std::stack<Node*> nodes;
        nodes.push(root_);
        Node* node = NULL;
        while (!nodes.empty())
        {
            node = nodes.top();
            outs << node->key << ',';
            nodes.pop();
            if (node->right != NULL)
                nodes.push(node->right);
            if (node->left != NULL)
                nodes.push(node->left);
        }
    }

    void inorder_traversal(std::ostream& outs=std::cout) const
    {
        std::stack<Node*> nodes;
        Node* node = root_;
        while (true)
        {
            while (node != NULL)
            {
                nodes.push(node);
                node = node->left;
            }
            if (nodes.empty())
                break;
            node = nodes.top();
            nodes.pop();
            outs << node->key << ',';
            node = node->right;
        }
    }

    void postorder_traversal(std::ostream& outs=std::cout) const
    {
        if (NULL == root_)
            return;
        std::stack<Node*> nodes;
        Node* node = NULL;
        nodes.push(root_);
        while (!nodes.empty())
        {
            node = nodes.top();
            if (NULL == node || (NULL == node->right && NULL == node->left))
            {
                while (true)
                {
                    if (node != NULL)
                        outs << node->key << ',';
                    nodes.pop();
                    if (!nodes.empty() &&
                        (nodes.top() != NULL && node == nodes.top()->right))
                        node = nodes.top();
                    else
                        break;
                }
            }
            else
            {
                //if (node->right != NULL)
                    nodes.push(node->right);
                if (node->left != NULL)
                    nodes.push(node->left);
            }
        }
    }

    void level_traversal(std::ostream& outs=std::cout, bool multiline=false) const
    {
        if (NULL == root_)
            return;
        std::queue<Node*> nodes;
        Node* node = NULL;
        nodes.push(root_);
        if (multiline)
            nodes.push(NULL);
        while (!nodes.empty())
        {
            node = nodes.front();
            nodes.pop();
            if (NULL == node) // end of current line
            {
                outs << '\n';
                if (nodes.empty()) // end of all!
                    break;
                nodes.push(NULL);
                continue;
            }
            else
                outs << node->key << ',';
            if (node->left != NULL)
                nodes.push(node->left);
            if (node->right != NULL)
                nodes.push(node->right);
        }
    }

    Node* root() { return root_; }
    
    std::pair<Node*, Node*> deepest_node_and_parent()
    {
        if (NULL == root_)
            return std::pair<Node*, Node*>(NULL, NULL);

        std::queue<std::pair<Node*, Node*> > nodes;
        nodes.push(std::pair<Node*, Node*>(root_, NULL));
        Node* node = NULL;
        Node* parent = NULL;
        while (!nodes.empty())
        {
            node = nodes.front().first;
            parent = nodes.front().second;
            nodes.pop();
            if (node->left != NULL)
                nodes.push(std::pair<Node*, Node*>(node->left, node));
            if (node->right != NULL)
                nodes.push(std::pair<Node*, Node*>(node->right, node));
        }

        return std::make_pair(node, parent);
    }

protected:
    static void delete_node(Node* node, Node* parent)
    {
        if (NULL == node)
            return;

        // 1. Both legs are NULL (leaf): direct delete
        if (node->left == NULL && node->right == NULL)
        {
            if (node == parent->left)
                parent->left = NULL;
            else
                parent->right = NULL;
            delete node;
            return;
        }

        // 2. One leg is NULL: replace current node with the other leg
        if (node->left == NULL || node->right == NULL)
        {
            Node* good_leg = node->left == NULL ? node->right : node->left;
            if (node == parent->left)
                parent->left = good_leg;
            else
                parent->right = good_leg;
            delete node;
            return;
        }

        // 3. Both legs are good: swap key with max(left) or min(right), and
        // delete the max(left) or min(right)

        // Find max(left)
        Node* maxleft = node->left;
        Node* maxleft_parent = node;
        size_t depth1 = 1;
        while (maxleft->right != NULL)
        {
            maxleft_parent = maxleft;
            maxleft = maxleft->right;
            ++ depth1;
        }
        // Find min(right)
        Node* minright = node->right;
        Node* minright_parent = node;
        size_t depth2 = 1;
        while (minright->left != NULL)
        {
            minright_parent = minright;
            minright = minright->left;
            ++ depth2;
        }
        // Choose the deeper one to swap and delete
        Node* swap_node = NULL;
        Node* swap_node_parent = NULL;
        if (depth1 > depth2)
        {
            swap_node = maxleft;
            swap_node_parent = maxleft_parent;
        }
        else
        {
            swap_node = minright;
            swap_node_parent = minright_parent;
        }
        key_type swap_node_key = swap_node->key;
        delete_node(swap_node, swap_node_parent);
        node->key = swap_node_key;
    }
    
private:
    Node* root_;
};

}

#endif

