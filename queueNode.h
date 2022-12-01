//
// Created by Franchesca Lazaro on 5/26/2022.
//

#ifndef ASSIGNMENT5_QUEUENODE_H
#define ASSIGNMENT5_QUEUENODE_H
#include <iostream>
using namespace std;

class queueNode{
public:
    explicit queueNode(const string& data);
    string transaction;
    queueNode* next;
    queueNode* prev;
private:

};


#endif //ASSIGNMENT5_QUEUENODE_H
