#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct MemoryRegion {
    void* startAddress; // Starting address of memory region
    size_t size; // Size of memory region
    bool isAvailable; // Availability of memory region
};

class MemoryMap {
public:
    // Adds a new memory region to the memory map.
    void addMemoryRegion(void* startAddress, size_t size) {
        MemoryRegion region;
        region.startAddress = startAddress;
        region.size = size;
        region.isAvailable = true;

        memoryRegions.push_back(region);
    }

    // Marks the specified memory region as occupied.
    void markMemoryOccupied(void* startAddress) {
        for (MemoryRegion& region : memoryRegions) {
            if (region.startAddress == startAddress) {
                region.isAvailable = false;
                break;
            }
        }
    }

    // Marks the specified memory region as available.
    void markMemoryAvailable(void* startAddress) {
        for (MemoryRegion& region : memoryRegions) {
            if (region.startAddress == startAddress) {
                region.isAvailable = true;
                break;
            }
        }
    }

    // Prints the memory map to the console.
    void printMemoryMap() const {
        cout << "Memory Map:" << endl;

        for (const MemoryRegion& region : memoryRegions) {
            cout << "Starting Address: " << region.startAddress
                << ", Size: " << region.size
                << ", Availability: " << (region.isAvailable ? "Available" : "Full")
                << endl;
        }
    }

    vector<MemoryRegion>& getMemoryRegions() {
        return memoryRegions;
    }

    // Memory allocation function
    void* allocateMemoryMap(size_t size, MemoryMap& memoryMap) {
        vector<MemoryRegion>& regions = memoryMap.getMemoryRegions();

        for (MemoryRegion& region : regions) {
            if (region.isAvailable && region.size >= size) {
                region.isAvailable = false;
                return region.startAddress;
            }
        }

        return nullptr;
    }

    // Memory release function
    void deallocateMemoryMap(void* address, MemoryMap& memoryMap) {
        // Find address of memory block in memory map
        for (MemoryRegion& region : memoryMap.getMemoryRegions()) {
            if (region.startAddress == address) {
                region.isAvailable = true;
                break;
            }
        }
    }

    // Example scenario monitoring memory usage
    void exampleMemoryMapUsageScenario() {
        MemoryMap memoryMap;

        // Add memory regions
        memoryMap.addMemoryRegion(reinterpret_cast<void*>(0x1000), 1024);
        memoryMap.addMemoryRegion(reinterpret_cast<void*>(0x2000), 2048);
        memoryMap.addMemoryRegion(reinterpret_cast<void*>(0x4000), 4096);

        // Allocate memory blocks
        void* block1 = allocateMemoryMap(512, memoryMap);
        void* block2 = allocateMemoryMap(1024, memoryMap);

        // Print memory usage
        memoryMap.printMemoryMap();

        // Free memory blocks
        deallocateMemoryMap(block1, memoryMap);
        deallocateMemoryMap(block2, memoryMap);

        // Reprint memory usage
        memoryMap.printMemoryMap();
    }

private:
    vector<MemoryRegion> memoryRegions;
};

