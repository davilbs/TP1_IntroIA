#include "algo.h"
#include <queue>

// Implementation of the Uniform Cost Search algorithm
class UCSalgo : public Algo
{
public:
    UCSalgo(std::vector<int>);

    Node findSolution() override;

private:
    bool qsearch(std::priority_queue<Node>, Node);
    std::priority_queue<Node> updateFrontier(std::priority_queue<Node>, Node);
    void printfront(std::priority_queue<Node>);
};