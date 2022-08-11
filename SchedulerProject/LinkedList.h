#pragma once

#include "Node.h"

template<class T>
class LinkedList
{
	Node<T>* first;
	Node<T>* last;
public:
	bool addToBack(T* data);
	T* popFront();
	Node<T>* getHead();
	int getLength();
	void deleteNode(Node<T>* node);
	LinkedList();
	~LinkedList();
};

template<class T>
LinkedList<T>::LinkedList() {
	 first = last = nullptr;
}
template<class T>
bool LinkedList<T>::addToBack(T* data) {
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
int LinkedList<T>::getLength() {
	if (first == nullptr) return 0;
	Node<T>* runer = first;
	int length = 0;
	while (runer) {
		length++;
		runer = runer->next;
	}
	return length;
}
template<class T>
T* LinkedList<T>::popFront() {
	if (first->data) {
		T* data = first->data;
		if (first->next) {
			Node<T>* toDel = first;
			first = first->next;
			delete toDel;
		}
		return data;
	}
	return nullptr;
}

template<class T>
void LinkedList<T>::deleteNode(Node<T>* node) {
	//edge case- node is the head
	if (node == first)
	{
		Node<T>* toDel = first;
		first = node->next;
		delete toDel;
		return;
	}
	Node<T>* temp = first;
	while (temp && temp->next) {
		if (temp->next == node)
		{
			if (temp->next == last)
				last = temp;
			Node<T>* toDel = temp->next;
			temp->next = temp->next->next;
			delete toDel;
		}
		temp = temp->next;
	}
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

