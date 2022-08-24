#pragma once
#include "Task.h"
#include <atomic>
#include <string>
class PrintIntro {
	std::string text;
	std::string color;
public:
	PrintIntro(std::string text, std::string color = "0F") :text(text), color("color " + color){}
	friend std::ostream& operator<<(std::ostream& os, const PrintIntro p);
};

static std::atomic<bool> is_active;

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

