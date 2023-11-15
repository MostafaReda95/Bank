#pragma once
#include <vector>

class Admin;    // Forward declaration
class Employee; // Forward declaration
class Client;   // Forward declaration

class DataSourceInterface {
protected:
	virtual void addAdmin(const Admin&) = 0;
	virtual void addEmployee(const Employee&) = 0;
	virtual void addClient(const Client&) = 0;
	virtual std::vector<Client> getAllClients() = 0;
	virtual std::vector<Employee> getAllEmployees() = 0;
	virtual std::vector<Admin> getAllAdmins() = 0;
	virtual void removeAllClients() = 0;
	virtual void removeAllEmployees() = 0;
	virtual void removeAllAdmins() = 0;
};