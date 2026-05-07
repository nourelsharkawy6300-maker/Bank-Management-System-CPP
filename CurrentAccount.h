#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include "Account.h"

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(string accNum, double bal, double limit) 
        : Account(accNum, bal) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override {
        if (status == "Active" && amount <= (balance + overdraftLimit)) {
            balance -= amount;
            recordTransaction("Withdrawal", amount);
            cout << "Successfully withdrawn (Overdraft used if needed): " << amount << endl;
        } else {
            cout << "Withdrawal denied! Overdraft limit reached or account inactive." << endl;
        }
    }
};

#endif
