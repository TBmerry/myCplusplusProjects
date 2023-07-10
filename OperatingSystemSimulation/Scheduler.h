#pragma once
#include <iostream>
#include <string>
#include "Process.h"

using namespace std;

struct TimingData {
		int startTime;//start time of the process
		int endTime;//process end time
		int remainingTime;//remaining time of the process
	};

class Scheduler
{
public : 
	void addProcess(const Process& process) { // used to add a process to the processes vector
        // Check if the process with the given PID already exists
        for (const Process& existingProcess : processes) {
            if (existingProcess.PID == process.PID) {
                cout << "Process with PID " << process.PID << " already exists. Skipping addition." << endl;
                return;
            }
        }

        // Add the process to the scheduler
        processes.push_back(process);
        cout << "Process with PID " << process.PID << " added to the scheduler." << endl;
	} 

	void start() { // used to manage process startup
        cout << "Scheduler started." << endl;

        // Execute the processes in the scheduler
        for (const Process& process : processes) {
            cout << "Executing process with PID: " << process.PID << endl;
            cout << "Status: " << process.status << endl;
            cout << "Priority: " << process.priority << endl;
            cout << endl;

            // Implement the logic to execute the process based on its status and priority
            if (process.status == "Running") {
                cout << "Process is running." << endl;
                // TODO: Implement the logic for a running process

                // Simulating the execution by printing a message
                cout << "Executing the running process with PID " << process.PID << endl;
            }
            else if (process.status == "Waiting") {
                cout << "Process is waiting." << endl;
                // TODO: Implement the logic for a waiting process

                // Simulating the waiting by printing a message
                cout << "Waiting for the process with PID " << process.PID << " to be ready." << endl;
            }
            else {
                cout << "Process status is unknown." << endl;
                // TODO: Implement the logic for other process statuses

                // Simulating the handling of unknown process status by printing a message
                cout << "Unknown process status for process with PID " << process.PID << ". Skipping execution." << endl;
            }
        }

        cout << "All processes executed." << endl;
	} 
    void switchProcess() { // used to manage switching between processes
        if (processes.empty()) {
            cout << "No processes in the scheduler to switch." << endl;
            return;
        }

        // Perform the logic to switch between processes
        // TODO: Implement the logic to switch between processes

        cout << "Switched to the next process." << endl;
    } 

private :
	vector<Process> processes; // Vector holding processes
};

