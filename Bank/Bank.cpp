#include "admin.h"
#include "client.h"
#include "employee.h"
#include "fileManager.h"
#include "person.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <conio.h>
#include <cctype>
using namespace std;
int main() {
    FileManager fileManager;
    fileManager.printWELCOME();
    this_thread::sleep_for(chrono::seconds(2));
    fileManager.printWE();
    this_thread::sleep_for(chrono::seconds(2));
    fileManager.printBANK();
    this_thread::sleep_for(chrono::seconds(2));
    // Choice Screen  
    system("cls");
    cout << "(1) Admin\n";
    cout << "(2) Employee\n";
    cout << "(3) Client\n";
    cout << "(4) Exit\n";
    cout << "Login As : ";
    // code For Choice Between Modules
    int choice;
    cin >> choice;
    system("cls");
    switch (choice) {
    case 1: {
        // Login Screen For Admin Module
        // Admin Module
        while (true) {
            cout << "=======================\n";
            cout << "Welcome To Admin Module\n";
            cout << "=======================\n";
            Admin admin;
            // Admin Id
            int adminLoginChoice;
            cout << "(1) Sign Up As New Admin\n";
            cout << "(2) Login\n";
            cout << "(3) Exit\n";
            cout << "Login As : ";
            cin >> adminLoginChoice;
            system("cls");
            switch (adminLoginChoice) {
            case 1: {
                // Sign Up For Admin Module
                FileManager fileManager;
                vector<Admin> allAdmins = fileManager.getAllAdmins();
                // Check if there is already an admin
                if (!allAdmins.empty()) {
                    cout << ":( Inavlid Signup There's An Admin Account Already Exists In The System.\n"
                        << "If you need to sign up as a new admin, please contact the System Administrator to remove the existing account.\n"
                       <<"Thank You For Using Our Banking System!\n";
                    cout << "Press Enter To Continue....\n";
                    cin.ignore();
                    cin.get();
                    system("cls");
                    break;
                }
                cout << "=============================\n";
                cout << "Create Admin Account\n";
                cout << "=============================\n";
                cout << "Enter Admin ID : ";
                int createAdminId;
                cin >> createAdminId;
                admin.setId(createAdminId);
                cout << "Enter Admin Name : ";
                string createAdminName;
                cin >> createAdminName;
                admin.setName(createAdminName);
                admin.getName();
                cout << "Enter Admin Password : ";
                string createAdminPassword;
                cin >> createAdminPassword;
                admin.setPassword(createAdminPassword);
                cout << "Enter Admin Salary : ";
                double createAdminSalary;
                cin >> createAdminSalary;
                admin.setSalary(createAdminSalary);
                fileManager.addAdmin(admin);
                cout << "Admin Account Created Successfully\n";
                cout << "Press Enter To Continue\n";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            }
            case 2: {
                // Login For Admin Module
                cout << "=============================\n";
                cout << "Account Login\n";
                cout << "=============================\n";
                cout << "Enter Admin ID: ";
                int adminId;
                cin >> adminId;
                admin.setId(adminId);
                cout << "Enter Admin Password: ";
                string createAdminPassword;
                char ch;
                bool showPassword = false;
                while (true) {
                    ch = _getch();
                    if (ch == 13) {  // Enter key
                        break;
                    }
                    else if (ch == 8) {  // Backspace
                        if (!createAdminPassword.empty()) {
                            createAdminPassword.pop_back();
                            cout << "\b \b";  // Move cursor back and overwrite with space
                        }
                    }
                    else if (ch == 27) {  // Escape key
                        break;
                    } // end of else if
                    else if (ch == '-') {
                        FileManager fileManager;
                        fileManager.togglePasswordVisibility(createAdminPassword, showPassword);
                    } // end of else if
                    else {
                        createAdminPassword += ch;
                        if (showPassword) {
                            cout << ch;
                        } // end of if
                        else {
                            cout << '*';
                        } // end of else
                    } // End Of Else
                } 
                FileManager fileManager;
                vector<Admin> allAdmins = fileManager.getAllAdmins();
                bool LoginSuccess = false;
                // Login Validation
                for (const auto& storedAdmin : allAdmins) {
                    if (adminId == storedAdmin.getId() &&
                        createAdminPassword == storedAdmin.getPassword()) {
                        admin = storedAdmin; // Update Admin Object With Logged In Admin's
                        // Details
                        LoginSuccess = true;
                        break;
                    } // end of if
                } // end of for
                system("cls");
                if (LoginSuccess) {
                    int adminOption;
                    while (true) {
                        cout << "=============================\n";
                        cout << "Welcome To Admin Control Menu "
                            << "(" << admin.getName() << ")" << endl;
                        cout << "==============================\n";
                        cout << "(1) Display Admin Info\n";
                        cout << "(2) Update Admin Password\n";
                        cout << "(3) Edit Admin Info \n";
                        cout << "(4) Remove Admin Account\n";
                        cout << "---------------------------\n";
                        cout << "Client Options\n";
                        cout << "---------------------------\n";
                        cout << "(5) Add New Client\n";
                        cout << "(6) Search For Clients\n";
                        cout << "(7) List All Clients\n";
                        cout << "(8) Edit Client Info\n";
                        cout << "(9) Remove Client\n";
                        cout << "(10) Remove All Clients\n";
                        cout << "---------------------------\n";
                        cout << "Employee Options\n";
                        cout << "---------------------------\n";
                        cout << "(11) Add New Employee\n";
                        cout << "(12) Search For Employees\n";
                        cout << "(13) List All Employees\n";
                        cout << "(14) Edit Employee Info\n";
                        cout << "(15) Remove Employee\n";
                        cout << "(16) Remove All Employee\n";
                        cout << "(17) Logout\n";
                        cout << "Your choice Is : ";
                        // choose Admin Option
                        cin >> adminOption;
                        system("cls");
                        switch (adminOption) {
                        case 1: {
                            // Display Admin Info
                            cout << "=======================\n";
                            cout << "1- Displaying Admin Info\n";
                            cout << "=======================\n";
                            FileManager fileManager;
                            fileManager.getAllAdmins();
                            admin.displayInfo();
                            cout << "Press Enter To Return Admin Options \n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            break;
                        } // end of case 1
                          //--------------------------------------------
                        case 2: {
                            // update password
                            system("cls");
                            cout << "=======================\n";
                            cout << "2- Update Admin Password\n";
                            cout << "=======================\n";
                            bool correctPasswordEntered = false;
                            do {
                                cout << "Enter Old Password : ";
                                string oldAdminPassword;
                                cin >> oldAdminPassword;
                                admin.setPassword(oldAdminPassword);
                                if (fileManager.checkAdminPassword(admin.getId(),
                                    oldAdminPassword)) {
                                    cout << "Enter New Password: ";
                                    string newAdminPassword;
                                    cin >> newAdminPassword;
                                    // Update The Password In The File
                                    fileManager.updateAdminPassword(admin.getId(),
                                        newAdminPassword);
                                    admin.setPassword(newAdminPassword);
                                    cout << "Password Updated Successfully\n";
                                    correctPasswordEntered = true;
                                }
                                else {
                                    cout << "Incorrect Old Password\n";
                                    cout << "Enter the correct old password once more or type "
                                        "'back' to return to admin options: ";
                                    string tryAgain;
                                    cin >> tryAgain;
                                    if (tryAgain == "back") {
                                        correctPasswordEntered = true;
                                        break; // Exit the loop and return to admin options
                                    }
                                }
                            } while (!correctPasswordEntered);
                            cout << "Press Enter To Continue... \n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            break;
                        } // end of case 2
                        case 3: {
                            // Edit Admin Info
                            system("cls");
                            FileManager fileManager;
                            // Step 1: Enter the ID of the Admin to edit
                            cout << "=======================\n";
                            cout << "3- Edit Admin Info\n";
                            cout << "=======================\n";
                            cout << "Enter Admin ID to edit: ";
                            cout << "------------------------------\n";
                            int editId;
                            cin >> editId;
                            // Step 2: Search for the Admin in Admins.txt
                            Admin adminToEdit;
                            vector<Admin> allAdmins = fileManager.getAllAdmins();
                            auto it = find_if(
                                allAdmins.begin(), allAdmins.end(),
                                [editId](const Admin& c) { return c.getId() == editId; });
                            if (it != allAdmins.end()) {
                                // Step 3: Allow the admin to modify Admin info
                                cout << "Enter New Admin ID : ";
                                int editId;
                                cin >> editId;
                                it->setId(editId);
                                cout << "Enter New Admin Name : ";
                                string editName;
                                cin >> editName;
                                it->setName(editName);
                                cout << "Enter New Admin Password : ";
                                string editPassword;
                                cin >> editPassword;
                                it->setPassword(editPassword);
                                cout << "Enter New Admin Salary : ";
                                double editSalary;
                                cin >> editSalary;
                                it->setSalary(editSalary);
                                // Step 4: Update the information in Admins.txt
                                fileManager.removeAllAdmins(); // cls the existing content
                                for (const Admin& admin : allAdmins) {
                                    fileManager.addAdmin(
                                        admin); // Add all Admins back to the file
                                }
                                cout << "Successfully Edited Admin Info\n";
                                cout << "Press Enter To Continue....\n";
                                cin.ignore();
                                cin.get();
                                system("cls");
                            }
                            else {
                                cout << "Admin with ID " << editId << " not found.\n";
                                cout << "Press Enter To Continue....\n";
                                cin.ignore();
                                cin.get();
                                system("cls");
                            }
                            break;
                        } // End Of Case 3
                        case 4: {
                            //  Remove Admin Account
                            system("cls");
                            cout << "=======================\n";
                            cout << "Remove Admin Account\n";
                            cout << "=======================\n";
                            cout << "Are You Sure You Want To Remove Admin Account? (Y/N) : ";
                            char choice;
                            cin >> choice;
                            if (choice == 'Y' || choice == 'y') {
                                fileManager.removeAdmin(adminId); // cls the existing content
                                cout << "Admin Account Removed Successfully\n";
                                cout << "Press Enter To Continue....\n";
                                cin.ignore();
                                cin.get();
                                system("cls");
                                return main();
                                break;
                            }
                            else {
                                cout << "Admin Account Not Removed\n";
                                cout << "Press Enter To Continue....\n";
                                cin.ignore();
                                cin.get();
                                system("cls");
                                break;
                            }
                        } // End Of Case 4
                          //--------------------------------------------
                        case 5: {
                            system("cls");
                            FileManager fileManager;
                            Client newClient;

                            cout << "=======================\n";
                            cout << "Add New Client\n";
                            cout << "=======================\n";

                            // Automatically generate the new Client ID
                            vector<Client> allClients = fileManager.getAllClients();
                            int maxClientId = 0;
                            for (const auto& client : allClients) {
                                if (client.getId() > maxClientId) {
                                    maxClientId = client.getId();
                                }
                            }
                            int newClientId = maxClientId + 1;
                            newClient.setId(newClientId);

                            // Display the automatically generated Client ID
                            cout << "1- Client ID (Automatically generated): " << newClientId << endl;

                            // Add New Client Name
                            cout << "2- Enter Client Name: ";
                            string clientName;
                            cin >> clientName;
                            newClient.setName(clientName);

                            // Add New Client Password
                            cout << "3- Enter Client Password: ";
                            string newClientPassword;
                            cin >> newClientPassword;
                            newClient.setPassword(newClientPassword);

                            // Add New Client Balance
                            cout << "4- Enter Client Balance: ";
                            double newClientBalance;
                            cin >> newClientBalance;
                            newClient.setBalance(newClientBalance);

                            // Ask the admin if they want to continue or cancel
                            cout << "5- Do you want to continue adding this client? (Y/N): ";
                            char choice;
                            cin >> choice;

                            if (toupper(choice) == 'N') {
                                cout << "Operation Canceled. No Changes Occurred.\n";
                            }
                            else {
                                // Save the new client to the file
                                fileManager.addClient(newClient);
                                cout << "Client Added Successfully\n";
                            }

                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            break;
                        } // end of case 5

                          //--------------------------------------------
                        case 6: {
                            system("cls");
                            Client client;
                            // Search For Client Id
                            cout << "=======================\n";
                            cout << "Search For Client\n";
                            cout << "=======================\n";
                            cout << "Enter Client ID : ";
                            int searchId;
                            cin >> searchId;
                            client.setId(searchId);
                            cout << "=======================\n";
                            client = fileManager.searchClientById(searchId);
                            if (client.getId() != 0) {
                                client.displayInfo();
                            }
                            else {
                                cout << "Client with ID " << searchId << " not found." << endl;
                            }
                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            break;
                        } // end of case 6
                        case 7: {
                            system("cls");
                            // list all client
                            FileManager fileManager;
                            fileManager.listAllClients();
                            break;
                        } // end of case 7
                          //--------------------------------------------
                        case 8: {
                            system("cls");
                            FileManager fileManager;
                            // Step 1: Enter the ID of the client to edit
                            cout << "=======================\n";
                            cout << "Edit Client Info\n";
                            cout << "=======================\n";
                            cout << "Enter Client ID to edit: ";
                            int editId;
                            cin >> editId;
                            // Step 2: Search for the client in clients.txt
                            Client clientToEdit;
                            vector<Client> allClients = fileManager.getAllClients();
                            auto it = find_if(
                                allClients.begin(), allClients.end(),
                                [editId](const Client& c) { return c.getId() == editId; });
                            if (it != allClients.end()) {
                                // Step 3: Allow the admin to modify client info
                                cout << "Enter New Client ID : ";
                                int editId;
                                cin >> editId;
                                it->setId(editId);
                                cout << "Enter New Client Name : ";
                                string editName;
                                cin >> editName;
                                it->setName(editName);
                                cout << "Enter New Client Password : ";
                                string editPassword;
                                cin >> editPassword;
                                it->setPassword(editPassword);
                                cout << "Enter New Client Balance : ";
                                double editBalance;
                                cin >> editBalance;
                                it->setBalance(editBalance);
                                // Step 4: Update the information in clients.txt
                                fileManager.removeAllClients(); // cls the existing content
                                for (const Client& client : allClients) {
                                    fileManager.addClient(
                                        client); // Add all clients back to the file
                                }
                                cout << "Successfully Edited Client Info\n";
                                cout << "Press Enter To Continue....\n";
                                cin.ignore();
                                cin.get();
                                system("cls");
                            }
                            else {
                                cout << "Client with ID " << editId << " not found.\n";
                                cout << "Press Enter To Continue....\n";
                                cin.ignore();
                                cin.get();
                                system("cls");
                            }
                            break;
                        } // end of case 8
                          //--------------------------------------------
                        case 9: {
                            system("cls");
                            cout << "=======================\n";
                            cout << "Remove Client\n";
                            cout << "=======================\n";
                            int clientId;
                            cout << "Enter the ID of the client to remove : ";
                            cin >> clientId;
                            // fileManager.removeClient(clientId);
                            cout << "Are You Sure You Want To Remove This Client? (Y/N) : ";
                            char choice;
                            cin >> choice;
                            if (choice == 'y' || choice == 'Y') {
                                fileManager.removeClient(clientId); // cls the existing conten
                                cout << "Client with ID " << clientId
                                    << " removed successfully.\n";
                            }
                            else {
                                cout << "Client with ID " << clientId << " not removed.\n";
                            } // End Of Else
                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            break;
                        } // end of case 9
                          //--------------------------------------------
                        case 10: {
                            system("cls");
                            cout << "=======================\n";
                            cout << "Remove All Clients\n";
                            cout << "=======================\n";
                            cout << "Are You Sure You Want To Remove All Clients? (Y/N) : ";
                            char choice;
                            cin >> choice;
                            if (choice == 'y' || choice == 'Y') {
                                fileManager.removeAllClients();
                                cout << "All Clients removed successfully.\n";
                            }
                            else {
                                cout << "Clients Not Removed.\n";
                            }
                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            break;
                        } // end of case 10
                          //--------------------------------------------
                        case 11: {
                            system("cls");
                            // Add New Employee
                            Employee newEmployee;
                            cout << "=======================\n";
                            cout << "Add New Employee\n";
                            cout << "=======================\n";
                            // Automatically generate the new Employee ID
                            vector<Employee> allEmployees = fileManager.getAllEmployees();
                            int maxEmployeeId = 0;
                            for (const auto& employee : allEmployees) {
                                if (employee.getId() > maxEmployeeId) {
                                    maxEmployeeId = employee.getId();
                                }
                            }
                            int newEmployeeId = maxEmployeeId + 1;
                            newEmployee.setId(newEmployeeId);

                            // Display the automatically generated Employee ID
                            cout << "1- Employee ID (Automatically generated): " << newEmployeeId << endl;

                            // Add New Employee Name
                            cout << "2- Enter Employee Name: ";
                            string employeeName;
                            cin >> employeeName;
                            newEmployee.setName(employeeName);

                            // Add New Employee Password
                            cout << "3- Enter Employee Password: ";
                            string newEmployeePassword;
                            cin >> newEmployeePassword;
                            newEmployee.setPassword(newEmployeePassword);

                            // Add New Employee Balance
                            cout << "4- Enter Employee Salary: ";
                            double newEmployeeSalary;
                            cin >> newEmployeeSalary;
                            newEmployee.setSalary(newEmployeeSalary);

                            // Ask the admin if they want to continue or cancel
                            cout << "5- Do You Want To Continue Adding This Employee? (Y/N): ";
                            char choice;
                            cin >> choice;

                            if (toupper(choice) == 'N') {
                                cout << "Operation Canceled. No Changes Occurred.\n";
                            }
                            else {
                                // Save the new client to the file
                                fileManager.addEmployee(newEmployee);
                                cout << "Employee Added Successfully\n";
                            }
                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            break;
                        } // end of case 11
                          //--------------------------------------------
                        case 12: {
                            system("cls");
                            // Search For Employee Id
                            Employee employee;
                            cout << "=======================\n";
                            cout << "Search For Employee\n";
                            cout << "=======================\n";
                            cout << "Enter Employee ID:  ";
                            int searchId;
                            cin >> searchId;
                            employee.setId(searchId);
                            employee = fileManager.searchEmployeeById(searchId);
                            if (employee.getId() != 0) {
                                employee.displayInfo();
                            }
                            else {
                                cout << "Employee with ID " << searchId << " not found."
                                    << endl;
                            }
                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            break;
                        } // end of case 12
                          //--------------------------------------------
                        case 13: {
                            system("cls");
                            Admin admin;
                            // list all employee
                            FileManager fileManager;
                            fileManager.listAllEmployees();
                            break;
                        } // end of case 13
                          //--------------------------------------------
                        case 14: {
                            system("cls");
                            FileManager fileManager;
                            // Step 1: Enter the ID of the Employee to edit
                            cout << "=======================\n";
                            cout << "Edit Employee Info\n";
                            cout << "=======================\n";
                            cout << "Enter Employee ID to edit: ";
                            int editId;
                            cin >> editId;
                            // Step 2: Search for the Employee in employees.txt
                            Employee employeeToEdit;
                            vector<Employee> allEmployees = fileManager.getAllEmployees();
                            auto it = find_if(
                                allEmployees.begin(), allEmployees.end(),
                                [editId](const Employee& e) { return e.getId() == editId; });
                            if (it != allEmployees.end()) {
                                // Step 3: Allow the admin to modify Employee info
                                cout << "Enter New Employee ID : ";
                                int editId;
                                cin >> editId;
                                it->setId(editId);
                                cout << "Enter New Employee Name : ";
                                string editName;
                                cin >> editName;
                                it->setName(editName);
                                cout << "Enter New Employee Password : ";
                                string editPassword;
                                cin >> editPassword;
                                it->setPassword(editPassword);
                                cout << "Enter New Employee Salary : ";
                                double editSalary;
                                cin >> editSalary;
                                it->setSalary(editSalary);
                                // Step 4: Update the information in employees.txt
                                fileManager.removeAllEmployees(); // cls the existing content
                                for (const Employee& employee : allEmployees) {
                                    fileManager.addEmployee(
                                        employee); // Add all Employees back to the file
                                }
                                cout << "Successfully Edited Employee Info\n";
                                cout << "Press Enter To Continue....\n";
                                cin.ignore();
                                cin.get();
                                system("cls");
                            }
                            else {
                                cout << "Employee with ID " << editId << " not found.\n";
                                cout << "Press Enter To Continue....\n";
                                cin.ignore();
                                cin.get();
                                system("cls");
                            }
                            break;
                        } // end of case 14
                          //--------------------------------------------
                        case 15: {
                            system("cls");
                            cout << "=======================\n";
                            cout << "Remove Employee\n";
                            cout << "=======================\n";
                            int employeeId;
                            cout << "Enter ID Of The Employee To Remove: ";
                            cin >> employeeId;
                            // fileManager.removeEmployee(employeeId);
                            cout << "Are You Sure You Want To Remove This Employee? (Y/N) : ";
                            char choice;
                            cin >> choice;
                            if (choice == 'Y' || choice == 'y') {
                                fileManager.removeEmployee(
                                    employeeId); // cls the existing content
                                cout << "Employee With Id " << employeeId
                                    << "Removed Successfully";
                            }
                            else {
                                cout << "Employee With Id " << employeeId << "Not Removed\n";
                            }
                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            break;
                        } // end of case 15
                          //--------------------------------------------
                        case 16: {
                            system("cls");
                            cout << "=======================\n";
                            cout << "Remove All Employees\n";
                            cout << "=======================\n";
                            cout << "Are You Sure You Want To Remove All Employees? (Y/N) : "
                                "\n";
                            char choice;
                            cin >> choice;
                            if (choice == 'Y' || choice == 'y') {
                                fileManager.removeAllEmployees(); // cls the existing content
                                cout << "All Employees Removed Successfully\n";
                            }
                            else {
                                cout << "All Employees Not Removed\n";
                            }
                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            break;
                        } // end of case 16
                          //--------------------------------------------
                        case 17: {
                            system("cls");
                            // logout
                            cout << "Successfully Logged Out\n";
                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                            return main();
                            break;
                        } // end of case 17
                        } // end of admin options
                    }   // end of while true
                }     // end of if
                else {
                    cout << "Incorrect Id Or Password\n";
                    cout << "Press Enter To Retry....\n";
                    cin.ignore();
                    cin.get();
                    system("cls");
                } // end of eles
                break;
            } // end of case 2
              //--------------------------------------------
            case 3: {
                cout << "Successfully Logged Out\n";
                cout << "Press Enter To Continue....\n";
                cin.ignore();
                cin.get();
                system("cls");
                return main();
                break;
            } // end of case 3

            default: {
                system("cls");
                cout << "Invalid Choice!\n";
                cout << "Press Enter To Continue....\n";
                cin.ignore();
                cin.get();
                system("cls");
                break;
            } // end of default
            } // end of admin choice
        }   // End Of while loop
    }     // end case 1
          //===================================================================
      // Employee Module
    case 2: {
        while (true) {
            // Login Screen For Employee Module
            cout << "==========================\n";
            cout << "Welcome To Employee Module\n";
            cout << "==========================\n";
            Employee employee;
            // Step 1: Ask for Employee ID
            cout << "Enter Employee ID: ";
            int employeeId;
            cin >> employeeId;
            // Step 2: Ask For Employee Password;
            cout << "Enter Employee Password: ";
            string employeePassword;
            cin >> employeePassword;
            // Step 3: Validate Employee ID and Password
            FileManager fileManager;
            vector<Employee> allEmployees = fileManager.getAllEmployees();
            bool LoginSuccess = false;
            // Login Validation
            for (const auto& storedEmployee : allEmployees) {
                if (employeeId == storedEmployee.getId() &&
                    employeePassword == storedEmployee.getPassword()) {
                    employee = storedEmployee; // Update Employee Object With Logged In
                    // employeeS Details
                    LoginSuccess = true;
                    break;
                }
            }
            system("cls");
            //  Check Login Credentials
            if (LoginSuccess) {
                // Employee Options
                int employeeOption;
                while (true) {
                    cout << "================================\n";
                    cout << "Welcome To Employee Options Menu "
                        << "(" << employee.getName() << ")" << endl;
                    cout << "================================\n";
                    cout << "(1) Display My Info\n";
                    cout << "(2) Add New Client\n";
                    cout << "(3) Search For Clients\n";
                    cout << "(4) List All Clients\n";
                    cout << "(5) Edit Client Info\n";
                    cout << "(6) Remove Client\n";
                    cout << "(7) Remove All Clients\n";
                    cout << "(8) Logout\n";
                    cout << "Your choice Is: ";
                    // choose Employee Option
                    cin >> employeeOption;
                    system("cls");
                    switch (employeeOption) {
                    case 1: {
                        // Display Employee Info
                        cout << "=======================\n";
                        cout << "Display Employee Info\n";
                        cout << "=======================\n";
                        employee.displayInfo();
                        cout << "Press Enter To Return Admin Options \n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 1
                      //--------------------------------------------
                    case 2: {
                        system("cls");
                        Client newClient;
                        // Add New Client Id
                        cout << "=======================\n";
                        cout << "Add New Client\n";
                        cout << "=======================\n";
                        cout << "Enter Client Id : ";
                        int newClientId;
                        cin >> newClientId;
                        newClient.setId(newClientId);
                        // Add New Client Name
                        cout << "Enter Client Name : ";
                        string newClientName;
                        cin >> newClientName;
                        newClient.setName(newClientName);
                        // Add New Client Password
                        cout << "Enter Client Password : ";
                        string newClientPassword;
                        cin >> newClientPassword;
                        newClient.setPassword(newClientPassword);
                        // Add New Client Balance
                        cout << "Enter Client Balance : ";
                        double newClientBalance;
                        cin >> newClientBalance;
                        newClient.setBalance(newClientBalance);
                        FileManager fileManager;
                        fileManager.addClient(newClient);
                        cout << "Client Added Successfully\n";
                        cout << "Successfully Added New Client\n";
                        cout << "Press Enter To Continue....\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 2
                      //--------------------------------------------
                    case 3: {
                        system("cls");
                        Client client;
                        // Search For Client Id
                        cout << "=======================\n";
                        cout << "Search For Client\n";
                        cout << "=======================\n";
                        cout << "Enter Client ID :  ";
                        int searchId;
                        cin >> searchId;
                        client.setId(searchId);
                        client = fileManager.searchClientById(searchId);
                        if (client.getId() != 0) {
                            client.displayInfo();
                        }
                        else {
                            cout << "Client with ID " << searchId << " not found." << endl;
                        }
                        cout << "Press Enter To Continue....\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 3
                    case 4: {
                        system("cls");
                        // list all client
                        FileManager fileManager;
                        fileManager.listAllClients();
                        break;
                    } // end of case 4
                      //--------------------------------------------
                    case 5: {
                        system("cls");
                        FileManager fileManager;
                        // Step 1: Enter the ID of the client to edit
                        cout << "=======================\n";
                        cout << "Edit Client Info\n";
                        cout << "=======================\n";
                        cout << "Enter Client ID to edit: ";
                        int editId;
                        cin >> editId;
                        // Step 2: Search for the client in clients.txt
                        Client clientToEdit;
                        vector<Client> allClients = fileManager.getAllClients();
                        auto it = find_if(
                            allClients.begin(), allClients.end(),
                            [editId](const Client& c) { return c.getId() == editId; });
                        if (it != allClients.end()) {
                            // Step 3: Allow the admin to modify client info
                            cout << "Enter New Client ID : ";
                            int editId;
                            cin >> editId;
                            it->setId(editId);
                            cout << "Enter New Client Name : ";
                            string editName;
                            cin >> editName;
                            it->setName(editName);
                            cout << "Enter New Client Password : ";
                            string editPassword;
                            cin >> editPassword;
                            it->setPassword(editPassword);
                            cout << "Enter New Client Balance : ";
                            double editBalance;
                            cin >> editBalance;
                            it->setBalance(editBalance);
                            // Step 4: Update the information in clients.txt
                            fileManager.removeAllClients(); // cls the existing content
                            for (const Client& client : allClients) {
                                fileManager.addClient(
                                    client); // Add all clients back to the file
                            }
                            cout << "Successfully Edited Client Info\n";
                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                        }
                        else {
                            cout << "Client with ID " << editId << " not found.\n";
                            cout << "Press Enter To Continue....\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                        }
                        break;
                    } // end of case 5
                    //--------------------------------------------
                    case 6: {
                        system("cls");
                        cout << "=======================\n";
                        cout << "Remove Client\n";
                        cout << "=======================\n";
                        int clientId;
                        cout << "Enter the ID of the client to remove : ";
                        cin >> clientId;
                        // fileManager.removeClient(clientId);
                        cout << "Are You Sure You Want To Remove This Client "
                            << "(Y/N)?: ";
                        char choice;
                        cin >> choice;
                        if (choice == 'y' || choice == 'Y') {
                            fileManager.removeClient(clientId); // cls the existing conten
                            cout << "Client with ID " << clientId
                                << " removed successfully.\n";
                        }
                        else {
                            cout << "Client with ID " << clientId << " not removed.\n";
                        } // End Of Else
                        cout << "Press Enter To Continue....\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 6
                    //--------------------------------------------
                    case 7: {
                        system("cls");
                        cout << "=======================\n";
                        cout << "Remove All Clients\n";
                        cout << "=======================\n";
                        cout << "Are You Sure You Want To Remove All Clients? (Y/N) : ";
                        char choice;
                        cin >> choice;
                        if (choice == 'y' || choice == 'Y') {
                            fileManager.removeAllClients();
                            cout << "All Clients removed successfully.\n";
                        }
                        else {
                            cout << "Clients Not Removed.\n";
                        }
                        cout << "Press Enter To Continue....\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 7
                      //--------------------------------------------
                    case 8: {
                        // logout
                        cout << "Successfully Logged Out\n";
                        cout << "Press Enter To Continue....\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        return main();
                        break;
                    } // end of case 6
                    default: {
                        cout << "Invalid Choice!\n";
                        cout << "Press Enter To Continue....\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of Deafault case
                    } // end of switch Employee options
                }   // end of while loop Employee options
            }     // end of if Employee login
            else {
                cout << "Incorrect Id Or Password\n";
                cout << "Press Enter To Retry....\n";
                cin.ignore();
                cin.get();
                system("cls");
                continue; // Continue the outer loop to retry login
            }           // end of eles
            break;
        } // End Of While Loop
    }   // end of Employee
        //===================================================================
    case 3: {
        // Login Screen For Client Module
        // Client Module
        while (true) {
            // Login Screen For Client Module
            cout << "==========================\n";
            cout << "Welcome To Client Module\n";
            cout << "==========================\n";
            Client client;
            // Step 1: Ask for Client ID
            cout << "Enter Client ID: ";
            int clientId;
            cin >> clientId;
            // Step 2: Ask For Client Password;
            cout << "Enter Client Password: ";
            string clientPassword;
            cin >> clientPassword;
            // Step 3: Validate Client ID and Password
            FileManager fileManager;
            vector<Client> allClients = fileManager.getAllClients();
            bool LoginSuccess = false;
            // Login Validation
            for (const auto& storedClient : allClients) {
                if (clientId == storedClient.getId() &&
                    clientPassword == storedClient.getPassword()) {
                    client = storedClient; // Update Client Object With Logged In
                    // Client Details
                    LoginSuccess = true;
                    break;
                }
            }
            system("cls");
            //  Check Login Credentials
            if (LoginSuccess) {
                // client Options
                int clientOption;
                while (true) {
                    cout << "=======================\n";
                    cout << "Welcome To Client Module Options "
                        << "(" << client.getName() << ")\n";
                    cout << "=======================\n";
                    cout << "(1) Display My Info\n";
                    cout << "(2) Check Balance\n";
                    cout << "(3) Update Password\n";
                    cout << "(4) Withdraw\n";
                    cout << "(5) Deposit\n";
                    cout << "(6) Transfer Amount \n";
                    cout << "(7) Logout\n";
                    cout << "Your choice Is: ";
                    // choose Employee Option
                    cin >> clientOption;
                    system("cls");
                    switch (clientOption) {
                    case 1: {
                        // Display Employee Info
                        cout << "=======================\n";
                        cout << "Display Client Info\n";
                        cout << "=======================\n";
                        client.displayInfo();
                        cout << "Press Enter To Return Client Options \n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 1
                    case 2: {
                        // check Balance
                        cout << "=======================\n";
                        cout << "Check Client Balance\n";
                        cout << "=======================\n";
                        client.checkbalance();
                        cout << "Press Enter To Contniue...\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 2
                    case 3: {
                        // update password
                        system("cls");
                        cout << "=======================\n";
                        cout << "Update Client Password\n";
                        cout << "=======================\n";
                        bool correctPasswordEntered = false;
                        do {
                            cout << "Enter Old Password : ";
                            string oldClientPassword;
                            cin >> oldClientPassword;
                            client.setPassword(oldClientPassword);
                            if (fileManager.checkClientPassword(client.getId(),
                                oldClientPassword)) {
                                cout << "Enter New Password: ";
                                string newClientPassword;
                                cin >> newClientPassword;
                                // Update The Password In The File
                                fileManager.updateClientPassword(client.getId(),
                                    newClientPassword);
                                client.setPassword(newClientPassword);
                                cout << "Password Updated Successfully\n";
                                correctPasswordEntered = true;
                            }
                            else {
                                cout << "Incorrect Old Password\n";
                                cout << "Enter the correct old password once more or type "
                                    "'back' to return to admin options: ";
                                string tryAgain;
                                cin >> tryAgain;
                                if (tryAgain == "back") {
                                    correctPasswordEntered = true;
                                    break; // Exit the loop and return to admin options
                                }
                            }
                        } while (!correctPasswordEntered);
                        cout << "Press Enter To Continue... \n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 3
                    case 4: {
                        //   Withdraw
                        cout << "=======================\n";
                        cout << "Withdraw Money\n";
                        cout << "=======================\n";
                        cout << "Enter Amount To Withdraw: ";
                        double withdrawAmount;
                        cin >> withdrawAmount;
                        client.withdraw(withdrawAmount);
                        FileManager fileManager;
                        fileManager.withdrawAmount(client.getId(), client.getBalance());
                        cout << "Press Enter To Contniue...\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 4
                    case 5: {
                        //   Depsoit
                        cout << "=======================\n";
                        cout << "Deposit Money\n";
                        cout << "=======================\n";
                        cout << "Enter Amount To Deposit : ";
                        double depositAmount;
                        cin >> depositAmount;
                        client.deposit(depositAmount);
                        FileManager fileManager;
                        fileManager.depositeAmount(client.getId(), client.getBalance());
                        cout << "Press Enter To Contniue...\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 5
                    case 6: {
                        // Transfer Amount
                        cout << "=======================\n";
                        cout << "Transfer Amount\n";
                        cout << "=======================\n";
                        FileManager fileManager;
                        int recipientId;
                        double transferAmount;
                        // Step 1: Ask the client to enter the recipient's account ID
                        cout << "Enter the ID of the account to transfer to: ";
                        cin >> recipientId;
                        client.setId(recipientId);
                        client = fileManager.searchClientById(recipientId);
                        if (client.getId() != 0) {
                            cout << "this Id Belong to : " << client.getName() << endl;
                        }
                        else {
                            cout << "Client with ID " << recipientId << " not found." << endl;
                            cout << "Press Enter To Continue...\n";
                            cin.ignore();
                            cin.get();
                            system("cls");
                        }

                        // Step 3: Ask the client to enter the amount to transfer
                        cout << "Enter the amount to transfer: ";
                        cin >> transferAmount;
                        // Step 4: Perform the transfer
                        fileManager.transferAmount(client.getId(), recipientId,
                            transferAmount);
                        cout << "Press Enter To Continue...\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } // end of case 6
                    case 7: {
                        // logout
                        cout << "Successfully Logged Out\n";
                        cout << "Press Enter To Continue....\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        return main();
                        break;
                    }
                    default: {
                        cout << "Invalid Choice!\n";
                        cout << "Press Enter To Continue....\n";
                        cin.ignore();
                        cin.get();
                        system("cls");
                        break;
                    } //  end of Deafault case
                    } // end of switch Client options
                }   // end of while loop Client options
            }     // end of if Client login
            else {
                cout << "Incorrect Id Or Password\n";
                cout << "Press Enter To Retry....\n";
                cin.ignore();
                cin.get();
                system("cls");
                continue; // Continue the outer loop to retry login
            }           // end of eles
            break;
        } // end of While Loop
    }   // end of Client
        //===================================================================
      // Project Credits
    case 4: {
        cout << "Thank You For Using Our Banking System\n";
        cout << "Devloped By Eng: Mostafa Reda\n";
        cout << "Asp.Net Software Engineer\n";
        break;
    }
    default: {
        cout << "Invalid Choice \n";
        cout << "Press Enter To Continue....\n";
        cin.ignore();
        return main();
        break;
    }
    }
}