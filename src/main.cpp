#include <iostream>
#include "tree.hpp"

int main(int argc, char const *argv[])
{
    Tree tree{0};
    auto values = {1,2,3,4,5,6};
    tree.insert(values);

    return EXIT_SUCCESS;
}
