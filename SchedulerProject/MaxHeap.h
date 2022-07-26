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
	bool Insert(T* item);
	bool IsEmpty();
	T* ExtractMax();
	void ChangePriority(T* item, int priority);
	T* operator[](int index);
	int getSize() const;
};

template<class T>
int MaxHeap<T>::parent(int i)
{
	return (i - 1) / 2;
}

template<class T>
int MaxHeap<T>::leftChild(int i)
{
	return i * 2 + 1;
}

template<class T>
int MaxHeap<T>::rightChild(int i)
{
	return i * 2 + 2;
}

template<class T>
void MaxHeap<T>::siftUp(int i)
{
	while (i > 0 && *(heap[parent(i)]) < *(heap[i]))
	{
		T* temp = heap[parent(i)];
		heap[parent(i)] = heap[i];
		heap[i] = temp;
		i = parent(i);
	}
}

template<class T>
void MaxHeap<T>::siftDown(int i)
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
MaxHeap<T>::MaxHeap(int maxSize) :maxSize(maxSize), size(0), heap(new T* [maxSize])
{

}

template<class T>
MaxHeap<T>::~MaxHeap()
{
	if (heap)
		delete[] heap;
}

template<class T>
bool MaxHeap<T>::Insert(T* item)
{
	if (size == maxSize)
		return false;
	heap[size] = item;
	siftUp(size);
	size++;
	return true;
}

template<class T>
bool MaxHeap<T>::IsEmpty()
{
	return size == 0;
}

template<class T>
T* MaxHeap<T>::ExtractMax()
{
	if (IsEmpty())
		return nullptr;
	T* maxItem = heap[0];
	size--;
	heap[0] = heap[size];
	siftDown(0);
	return maxItem;
}

template<class T>
void MaxHeap<T>::ChangePriority(T* item, int priority)
{
	for (int i = 0; i < size; i++)
	{
		if (heap[i] == item)
		{
			if (*item > priority)
			{
				*item = priority;
				siftDown(i);
			}
			else {
				*item = priority;
				siftUp(i);
			}
		}
	}
}

template <class T>
T* MaxHeap<T>::operator[](int index)
{
	if (index < 0 || index >= size)
		throw exception("the index is out of range");
	return heap[index];
}

template<class T>
int MaxHeap<T>::getSize() const
{
	return size;
}

