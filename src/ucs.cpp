#include "ucs.h"

UCSalgo::UCSalgo(std::vector<int> numbers) : Algo(numbers) {}

// Returns true if found a state inserted
bool UCSalgo::qsearch(std::priority_queue<Node> frontier, Node b)
{
    std::priority_queue<Node> frontier_copy = frontier;
    for (; !frontier_copy.empty(); frontier_copy.pop())
    {
        Node e = frontier_copy.top();
        if ((e.state == b.state))
            return true;
    }
    return false;
}

std::priority_queue<Node> UCSalgo::updateFrontier(std::priority_queue<Node> oldfrontier, Node b)
{
    std::priority_queue<Node> n_frontier;
    for (; !oldfrontier.empty(); oldfrontier.pop())
    {
        Node e = oldfrontier.top();
        if ((e.state == b.state) && (e.cost > b.cost))
        {
            n_frontier.push(b);
            break;
        }
        else
            n_frontier.push(e);
    }

    if (n_frontier.size() > oldfrontier.size())
    {
        while (!oldfrontier.empty())
        {
            n_frontier.push(oldfrontier.top());
            oldfrontier.pop();
        }
        return n_frontier;
    }
    while (!n_frontier.empty())
    {
        oldfrontier.push(n_frontier.top());
        n_frontier.pop();
    }
    return oldfrontier;
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
        {
            this->expnodes++;
            return sol;
        }

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

                if ((explored.find(child.state) == explored.end()) || (explored[child.state] > child.cost))
                {
                    if (!this->qsearch(frontier, child))
                        frontier.push(child);
                    else
                        frontier = this->updateFrontier(frontier, child);
                }
            }
        }
    }
    return Node();
}