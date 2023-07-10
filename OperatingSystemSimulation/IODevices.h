#pragma once
#include <iostream>
#include <string>
#include "InterruptTimer.h"

using namespace std;

class DeviceAccessInterface
{
public:
	virtual void startDevices() = 0;
	virtual bool devicesConnected(const string& devicesName) const = 0;
	virtual void readDevice(const string& devicesName) = 0;
	virtual void writeDevice(const string& devicesName, const string& data) = 0;
};

class IODevices : public DeviceAccessInterface {
private :
	string name;
	string type;
	bool connected;
	InterruptTimer timer;  // Include the InterruptTimer class

public : 
	IODevices() : name(""), type(""), connected(false), timer() {}

	// Constructor Function
	IODevices(const string& name, const string& type, bool connected)
		: name(name), type(type), connected(connected) {}

	// Implement functions derived from the DeviceAccessInterface interface
	void startDevices() override {
		// Perform devices initialization
		// For example, you can set the device's connection status to started
		connected = true;
		timer.start();
	}

	void handleInterrupt() {
	// Perform the necessary operations to handle the interrupt
	// TODO: Implement the logic to handle the interrupt

	// Example implementation: Simulating interrupt handling by calling the InterruptTimer's handleInterrupt() function
		timer.handleInterrupt();

		cout << "Interrupt handled." << endl;
	}

	bool devicesConnected(const string& devicesName) const override {
		// Check the connection status of the specified device and return the result
		return (name == devicesName) && connected;
	}

	void readDevice(const string& devicesName) override {
		// Perform data read from the specified device
		if (name == devicesName && connected) {
			// Perform data read operations
			cout << "Data Read from Device: " << endl;
		}
	}

	void writeDevice(const string& devicesName, const string& data) override {
		// Perform data writing to the specified device
		if (name == devicesName && connected) {
			// Perform data write operations
			cout << "Data Written to Device: " << data << endl;
		}
	}

	// get and set functions
	string getName() const { return name; } // A get function that returns the device name
	string getType() const { return type; } // A get function that returns the type of device
	bool isConnected() const { return connected; } // A get function that returns the device's connection status
	void setConnected(bool conn) { connected = conn; } // A set function that changes the device's connection state
};

