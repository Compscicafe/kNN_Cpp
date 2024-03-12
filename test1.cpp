#include "main.hpp"
#include "kNN.hpp"



int main()
{
    LinkedList<Linkedlist<int>*> lst;
    LinkedList<int> ls;
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);
    lst.push_back(ls);
    lst.print();
    return 0;
}

