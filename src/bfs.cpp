#include "bfs.h"

BFSalgo::BFSalgo(std::vector<int> numbers) : Algo(numbers) {}

// Returns true if found a state inserted with lower or equal cost,
// false otherwise
bool BFSalgo::qsearch(std::deque<Node> frontier, Node b)
{
    for (auto &v : frontier)
    {
        if (v.state == b.state)
            return true;
    }
    return false;
}

// Returns true if found a state inserted with lower or equal cost,
// false otherwise
bool BFSalgo::esearch(std::vector<Node> explored, Node b)
{
    for (auto &v : explored)
    {
        if (v.state == b.state)
            return true;
    }
    return false;
}

Node BFSalgo::findSolution()
{
    Node sol = this->root;
    Node *solp = this->makeSolp(sol);
    this->solution.push_back(solp);

    if (this->testGoal(sol.state))
        return sol;

    std::deque<Node> frontier;
    frontier.push_back(sol);
    std::set<std::vector<int>> explored;
    
    while (!frontier.empty())
    {
        sol = frontier.front();
        frontier.pop_front();

        if (explored.find(sol.state) == explored.end())
        {
            explored.insert(sol.state);
            this->expnodes++;

            for (auto &act : this->findActions(sol.state))
            {
                Node child;
                solp = this->makeSolp(sol);
                child.parent = solp;
                child.state = this->findState(std::get<0>(act), std::get<1>(act), sol.state);

                if ((explored.find(child.state) == explored.end()) && !this->qsearch(frontier, child))
                {
                    child.cost = this->calcCost(sol.cost, std::get<0>(act), std::get<1>(act));
                    solp = this->makeSolp(child);
                    this->solution.push_back(solp);

                    if (this->testGoal(child.state))
                    {
                        this->expnodes++;
                        return child;
                    }
                    frontier.push_back(child);
                }
            }
        }
    }
    return Node();
}