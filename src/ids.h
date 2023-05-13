#include "algo.h"

// Implementation of the Iterative Depth Search algorithm
class IDSalgo : public Algo
{
public:
    IDSalgo(std::vector<int>);

    Node findSolution() override;

private:
    Node depthLimited(int);
};