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


void tree_values_are_ascending_left_to_right_at_root()
{
    Tree tree{0};

    auto values = {-5,5};
    tree.insert(values);
    auto returned_values = tree.get_values();
    assert(std::vector<value_t>({-5, 0, 5}) == returned_values && "Returned values in the tree are incorrect.");
}

void tree_values_are_ascending_left_to_right_at_depth_1_multiple_insertions()
{
    Tree tree{0};

    tree.insert({-5,5});
    tree.insert({-2, -7});
    tree.insert({ 2, 7});

    auto returned_values = tree.get_values();
    assert(std::vector<value_t>({-7, -5, -2, 0, 2, 5, 7}) == returned_values && "Returned values in the tree are incorrect.");
}

void tree_values_are_ascending_left_to_right_at_depth_1_single_ordered_insertion()
{
    Tree tree{0};
    tree.insert({-7, -5, -2, 2, 5, 7});

    auto returned_values = tree.get_values();
    assert(std::vector<value_t>({-7, -5, -2, 0, 2, 5, 7}) == returned_values && "Returned values in the tree are incorrect.");
}

void tree_inserted_duplicates_increase_count_and_size()
{
    Tree tree{0};
    auto values = {-2, 0, 2};
    tree.insert(values);
    auto count_0 = tree.count(0);
    assert(count_0 == 2);
    assert(tree.size() == 4);

    tree.insert(0);
    count_0 = tree.count(0);
    assert(count_0 == 3);
    assert(tree.size() == 5);

    tree.insert(2);
    auto count_2 = tree.count(2);
    assert(count_2 == 2);
    assert(tree.size() == 6);
}

void tree_removing_duplicates_decrease_count()
{
    Tree tree{0};
    tree.insert({-2, 0, 2});
    assert(tree.count(0) == 2);
    tree.remove(0);
    assert(tree.count(0) == 1);
}

void tree_removing_non_duplicated_nodes_removes_them()
{
    Tree tree{0};
    tree.insert({-7, -5, -2, 2, 5, 7}); 
    tree.remove(-5);
    assert(tree.count(-5) == 0 && tree.contains(-5) == false);

    auto result = tree.get_values();
    auto expected = std::vector<value_t>{ -7, -2, 0, 2, 5, 7};
    assert(result == expected);

    tree.remove(-2);
    result = tree.get_values();
    expected = std::vector<value_t>{ -7, 0, 2, 5, 7};
    assert(result == expected);
}


int main(int argc, char const *argv[])
{
    tree_insertions_increase_size();
    tree_duplicate_insertions_increase_size();
    tree_values_are_ascending_left_to_right_at_root();
    tree_values_are_ascending_left_to_right_at_depth_1_multiple_insertions();
    tree_values_are_ascending_left_to_right_at_depth_1_single_ordered_insertion();

    tree_inserted_duplicates_increase_count_and_size();
    tree_removing_duplicates_decrease_count();
    tree_removing_non_duplicated_nodes_removes_them();

    return EXIT_SUCCESS;
}
