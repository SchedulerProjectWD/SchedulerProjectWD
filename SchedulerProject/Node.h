#pragma once
#ifndef _NODE_H
#define _NODE_H

template<class T>
class Node
{
public:
	Node* next;
	T* data;
	Node(T* data);
};

template<class T>
Node<T>::Node(T* data) : data(data) {
	next = nullptr;
};

#endif // !_NODE_H


