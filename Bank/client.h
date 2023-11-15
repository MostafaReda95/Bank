#pragma once
#include "person.h"
#include <iostream>
#include <vector>
using namespace std;
class Client : public Person {
private:
    double balance;
    // static int lastAssignedId;
public:
    Client() : Person() {
        balance = 0;
    }
    Client(int id, string name, string password, double balance)
        : Person(id, name, password) {
        setBalance(balance);
    }
    // getters
    double getBalance() const { return balance; }
    // Setters
    void setBalance(double balance) {
        if (Validation::validatebalance(balance)) {
            this->balance = balance;
        }
        else {
            cout << balance << " Is Invalid balance! balance must be at least 1500."
                << endl;
            cout << "Enter Valid Balance : ";
            double balance;
            cin >> balance;
            setBalance(balance);
        }
    }
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited  " << amount << endl;
        }
        else {
            cout << amount << " Is Invalid amount" << endl;
            cout << "Please Enter Valid Amount : ";
            double validAmount;
            cin >> validAmount;
            deposit(validAmount);
        }
    }
    void withdraw(double amount) {
        if (amount > 0 && balance >= amount &&
            Validation::validatebalance(balance - amount)) {
            balance -= amount;
            cout << "Successfully withdrew " << amount << endl;
        }
        else {
            cout << "Error , Your balance is not enough to complete this transaction."
                << endl;
            cout << "Do you want to Withdraw another amount? (Y/N) : ";
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                cout << "Enter Amount to withdraw : ";
                double newAmount;
                cin >> newAmount;
                withdraw(newAmount);
            }
            else {
                cout << "Going back. \n";
            }
        }
    }
    void transferTo(double amount, Client& recipient) {
        if (amount > 0 && balance >= amount &&
            Validation::validatebalance(balance - amount)) {
            balance -= amount;
            recipient.deposit(amount);
            cout << " Successfully transferred " << amount << endl;
        }
        else {
            cout << "Error , Your balance is not enough to complete this transaction."
                << endl;
            cout << "Enter Vaild Amount To Transfer It To Another Client : ";
            double validAmount;
            cin >> validAmount;
            transferTo(validAmount, recipient);
        }
    }
    void checkbalance() {
        cout << "Now Your Currunt Balance Is : " << balance << endl;
    }

    void displayInfo() const {
        Person::printInfo();
        cout << "balance: " << balance << endl;
    }
    //static int getNextClientId();
};