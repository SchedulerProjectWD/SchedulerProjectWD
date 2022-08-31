#pragma once
#include <mutex>
#include <condition_variable>
#include "UI.h"
#include <string>

const int QUEUES_COUNT = 3;
const int MLQ_MAX_CAPACITY = 30;
const int WAITING_TIME_LIMIT_RT = MLQ_MAX_CAPACITY * 2 ;
const int CLOSE_TO_STARVATION_RT = WAITING_TIME_LIMIT_RT / 2;
const int CLOSE_TO_STARVATION_HIGH = 10;
const int CLOSE_TO_STARVATION_LOW = 20;
//const int WAITING_TIME_LIMIT_HIGH = 0;
//const int WAITING_TIME_LIMIT_LOW = 20;
const int MAX_STARVED_TASKS_RT = 10;
const int MAX_TASK_PRIORITY = 200;
const int TIME_TO_DETECT_SYSTEM = 10;
const int DEFAULT_VALUE = -1;
const int LOG_MESSAGE_SIZE = 50;
const int RESERVED_SPACE_TO_RT_TASKS = MLQ_MAX_CAPACITY / 10;

static std::atomic_bool isInsertionActive(true);
const PrintIntro GET_TASK_ID(R"(choose a task to done :
1--> open application.
2--> send messeg.
3--> backup files.
4--> take a photo.
5--> download a file.
6--> low task.
7--> high task.
8--> real-time task.)",
"F5");
const PrintIntro SAY_GOODBYE("--> the scheduler is now shutting down.... some tasks will continue in the background \n C U soon!!!", "05");
//const char* LOGGER_FILE_PATH = "log.bin";
//const char* HISTORY_FILE_PATH = "history_log.txt";
