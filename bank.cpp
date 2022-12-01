//
// Created by Franchesca Lazaro on 5/26/2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "bank.h"
#include "bankQ.h"
#include "account.h"
#include "bstree.h"

using namespace std;

//Function to read in a file
int bank::readFile(const string &filename) {
    fstream myFile;
    myFile.open(filename.c_str());

    if(myFile.is_open()){
        string line;
        while (getline(myFile, line)){
           q.enqueue(line);
        }
        myFile.close();
    } else {
        cout << "Unable to open the file." << endl;
    }
    return 0;
}

//Default Constructor
bank::bank() = default;

//Override cout operator to print out bank details
ostream &operator<<(ostream &os, bank &bank) {
    return os;
}

//put for loop to read all transactions
//not just one at a time
void bank::readTransactions() {
    string transaction;
    while (q.front != nullptr){
        transaction = q.popTransaction();
        implementTransaction(transaction);
        q.dequeue();
    }
    tree.display();
    tree.empty();
}

//Constructor that takes in a file
bank::bank(const string &filename) {
    readFile(filename);
}

//Function that adds the correlating transaction to its vector
void bank::addTransactionList(const int& fund, const string& transaction) {
    if (fund == 0){
        accPtr->money_market.push_back(transaction);
    }
    if (fund == 1){
        accPtr->prime_money_market.push_back(transaction);
    }
    if (fund == 2){
        accPtr->long_term_bond.push_back(transaction);
    }
    if (fund == 3){
        accPtr->short_term_bond.push_back(transaction);
    }
    if (fund == 4){
        accPtr->index_bond.push_back(transaction);
    }
    if (fund == 5){
        accPtr->capital_value_fund.push_back(transaction);
    }
    if (fund == 6){
        accPtr->growth_equity_fund.push_back(transaction);
    }
    if (fund == 7){
        accPtr->growth_index_fund.push_back(transaction);
    }
    if (fund == 8){
        accPtr->value_fund.push_back(transaction);
    }
    if (fund == 9){
        accPtr->value_stock_index.push_back(transaction);
    }
}

