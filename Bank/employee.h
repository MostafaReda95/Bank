#pragma once
#include "client.h"
#include "person.h"
#include <iostream>
#include <vector>
using namespace std;
class Employee : public Person {
protected:
    /*
        int id;
        string name;
        string password;
        */
    double salary;
    vector<Client> clients;

public:
    Employee() : Person() { salary = 0; }
    Employee(int id, string name, string password, double salary)
        : Person(id, name, password) {
        setId(id);
        setName(name);
        setPassword(password);
        setSalary(salary);
    }
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
    int getId() const { return id; }

    string getName() const { return name; }

    string getPassword() const { return password; }

    double getSalary() const { return salary; }

    // Display function
    void displayInfo() const {
        cout << "Employee ID: " << id << endl;
        cout << "Employee Name: " << name << endl;
        cout << "Employee Password: " << password << endl;
        cout << "Employee Salary: " << salary << endl;
    }
    void addClient(Client& client) { clients.push_back(client); }

    Client* searchClient(int id) {
        for (Client& client : clients) {
            if (client.getId() == id) {
                return &client;
            }
        }

        return nullptr;
    }

    void listClients() {
        for (Client& client : clients) {
            client.printInfo();
            cout << endl;
        }
    }

    void editClient(int id, string name, string password, double balance) {
        Client* client = searchClient(id);

        if (client != nullptr) {
            client->setName(name);
            client->setPassword(password);
            client->setBalance(balance);
        }
    }
};