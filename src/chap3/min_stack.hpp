// 3.2
// How would you design a stack which, in addition to push and pop, also has a
// function min which returns the minimum element? Push, pop and min should all
// operate in O(1) time.

#ifndef _CHAP3_2_MIN_STACK_H_
#define _CHAP3_2_MIN_STACK_H_

#include <common/ww_stack.hpp>

template <typename T>
class MinStack : public ww::Stack<T>
{
public:
    typedef T value_type;
    typedef ww::Stack<value_type> Parent;
    typedef typename ww::Stack<value_type>::Node TNode;
    
    MinStack() : Parent(), min_nodes_()
    {
    }
    
    // TODO: copy and stuff
    
    ~MinStack() {}
    
    void push(const value_type& val)
    {
        Parent::push(val);
        if (min_nodes_.empty() || min_nodes_.top()->val_ > val)
            min_nodes_.push(this->top_node());
    }
    
    void pop()
    {
        if (!min_nodes_.empty() && min_nodes_.top() == this->top_node())
            min_nodes_.pop();
        Parent::pop();
    }
    
    const value_type& min() const
    {
        return min_nodes_.top()->val_;
    }
    
private:
    ww::Stack<TNode*> min_nodes_;
};

#endif

