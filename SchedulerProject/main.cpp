#include <thread>
#include "Timer.h"
#include "Scheduler.h"
#include "UI.h"

using namespace std;
atomic_int Timer::time = 0;
int UI::autoId = 0;

int main()
{
	isInsertionActive = true;
	thread userInterface(
		[](void* param)
		{
			UI ui;
			ui((std::condition_variable*)param); 
		},
		&CVisThereWaitingTask);

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	Scheduler scheduler;
	scheduler.SystemActivation(&CVisThereWaitingTask);

	userInterface.join();
}

//system("start C:\\eclipse\\eclipse.exe");
//system("start C:\\Users\\שניידר\\AppData\\Local\\slack\\slack.exe");