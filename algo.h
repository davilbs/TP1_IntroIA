#include <vector>
#include <iostream>
#include <string>
#include <tuple>
#include <deque>
#include <set>

#ifndef ALGO
#define ALGO
typedef struct Node
{
    Node *parent;
    std::vector<int> state;
    int cost;
    bool cutoff = false;

    bool operator< (const Node &a) const
    {
        return cost > a.cost;
    }
} Node;

class Algo
{
public:
    Algo(std::vector<int>);

    virtual Node findSolution();
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

#endif