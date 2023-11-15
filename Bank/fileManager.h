#include "admin.h"
#include "client.h"
#include "dataSourceInterface.h"
#include "employee.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class FileManager : public DataSourceInterface {
public:
    Client searchClientById(int clientId);
    Employee searchEmployeeById(int employeeId);
    void listAllClients();
    void listAllEmployees();
    // after withdraw ubdate balance
    void withdrawAmount(int clientId, double withdrawAmount);
    void depositeAmount(int clientId, double depositeAmount);
    void transferAmount(int senderId, const int& recipientId,
        double transferAmount);
    bool isClientIdValid(const int& clientId);
    void printWELCOME();
    void printWE();
    void printBANK();
    void addClient(const Client& client) override {
        ofstream file("clients.txt", ios::app);
        if (file.is_open()) {
            file << client.getId() << "," << client.getName() << ","
                << client.getPassword() << "," << client.getBalance() << endl;
            file.close();
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }
    // Remove One Client
    void removeClient(int clientId) {
        vector<Client> clients = getAllClients();
        for (auto it = clients.begin(); it != clients.end();) {
            if (it->getId() == clientId) {
                it = clients.erase(it);
            }
            else {
                ++it;
            }
        }
        removeAllClients();
        for (const auto& client : clients) {
            addClient(client);
        }
    }
    // Add Employee
    void addEmployee(const Employee& employee) override {
        ofstream file("employees.txt", ios::app);
        if (file.is_open()) {
            file << employee.getId() << "," << employee.getName() << ","
                << employee.getPassword() << "," << employee.getSalary() << endl;
            file.close();
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }
    // Remove Employee
    void removeEmployee(int employeeId) {
        vector<Employee> employees = getAllEmployees();
        for (auto it = employees.begin(); it != employees.end();) {
            if (it->getId() == employeeId) {
                it = employees.erase(it);
            }
            else {
                ++it;
            }
        }
        removeAllEmployees();
        for (const auto& employee : employees) {
            addEmployee(employee);
        }
    }
    void addAdmin(const Admin& admin) override {
        ofstream file("admins.txt", ios::out | ios::app);
        if (file.is_open()) {
            file << admin.getId() << "," << admin.getName() << ","
                << admin.getPassword() << "," << admin.getSalary() << endl;
            file.close();
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }

    // Remove Admin
    void removeAdmin(int adminId) {
        vector<Admin> admins = getAllAdmins();
        for (auto it = admins.begin(); it != admins.end();) {
            if (it->getId() == adminId) {
                it = admins.erase(it);
            }
            else {
                ++it;
            }
        }
        // Remove all Admins
        removeAllAdmins();
        for (const auto& admin : admins) {
            addAdmin(admin);
        }
    }
    // Function to toggle password visibility
    void togglePasswordVisibility(string& password, bool& showPassword) {
        showPassword = !showPassword;
        system("cls");
        cout << "Enter Admin Password: ";
        if (showPassword) {
            cout << password;
        }
        else {
            for (size_t i = 0; i < password.size(); ++i) {
                cout << '*';
            }
        }
    }
    vector<Client> getAllClients() override {
        vector<Client> clients;
        ifstream file("clients.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<string> clientData = split(line);
                if (clientData.size() == 4) {
                    int id = stoi(clientData[0]);
                    string name = clientData[1];
                    string password = clientData[2];
                    double balance = stod(clientData[3]);
                    clients.push_back(Client(id, name, password, balance));
                }
            }
            file.close();
        }
        else {
            cout << "Unable to open file." << endl;
        }
        return clients;
    }
    vector<Employee> getAllEmployees() override {
        vector<Employee> employees;
        ifstream file("employees.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<string> employeeData = split(line);
                if (employeeData.size() == 4) {
                    int id = stoi(employeeData[0]);
                    string name = employeeData[1];
                    string password = employeeData[2];
                    double salary = stod(employeeData[3]);
                    employees.push_back(Employee(id, name, password, salary));
                }
            }
            file.close();
        }
        else {
            cout << "Unable to open file." << endl;
        }
        return employees;
    }
    vector<Admin> getAllAdmins() override {
        vector<Admin> admins;
        ifstream file("admins.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<string> adminData = split(line);
                if (adminData.size() == 4) {
                    int id = stoi(adminData[0]);
                    string name = adminData[1];
                    string password = adminData[2];
                    double salary = stod(adminData[3]);
                    admins.push_back(Admin(id, name, password, salary));
                }
            }
            file.close();
        }
        else {
            cout << "Unable to open file." << endl;
        }
        return admins;
    }
    //  check Admin Password
    bool checkAdminPassword(int adminId, const string& enterdPassword) {
        vector<Admin> admins = getAllAdmins();
        for (const auto& admin : admins) {
            if (admin.getId() == adminId && admin.getPassword() == enterdPassword) {
                return true;
            }
        }
        return false;
    }
    // Update Admin Password
    void updateAdminPassword(int adminId, const string& newPassword) {
        vector<Admin> admins = getAllAdmins();
        for (auto& admin : admins) {
            if (admin.getId() == adminId) {
                admin.setPassword(newPassword);
                break;
            }
        }
        removeAllAdmins();
        for (const auto& admin : admins) {
            addAdmin(admin);
        }
    }
    //  check Client Password
    bool checkClientPassword(int clientId, const string& enterdPassword) {
        vector<Client> clients = getAllClients();
        for (const auto& client : clients) {
            if (client.getId() == clientId &&
                client.getPassword() == enterdPassword) {
                return true;
            }
        }
        return false;
    }
    // Update Client Password
    void updateClientPassword(int clientId, const string& newPassword) {
        vector<Client> clients = getAllClients();
        for (auto& client : clients) {
            if (client.getId() == clientId) {
                client.setPassword(newPassword);
                break;
            }
        }
        removeAllClients();
        for (const auto& client : clients) {
            addClient(client);
        }
    }
    void removeAllClients() override { clsFile("clients.txt"); }

    void removeAllEmployees() override { clsFile("employees.txt"); }

    void removeAllAdmins() override { clsFile("admins.txt"); }

