#pragma once
template <typename T>
class Queue
{
private:
	linked_list<T>* list;
public:
	bool is_empty() { return list->Head == NULL; }
	void enqueue(T* in) { list->insert_to_end(in); }
	T* dequeue(); {return list->delete_head(); }
	T* operator[](int i) { return list[i]; }
};

