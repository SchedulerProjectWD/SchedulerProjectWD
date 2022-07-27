#pragma once
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "Node.h"

template<class T>
class LinkedList
{
	Node<T>* first;
	Node<T>* last;
public:
	bool addToBack(const T data);
	T& remove();
	Node<T>* getHead();
	LinkedList();
	~LinkedList();
};

template<class T>
LinkedList<T>::LinkedList() {
	 first = last = nullptr;
}
template<class T>
bool LinkedList<T>::addToBack(const T data) {
	if (!first) {
		first = new Node<T>(data);
		last = first;
	}
	else {
		if (last == first) {
			last = new Node<T>(data);
			first->next = last;
		}
		else {
			Node<T>* temp = new Node<T>(data);
			last->next = temp;
			last = last->next;
		}
	}
	return true;
}
template<class T>
T& LinkedList<T>::remove() {
	if (first->data) {
		T _data = first->data;
		if (first->next)
			first = first->next;
		return _data;
	}
	return nullptr;
}
template<class T>
Node<T>* LinkedList<T>::getHead() {
	return first;
}
template<class T>
LinkedList<T>::~LinkedList() {
	Node<T>* prev = first;
	for (Node<T>* temp = prev->next; temp != nullptr; temp = temp->next)
	{
		delete prev;
		prev = temp;
	}
	delete prev;
}
#endif // !_LINKEDLIST_H_

