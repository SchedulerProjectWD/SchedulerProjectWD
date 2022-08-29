#pragma once
#include "Task.h"
#include <atomic>
#include <string>
#include <condition_variable>
class PrintIntro {
	std::string text;
	std::string color;
public:
	PrintIntro(std::string text, std::string color = "0F") :text(text), color("color " + color) {}
	friend std::ostream& operator<<(std::ostream& os, const PrintIntro p);
};


class UI
{
	void printIntro();
	void printMenu();
	Task* getNewTaskFromUser(int id);
	bool sendTaskToMLQ(Task* newTask, std::condition_variable* CVisThereWaitingTask);
	static int autoId;
public:
	void operator()(std::condition_variable* CVisThereWaitingTask);
};

