//
// Created by Franchesca Lazaro on 5/26/2022.
//
#include "bankQ.h"
using namespace std;

int bankQ::size() const {
    int count = 1;
    queueNode* temp = front;
    while (temp->next != nullptr){
        temp = temp->next;
        count++;
    }
    free(temp);
    return count;
}

void bankQ::dequeue() {
    queueNode* temp = front;
    if (front == nullptr) return;
    if (front == rear){
        front = rear = nullptr;
    } else {
        front = front->next;
    }
    free(temp);
}

void bankQ::enqueue(const string &data) {
    auto *temp = new queueNode(data);
    if (front == nullptr && rear == nullptr){
        front = rear = temp;
        return;
    } else {
        rear->next = temp;
        rear = temp;
    }
}

bankQ::bankQ() {
    front = nullptr;
    rear = nullptr;
}

bankQ::~bankQ() = default;

string bankQ::popTransaction() const {
    return front->transaction;
}

void bankQ::getFront() const{

}




