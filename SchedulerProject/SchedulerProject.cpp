#include <iostream>
#include "MaxHeap.h"
using namespace std;

int main()
{
	MaxHeap<int> heap(10);
	int x[] = { 1,2,3,4,5,6,7 };
	heap.insert(x);
	heap.insert(x + 1);
	heap.insert(x + 2);
	heap.insert(x + 3);
	heap.insert(x + 4);
	heap.insert(x + 5);
	heap.insert(x + 6);
	for (int i = 0; i < 5; i++)
	{
		cout << *(heap.extractMax()) << endl;
	}

	std::cout << "Hello World! its Blumi Racheli and Miri's projectos" << endl;
}