private:
    vector<string> split(string line) {
        vector<string> result;
        stringstream ss(line);
        string item;
        while (getline(ss, item, ',')) {
            result.push_back(item);
        }
        return result;
    }

    void clsFile(string fileName) {
        ofstream file(fileName, ios::trunc);
        if (file.is_open()) {
            file.close();
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }
    
};
// Search For Clients
Client FileManager::searchClientById(int clientId) {
    ifstream file("clients.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> clientData = split(line);
            if (clientData.size() == 4) {
                int id = stoi(clientData[0]);
                if (id == clientId) {
                    string name = clientData[1];
                    string password = clientData[2];
                    double balance = stod(clientData[3]);
                    file.close();
                    return Client(id, name, password, balance);
                }
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file." << endl;
    }

    // If the client with the specified ID is not found, return a
    // default-constructed client
    return Client();
}
// Search For Employee
Employee FileManager::searchEmployeeById(int employeeId) {
    ifstream file("employees.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> employeeData = split(line);
            if (employeeData.size() == 4) {
                int id = stoi(employeeData[0]);
                if (id == employeeId) {
                    string name = employeeData[1];
                    string password = employeeData[2];
                    double salary = stod(employeeData[3]);
                    file.close();
                    return Employee(id, name, password, salary);
                }
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file." << endl;
    }

    // If the client with the specified ID is not found, return a
    // default-constructed client
    return Employee();
}
// List All Clients
void FileManager::listAllClients() {
    vector<Client> clients = getAllClients();

    cout << "=======================\n";
    cout << "List of All Clients\n";
    cout << "=======================\n";

    for (const auto& client : clients) {
        client.displayInfo();
        cout << "-----------------------\n";
    }

    cout << "Press Enter To Continue....\n";
    cin.ignore();
    cin.get();
    system("cls");
}
// List All Employess
void FileManager::listAllEmployees() {
    vector<Employee> employees = getAllEmployees();
    cout << "=======================\n";
    cout << "List of All Employees\n";
    cout << "=======================\n";

    for (const auto& employee : employees) {
        employee.displayInfo();
        cout << "-----------------------\n";
    }
    cout << "Press Enter To Continue....\n";
    cin.ignore();
    cin.get();
    system("cls");
}
// Withdraw Amount for client
void FileManager::withdrawAmount(int clientId, double withdrawAmount) {
    vector<Client> clients = getAllClients();
    for (auto& client : clients) {
        if (client.getId() == clientId) {
            client.setBalance(withdrawAmount);
            break;
        }
    }
    removeAllClients();
    for (const auto& client : clients) {
        addClient(client);
    }
}
// Deposit Amount for client
void FileManager::depositeAmount(int clientId, double depositeAmount) {
    vector<Client> clients = getAllClients();
    for (auto& client : clients) {
        if (client.getId() == clientId) {
            client.setBalance(depositeAmount);
            break;
        }
    }
    removeAllClients();
    for (const auto& client : clients) {
        addClient(client);
    }
}
// Transfer Amount for client
void FileManager::transferAmount(int senderId, const int& recipientId,
    double transferAmount) {
    vector<Client> clients = getAllClients();
    // Find the sender
    auto senderIt =
        find_if(clients.begin(), clients.end(), [senderId](const Client& client) {
        return client.getId() == senderId;
            });
    // Find the recipient
    auto recipientIt = find_if(clients.begin(), clients.end(),
        [recipientId](const Client& client) {
            return client.getId() == (recipientId);
        });
    // Check if both sender and recipient are valid
    if (senderIt != clients.end() && recipientIt != clients.end()) {
        // Check if the sender has enough balance
        if (senderIt->getBalance() >= transferAmount) {
            // Update balances
            senderIt->withdraw(transferAmount);
            recipientIt->deposit(transferAmount);
            // Update clients.txt immediately
            removeAllClients();
            for (const auto& client : clients) {
                addClient(client);
            }
            cout << "Transfer successful. Balance updated.\n";
        }
        else {
            cout << "Insufficient balance. Transfer cannot be completed.\n";
        }
    }
    else {
        cout << "Invalid sender or recipient ID. Transfer cannot be completed.\n";
    }
}

// Check if a client ID is valid
bool FileManager::isClientIdValid(const int& clientId) {
    vector<Client> clients = getAllClients();
    return find_if(clients.begin(), clients.end(),
        [clientId](const Client& client) {
            return client.getId() == (clientId);
        }) != clients.end();
}

// print login screen Pattern
void FileManager:: printWELCOME() {
    cout << "W   W  EEEEE  L      CCCCC  OOOOO   M     M  EEEEE" << endl;
    cout << "W   W  E      L      C      O   O   MM   MM  E" << endl;
    cout << "W W W  EEEE   L      C      O   O   M M M M  EEEE" << endl;
    cout << "W W W  E      L      C      O   O   M  M  M  E" << endl;
    cout << " W W   EEEEE  LLLLL  CCCCC  OOOOO   M     M  EEEEE" << endl;
    cout << endl;
}

void FileManager::printWE() {
    cout << "W   W  EEEEE" << endl;
    cout << "W   W  E" << endl;
    cout << "W W W  EEEE" << endl;
    cout << "W W W  E" << endl;
    cout << " W W   EEEEE" << endl;
    cout << endl;
}

void FileManager::printBANK() {
    cout << "B  B      A     N   N  K   K" << endl;
    cout << "B   B    A A    NN  N  K  K" << endl;
    cout << "B   B   A   A   N N N  K K" << endl;
    cout << "B B     AAAAA   N  NN  K  K" << endl;
    cout << "B   B   A   A   N   N  K   K" << endl;
    cout << "B B B   A   A   N   N  K    K" << endl;
    cout << endl;

}

