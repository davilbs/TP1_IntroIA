#include <deque>
#include <iostream>

int main()
{
    std::deque<int*> dq;
    int *x;
    for(int i = 0; i < 10; i++){
        x = new int(i);
        dq.push_back(x);
    }
    std::deque<int*> dq2 = dq;
    int *j = new int(32);
    for (; !dq2.empty(); dq2.pop_front()) {
        int* e = dq2.front();
        if (*e == 2) *e = *j;
    }
    for (; !dq.empty(); dq.pop_front()) {
        int* e = dq.front();
        std::cout << *e << " ";
    }
    std::cout << std::endl;
}