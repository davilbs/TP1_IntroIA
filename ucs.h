#include "algo.h"
#include <queue>

class UCSalgo : public Algo
{
public:
    UCSalgo(std::vector<int>);

    Node findSolution() override;

private:
    bool qsearch(std::priority_queue<Node>, Node);
    bool esearch(std::vector<Node>, Node);
    void printfront(std::priority_queue<Node>);
};