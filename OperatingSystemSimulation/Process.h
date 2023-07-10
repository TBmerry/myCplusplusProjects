#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Process
{ 
public :

	int PID; // It is used to assign a unique ID to each process. ( Process ID Number = PID )
	string status; // Represents the current state of the process (running, stopping..)
	int priority; // Specifies the priority of the process

	 Process(int pid, int prio, string stat) { // Constructor Method written.
		PID = pid;
		status = stat;
		priority = prio;
	}

	static Process createProcess(int pid, string stat, int prio) { // Process creation functionality
		Process newProcess(pid, prio, stat);
		return newProcess;
	}

	void uptadeProcessStatus(Process& process, string newStatus) { // Process Status Update Function
		process.status = newStatus;
	}

	void setPriority(int newPriority) { // This function will change the priority of a process
		priority = newPriority;
	}

	vector<Process> monitoredProcesses; // Process monitoring data structure

	void monitorProcess(const Process& process) { // adds monitored processes to the monitoring data structure (monitoredProcesses).
		monitoredProcesses.push_back(process);
	}

	void reportProcess() { //  reports the information of the monitored processes. 
		cout << "Monitored Processes:\n";
		for (const Process& process : monitoredProcesses) {
			cout << "PID : " << process.PID << " | Status : " << process.status << " | Priority : " << process.priority << endl;
		}
	}

	void terminateProcess(Process& process) { // Process Termination Function
		process.status = "Terminated";
	}

};

