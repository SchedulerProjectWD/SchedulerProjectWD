#pragma once
#include <chrono>
#include <thread>
#include <iostream>
#include "Logger.h"

class TasksFuncs
{
	/*(R"(choose a task to done :	1--> open application.
									2--> send messeg.
									3--> backup files.
									4--> take a photo.
									5--> download a file.
									6--> low task.
									7--> high task.
									8--> real-time task.*/
public:
	static int open_application(void* arg) {
		Logger taskLogger("tasks.bin", "tasks_excecution.txt");

		LogRecord recordStart("======>open aplication started");
		taskLogger << recordStart;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		LogRecord recordEnd("======>open aplication finished");
		taskLogger << recordEnd;
		return 1;
	}
	static int send_messeg(void* arg) {
		Logger taskLogger("tasks.bin", "tasks_excecution.txt");

		LogRecord recordStart("======>send messeg started");
		taskLogger << recordStart;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		LogRecord recordEnd("======>send messeg finished");
		taskLogger << recordEnd;
		return 1;
	}
	static int backup_files(void* arg) {
		Logger taskLogger("tasks.bin", "tasks_excecution.txt");

		LogRecord recordStart("======>backup_files started");
		taskLogger << recordStart;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		LogRecord recordEnd("======>backup_files finished");
		taskLogger << recordEnd;
		return 1;
	}
	static int take_photo(void* arg) {
		Logger taskLogger("tasks.bin", "tasks_excecution.txt");

		LogRecord recordStart("======>take photo started");
		taskLogger << recordStart;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		LogRecord recordEnd("======>take photo finished");
		taskLogger << recordEnd;
		return 1;
	}
	static int download_file(void* arg) {
		Logger taskLogger("tasks.bin", "tasks_excecution.txt");

		LogRecord recordStart("======>download file started");
		taskLogger << recordStart;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		LogRecord recordEnd("======>download file finished");
		taskLogger << recordEnd;
		return 1;
	}
	static int low_task(void* arg) {
		Logger taskLogger("tasks.bin", "tasks_excecution.txt");

		LogRecord recordStart("======>low task started");
		taskLogger << recordStart;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		LogRecord recordEnd("======>low task finished");
		taskLogger << recordEnd;
		return 1;
	}
	static int high_task(void* arg) {
		Logger taskLogger("tasks.bin", "tasks_excecution.txt");

		LogRecord recordStart("======>high task started");
		taskLogger << recordStart;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		LogRecord recordEnd("======>high task finished");
		taskLogger << recordEnd;
		return 1;
	}
	static int realtime_task(void* arg) {
		Logger taskLogger("tasks.bin", "tasks_excecution.txt");

		LogRecord recordStart("======>real time task started");
		taskLogger << recordStart;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		LogRecord recordEnd("======>real time task finished");
		taskLogger << recordEnd;
		return 1;
	}
	static int (*functionForTasks[8])(void*);
};


