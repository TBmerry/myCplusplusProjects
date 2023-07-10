#include <iostream>
#include <string>
#include "Process.h"
#include "Scheduler.h"
#include "MemoryMap.h"
#include "IODevices.h"
#include "InterruptTimer.h"

using namespace std;

int main() {
    Scheduler scheduler; // Creating an instance from the Scheduler class
    IODevices ioDevices; // Creating an instance of the IODevices class

    bool isRunning = true;
    string command;

    while (isRunning) {
        cout << "Enter command (add, start, switch, read, write, quit): ";
        cin >> command;

        if (command == "add") {
            // Adding a new process
            int pid, prio;
            string stat;

            cout << "Enter the process PID: ";
            cin >> pid;
            cout << "Enter the process status: ";
            cin >> stat;
            cout << "Enter the process priority: ";
            cin >> prio;

            Process process(pid, prio, stat);
            scheduler.addProcess(process);
        }
        else if (command == "start") {
            // Scheduler startup process
            scheduler.start();
        }
        else if (command == "switch") {
            // Process migration process
            scheduler.switchProcess();
        }
        else if (command == "read") {
            // The process of reading data from a device
            string deviceName;
            cout << "Enter the device name to read: ";
            cin >> deviceName;

            ioDevices.readDevice(deviceName);
        }
        else if (command == "write") {
            // The process of writing data to a device
            string deviceName, data;
            cout << "Enter the device name to write data to: ";
            cin >> deviceName;
            cout << "Enter the data: ";
            cin >> data;

            ioDevices.writeDevice(deviceName, data);
        }
        else if (command == "quit") {
            // Ending the program
            isRunning = false;
        }
        else {
            cout << "Invalid command. Please try again." << endl;
        }
    }

    return 0;
}

