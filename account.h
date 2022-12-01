//
// Created by Franchesca Lazaro on 5/26/2022.
//

#ifndef ASSIGNMENT5_ACCOUNT_H
#define ASSIGNMENT5_ACCOUNT_H
#include <iostream>
#include <vector>
using namespace std;

class account {
private:
    //Data members
    int moneyMarket{};
    int primeMoneyMarket{};
    int longTermBond{};
    int shortTermBond{};
    int indexBond{};
    int capitalValueFund{};
    int growthEquityFund{};
    int growthEquityFundl{};
    int valueFund{};
    int valueStockIndex{};

public:
    //Data members
    string firstName;
    string lastName;
    int identifier = 0;

    vector<string> money_market;
    vector<string> prime_money_market;
    vector<string> long_term_bond;
    vector<string> short_term_bond;
    vector<string> index_bond;
    vector<string> capital_value_fund;
    vector<string> growth_equity_fund;
    vector<string> growth_index_fund;
    vector<string> value_fund;
    vector<string> value_stock_index;

    int funds[10] {moneyMarket, primeMoneyMarket, longTermBond, shortTermBond, indexBond,
                   capitalValueFund, growthEquityFund, growthEquityFundl, valueFund, valueStockIndex};

    string fundNames[10]{"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Bond",
                         "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund", "Value Stock Index"};

    //Methods
    account();
    account(const string& lN, const string& fN, const int& ID);

};

#endif //ASSIGNMENT5_ACCOUNT_H
