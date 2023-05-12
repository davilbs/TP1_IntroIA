#include "astar.h"

AStaralgo::AStaralgo(std::vector<int> numbers) : Algo(numbers) 
{
    this->target = numbers;
    std::sort(this->target.begin(), this->target.end());
    this->root.g = 0;
    this->root.h = this->calcHeur(root.state);
    this->root.cost = this->root.g + this->root.h;
}

int AStaralgo::calcHeur(std::vector<int> state)
{
    int h = 0;
    for(int i = 0; i < state.size(); i++)
        if(this->target[i] != state[i]) h++;
    return h;
}

// Returns true if found a state inserted
bool AStaralgo::qsearch(std::priority_queue<Node> frontier, Node b)
{
    std::priority_queue<Node> frontier_copy = frontier;
    for (; !frontier_copy.empty(); frontier_copy.pop())
    {
        Node e = frontier_copy.top();
        if (e.state == b.state)
        {
            if (e.cost > b.cost)
                e = b;
            return true;
        }
    }
    return false;
}


Node AStaralgo::findSolution()
{
    std::priority_queue<Node> frontier;
    frontier.push(this->root);
    std::set<std::tuple<std::vector<int>, int>> explored;
    while (!frontier.empty())
    {
        Node sol = frontier.top();
        if (this->testGoal(sol.state))
        {
            this->solution.push_back(&sol);
            return sol;
        }
        frontier.pop();
        if (explored.find(std::make_tuple(sol.state, sol.cost)) == explored.end())
            explored.insert(std::make_tuple(sol.state, sol.cost));
        this->expnodes++;
        for (auto &act : this->findActions(sol.state))
        {
            Node child;
            child.parent = &sol;
            child.state = this->findState(std::get<0>(act), std::get<1>(act), sol.state);
            child.h = this->calcHeur(child.state);
            child.g = this->calcCost(sol.g, std::get<0>(act), std::get<1>(act));
            child.cost = child.h + child.g;
            bool inque = this->qsearch(frontier, child);
            if ((explored.find(std::make_tuple(child.state, child.cost)) == explored.end()) && !inque)
                frontier.push(child);
        }
    }
    return Node();
}