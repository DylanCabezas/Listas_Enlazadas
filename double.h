#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include "list.h"

using namespace std;

template <typename T>
class DoubleList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(){
            next = nullptr;
            prev = nullptr;
        }

        Node(T value){
            data = value;
            next = nullptr;
            prev = nullptr;
        }

        void killSelf() {
            delete this;
        }
    };

private:
    Node* head;
    Node* tail;
    int nodes;

public:
    DoubleList() : head(nullptr), tail(nullptr), nodes(0) {}

    ~DoubleList() {
        clear();
    }

    T front() {
        if (head == nullptr) throw out_of_range("Lista vacía");
        return head->data;
    }

    T back() {
        if (tail == nullptr) throw out_of_range("Lista vacía");
        return tail->data;
    }

    void push_front(T data) {
        Node* new_node = new Node(data);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        nodes++;
    }

    void push_back(T data) {
        Node* new_node = new Node(data);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        nodes++;
    }

    T pop_front() {
        if (head == nullptr) throw out_of_range("Lista vacía");
        Node* temp = head;
        T value = head->data;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        delete temp;
        nodes--;
        return value;
    }

    T pop_back() {
        if (tail == nullptr) throw out_of_range("Lista vacía");
        Node* temp = tail;
        T value = tail->data;
        tail = tail->prev;
        if (tail != nullptr) tail->next = nullptr;
        delete temp;
        nodes--;
        return value;
    }

    bool insert(T data, int pos) {
        if (pos < 0 || pos > nodes) throw out_of_range("Posición fuera de rango");
        if (pos == 0) {
            push_front(data);
        } else if (pos == nodes) {
            push_back(data);
        } else {
            Node* new_node = new Node(data);
            Node* temp = head;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            new_node->prev = temp->prev;
            new_node->next = temp;
            temp->prev->next = new_node;
            temp->prev = new_node;
            nodes++;
        }
        return true;
    }

    bool remove(int pos) {
        if (pos < 0 || pos >= nodes) return false;
        if (pos == 0) {
            pop_front();
        } else if (pos == nodes - 1) {
            pop_back();
        } else {
            Node* temp = head;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            nodes--;
        }
        return true;
    }

    T& operator[](int pos) {
        if (pos < 0 || pos >= nodes) throw out_of_range("Posición del elemento fuera del rango");
        Node* temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool is_empty() {
        return nodes == 0;
    }

    int size() {
        return nodes;
    }

    void clear() {
        while (head != nullptr) {
            pop_front();  // Elimina el primer nodo
        }
    }

    void sort() {
        for (Node* i = head; i != nullptr; i = i->next) {
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (i->data > j->data) {
                    T temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
    }

    bool is_sorted() {
        if (head == nullptr) return true;
        Node* temp = head;
        while (temp->next != nullptr) {
            if (temp->data > temp->next->data) {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }

    void reverse() {
        Node* temp = nullptr;
        Node* current = head;
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp != nullptr) {
            head = temp->prev;
        }
    }

    string name() {
        return "DoubleList";
    }
};

#endif
