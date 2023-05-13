#include <vector>
#include <iostream>
#include <string>
#include <tuple>
#include <deque>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

#ifndef ALGO
#define ALGO
typedef struct Node
{
    Node *parent = nullptr;
    std::vector<int> state;
    int cost = 0, g = 0, h = 0;
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
    ~Algo();

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
    int calcCost(int, int, int);
    void freeSolutions();
    Node *makeSolp(Node);
};

#endif