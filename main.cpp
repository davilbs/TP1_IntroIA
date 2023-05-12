#include <iostream>
#include <vector>
#include <string>
#include "src/bfs.h"
#include "src/ucs.h"
#include "src/ids.h"
#include "src/astar.h"
#include "src/greedy.h"

int main(int argc, char *argv[])
{
    char label = *argv[1];
    bool print = argc > (atoi(argv[2]) + 3);
    std::vector<int> numbers;
    for (int i = 0; i < atoi(argv[2]); i++)
        numbers.push_back(atoi(argv[i + 3]));

    Algo *solver;
    switch (label)
    {
    case 'B':
        solver = new BFSalgo(numbers);
        break;
    case 'U':
        solver = new UCSalgo(numbers);
        break;
    case 'I':
        solver = new IDSalgo(numbers);
        break;
    case 'A':
        solver = new AStaralgo(numbers);
        break;
    case 'G':
        solver = new Greedyalgo(numbers);
        break;
    default:
        std::cout << "Algorithm " << label << " not implemented!" << std::endl;
        exit(1);
    }

    Node sol = solver->findSolution();
    if (!sol.state.empty())
    {
        std::cout << sol.cost << " " << solver->getNodeCount() << std::endl;
        if (print)
            solver->getPath();
        else
        {
            for (auto &v : sol.state)
                std::cout << v << " ";
            std::cout << std::endl;
        }
    }
    else
        std::cout << "No solution found" << std::endl;

    exit(0);
}