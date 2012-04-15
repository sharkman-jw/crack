#ifndef _WW_STACK_HPP_
#define _WW_STACK_HPP_

#include <stdexcept>

namespace ww {

template <typename T>
class Stack
{
public:
    typedef T value_type;
    
    struct Node
    {
        Node(const value_type& val, Node* prev=NULL)
            : val_(val), prev_(prev)
        {
        }
        value_type val_;
        Node* prev_;
    };
    
    Stack() : top_node_(NULL) {}
    virtual ~Stack()
    {
        clear();
    }
    
    //
    // Modifiers
    //
    
    void push(const value_type& val)
    {
        top_node_ = new Node(val, top_node_);
    }
    
    void pop()
    {
        if (NULL == top_node_)
            return;
        Node* to_del = top_node_;
        top_node_ = top_node_->prev_;
        delete to_del;
    }
    
    void clear()
    {
        Node* to_del = NULL;
        while (top_node_ != NULL)
        {
            to_del = top_node_;
            top_node_ = top_node_->prev_;
            delete to_del;
        }
    }
    
    //
    // Access
    //
    
    bool empty() const
    {
        return NULL == top_node_;
    }
    
    const value_type& top() const
    {
        if (NULL == top_node_)
            throw std::runtime_error("Accessing empty stack top.");
        return top_node_->val_;
    }

protected:
    Node* top_node()
    {
        return top_node_;
    } 
    
private:
    Node* top_node_;
};

    
}

#endif
