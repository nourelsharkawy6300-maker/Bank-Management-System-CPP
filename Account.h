#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <sstream>
#include "Transaction.h"

using namespace std;

inline string intToString(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}

class Account {
protected:
    string accountNumber;
    string status;
    double balance;
    Transaction transactions[50];
    int transactionCount;

public:
    Account(string accNum, double intBalance) {
        accountNumber = accNum;
        balance = intBalance;
        status = "Active";
        transactionCount = 0;
    }

    virtual ~Account() {}

    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    string getStatus() const { return status; }
    
    void setStatus(string newStatus) { status = newStatus; }

    void recordTransaction(string type, double amt) {
        if (transactionCount < 50) {
            string id = "TRX" + intToString(transactionCount + 101);
            transactions[transactionCount] = Transaction(id, type, amt, balance);
            transactionCount++;
        }
    }

    void deposit(double amount) {
        if (amount > 0 && status == "Active") {
            balance += amount;
            recordTransaction("Deposit", amount);
            cout << "Successfully deposited: " << amount << endl;
        }
    }

    virtual void withdraw(double amount) = 0;

    void viewAllTransactions() const {
        cout << "\n--- Transactions for Account: " << accountNumber << " ---" << endl;
        for (int i = 0; i < transactionCount; i++) {
            transactions[i].getTransactionDetails();
        }
    }
};

#endif
