#pragma once
#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;  // dynamically allocated array to store stack elements
    int size;  // current size of the stack
    int capacity;  // maximum capacity of the stack

public:
    // constructor
    Stack(int capacity = 10) {
        this->capacity = capacity;
        this->size = 0;
        this->arr = new int[capacity];
    }

    // destructor
    ~Stack() {
        delete[] this->arr;
    }

    // push an element onto the stack
    void push(int value) {
        if (this->size == this->capacity) {
            // if the stack is full, resize the array
            this->capacity *= 2;
            int* newArr = new int[this->capacity];
            for (int i = 0; i < this->size; i++) {
                newArr[i] = this->arr[i];
            }
            delete[] this->arr;
            this->arr = newArr;
        }

        this->arr[this->size++] = value;
    }

    // remove and return the top element from the stack
    int pop() {
        if (this->size == 0) {
            return -1;
        }

        int value = this->arr[--this->size];

        if (this->size < this->capacity / 2) {
            // if the stack is less than half full, resize the array
            this->capacity /= 2;
            int* newArr = new int[this->capacity];
            for (int i = 0; i < this->size; i++) {
                newArr[i] = this->arr[i];
            }
            delete[] this->arr;
            this->arr = newArr;
        }

        return value;
    }

    // return the top element of the stack without removing it
    int top() {
        if (this->size == 0) {
            return -1;
        }

        return this->arr[this->size - 1];
    }

    // return true if the stack is empty, false otherwise
    bool empty() {
        return this->size == 0;
    }

    // return the current size of the stack
    int getSize() {
        return this->size;
    }
};