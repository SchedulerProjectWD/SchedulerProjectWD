#pragma once
#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "LinkedList.h"
template<class T>
class Queue
{ 
private:
	LinkedList<T>* list;
public:
	Queue() { list = new LinkedList<T>; }
	bool is_empty() { return list->getHead() == nullptr; }
	void enqueue(T* in) { list->addToBack(in); }
	T* dequeue() { return list->popFront(); }
	Node<T>* getHead() { return list->getHead(); }
	LinkedList<T>* getInnerList() { return list; }
	int getSize() { return list->getLength(); }
};
#endif // !_QUEUE_H_
