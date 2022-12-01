//
// Created by Franchesca Lazaro on 5/30/2022.
//
#include "bstree.h"

//Constructor
bstree::bstree() = default;

//Destructor
//Remember to put input
bstree::~bstree() {
    emptyPrivate(root);
}

void bstree::display() const {
    cout << endl;
    cout << "Processing Done. Final Balances: " << endl;
    displayPrivate(root);
}

void bstree::displayPrivate(Node *n) const {
    if (n != nullptr){
        cout << n->pAcct->firstName << " " << n->pAcct->lastName <<
        " Account ID: " << n->pAcct->identifier << endl;
        for (int i = 0; i <= 9; i++){
            cout << " ";
            cout << n->pAcct->fundNames[i] << ": $" << n->pAcct->funds[i] << endl;
        }
        cout << endl;
        displayPrivate(n->left);
        displayPrivate(n->right);
    }
}

void bstree::empty() {
    emptyPrivate(root);
    root = nullptr;
}

void bstree::emptyPrivate(Node *n) {
    if (n == nullptr){
        return;
    }
    emptyPrivate(n->left);
    emptyPrivate(n->right);
    delete n;
}

bool bstree::isEmpty() const {
    if (root == nullptr){
        return true;
    }
    return false;
}

bool bstree::insert(account* &acc) {
    insertData(root, acc);
    return true;
}
//< acc->identifier

void bstree::insertData(Node* &r, account* acc) {
    if (r == nullptr){
        r = getNewNode(acc);
        return;
    } else if (acc->identifier < r->pAcct->identifier){
        insertData(r->left, acc);
    } else if (acc->identifier > r->pAcct->identifier) {
        insertData(r->right, acc);
    }
}

bstree::Node *bstree::getNewNode(account *&acc) {
    Node* newNode = new Node();
    newNode->pAcct = acc;
    return newNode;
}

bool bstree::retrieve(const int &num, account* &accPtr) {
    traverse(num, root);
    if (retrievedNode != nullptr){
        accPtr = retrievedNode->pAcct;
        return true;
    } else{
        return false;
    }
}

void bstree::traverse(const int &num, Node *n) {
    if (n == nullptr){
        retrievedNode = nullptr;
        return;
    } else if (n->pAcct->identifier == num){
        retrievedNode = n;
        return;
    }
    traverse(num, n->left);
    traverse(num, n->right);
}







