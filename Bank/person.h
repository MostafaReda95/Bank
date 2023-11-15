#pragma once
#include "validate.h"
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    int id;
    string name;
    string password;

public:
    Person() { this->id = 0; }
    Person(int id, string name, string password) {
        setId(id);
        setName(name);
        setPassword(password);
    }
    // Setters
    void setId(int id) {
        if (id > 0) {
            this->id = id;
        }

        else {
            cout << "Invalid ID! ID must be greater than zero." << endl;
            cout << "Please Enter Valid Id : ";
            int validId;
            cin >> validId;
            setId(validId);
        }
    }
    void setName(string name) {
        if (Validation::validateName(name)) {
            this->name = name;
        }
        else {
            cout << "Invalid name! Name must be between 5 and 20 characters long and "
                "contain only alphabetic characters."
                << endl;
            cout << "Please enter a valid name: ";
            string validName;
            cin >> validName;
            setName(validName);
        }
    }

    void setPassword(string password) {
        if (Validation::validatePassword(password)) {
            this->password = password;
        }
        else {
            cout << "Invalid password! Password must be between 8 and 20 characters."
                << endl;
            cout << "Please enter a valid password: ";
            string validPassword;
            cin >> validPassword;
            setPassword(validPassword);
        }
    }

    void setvalidId(int id) { this->id = id; }

    // Getters
    string getName() const { return name; }

    string getPassword() const { return password; }

    int getId() const { return id; }

    void printInfo() const {
        cout << "id = " << id << endl;
        cout << "name = " << name << endl;
        cout << "password = " << password << endl;
    }
};