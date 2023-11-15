#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Client.h"
#include "Employee.h"
#include "Admin.h"
using namespace std;

class Parser {
public:
    static vector<string> split(string line) {

        vector<string> result;

        return result;
    }

    static Client parseToClient(string line) {

        Client client(0, "", "", 0.0);

        return client;
    }

    static Employee parseToEmployee(string line) {

        Employee employee("", "", 0, 0.0);

        return employee;
    }

    static Admin parseToAdmin(string line) {

        Admin admin("", "", 0, 0.0);

        return admin;
    }
};
