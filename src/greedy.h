#include "algo.h"

class Greedyalgo : public Algo
{
    public:
    Greedyalgo(std::vector<int>);

    Node findSolution() override;

private:
    std::vector<int> target;

    bool qsearch(std::priority_queue<Node>, Node);
    int calcHeur(std::vector<int>);
};