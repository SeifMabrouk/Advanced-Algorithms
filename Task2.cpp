#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(int val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

Node* getTail(Node* cur) {
    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;
    return cur;
}

Node* partition(Node* low, Node* high) {
    int pivot = high->data;
    Node* i = low->prev;

    for (Node* j = low; j != high; j = j->next) {
        if (j->data <= pivot) {
            i = (i == nullptr) ? low : i->next;
            swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? low : i->next;
    swap(i->data, high->data);
    return i;
}

void _quickSort(Node* low, Node* high) {
    if (high != nullptr && low != high && low != high->next) {
        Node* p = partition(low, high);
        _quickSort(low, p->prev);
        _quickSort(p->next, high);
    }
}

void quickSort(DoublyLinkedList& list) {
    Node* tail = getTail(list.head);
    _quickSort(list.head, tail);
}

int main() {
    DoublyLinkedList dll;
    dll.append(9);
    dll.append(2);
    dll.append(6);
    dll.append(5);
    dll.append(8);

    cout << "Original List: ";
    dll.printList();

    quickSort(dll);

    cout << "Sorted List: ";
    dll.printList();

    return 0;
}

