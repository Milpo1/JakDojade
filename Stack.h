#pragma once
#include <iostream>
using namespace std;

template <class T>
class Stack {
public:
    T* arr;  // dynamically allocated array to store stack elements
    int size;  // current size of the stack
    int capacity;  // maximum capacity of the stack

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
    void push(T& value) {
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
    T& pop() {
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
    T* top() {
        if (this->size == 0) {
            return -1;
        }

        return &this->arr[this->size - 1];
    }

    // check is stack contains a given value
    bool contains(const T& value) {
        for (int i = this->size - 1; i >= 0; i--) {
            if (this->arr[i] == value) {
                return true;
            }
        }
        return false;
    }

    // return true if the stack is empty, false otherwise
    bool empty() {
        return this->size == 0;
    }

    // return the current size of the stack
    int getSize() {
        return this->size;
    }

    // return the value at index i of the stack
    T& get(int i) {
        if (i < 0 || i >= this->size) {
            // throw an exception or return a default value
            // depending on the desired behavior
            throw "Index out of bounds";
        }

        return this->arr[i];
    }
};