#include "algo.h"

Algo::Algo(std::vector<int> numbers)
{
    this->root = {nullptr, numbers, 0};
    this->expnodes = 0;
}

Node *Algo::findSolution()
{
    return nullptr;
}

std::vector<std::tuple<int, int>> Algo::findActions(std::vector<int> state)
{
    std::vector<std::tuple<int, int>> actions;
    for (int i = 0; i < state.size() - 1; i++)
    {
        for (int j = i + 1; j < state.size(); j++)
        {
            if (state[i] > state[j])
            {
                actions.push_back(std::make_tuple(i, j));
            }
        }
    }
    return actions;
}

std::vector<int> Algo::findState(int a, int b, std::vector<int> currstate)
{
    std::vector<int> newstate = currstate;
    int x = newstate[a];
    newstate[a] = newstate[b];
    newstate[b] = x;
    return newstate;
}

bool Algo::testGoal(std::vector<int> state)
{
    for (int i = 0; i < state.size() - 1; i++)
        if (state[i] > state[i + 1])
            return false;
    return true;
}

void Algo::getPath()
{
    Node *curr = this->solution.back();
    while (curr != nullptr)
    {
        this->solution.push_back(curr);
        curr = curr->parent;
    }
    for (int i = this->solution.size() - 1; i > 0; i--)
    {
        for (auto &v : this->solution[i]->state)
            std::cout << v << " ";
        std::cout << std::endl;
    }
}