#pragma once
#include <iostream>
using namespace std;
class Validation {
public:
    static bool validateName(const string& name) {
        if (name.size() < 5 || name.size() > 20) {
            return false;
        }
        for (char c : name) {
            if (!isalpha(c)) {
                return false;
            }
        }
        return true;
    }
    static bool validatePassword(const string& password) {
        if (password.size() < 8 || password.size() > 20) {
            return false;
        }
        return true;
    }
    static bool validatebalance(double balance) {
        return balance >= 1500;
    }
    static bool validateSalary(double salary) {
        return salary >= 5000;
    }
};
