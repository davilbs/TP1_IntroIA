#include "algo.h"

Algo::Algo(std::vector<int> numbers)
{
    this->root = {nullptr, numbers, 0};
    this->expnodes = 0;
}

Algo::~Algo()
{
    this->freeSolutions();
}

void Algo::freeSolutions()
{
    for(int i = 0; i < this->solution.size();i++)
        delete(this->solution[i]);
    this->solution.clear();
}

Node Algo::findSolution()
{
    return Node();
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

int Algo::calcCost(int c, int a, int b)
{
    return c + ((std::abs(a - b) > 1) ? 4 : 2);
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
    std::deque<std::vector<int>> steps;
    while (curr != nullptr)
    {
        steps.push_back(curr->state);
        curr = curr->parent;
    }
    for (;!steps.empty(); steps.pop_back())
    {
        std::vector<int> cstate = steps.back();
        for (auto &v : cstate)
            std::cout << v << " ";
        std::cout << std::endl;
    }
}

Node *Algo::makeSolp(Node n)
{
    Node *solp = new Node();
    solp->state = n.state;
    solp->parent = n.parent;
    solp->cost = n.cost;
    solp->cutoff = n.cutoff;
    solp->g = n.g;
    solp->h = n.h;
    return solp;
}