//Function that reads a transaction and decides what to do with a fund based on the opening letter of the transaction
void bank::implementTransaction(const string& t) {
    stringstream ss(t);
    string line;
    //Get the first opening letter of the line
    ss >> line;

    if (line == "O"){
        //Retrieve the last name of the person
        ss >> line;
        string lN = line;

        //Retrieve the first name of the person
        ss >> line;
        string fN = line;

        //Retrieve the identifier of the person
        ss >> line;
        string temp = line;
        identifier = stoi(temp);

        //Check for a valid identifier
        int countDigit = floor(log10(identifier) + 1);
        if (countDigit > 4 || countDigit < 4){
            cout << "ERROR: Account does not have a valid identifier." << endl;
            return;
        }

        //Read in each digit of the identifier
        int tmp;
        int tmpIdentifier = identifier;
        while (tmpIdentifier > 0){
            for (int & i : identifierIndividual){
                tmp = tmpIdentifier % 10;
                i = tmp;
                tmpIdentifier /= 10;
            }
        }

        accPtr = new account(lN, fN, identifier);

        if (!tree.retrieve(identifier, accPtr)){
            tree.insert(accPtr);
        } else {
            cout << "Account " << identifier << " is already open. Transaction refused." << endl;
        }

    } else if (line == "D"){
        //Get the identifier with the unique ending
        ss >> line;
        string temp = line;
        int tempDigit = stoi(temp);

        //Get just the identifier
        int justIdentifier = tempDigit;
        justIdentifier /= 10;
        tree.retrieve(justIdentifier, retrievePtr);

        //Check for a valid identifier with an individual fund
        int countDigit = floor(log10(tempDigit) + 1);
        if (countDigit > 5 || countDigit < 5){
            cout << "ERROR: Account does not have a valid identifier with the individual fund." << endl;
            return;
        }

        //Check each digit of the identifier to make sure it is valid
        checkIdentity(tempDigit);

        int uniqueFund = tempDigit % 10;

        //Get the deposit number
        ss >> line;
        string temp2 = line;
        int deposit = stoi(temp2);

        //Cannot deposit an amount less than 0
        if (deposit < 0){
            cout << "ERROR: Cannot deposit " << deposit << " from " << retrievePtr->firstName << " " << retrievePtr->lastName << "'s account." << endl;
            return;
        }

        //For loop to add the deposit to the correct amount
        for (int i = 0; i <= 9; i++){
            if (i == uniqueFund){
                addTransactionList(uniqueFund, t);
                retrievePtr->funds[i] += deposit;
            }
        }

    } else if (line == "W"){
        //Get the identifier with the unique ending
        ss >> line;
        string temp = line;
        int tempDigit = stoi(temp);

        //Check for a valid identifier with an individual fund
        int countDigit = floor(log10(tempDigit) + 1);
        if (countDigit > 5 || countDigit < 5){
            cout << "ERROR: Account does not have a valid identifier with the individual fund." << endl;
            return;
        }

        //Check each digit of the identifier to make sure it is valid
        checkIdentity(tempDigit);

        int uniqueFund = tempDigit % 10;

        //Get the withdrawal number
        ss >> line;
        string temp2 = line;
        int withdrawal = stoi(temp2);

        //Cannot withdraw an amount less than 0
        if (withdrawal < 0){
            cout << "ERROR: Not enough funds to withdraw " << withdrawal << " from " << retrievePtr->firstName << " " << retrievePtr->lastName << "'s account." << endl;
            return;
        }

        for (int i = 0; i <= 9; i++){
            if (i == uniqueFund){
                //If user is trying to withdraw more than what is in the account, return
                if (retrievePtr->funds[i] - withdrawal < 0){
                    if (i == 0){
                        if (retrievePtr->funds[1] - withdrawal >= 0){
                            int tp = withdrawal - retrievePtr->funds[0];
                            retrievePtr->funds[1] -= tp;
                            retrievePtr->funds[0] = tp;
                            addTransactionList(0, t);
                            addTransactionList(1, t);
                            return;
                        }
                        cout << "ERROR: Not enough funds to withdraw " << withdrawal << " from " << retrievePtr->firstName << " " << retrievePtr->lastName << "'s account." << endl;
                        return;
                    } else if (i == 1){
                        if (retrievePtr->funds[0] - withdrawal >= 0) {
                            int tp = withdrawal - retrievePtr->funds[1];
                            retrievePtr->funds[0] -= tp;
                            retrievePtr->funds[1] = tp;
                            addTransactionList(0, t);
                            addTransactionList(1, t);
                            return;
                        }
                        cout << "ERROR: Not enough funds to withdraw " << withdrawal << " from " << retrievePtr->firstName << " " << retrievePtr->lastName << "'s account." << endl;
                        return;
                    } else {
                        cout << "ERROR: Not enough funds to withdraw " << withdrawal << " from " << retrievePtr->firstName << " " << retrievePtr->lastName << "'s account." << endl;
                        return;
                    }
                }
                addTransactionList(uniqueFund, t);
                retrievePtr->funds[i] -= withdrawal;
            }
        }

    } else if (line == "T"){
        //Get the first fund
        ss >> line;
        string temp = line;
        int tempDigit = stoi(temp);

        //Check for a valid identifier with an individual fund
        int countDigit = floor(log10(tempDigit) + 1);
        if (countDigit > 5 || countDigit < 5){
            cout << "ERROR: Account does not have a valid identifier/individual fund." << endl;
            return;
        }

        //Check each digit of the identifier to make sure it is valid
        checkIdentity(tempDigit);

        int firstFund = tempDigit % 10;

        //Get the transfer amount
        ss >> line;
        temp = line;
        int transfer = stoi(temp);

        //Get the second fund
        ss >> line;
        temp = line;
        tempDigit = stoi(temp);

        countDigit = floor(log10(tempDigit) + 1);
        if (countDigit > 5 || countDigit < 5){
            cout << "ERROR: Account does not have a valid identifier with the individual fund." << endl;
            return;
        }

        //Check each digit of the identifier to make sure it is valid
        checkIdentity(tempDigit);

        int secondFund = tempDigit % 10;

        for (int i = 0; i <= 9; i++){
           if (i == firstFund){
               //If there is not a sufficient amount in the first fund to transfer, return
               if (retrievePtr->funds[i] - transfer < 0){
                   cout << "ERROR: First fund does not have sufficient amount to transfer to second fund." << endl;
                   return;
               }
               addTransactionList(firstFund, t);
               retrievePtr->funds[i] -= transfer;
           } else if (i == secondFund){
               addTransactionList(secondFund, t);
               retrievePtr->funds[i] += transfer;
           }
        }

    } else if (line == "H"){
        //Get the second digit
        ss >> line;
        string temp = line;
        int tempDigit = stoi(temp);
        int countDigit = floor(log10(tempDigit) + 1);
        int uniqueFund = tempDigit % 10;

        if (countDigit == 5){
            for (int i = 0; i <= 9; i++){
                if (i == uniqueFund){
                    cout << retrievePtr->fundNames[i] << " for "<< retrievePtr->firstName << " " << retrievePtr->lastName << ": "<< "$" << retrievePtr->funds[i] << endl;
                    printTransaction(i);
                }
            }
        } else {
            //Print out the transaction history of all the funds
            cout << "Transaction History for " << retrievePtr->firstName << " " << retrievePtr->lastName << " by fund." << endl;
            for (int i = 0; i <= 9; i++){
                cout << retrievePtr->fundNames[i] << ": $" << retrievePtr->funds[i] << endl;
                printTransaction(i);
            }
            cout << endl;
        }
    }
}

