#include "pch.h"
#include "../SchedulerProject/MaxHeap.h"

TEST(MaxHeapTest, ExtractMax)
{
	MaxHeap<int> heap(5);
	int arr[] = { 3,7,2,4,8 };
	for (int i = 0; i < 5; i++)
	{
		heap.Insert(arr + i);
	}
	EXPECT_EQ(*(heap.ExtractMax()), 8);
}