#include <vector>
#include <string>

typedef struct Node
{
    Node* parent;
    std::vector<int> state;
} Node;

class GreedyAlgo{
    public:
        GreedyAlgo(std::vector<int>);

        Node* findSolution();
    private:
        Node root;
        std::vector<Node*> solution;
};