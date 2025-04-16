#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"

using namespace std;

template <typename T>
class CircularList : public List<T> {  
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;

            Node() : data(T()), next(nullptr), prev(nullptr) {}

            Node(T value) : data(value), next(nullptr), prev(nullptr) {}

            void killSelf(){
                // TODO      
            }    
        };

    private:
        Node* head; // sentinel
        int nodes; 

    public:
        CircularList() : List<T>(), head(nullptr), nodes(0) {}

        ~CircularList() {
            clear();
        }

        T front(){
            return head->data;
        }

        T back(){
            return head->prev->data;
        }

        void push_front(T data){
            Node* new_node = new Node(data);
            if (is_empty()) {
                new_node->next = new_node;
                new_node->prev = new_node;
                head = new_node;
            } else {
                Node* tail = head->prev;
                new_node->next = head;
                new_node->prev = tail;
                head->prev = new_node;
                tail->next = new_node;
                head = new_node;
            }
            nodes++;
        }

        void push_back(T data){
            Node* new_node = new Node(data);
            if (is_empty()) {
                new_node->next = new_node;
                new_node->prev = new_node;
                head = new_node;
            } else {
                Node* tail = head->prev;
                new_node->next = head;
                new_node->prev = tail;
                tail->next = new_node;
                head->prev = new_node;
            }
            nodes++;
        }

        T pop_front(){
            T value = head->data;
            if (nodes == 1) {
                delete head;
                head = nullptr;
            } else {
                Node* tail = head->prev;
                Node* next = head->next;
                tail->next = next;
                next->prev = tail;
                delete head;
                head = next;
            }
            nodes--;
            return value;
        }

        T pop_back(){
            Node* tail = head->prev;
            T value = tail->data;
            if (nodes == 1) {
                delete head;
                head = nullptr;
            } else {
                Node* new_tail = tail->prev;
                new_tail->next = head;
                head->prev = new_tail;
                delete tail;
            }
            nodes--;
            return value;
        }

        T insert(T data, int pos){
            if (pos == 0) {
                push_front(data);
            } else if (pos == nodes) {
                push_back(data);
            } else {
                Node* current = head;
                for (int i = 0; i < pos; ++i) {
                    current = current->next;
                }
                Node* prev = current->prev;
                Node* new_node = new Node(data);
                new_node->next = current;
                new_node->prev = prev;
                prev->next = new_node;
                current->prev = new_node;
                nodes++;
            }
            return data;
        }

        bool remove(int pos){
            if (pos < 0 || pos >= nodes) {
                return false;
            }
            if (pos == 0) {
                pop_front();
            } else if (pos == nodes - 1) {
                pop_back();
            } else {
                Node* current = head;
                for (int i = 0; i < pos; ++i) {
                    current = current->next;
                }
                Node* prev = current->prev;
                Node* next = current->next;
                prev->next = next;
                next->prev = prev;
                delete current;
                nodes--;
            }
            return true;
        }

        T& operator[](int pos){
            Node* current = head;
            for (int i = 0; i < pos; ++i) {
                current = current->next;
            }
            return current->data;
        }

        bool is_empty(){
            return nodes == 0;
        }

        int size(){
            return nodes;
        }

        void clear(){
            while (!is_empty()) {
                pop_front();
            }
        }

        void sort(){
            if (nodes <= 1) return;
            bool swapped;
            do {
                swapped = false;
                Node* current = head;
                for (int i = 0; i < nodes - 1; ++i) {
                    Node* next = current->next;
                    if (current->data > next->data) {
                        swap(current->data, next->data);
                        swapped = true;
                    }
                    current = next;
                }
            } while (swapped);
        }

        bool is_sorted(){
            if (nodes <= 1) return true;
            Node* current = head;
            for (int i = 0; i < nodes - 1; ++i) {
                if (current->data > current->next->data) {
                    return false;
                }
                current = current->next;
            }
            return true;
        }

        void reverse(){
            if (nodes <= 1) return;
            Node* current = head;
            for (int i = 0; i < nodes; ++i) {
                swap(current->next, current->prev);
                current = current->prev;
            }
            head = head->prev;
        }

        string name(){
            return "CircularList";
        }
};

#endif
