//
// Created by Franchesca Lazaro on 5/26/2022.
//

#ifndef ASSIGNMENT5_BANK_H
#define ASSIGNMENT5_BANK_H
#include <iostream>
#include "bankQ.h"
#include "bstree.h"

using namespace std;

class bank{
private:
    //Data members
    int identifier = 0;

    int identOne = 0;
    int identTwo = 0;
    int identThree = 0;
    int identFour = 0;
    int identifierIndividual[4] {identOne, identTwo, identThree, identFour};

    account* accPtr = nullptr;
    account* retrievePtr = nullptr;

    bankQ q;
    bstree tree;

    //Methods
    void addTransactionList(const int& fund, const string& transaction);
    void printTransaction(const int& fund);
    void checkIdentity(const int& num) const;
    void printFinalBalances();
public:

    //Methods
    bank();
    explicit bank(const string &filename);
    friend ostream &operator<<(ostream &os, bank &bank);
    int readFile(const string &filename);
    void implementTransaction(const string &t);
    void readTransactions();

};

#endif //ASSIGNMENT5_BANK_H
