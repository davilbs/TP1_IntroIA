#include "algo.h"

// Implementation of the Breadth First Search algorithm
class BFSalgo : public Algo
{
public:
    BFSalgo(std::vector<int>);

    Node findSolution() override;

private:
    bool qsearch(std::deque<Node>, Node);
    bool esearch(std::vector<Node>, Node);
};