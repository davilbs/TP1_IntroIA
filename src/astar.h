#include "algo.h"

// Implementation of the A* Algorithm
class AStaralgo : public Algo
{
public:
    AStaralgo(std::vector<int>);

    Node findSolution() override;

private:
    std::vector<int> target;

    std::priority_queue<Node> updateFrontier(std::priority_queue<Node>, Node);
    bool qsearch(std::priority_queue<Node>, Node);
    int calcHeur(std::vector<int>);
};