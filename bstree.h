//
// Created by Franchesca Lazaro on 5/26/2022.
//

#ifndef ASSIGNMENT5_BSTREE_H
#define ASSIGNMENT5_BSTREE_H
#include <iostream>
#include "account.h"
using namespace std;

class bstree{
public:
    bstree();
    ~bstree();
    bool retrieve (const int &num, account* &accPtr);
    void display() const;
    void empty();
    bool isEmpty() const;
    bool insert(account* &acc);

private:
    struct Node{
        account* pAcct = nullptr;
        Node* right = nullptr;
        Node* left = nullptr;
    };
    Node* root = nullptr;
    Node* retrievedNode = nullptr;
    void insertData(Node* &r, account* acc);
    Node* getNewNode(account* &acc);
    void emptyPrivate(Node* n);
    void displayPrivate(Node* ptr) const;
    void traverse(const int &num, Node* n);
    //void traverse(const int& num, Node* rootPtr, account* acc);


};


#endif //ASSIGNMENT5_BSTREE_H
