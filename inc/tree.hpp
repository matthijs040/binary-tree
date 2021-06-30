#pragma once

#include <memory>
#include <vector>

using value_t = int;



class Tree
{
    private:

    struct Node  
    {
        value_t value;
        size_t count;
        std::unique_ptr<Node> lhs;
        std::unique_ptr<Node> rhs;
    
        Node(value_t value)
        : value(value)
        , count(1)
        , lhs(nullptr)
        , rhs(nullptr)
        {}
    
        Node(Node& other)
        {
            this->value = other.value;
            this->count = other.count;
            this->lhs = std::move(other.lhs);
            this->rhs = std::move(other.rhs);
        } 
    
        void insert(Node& n)
        {
            if(n.value == value)
            {
                count++;
                if(n.lhs)
                    lhs->insert(*n.lhs);
                if(n.rhs)
                    rhs->insert(*n.rhs);
            }
    
            else if(n.value > value)
                if(rhs)
                    rhs->insert(n);
                else
                    rhs = std::make_unique<Node>(n);
            
            else if(n.value < value)
            {
                if(lhs)
                    lhs->insert(n);
                else
                    lhs = std::make_unique<Node>(n);
            }
    
        }
    
        void remove(value_t val)
        {
            if(rhs)
            {
                if(val == rhs->value)
                {
                    if( --(rhs->count) == 0 )
                    {
                        if(rhs->lhs)        // If it has an lhs
                        {
                            if(rhs->rhs)    // And a rhs atop of that.
                                rhs->lhs->insert(*(rhs->rhs)); // NOTE: I think this can be moved without the deref copy.
                            this->rhs = std::move(rhs->lhs);
                            return;
                        }
                        else if(rhs->rhs)   // If it has only an rhs
                            this->rhs = std::move(rhs->rhs);
                        else
                            this->rhs = nullptr;
                    }
                }
                else if(val > value)
                    rhs->remove(val);
            }
            else if(lhs)
            {
                if(val == lhs->value)
                {
                    if( --(lhs->count) == 0 )
                    {
                        if(lhs->rhs)
                        {
                            if(lhs->lhs)
                                lhs->rhs->insert(*(lhs->lhs)); // I think this can be moved without the deref copy.
                            this->lhs = std::move(lhs->rhs);
                            return;
                        }
                        else if(lhs->lhs)
                            this->lhs = std::move(lhs->lhs);
                        else
                            this->lhs = nullptr;
                    }
                }
                else if(val < value)
                    lhs->remove(val);
            }
        }
    };

    Node root;
    Node true_root;
    size_t size;

    public:

    Tree(value_t value) 
    : root(value)
    , true_root(0)
    {
        true_root.insert(root);
    }

    void insert(const value_t val)
    {
        Node to_insert{val};
        root.insert(to_insert);
    }

    void insert(const std::vector<value_t> values)
    {
        for(const auto& v : values)
        {
            insert(v);
        }
    }

    void remove(const value_t n)
    {
        true_root.remove(n);
    }

    void remove_all(const value_t n);

    size_t count() 
    { 
        return size; 
    }
};
