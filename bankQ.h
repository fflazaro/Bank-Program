//
// Created by Franchesca Lazaro on 5/26/2022.
//

#ifndef ASSIGNMENT5_BANKQ_H
#define ASSIGNMENT5_BANKQ_H
#include <iostream>
#include "queueNode.h"
using namespace std;

class bankQ{
public:
    //Variables
    queueNode* front;
    queueNode* rear;

    //Methods
    bankQ();
    ~bankQ();
    int size() const;
    void dequeue();
    string popTransaction() const;
    void enqueue(const string& data);
    void getFront() const;
private:
    string transaction;
};
#endif //ASSIGNMENT5_BANKQ_H
