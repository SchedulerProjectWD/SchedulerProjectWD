#pragma once

template<class T>
class Node
{
public:
	Node* next;
	T* data;
	Node() = default;
	Node(T* data);
};

template<class T>
Node<T>::Node(T* data) : data(data) {
	next = nullptr;
};


