#include "ids.h"

IDSalgo::IDSalgo(std::vector<int> numbers) : Algo(numbers) {}

Node IDSalgo::depthLimited(int cutoff)
{
    std::deque<Node> frontier;
    frontier.push_back(this->root);
    Node result = Node();
    while (!frontier.empty())
    {
        Node sol = frontier.back();
        frontier.pop_back();
        this->expnodes++;
        if (this->testGoal(sol.state))
            return sol;
        if (sol.cost > cutoff)
            result.cutoff = true;
        else
        {
            // We already removed cycles by limiting the possible swaps
            for (auto &act : this->findActions(sol.state))
            {
                Node child;
                child.parent = &sol;
                child.state = this->findState(std::get<0>(act), std::get<1>(act), sol.state);
                child.cost = sol.cost + 1;
                frontier.push_back(child);
            }
        }
    }
    return result;
}

Node IDSalgo::findSolution()
{
    int level = 0;
    Node result;
    do
    {
        result = this->depthLimited(level);
        level++;
    } while (result.cutoff);
    return result;
}