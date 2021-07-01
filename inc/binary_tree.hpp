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
        size_t pCount;
        std::unique_ptr<Node> lhs;
        std::unique_ptr<Node> rhs;

        Node(value_t value)
        : value(value)
        , pCount(1)
        , lhs(nullptr)
        , rhs(nullptr)
        {}

        Node(Node& other)
        {
            this->value = other.value;
            this->pCount = other.pCount;
            this->lhs = std::move(other.lhs);
            this->rhs = std::move(other.rhs);
        } 

        void insert(Node& n)
        {
            if(n.value == value)
            {
                pCount++;
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

        size_t remove(value_t val, const bool remove_all = false)
        {
            if(rhs)
            {
                if(val == rhs->value)
                {
                    if( remove_all || --(rhs->pCount) == 0 )
                    {
                        const auto num_removed = rhs->pCount;
                        if(rhs->lhs)        // If it has an lhs
                        {
                            if(rhs->rhs)    // And a rhs atop of that.
                                rhs->lhs->insert(*(rhs->rhs)); // NOTE: I think this can be moved without the deref copy.
                            this->rhs = std::move(rhs->lhs);
                        }
                        else if(rhs->rhs)   // If it has only an rhs
                            this->rhs = std::move(rhs->rhs);
                        else
                            this->rhs = nullptr;
                        return num_removed;
                    }
                    return 1;
                }
                else if(val > value)
                    return rhs->remove(val, remove_all);
            }
            if(lhs)
            {
                if(val == lhs->value)
                {
                    if( remove_all || --(lhs->pCount) == 0 )
                    {
                        const auto num_removed = lhs->pCount;
                        if(lhs->rhs)
                        {
                            if(lhs->lhs)
                                lhs->rhs->insert(*(lhs->lhs)); // I think this can be moved without the deref copy.
                            this->lhs = std::move(lhs->rhs);
                        }
                        else if(lhs->lhs)
                            this->lhs = std::move(lhs->lhs);
                        else
                            this->lhs = nullptr;
                        
                        return num_removed;
                    }
                }
                else if(val < value)
                    return lhs->remove(val, remove_all);
            }
            return 0;
        }
    
        bool contains(value_t val)
        {
            if(val == value)
                return true;

            else if(val > value)
            {
                if(rhs)
                    return rhs->contains(val);
                else 
                    return false;
            }
            else // if(val < value)
            {
                if(lhs)
                    return lhs->contains(val);
                else
                    return false;
            }
        }
    
        size_t count(value_t val)
        {
            if(val == value)
                return pCount;

            else if(val > value)
            {
                if(rhs)
                    return rhs->count(val);
                else 
                    return 0;
            }
            else // if(val < value)
            {
                if(lhs)
                    return lhs->count(val);
                else
                    return 0;
            }
        }

        void get_values(std::vector<value_t>& values)
        {
            if(lhs)
                lhs->get_values(values);
            
            values.push_back(value);
            
            if(rhs)
                rhs->get_values(values);

        }
    };

    Node root;
    Node true_root;
    size_t tree_size;

    public:

    Tree(value_t value) 
    : root(value)
    , true_root(INT32_MAX)
    , tree_size(1)
    {
        true_root.insert(root);
    }

    void insert(const value_t val)
    {
        Node to_insert{val};
        true_root.insert(to_insert);
        tree_size++;
    }

    void insert(const std::vector<value_t>& values)
    {
        for(const auto& v : values)
        {
            insert(v);
        }
    }

    void remove(const value_t n)
    {
        tree_size = tree_size - true_root.remove(n);
    }

    void remove_all(const value_t n)
    {
        tree_size = tree_size - true_root.remove(n, true);
    }

    size_t size() 
    { 
        return tree_size; 
    }

    bool contains(value_t val)
    {
        return true_root.contains(val);
    }

    size_t count(value_t val)
    {
        return true_root.count(val);
    }

    std::vector<value_t> get_values()
    {
        std::vector<value_t> ret;
        ret.reserve(tree_size);
        true_root.lhs->get_values(ret);
        return ret;
    }
};
