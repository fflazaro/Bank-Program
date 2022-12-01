//
// Created by Franchesca Lazaro on 5/30/2022.
//
#include "queueNode.h"

queueNode::queueNode(const string& data) {
    transaction = data;
    next = nullptr;
    prev = nullptr;
}
