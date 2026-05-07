#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Transaction {
private:
    string transactionID;
    string type;
    double amount;
    string timestamp;
    double resultingBalance;

public:
    Transaction() {
        transactionID = ""; type = ""; amount = 0; resultingBalance = 0; timestamp = "";
    }

    Transaction(string id, string t, double amt, double resBal) {
        transactionID = id;
        type = t;
        amount = amt;
        resultingBalance = resBal;
        time_t now = time(0);
        timestamp = ctime(&now);
        if (!timestamp.empty()) timestamp.erase(timestamp.length() - 1);
    }

    void getTransactionDetails() const {
        if (transactionID != "") {
            cout << "[ID: " << transactionID << " | Type: " << type 
                 << " | Amount: " << amount << " | Balance: " << resultingBalance 
                 << " | Date: " << timestamp << "]\n";
        }
    }
};

#endif
