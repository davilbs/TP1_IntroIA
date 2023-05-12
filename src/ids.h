#include "algo.h"

class IDSalgo : public Algo
{
public:
    IDSalgo(std::vector<int>);

    Node findSolution() override;

private:
    Node depthLimited(int);
};