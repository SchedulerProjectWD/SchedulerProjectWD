#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class MaxHeap
{
private:
	T** heap;
	int size;
	int maxSize;
	int parent(int i);
	int leftChild(int i);
	int rightChild(int i);
	void siftUp(int i);
	void siftDown(int i);

public:
	MaxHeap(int maxSize);
	~MaxHeap();
	bool insert(T* item);
	bool isEmpty();
	T* extractMax();
	friend void detactStarvation<T>(MaxHeap<T>* maxHeap, int limit);
};

template<class T>
inline int MaxHeap<T>::parent(int i)
{
	return (i - 1) / 2;
}

template<class T>
inline int MaxHeap<T>::leftChild(int i)
{
	return i * 2 + 1;
}

template<class T>
inline int MaxHeap<T>::rightChild(int i)
{
	return i * 2 + 2;
}

template<class T>
inline void MaxHeap<T>::siftUp(int i)
{
	while (i > 0 and *(heap[parent(i)]) < *(heap[i]))
	{
		T* temp = heap[parent(i)];
		heap[parent(i)] = heap[i];
		heap[i] = temp;
		i = parent(i);
	}
}

template<class T>
inline void MaxHeap<T>::siftDown(int i)
{
	int maxIndex, left, right;
	T* temp;
	maxIndex = i;
	left = leftChild(i);
	if (left<size && *(heap[left])>*(heap[maxIndex]))
		maxIndex = left;
	right = rightChild(i);
	if (right<size && *(heap[right])>*(heap[maxIndex]))
		maxIndex = right;
	if (i != maxIndex)
	{
		temp = heap[i];
		heap[i] = heap[maxIndex];
		heap[maxIndex] = temp;
		siftDown(maxIndex);
	}
}

template<class T>
inline MaxHeap<T>::MaxHeap(int maxSize) :maxSize(maxSize), size(0), heap(new T* [maxSize])
{

}

template<class T>
inline MaxHeap<T>::~MaxHeap()
{
	if (heap)
		delete[] heap;
}

template<class T>
inline bool MaxHeap<T>::insert(T* item)
{
	if (size == maxSize)
		return false;
	size++;
	heap[size - 1] = item;
	siftUp(size - 1);
	return true;
}

template<class T>
inline bool MaxHeap<T>::isEmpty()
{
	return size == 0;
}

template<class T>
inline T* MaxHeap<T>::extractMax()
{
	T* maxItem = heap[0];
	heap[0] = heap[size - 1];
	size--;
	siftDown(0);
	return maxItem;
}

template <class T>
inline void detactStarvation(MaxHeap<T>* maxHeap, int limit)
{
}
