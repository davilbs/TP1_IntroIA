#include "algo.h"

// Implementation of the Greedy Best First Search algorithm
class Greedyalgo : public Algo
{
public:
    Greedyalgo(std::vector<int>);

    Node findSolution() override;

private:
    std::vector<int> target;

    std::priority_queue<Node> updateFrontier(std::priority_queue<Node>, Node);
    bool qsearch(std::priority_queue<Node>, Node);
    int calcHeur(std::vector<int>);
};