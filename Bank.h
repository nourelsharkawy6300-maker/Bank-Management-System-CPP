#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;


struct Transaction {
    string type;
    double amount;
    string date;
    
    Transaction() {
        type = "";
        amount = 0.0;
        date = "";
    }
    
    Transaction(string t, double a, string d) : type(t), amount(a), date(d) {}
};


class Account {
protected:
    string accountNumber;
    double balance;
    string status; 
    
    Transaction history[50]; 
    int historyCount;

public:
    Account(string accNum, double bal) {
        accountNumber = accNum;
        balance = bal;
        status = "Active";
        historyCount = 0;
        logTransaction("Account Created", bal);
    }
    
    virtual ~Account() {}

    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    string getStatus() const { return status; }
    void setStatus(string s) { status = s; }

    void logTransaction(string type, double amount) {
        if (historyCount < 50) { 
            history[historyCount] = Transaction(type, amount, "Today"); 
            historyCount++;
        }
    }

    
    void clearBalance() {
        if (balance > 0) {
            logTransaction("Final Closure Withdrawal", balance);
            cout << "?? Withdrawing remaining balance: " << balance << "\n";
            balance = 0;
        }
    }

    virtual bool withdraw(double amount) {
        if (status != "Active") {
            cout << "? Error: Account is " << status << ". Cannot withdraw.\n";
            return false;
        }
        if (amount > balance) {
            cout << "? Error: Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        logTransaction("Withdrawal", amount);
        return true;
    }

    virtual void deposit(double amount) {
        if (status != "Active") {
            cout << "? Error: Account is " << status << ". Cannot deposit.\n";
            return;
        }
        balance += amount;
        logTransaction("Deposit", amount);
        cout << "? Deposit successful! New Balance: " << balance << "\n";
    }

    virtual void display() const {
        cout << "Account: " << accountNumber << " | Balance: " << balance 
             << " | Status: " << status << "\n";
    }
};


class SavingsAccount : public Account {
private:
    double minBalance;
public:
    SavingsAccount(string accNum, double bal) : Account(accNum, bal) {
        minBalance = 500.0;
    }

    bool withdraw(double amount) { 
        if (status != "Active") {
            cout << "? Error: Account is " << status << ".\n";
            return false;
        }
        if (balance - amount < minBalance) {
            cout << "? Error: Savings account must maintain a minimum balance of 500!\n";
            return false;
        }
        balance -= amount;
        logTransaction("Withdrawal", amount);
        cout << "? Withdrawal successful! New Balance: " << balance << "\n";
        return true;
    }
    
    void display() const { 
        cout << "[Savings] ";
        Account::display();
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(string accNum, double bal) : Account(accNum, bal) {}

    bool withdraw(double amount) { 
        if (status != "Active") {
            cout << "? Error: Account is " << status << ".\n";
            return false;
        }
        if (balance < amount) {
            cout << "? Error: Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        logTransaction("Withdrawal", amount);
        cout << "? Withdrawal successful! New Balance: " << balance << "\n";
        return true;
    }

    void display() const { 
        cout << "[Current] ";
        Account::display();
    }
};


class Customer {
private:
    string name;
    string nationalID;
    string phone;
    
    Account* accounts[10]; 
    int accountCount;

public:
    Customer() {
        name = "";
        nationalID = "";
        phone = "";
        accountCount = 0;
    }

    Customer(string n, string id, string p) : name(n), nationalID(id), phone(p) {
        accountCount = 0;
    }

    string getID() const { return nationalID; }
    string getName() const { return name; }
    string getPhone() const { return phone; }

    void addAccount(Account* acc) {
        if (accountCount < 10) {
            accounts[accountCount] = acc;
            accountCount++;
        } else {
            cout << "? Error: Maximum accounts reached for this customer!\n";
        }
    }

    void displayCustomerInfo() const {
        cout << "Customer: " << name << " | ID: " << nationalID << " | Phone: " << phone << "\n";
        if (accountCount == 0) {
            cout << "   -> No accounts linked yet.\n";
        } else {
            for (int i = 0; i < accountCount; ++i) {
                cout << "   -> ";
                accounts[i]->display();
            }
        }
    }
};

class Bank {
private:
    Customer customers[100];    
    int customerCount;

    Account* allAccounts[200];  
    int totalAccounts;

    bool isValidNationalID(string id) {
        if (id.length() != 14) return false;
        for (size_t i = 0; i < id.length(); ++i) {
            if (!isdigit(id[i])) return false;
        }
        return true;
    }

    bool isValidPhone(string phone) {
        if (phone.length() != 11) return false;
        if (phone[0] != '0' || phone[1] != '1') return false;
        for (size_t i = 0; i < phone.length(); ++i) {
             if (!isdigit(phone[i])) return false;
        }
        return true;
    }

    Account* findAccount(string accNum) {
        for (int i = 0; i < totalAccounts; ++i) {
            if (allAccounts[i]->getAccountNumber() == accNum) return allAccounts[i];
        }
        return NULL; 
    }

    Customer* findCustomer(string id) {
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].getID() == id) return &customers[i];
        }
        return NULL; 
    }

public:
    Bank() {
        customerCount = 0;
        totalAccounts = 0;
    }

