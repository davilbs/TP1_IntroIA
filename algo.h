#include <vector>
#include <iostream>
#include <string>
#include <tuple>
#include <deque>
#include <set>

typedef struct Node
{
    Node *parent;
    std::vector<int> state;
    int cost;
} Node;

class Algo
{
public:
    Algo(std::vector<int>);

    virtual Node *findSolution();
    int getNodeCount() { return expnodes; };
    void getPath();
protected:
    Node root;
    int expnodes;
    std::vector<Node *> solution;

    std::vector<std::tuple<int, int>> findActions(std::vector<int>);
    std::vector<int> findState(int, int, std::vector<int>);
    bool testGoal(std::vector<int>);
};