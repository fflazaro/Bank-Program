#include <iostream>
#include "bank.h"
#include "bstree.h"

using namespace std;

int main() {
    bank b("BankTransIn.txt");
    b.readTransactions();
    return 0;
}
