#pragma once
#include <iostream>

template <class T>
struct Node {
    T data;
    Node<T>* next;
    Node(T data) {
        this->data = data;
        this->next = NULL;
    }
};

template <class T>
class LinkedList {
public:
    Node<T>* head;
    int size;

    // constructor
    LinkedList() {
        this->head = NULL;
        this->size = 0;
    }

    // destructor
    ~LinkedList() {
        Node<T>* current = this->head;
        while (current != NULL) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    // add an element to the beginning of the list
    void push(T& data) {
        Node<T>* node = new Node<T>(data);
        if (this->head == NULL) {
            this->head = node;
        }
        else {
            node->next = this->head;
            this->head = node;
        }
        this->size++;
    }

    // remove and return the first element from the list
    T* pop() {
        if (this->size == 0) {
            return NULL;
        }

        Node<T>* node = this->head;
        T* data = &node->data;

        if (this->size == 1) {
            this->head = NULL;
        }
        else {
            this->head = node->next;
        }

        this->size--;

        return data;
    }

    // return the first element from the list without removing it
    T* top() {
        if (this->size == 0) {
            return NULL;
        }

        return &this->head->data;
    }

    // checks if a given data value is in the list
    bool contains(T& data) {
        Node<T>* current = this->head;
        while (current != NULL) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }


    // return true if the list is empty, false otherwise
    bool empty() {
        return this->size == 0;
    }

    // return the current size of the list
    int getSize() {
        return this->size;
    }
};