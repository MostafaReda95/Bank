#pragma once
#include "employee.h" 
#include "client.h"   
#include <iostream>
#include <vector>
using namespace std;

class Admin : public Employee {
public:
    // Constructors

    Admin() {} // Default constructor

    Admin(int id, string name, string password, double salary)
        : Employee(id, name, password, salary) {}

    // Setters
    void setSalary(double salary) {
        if (Validation::validateSalary(salary)) {
            this->salary = salary;
        }
        else {
            cout << salary << " is an invalid salary! Salary must be at least 5000."
                << endl;
            cout << "Please enter a valid salary: ";
            double validSalary;
            cin >> validSalary;
            setSalary(validSalary);
        }
    }
    // Getters

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getPassword() const {
        return password;
    }

    double getSalary() const {
        return salary;
    }

    // Display function
    void displayInfo() {
        cout << "Admin ID: " << id << endl;
        cout << "Admin Name: " << name << endl;
        cout << "Admin Password: " << password << endl;
        cout << "Admin Salary: " << salary << endl;
    }

    // Member functions

    void addClient(Client& client) {
        clients.push_back(client);
    }

    Client* searchClient(int id) {
        for (auto& client : clients) {
            if (client.getId() == id) {
                return &client;
            }
        }
        return nullptr;
    }

    void listClients() {
        for (const auto& client : clients) {
            cout << "Client ID: " << client.getId() << endl;
            cout << "Client Name: " << client.getName() << endl;
            cout << "Client Balance: " << client.getBalance() << endl;
        }
    }

    void editClient(int id, string name, string password, double balance) {
        Client* client = searchClient(id);
        if (client != nullptr) {
            client->setName(name);
            client->setPassword(password);
            client->setBalance(balance);
        }
        else {
            cout << "Could not find client with ID: " << id << endl;
        }
    }

    void addEmployee(Employee& employee) {
        employees.push_back(employee);
    }

    Employee* searchEmployee(int id) {
        for (auto& employee : employees) {
            if (employee.getId() == id) {
                return &employee;
            }
        }
        return nullptr;
    }

    void editEmployee(int id, string name, string password, double salary) {
        Employee* employee = searchEmployee(id);
        if (employee != nullptr) {
            employee->setName(name);
            employee->setPassword(password);
            employee->setSalary(salary);
        }
        else {
            cout << "Could not find employee with ID: " << id << endl;
        }
    }

    void listEmployees() {
        for (const auto& employee : employees) {
            cout << "Employee ID: " << employee.getId() << endl;
            cout << "Employee Name: " << employee.getName() << endl;
            cout << "Employee Salary: " << employee.getSalary() << endl;
        }
    }

private:
    vector<Client> clients;   // Container for clients
    vector<Employee> employees; // Container for employees

    // Validation functions (you need to define these)
    bool validateName(const string& name) {
        // Implement name validation logic
        return true; // Change this to your validation logic
    }

    bool validatePassword(const string& password) {
        // Implement password validation logic
        return true; // Change this to your validation logic
    }
};