    ~Bank() {
        for (int i = 0; i < totalAccounts; ++i) {
             delete allAccounts[i]; 
        }
    }

    void addCustomer(string name, string id, string phone) {
        if (customerCount >= 100) {
            cout << "? Error: Bank customer limit reached!\n";
            return;
        }
        if (!isValidNationalID(id)) {
            cout << "? Logic Error: National ID must be exactly 14 digits!\n";
            return;
        }
        if (!isValidPhone(phone)) {
            cout << "? Logic Error: Phone number must be 11 digits and start with 01!\n";
            return;
        }
        if (findCustomer(id) != NULL) { 
            cout << "? Error: Customer with this ID already exists!\n";
            return;
        }
        
        customers[customerCount] = Customer(name, id, phone);
        customerCount++;
        cout << "? Customer added successfully!\n";
    }

    void openAccount(string id, int type, string accNum, double bal) {
        if (totalAccounts >= 200) {
            cout << "? Error: Bank account limit reached!\n";
            return;
        }

        Customer* cust = findCustomer(id);
        if (!cust) {
            cout << "? Error: Customer not found. Please add customer first.\n";
            return;
        }
        if (findAccount(accNum) != NULL) { 
            cout << "? Error: Account number already exists!\n";
            return;
        }

        Account* newAcc = NULL; 
        if (type == 1) {
            newAcc = new SavingsAccount(accNum, bal);
        } else {
            newAcc = new CurrentAccount(accNum, bal);
        }

        allAccounts[totalAccounts] = newAcc;
        totalAccounts++;
        cust->addAccount(newAcc);
        
        cout << "? Account opened and linked to customer successfully!\n";
    }

    void depositToAccount(string accNum, double amt) {
        Account* acc = findAccount(accNum);
        if (acc) acc->deposit(amt);
        else cout << "? Error: Account not found!\n";
    }

    void withdrawFromAccount(string accNum, double amt) {
        Account* acc = findAccount(accNum);
        if (acc) acc->withdraw(amt);
        else cout << "? Error: Account not found!\n";
    }

    void transfer(string fromAccNum, string toAccNum, double amt) {
        Account* fromAcc = findAccount(fromAccNum);
        Account* toAcc = findAccount(toAccNum);

        if (!fromAcc || !toAcc) {
            cout << "? Error: One or both accounts not found!\n";
            return;
        }
        if (fromAcc->getStatus() != "Active" || toAcc->getStatus() != "Active") {
            cout << "? Error: Both accounts must be Active to transfer money.\n";
            return;
        }

        if (fromAcc->withdraw(amt)) { 
            toAcc->deposit(amt);
            cout << "? Transfer of " << amt << " completed successfully!\n";
        }
    }

    void searchCustomer(string id) {
        Customer* cust = findCustomer(id);
        if (cust) {
            cout << "\n--- Customer Found ---\n";
            cust->displayCustomerInfo();
        } else {
            cout << "? Customer not found!\n";
        }
    }

    void updateAccountStatus(string accNum, string status) {
        Account* acc = findAccount(accNum);
        if (acc) {
            if (acc->getStatus() == "Closed") {
                cout << "? Error: Closed accounts cannot be reactivated!\n";
            } else {
                acc->setStatus(status);
                cout << "? Account status updated to " << status << ".\n";
            }
        } else cout << "? Error: Account not found!\n";
    }

    
    void closeAccount(string accNum) {
        Account* acc = findAccount(accNum);
        if (acc) {
            if (acc->getStatus() == "Closed") {
                cout << "?? Account is already closed.\n";
            } else {
                
                if (acc->getBalance() > 0) {
                    cout << "?? Account has a balance of " << acc->getBalance() << ".\n";
                    acc->clearBalance(); 
                }
                
                acc->setStatus("Closed");
                cout << "? Account successfully closed and archived.\n";
            }
        } else cout << "? Error: Account not found!\n";
    }

    void saveDataToFile() {
        ofstream outFile("BankData.txt");
        if (outFile.is_open()) {
            outFile << "BANK SYSTEM BACKUP\n";
            outFile << "Total Customers: " << customerCount << "\n";
            outFile << "Total Accounts: " << totalAccounts << "\n";
            outFile.close();
        } else {
            cout << "? Error opening file for writing!\n";
        }
    }

    void displayAllData() {
        if (customerCount == 0) {
            cout << "No data in the system yet.\n";
            return;
        }
        for (int i = 0; i < customerCount; ++i) {
            customers[i].displayCustomerInfo();
            cout << "-----------------------\n";
        }
    }
};

#endif 
