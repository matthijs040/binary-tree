#include <iostream>
#include "binary_tree.hpp"
#include <cassert>

void tree_insertions_increase_size()
{
    Tree tree{0};
    size_t expected_size = 1;
    assert(tree.size() == expected_size && "Initialized tree does not show its initial node.");

    auto values1 = { 1, 2, 3};
    tree.insert(values1);
    expected_size += values1.size();
    assert(tree.size() == expected_size  && "Tree does not show first inserted values.");

    auto values2 = { 15, -12, 45, 85, -23};
    tree.insert(values2);
    expected_size += values2.size();
    assert(tree.size() == expected_size && "Tree does not show second inserted values.");
}

void tree_duplicate_insertions_increase_size()
{
    Tree tree{0};
    size_t expected_size = 1;

    auto duplicate_values = { 3, 3, 2, 2, 2, 2, 41, 41};
    tree.insert(duplicate_values);
    expected_size += duplicate_values.size();

    assert(tree.size() == expected_size && "Tree does not show duplicate values after insertion.");
}


void tree_inserts_left_to_right_by_value_at_root()
{
    Tree tree{0};

    auto values = {-5,5};
    tree.insert(values);
    auto returned_values = tree.get_values();
    assert(std::vector<value_t>({-5, 5, 0}) == returned_values && "Returned values in the tree are incorrect.");
    
}


int main(int argc, char const *argv[])
{
    Tree tree{0};
    auto values = {1,2,3,4,5,6};
    tree.insert(values);

    tree_insertions_increase_size();
    tree_duplicate_insertions_increase_size();
    tree_inserts_left_to_right_by_value_at_root();

    return EXIT_SUCCESS;
}
