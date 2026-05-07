#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

class Customer {
private:
    string name;
    string nationalID;
    string contactInfo;
    Account* accounts[5]; 
    int accountsCount;

public:
    Customer(string n, string id, string contact) {
        name = n;
        nationalID = id;
        contactInfo = contact;
        accountsCount = 0;
        for(int i = 0; i < 5; i++) accounts[i] = NULL;
    }

    void linkAccount(Account* acc) {
        if (accountsCount < 5) {
            accounts[accountsCount++] = acc;
        }
    }

    void showCustomerProfile() const {
        cout << "\n--- Customer: " << name << " | ID: " << nationalID << " ---" << endl;
        for (int i = 0; i < accountsCount; i++) {
            if (accounts[i] != NULL) {
                cout << "  - Account: " << accounts[i]->getAccountNumber() 
                     << " | Balance: " << accounts[i]->getBalance() 
                     << " | Status: " << accounts[i]->getStatus() << endl;
            }
        }
    }

    string getNationalID() const { return nationalID; }
    string getName() const { return name; }
};

#endif