void bank::checkIdentity(const int &num) const {
    int tmp;
    int tmpIdentifier = num;
    tmpIdentifier /= 10;
    while (tmpIdentifier > 0){
        for (int i : identifierIndividual){
            tmp = tmpIdentifier % 10;
            if (tmp != i){
                cout << "ERROR: Account " << tmpIdentifier << " not found. Transferal refused." << endl;
                return;
            }
            tmpIdentifier /= 10;
        }
    }
}

//Function that prints all the transactions that occurred in a fund
void bank::printTransaction(const int &fund) {
    if (fund == 0){
        for(auto & i : accPtr->money_market) {
            cout << "--> " << i << endl;
        }
    }
    if (fund == 1){
        for(auto & i : accPtr->prime_money_market) {
            cout << "--> " << i << endl;
        }
    }
    if (fund == 2){
        for(auto & i : accPtr->long_term_bond) {
            cout << "--> " << i << endl;
        }
    }
    if (fund == 3){
        for(auto & i : accPtr->short_term_bond) {
            cout << "--> " << i << endl;
        }
    }
    if (fund == 4){
        for(auto & i : accPtr->index_bond) {
            cout << "--> " << i << endl;
        }
    }
    if (fund == 5){
        for(auto & i : accPtr->capital_value_fund) {
            cout << "--> " << i << endl;
        }
    }
    if (fund == 6){
        for(auto & i : accPtr->growth_equity_fund) {
            cout << "--> " << i << endl;
        }
    }
    if (fund == 7){
        for(auto & i : accPtr->growth_index_fund) {
            cout << "--> " << i << endl;
        }
    }
    if (fund == 8){
        for(auto & i : accPtr->value_fund) {
            cout << "--> " << i << endl;
        }
    }
    if (fund == 9){
        for(auto & i : accPtr->value_stock_index) {
            cout << "--> " << i << endl;
        }
    }
}


