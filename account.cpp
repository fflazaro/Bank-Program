//
// Created by Franchesca Lazaro on 5/31/2022.
//
#include "account.h"


account::account() = default;

account::account(const string& lN, const string& fN, const int& ID) {
    lastName = lN;
    firstName = fN;
    identifier = ID;
}
