#include "greedy.h"

Greedyalgo::Greedyalgo(std::vector<int> numbers) : Algo(numbers)
{
    this->target = numbers;
    std::sort(this->target.begin(), this->target.end());
    this->root.cost = this->calcHeur(root.state);
}

int Greedyalgo::calcHeur(std::vector<int> state)
{
    int h = 0;
    for (int i = 0; i < state.size(); i++)
        if (this->target[i] != state[i])
            h++;
    return h;
}

// Returns true if found a state inserted
bool Greedyalgo::qsearch(std::priority_queue<Node> frontier, Node b)
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

std::priority_queue<Node> Greedyalgo::updateFrontier(std::priority_queue<Node> oldfrontier, Node b)
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

Node Greedyalgo::findSolution()
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
            solp->cost = solp->g;
            sol.cost = sol.g;
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

                if ((explored.find(child.state) == explored.end()) || (explored[child.state] >= child.cost))
                {
                    child.g = this->calcCost(sol.g, std::get<0>(act), std::get<1>(act));
                    child.cost = this->calcHeur(child.state);
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