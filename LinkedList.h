#pragma once
#include <iostream>

template <class T>
struct Node {
    T data;
    Node<T>* next;
    int priority;
    Node(T data) {
        this->data = data;
        this->next = NULL;
        this->priority = 0;
    }
};

template <class T>
class LinkedList {
public:
    Node<T>* head;
    Node<T>* tail;
    int size;

    // constructor
    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
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
    T* push(T& data) {
        Node<T>* node = new Node<T>(data);
        if (this->head == NULL) {
            this->head = node;
            this->tail = node;
        }
        else {
            node->next = this->head;
            this->head = node;
        }
        this->size++;
        return &node->data;
    }

    void priority_push(T& data, int priority) {
        Node<T>* node = new Node<T>(data);
        node->priority = priority;

        if (this->head == NULL) {
            // list is empty, add new node as the only node in the list
            this->head = node;
            this->tail = node;
        }
        else if (node->priority < this->head->priority) {
            // new node has the smallest priority value, add it to the beginning of the list
            node->next = this->head;
            this->head = node;
        }
        else {
            // find the position in the list where the new node should be inserted based on priority value
            Node<T>* current = this->head;
            while (current->next != NULL && current->next->priority < node->priority) {
                current = current->next;
            }

            // insert new node at the correct position
            node->next = current->next;
            current->next = node;

            // update tail pointer if necessary
            if (node->next == NULL) {
                this->tail = node;
            }
        }

        // update list size
        this->size++;
    }


    // add an element to the end of the list
    T* put(T& data) {
        Node<T>* node = new Node<T>(data);
        if (this->head == NULL) {
            this->head = node;
            this->tail = node;
        }
        else {
            this->tail->next = node;
            this->tail = node;
        }
        this->size++;
        return &node->data;
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
            this->tail = NULL;
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

    // insert a new node with the given data at the specified position
    void insert(T& data, int pos) {
        if (pos < 0) {
            return;
        }

        if (pos > this->size) {
            pos = this->size;
        }

        Node<T>* node = new Node<T>(data);

        if (pos == 0) {
            // insert at the beginning of the list
            push(data);
        }
        else if (pos == this->size) {
            // insert at the end of the list
            put(data);
        }
        else {
            // insert in the middle of the list
            Node<T>* current = this->head;
            for (int i = 0; i < pos - 1; i++) {
                current = current->next;
            }
            node->next = current->next;
            current->next = node;
            this->size++;
        }

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