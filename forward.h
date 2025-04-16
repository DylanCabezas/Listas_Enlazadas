#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class ForwardList : public List<T> {
    private:
        struct Node {
            T data;
            Node* next;

            Node() : data(T()), next(nullptr) { }

            Node(T value){ data = value; next = nullptr; }

            void killSelf(){
                // TODO      
            }    
        };

    private:
        Node* head;
        int nodes;

    public:
        ForwardList() : List<T>(), head(nullptr), nodes(0) { }

        ~ForwardList(){ clear();}

        T front(){
            return head->data;
        }

        T back(){
            Node* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            return temp->data;
        }

        void push_front(T data){
            Node* nodo = new Node(data);
            nodo->data = data;
            nodo->next = head;
            head = nodo;
        }

        void push_back(T data){
            Node* nodo = new Node(data);
            if (is_empty()) {
                head = nodo;
            } else {
                Node* temp = head;
                while(temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = nodo;
            }
            nodes++;
        }

        T pop_front(){
            Node* temp = head;
            T value = head->data;
            head = head->next;
            delete temp;
            nodes--;
            return value;
        }

        T pop_back(){
            T value;
            if (head -> next == nullptr) {
                value = head->data;
                delete head;
                head = nullptr;
            }
            else {
                Node* temp = head;
                while (temp->next->next != nullptr) {
                    temp = temp->next;
                }
                value = temp->next->data;
                delete temp -> next;
                temp -> next = nullptr;
            }
            nodes--;
            return value;
        }

        T insert(T data, int pos){
            Node* nodo = new Node(data);
            Node* temp = head;
            int i = 0;
            while (i++ < pos-1) temp = temp->next;
            nodo-> next = temp->next;
            temp->next = nodo;
            nodes++;
            return data;
        }

        bool remove(int pos){
            Node* temp = head;
            int i = 0;
            while (i++ < pos-1) temp = temp->next;
            Node* nodo = temp->next;
            temp->next = nodo->next;
            delete nodo;
            nodes--;
            return true;
        }

        T& operator[](int pos){
            Node* temp = head;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            return temp->data;
        }

        bool is_empty(){
            return head == nullptr;
        }

        int size(){
            return nodes;
        }

        void clear(){
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
        
        void sort(){
            if (!head || !head->next) return;
            // Usaremos bubble sort
            bool swapped;
            do {
                swapped = false;
                Node* current = head;
                while (current->next) {
                    if (current->data > current->next->data) {
                        std::swap(current->data, current->next->data);
                        swapped = true;
                    }
                    current = current->next;
                }
            } while (swapped);
        }

        bool is_sorted(){
            Node* temp = head;
            while (temp->next) {
                if (temp->data > temp->next->data)
                    return false;
                temp = temp->next;
            }
            return true;
        }

        void reverse(){
            Node* prev = nullptr;
            Node* current = head;
            Node* next = nullptr;
            while (current) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            head = prev;
        }

        std::string name(){
            return "ForwardList";
        }
        
};

#endif