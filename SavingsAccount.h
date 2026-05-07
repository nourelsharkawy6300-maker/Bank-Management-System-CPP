#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;
    double minBalance;

public:
    SavingsAccount(string accNum, double bal, double rate, double minB) 
        : Account(accNum, bal) {
        interestRate = rate;
        minBalance = minB;
    }

    void withdraw(double amount) override {
        if (status == "Active" && (balance - amount) >= minBalance) {
            balance -= amount;
            recordTransaction("Withdrawal", amount);
            cout << "Successfully withdrawn: " << amount << endl;
        } else {
            cout << "Withdrawal denied! Constraint: Min Balance " << minBalance << endl;
        }
    }

    void addMonthlyInterest() {
        if (status == "Active") {
            double interest = balance * (interestRate / 100);
            deposit(interest);
            cout << "Monthly interest added: " << interest << endl;
        }
    }
};

#endif
