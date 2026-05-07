#include <iostream>
#include <string>
#include <limits> 
#include "Bank.h"

using namespace std;


void pauseScreen() {
    cout << "\nPress Enter to return to the Main Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    Bank bank;
    int choice;
    do {
        system("cls"); 
        cout << "=========================================\n";
        cout << "        ?? BANK MANAGEMENT SYSTEM ??       \n";
        cout << "=========================================\n";
        cout << "1. Add New Customer\n";
        cout << "2. Open New Account\n";
        cout << "3. Deposit Money\n";        
        cout << "4. Withdraw Money\n";       
        cout << "5. Transfer Money\n";
        cout << "6. Search Customer\n";
        cout << "7. Update Account Status\n";
        cout << "8. Close Account\n";
        cout << "9. Save Data to File (Bonus)\n";
        cout << "10. Display All System Data\n";
        cout << "11. Exit\n";
        cout << "=========================================\n";
        cout << "Enter your choice (1-11): ";
        
        
        if (!(cin >> choice)) {
            cout << "? Invalid Input! Please enter a number.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            pauseScreen();
            continue; 
        }

        switch (choice) {
            case 1: {
                string name, id, phone;
                cout << "Enter Customer Name: ";
                cin.ignore(); 
                getline(cin, name);
                cout << "Enter National ID: ";
                cin >> id;
                cout << "Enter Phone Number: ";
                cin >> phone;
                bank.addCustomer(name, id, phone);
                break;
            }
            case 2: {
                string id, accNum;
                int type;
                double bal;
                
                cout << "Enter Customer National ID: ";
                cin >> id;

                do {
                    cout << "Enter Account Type (1 for Savings, 2 for Current): ";
                    cin >> type;
                    if (type != 1 && type != 2) cout << "? Invalid type! Must be 1 or 2.\n";
                } while (type != 1 && type != 2);

                cout << "Enter New Account Number (e.g., ACC101): ";
                cin >> accNum;

                do {
                    cout << "Enter Initial Balance: ";
                    cin >> bal;
                    if (bal < 0) cout << "? Balance cannot be negative!\n";
                    else if (type == 1 && bal < 500) cout << "? Savings account requires at least 500 initial balance!\n";
                } while (bal < 0 || (type == 1 && bal < 500));

                bank.openAccount(id, type, accNum, bal);
                break;
            }
            case 3: { 
                string accNum;
                double amt;
                cout << "Enter Account Number: ";
                cin >> accNum;
                do {
                    cout << "Enter Amount to Deposit: ";
                    cin >> amt;
                    if (amt <= 0) cout << "? Amount must be positive!\n";
                } while (amt <= 0);
                bank.depositToAccount(accNum, amt);
                break;
            }
            case 4: { 
                string accNum;
                double amt;
                cout << "Enter Account Number: ";
                cin >> accNum;
                do {
                    cout << "Enter Amount to Withdraw: ";
                    cin >> amt;
                    if (amt <= 0) cout << "? Amount must be positive!\n";
                } while (amt <= 0);
                bank.withdrawFromAccount(accNum, amt);
                break;
            }
            case 5: { 
                string fromAcc, toAcc;
                double amt;
                cout << "Enter Sender Account Number: ";
                cin >> fromAcc;
                cout << "Enter Receiver Account Number: ";
                cin >> toAcc;

                if (fromAcc == toAcc) {
                    cout << "? Error: Cannot transfer money to the same account!\n";
                    break;
                }

                do {
                    cout << "Enter Amount to Transfer: ";
                    cin >> amt;
                    if (amt <= 0) cout << "? Amount must be greater than zero!\n";
                } while (amt <= 0);

                bank.transfer(fromAcc, toAcc, amt);
                break;
            }
            case 6: { 
                string id;
                cout << "Enter Customer National ID to search: ";
                cin >> id;
                bank.searchCustomer(id);
                break;
            }
            case 7: { 
                string accNum, status;
                int statusChoice;
                cout << "Enter Account Number: ";
                cin >> accNum;

                do {
                    cout << "Choose New Status:\n1. Active\n2. Frozen\nEnter (1 or 2): ";
                    cin >> statusChoice;
                    if (statusChoice == 1) status = "Active";
                    else if (statusChoice == 2) status = "Frozen";
                    else cout << "? Invalid choice! Enter 1 or 2.\n";
                } while (statusChoice != 1 && statusChoice != 2);

                bank.updateAccountStatus(accNum, status);
                break;
            }
            case 8: { 
                string accNum;
                cout << "Enter Account Number to Close: ";
                cin >> accNum;
                bank.closeAccount(accNum);
                break;
            }
            case 9: {
                bank.saveDataToFile();
                break;
            }
            case 10: {
                bank.displayAllData();
                break;
            }
            case 11: {
                cout << "?? Exiting the system. Thank you!\n";
                break;
            }
            default: {
                cout << "? Invalid choice! Please enter a number between 1 and 11.\n";
                break;
            }
        }
        
        if (choice != 11) {
            pauseScreen();
        }

    } while (choice != 11);

    return 0;
}
