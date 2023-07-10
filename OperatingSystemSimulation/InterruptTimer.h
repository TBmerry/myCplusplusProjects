#pragma once
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

class InterruptTimer
{
private:
	HANDLE hTimer; // timer identifier
	HANDLE hTimerQueue; // Scheduler queue handle
	DWORD dwDueTime = 1000; // Timer duration (in milliseconds)

public:
	InterruptTimer() {
		hTimerQueue = CreateTimerQueue(); // Creates the timer queue
		if (hTimerQueue == NULL) {
			cerr << "Failed to create timer queue!" << endl;
			return;
		}

		// Creates and starts the timer
		if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, TimerCallback, NULL, dwDueTime, 0, 0)) {
			cerr << "Failed to create timer!" << endl;
			DeleteTimerQueue(hTimerQueue); // Clears the created scheduler queue
			return;
		}
	}

	~InterruptTimer() {
		// Stops the timer and clears the timer queue
		DeleteTimerQueueTimer(hTimerQueue, hTimer, NULL);
		DeleteTimerQueue(hTimerQueue);
	}

	static VOID CALLBACK TimerCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
		// Function called when timer interrupt occurs
		cout << "The timer interrupt has occurred!" << endl;
	}

	void start() {
		hTimerQueue = CreateTimerQueue(); // Creates a new scheduler queue
		if (hTimerQueue == NULL) {
			cerr << "Failed to create timer queue!" << endl;
			return;
		}

		// Creates and starts the timer
		if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, TimerCallback, NULL, dwDueTime, 0, 0)) {
			cerr << "Failed to create timer!" << endl;
			DeleteTimerQueue(hTimerQueue); // Clears the created scheduler queue
			return;
		}

		cout << "The timer has been started." << endl;
	}

	void stop() {
		// Stops the timer and clears the timer queue
		DeleteTimerQueueTimer(hTimerQueue, hTimer, NULL);
		DeleteTimerQueue(hTimerQueue);

		cout << "The timer has been stopped." << endl;
	}

	void handleInterrupt() {
		// Function that handles interrupt event
		cout << "The cut thing happened!" << endl;
	}
};


