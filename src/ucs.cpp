#include "ucs.h"

UCSalgo::UCSalgo(std::vector<int> numbers) : Algo(numbers) {}

// Returns true if found a state inserted
bool UCSalgo::qsearch(std::priority_queue<Node> frontier, Node b)
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

// Returns true if found a state inserted with lower or equal cost,
// false otherwise
bool UCSalgo::esearch(std::vector<Node> explored, Node b)
{
    for (auto &v : explored)
    {
        if (v.state == b.state)
            return true;
    }
    return false;
}

void UCSalgo::printfront(std::priority_queue<Node> frontier)
{
    std::priority_queue<Node> frontier_copy = frontier;
    int pos = 1;
    for (; !frontier_copy.empty(); frontier_copy.pop())
    {
        Node e = frontier_copy.top();
        std::cout << "[COST] " << e.cost << " [STATE] ";
        for (auto v : e.state)
            std::cout << v << " ";
        std::cout << "[POS] " << pos << std::endl;
        pos++;
    }
}

Node UCSalgo::findSolution()
{
    std::priority_queue<Node> frontier;
    frontier.push(this->root);
    std::map<std::vector<int>, int> explored;
    while (!frontier.empty())
    {
        Node sol = frontier.top();
        Node *solp = this->makeSolp(sol);
        this->solution.push_back(solp);
        frontier.pop();

        if (this->testGoal(sol.state))
            return sol;

        if ((explored.find(sol.state) == explored.end()) || (explored[sol.state] > sol.cost))
        {
            explored[sol.state] = sol.cost;
            this->expnodes++;

            for (auto &act : this->findActions(sol.state))
            {
                Node child;
                child.parent = solp;
                child.state = this->findState(std::get<0>(act), std::get<1>(act), sol.state);
                child.cost = this->calcCost(sol.cost, std::get<0>(act), std::get<1>(act));
                bool inque = this->qsearch(frontier, child);
                bool inexp = (explored.find(child.state) == explored.end()) || (explored[child.state] >= child.cost);
                if (inexp && !inque)
                    frontier.push(child);
            }
        }
    }
    return Node();
}