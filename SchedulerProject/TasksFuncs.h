#pragma once
#include <chrono>
#include <thread>
#include <iostream>

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
		std::cout << "======>open aplication sleep" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "open aplication awake" << std::endl;
		return 1;
	}
	static int send_messeg(void* arg) {
		std::cout << "======>send_messeg sleep" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		std::cout << "send_messeg awake" << std::endl;
		return 1;
	}
	static int backup_files(void* arg) {
		std::cout << "======>backup_files sleep" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		std::cout << "backup_files awake" << std::endl;
		return 1;
	}
	static int take_photo(void* arg) {
		std::cout << "======>take photo sleep" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "take photo awake" << std::endl;
		return 1;
	}
	static int download_file(void* arg) {
		std::cout << "======>download file sleep" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "download file awake" << std::endl;		return 1;
	}
	static int low_task(void* arg) {
		std::cout << "======>low sleep" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "low awake" << std::endl; 
		return 1;
	}
	static int high_task(void* arg) {
		std::cout << "======>high sleep" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "high awake" << std::endl;
		return 1;
	}
	static int realtime_task(void* arg) {
		std::cout << "======>rt sleep" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "rt awake" << std::endl;
		return 1;
	}
	static int (*functionForTasks[8])(void*);
	

};


