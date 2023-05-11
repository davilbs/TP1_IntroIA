#include <iostream>
#include <vector>
#include <string>
#include "greedy.h"

int main(int argc, char *argv[])
{
    std::string label;
    bool print = false;
    std::vector<int> numbers;

    label = argv[1];
    int siz = atoi(argv[2]);
    if (argc > (siz + 3))
    {
        print = true;
    }

    for (int i = 0; i < siz; i++)
    {
        numbers.push_back(atoi(argv[i + 3]));
    }

    return 0;
}