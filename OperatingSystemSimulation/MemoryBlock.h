#pragma once
#include <iostream>

class MemoryBlock {
public:
    MemoryBlock* previous; // Link pointing to previous memory block
    MemoryBlock* next; // Link pointing to next memory block

    static MemoryBlock* allocateMemoryBlock() {
        MemoryBlock* newBlock = new MemoryBlock; // Creating new memory block

        newBlock->previous = nullptr; // Updating link between newBlock and memory block
        newBlock->next = head;

        if (head != nullptr) {
            head->previous = newBlock; // Updating previous link of previous start node if list is not empty
        }

        head = newBlock; // Updating start node as new node

        return newBlock; // Returning new memory block
    }

    static void deallocateMemoryBlock(MemoryBlock* block) {
        if (block->previous != nullptr) {
            block->previous->next = block->next; // Updating the blog's links
        }
        else {
            head = block->next;
        }

        if (block->next != nullptr) {
            block->next->previous = block->previous;
        }

        delete block; // Freeing memory block from memory 
    }

private:
    static MemoryBlock* head; // The starting node representing the list head 
};

MemoryBlock* MemoryBlock::head = nullptr; // Start node is initially set to nullptr


