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
        Node *solp = this->makeSolp(sol);
        this->solution.push_back(solp);
        this->expnodes++;

        if (this->testGoal(sol.state))
            return sol;

        if (sol.g > cutoff)
            result.cutoff = true;
        else
        {
            for (auto &act : this->findActions(sol.state))
            {
                Node child;
                child.parent = solp;
                child.state = this->findState(std::get<0>(act), std::get<1>(act), sol.state);
                child.g = sol.g + 1;
                child.cost = this->calcCost(sol.cost, std::get<0>(act), std::get<1>(act));
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
        this->freeSolutions();
        result = this->depthLimited(level);
        level++;
    } while (result.cutoff);
    return result;
}