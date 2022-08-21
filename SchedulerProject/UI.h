#pragma once
#include "Task.h"

class UI
{
	void printIntro();
	void printMenu();
	Task* getNewTaskFromUser();
	bool sendTaskToMLQ(Task* newTask);
	static int autoId;

public:
	void operator()(void* params);

};

