#ifndef _WW_TREE_H_
#define _WW_TREE_H_

#include <iostream>
#include <queue>
#include <stack>

#define X_OVR

namespace ww {

template<typename T>
class BinaryTree
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
    
    typedef std::pair<Node*, Node*> NodePair;
    
    BinaryTree() : root_(NULL) {}
    virtual ~BinaryTree() 
    {
        clear();
    }
    
    //
    // Modifiers
    //
    virtual void insert(const key_type& key)
    {
        // TODO
    }
    
    virtual void erase(const key_type& key)
    {
        NodePair np = find_node_and_parent(key);
        if (NULL == np.first) // Skip if not found
            return;
        delete_node(np.first, np.second);
    }
    
    void clear()
    {
        if (NULL == root_)
            return;
        std::queue<Node*> nodes;
        nodes.push(root_);
        Node* node = NULL;
        while (!nodes.empty())
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

    //
    // Operations
    //
    virtual Node* find_node(const key_type& key)
    {
        return NULL; // TODO
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
    
    //
    // Capacity, Attributes
    //
    bool empty() { return NULL == root_; }
    
    Node* root() { return root_; }
    
    NodePair deepest_node_and_parent()
    {
        if (NULL == root_)
            return NodePair(NULL, NULL);

        std::queue<NodePair> nodes;
        nodes.push(NodePair(root_, NULL));
        Node* node = NULL;
        Node* parent = NULL;
        while (!nodes.empty())
        {
            node = nodes.front().first;
            parent = nodes.front().second;
            nodes.pop();
            if (node->left != NULL)
                nodes.push(NodePair(node->left, node));
            if (node->right != NULL)
                nodes.push(NodePair(node->right, node));
        }

        return NodePair(node, parent);
    }
    
protected:
    virtual NodePair find_node_and_parent(const key_type& key)
    {
        // TODO
        return NodePair(NULL, NULL);
    }
    
    virtual void delete_node(Node* node, Node* parent)
    {
        // TODO
    }
    
    void set_root(Node* node) { root_ = node; }

private: 
    Node* root_;
};



template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public:
    typedef T key_type;
    typedef BinaryTree<T> Parent;
    typedef typename Parent::Node Node;
    typedef typename Parent::NodePair NodePair;
    
    BinarySearchTree() : BinaryTree<T>() {}
    ~BinarySearchTree() {}
    
    X_OVR void insert(const key_type& key)
    {
        if (NULL == this->root())
        {
            set_root(new Node(key));
            return;
        }
        Node* node = this->root();
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
    
    X_OVR Node* find_node(const key_type& key)
    {
        Node* node = this->root();
        while (node != NULL)
        {
            if (key < node->key)
                node = node->left;
            else if (key > node->key)
                node = node->right;
            else // Found it
                break;
        }
        return node;
    }

protected:
    X_OVR void delete_node(Node* node, Node* parent)
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
    
    X_OVR NodePair find_node_and_parent(const key_type& key)
    {
        // Find target node
        Node* node = this->root();
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
        return NodePair(node, parent);
    }
};

}

#endif

