#include <iostream>
#include "Node.h"
#include "LinkedList.h"
#include "Queue.h"
using namespace std;
int main()
{
    cout << "Hello World! its blubi racheli and miris projectos\n";
    LinkedList<int> ll;
    ll.addToBack(7);
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    Node<int>* heat = queue.getHead();
    //while (heat)
    //{
    //    cout << heat->data;
    //    heat = heat->next;
    //}
}
