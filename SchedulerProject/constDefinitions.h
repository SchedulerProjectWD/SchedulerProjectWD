#pragma once
#include <mutex>
#include <condition_variable>
#include "UI.h"
#include <string>
//using namespace std;

const int QUEUES_COUNT = 3;
const int CLOSE_TO_STARVATION_HIGH = 5;
const int CLOSE_TO_STARVATION_LOW = 20;
const int CLOSE_TO_STARVATION_RT = 10;
const int PRIORITY_INVERSION_AVOID = 5;
const int MAX_STARVED_TASKS_RT = 10;
const int MAX_CAPACITY = 30;
const int TIME_TO_DETECT_SYSTEM = 20;
const int DEFAULT_VALUE = -1;
const int RESERVED_SPACE_TO_RT_TASKS = MAX_CAPACITY/10;
static std::atomic_bool is_active(true);
const PrintIntro GET_TASK_ID(R"(choose a task to done :
1--> open application.
2--> send messeg.
3--> backup files.
4--> take a photo.
5--> download a file.
6--> low task.
7--> high task.
8--> low task.)",
"F5");
const PrintIntro SAY_GOODBYE("--> the scheduler is now shutting down.... some tasks will continue in the background \n C U soon!!!", "05");

//std::mutex mtx;
//std::condition_variable condVar;
//bool isThereWaitingTask = false;
//const char* LOGGER_FILE_PATH = "log.bin";
//const char* HISTORY_FILE_PATH = "history_log.txt";
