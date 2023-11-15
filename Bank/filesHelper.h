#pragma once
#include <iostream>
#include <string>
#include<vector>
#include<fstream> 
#include"Client.h"
#include"Employee.h"
#include"Admin.h"
#include"Parser.h"
using namespace std;
class FilesHelper {
public:
    static void saveLast(string fileName, int id) {
        ofstream file(fileName);
        file << id << endl;
        file.close();
    }

    static int getLast(string fileName) {
        ifstream file(fileName);
        int id;
        file >> id;
        file.close();
        return id;
    }

    static void saveClient(Client c) {
        ofstream file("Clients.txt", ios::app);
        file << c.id << "," << c.name << "," << c.password << "," << c.balance << endl;
        file.close();
    }

    static void saveEmployee(string fileName, string lastIdFile, Employee e) {
        int id = getLast(lastIdFile);
        id++;
        ofstream file(fileName, ios::app);
        file << id << "," << e.name << "," << e.password << "," << e.salary << endl;
        file.close();
        saveLast(lastIdFile, id);
    }

    static vector<Client> getClients() {
        vector<Client> clients;
        ifstream file("Clients.txt");
        string line;
        while (getline(file, line)) {
            Client client = Parser::parseToClient(line);
            clients.push_back(client);
        }
        file.close();
        return clients;
    }

    static vector<Employee> getEmployees() {
        vector<Employee> employees;
        ifstream file("Employee.txt");
        string line;
        while (getline(file, line)) {
            Employee employee = Parser::parseToEmployee(line);
            employees.push_back(employee);
        }
        file.close();
        return employees;
    }

    static vector<Admin> getAdmins() {
        vector<Admin> admins;
        ifstream file("Admin.txt");
        string line;
        while (getline(file, line)) {
            Admin admin = Parser::parseToAdmin(line);
            admins.push_back(admin);
        }
        file.close();
        return admins;
    }

    static void clearFile(string fileName, string lastIdFile) {
        ofstream file(fileName, ios::trunc);
        file.close();
        saveLast(lastIdFile, 0);
    }
};