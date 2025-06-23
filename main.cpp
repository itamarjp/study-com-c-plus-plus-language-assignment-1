// EmployeeManagementSystem.cpp
// Author: Itamar Peixoto
// Assignment: Computer Science 112 - Assignment 1, Study.com
// Date: June 23, 2025
// Description: A C++ program implementing an employee management system with role-based access for HR, Managers, and Employees.
//              Features include login, CRUD operations, and input validation for unique IDs, usernames, and names.
// Usage: Compile with a C++11-compliant compiler (e.g., g++ -std=c++11 EmployeeManagementSystem.cpp).
//        Run and select options from the interactive menu.
// AI Usage: Grok (xAI) assisted with debugging unresponsiveness, adding validation for unique IDs/usernames,
//           and suggesting cosmetic improvements for readability and documentation (xAI, 2025).

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <regex>
using namespace std;

// =======================================
// Employee Class
// =======================================

class Employee {
protected:
    string name;
    int id;
    string username;
    string password;
    string role;

public:
    // Constructor for minimal employee data
    Employee(string name, int id, string username, string password, string role = "Employee")
        : name(name), id(id), username(username), password(password), role(role) {}

    // Displays employee information
    virtual void viewInfo() const {
        cout << "Name: " << name << "\nID: " << id << endl;
    }

    // Getters and setters
    int getId() const { return id; }
    string getName() const { return name; }
    void setName(const string& newName) { name = newName; }
    void setId(int newId) { id = newId; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
};

// =======================================
// Global Data
// =======================================

vector<Employee> employees = {
    Employee("Itamar", 1001, "itamar", "x", "Employee"),
    Employee("Pablo Escobar", 2001, "pablo", "platao", "Employee"),
    Employee("El Chapo", 2002, "chapo", "guzman", "Employee"),
    Employee("Griselda Blanco", 2003, "griselda", "blanco", "Employee"),
    Employee("Alice HR", 3001, "hr", "hr123", "HR"),
    Employee("Bob Manager", 3002, "manager", "manager123", "Manager")
};

// =======================================
// Helper Functions
// =======================================

// Checks if ID is unique, excluding the employee at excludeIndex (if applicable)
// Parameters: id - ID to check; excludeIndex - index to exclude (default -1)
// Returns: true if ID is unique and positive, false otherwise
bool isIdUnique(int id, int excludeIndex = -1) {
    if (id < 0) return false; // Reject negative IDs
    for (size_t i = 0; i < employees.size(); ++i) {
        if (static_cast<int>(i) != excludeIndex && employees[i].getId() == id) {
            return false;
        }
    }
    return true;
}

// Checks if username is unique, excluding the employee at excludeIndex (if applicable)
// Parameters: username - username to check; excludeIndex - index to exclude (default -1)
// Returns: true if username is unique and non-empty, false otherwise
bool isUsernameUnique(const string& username, int excludeIndex = -1) {
    if (username.empty()) return false; // Reject empty usernames
    for (size_t i = 0; i < employees.size(); ++i) {
        if (static_cast<int>(i) != excludeIndex && employees[i].getUsername() == username) {
            return false;
        }
    }
    return true;
}

// Validates name: allows letters, spaces, and hyphens; max length 50
// Parameters: name - name to validate
// Returns: true if name is valid, false otherwise
bool isValidName(const string& name) {
    if (name.empty() || name.length() > 50) return false;
    regex validNameRegex("^[A-Za-z\\s-]+$");
    return regex_match(name, validNameRegex);
}

// =======================================
// Employee Management Functions
// =======================================

// Adds a new employee with validated name, ID, username, and password
void addEmployee() {
    string name, username, password;
    int id;

    // Input name with validation
    cout << "Enter name (letters, spaces, hyphens; max 50 chars): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear residual newline
    getline(cin, name);
    if (!isValidName(name)) {
        cout << "Invalid name. Use letters, spaces, or hyphens only; max 50 characters.\n";
        return;
    }

    // Input ID with validation
    cout << "Enter ID (positive number): ";
    while (!(cin >> id) || !isIdUnique(id)) {
        cout << "Invalid or duplicate ID. Enter a unique positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Input username with validation
    cout << "Enter username: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear residual newline
    getline(cin, username);
    if (!isUsernameUnique(username)) {
        cout << "Username already exists. Choose a different username.\n";
        return;
    }

    // Input password with validation
    cout << "Enter password: ";
    getline(cin, password);
    if (password.empty()) {
        cout << "Password cannot be empty.\n";
        return;
    }

    // Add employee to database
    employees.emplace_back(name, id, username, password);
    cout << "Employee added successfully.\n";
}

// Displays all employees in the database
void viewAllEmployees() {
    if (employees.empty()) {
        cout << "No employees found.\n";
        return;
    }
    for (const auto& e : employees) {
        e.viewInfo();
        cout << "------------------\n";
    }
}

// Searches for an employee by ID
void searchEmployee() {
    int id;
    cout << "Enter ID to search: ";
    while (!(cin >> id) || id < 0) {
        cout << "Invalid ID. Enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    for (const auto& e : employees) {
        if (e.getId() == id) {
            e.viewInfo();
            return;
        }
    }
    cout << "Employee not found.\n";
}

// Modifies an existing employee with validated inputs
void modifyEmployee() {
    int id;
    cout << "Enter ID to modify: ";
    while (!(cin >> id) || id < 0) {
        cout << "Invalid ID. Enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    for (size_t i = 0; i < employees.size(); ++i) {
        if (employees[i].getId() == id) {
            string newName, newUsername, newPassword;
            int newId;

            // Input new name with validation
            cout << "Enter new name (letters, spaces, hyphens; max 50 chars): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, newName);
            if (!isValidName(newName)) {
                cout << "Invalid name. Use letters, spaces, or hyphens only; max 50 characters.\n";
                return;
            }

            // Input new ID with validation
            cout << "Enter new ID (positive number): ";
            while (!(cin >> newId) || !isIdUnique(newId, i)) {
                cout << "Invalid or duplicate ID. Enter a unique positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Input new username with validation
            cout << "Enter new username: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, newUsername);
            if (!isUsernameUnique(newUsername, i)) {
                cout << "Username already exists. Choose a different username.\n";
                return;
            }

            // Input new password with validation
            cout << "Enter new password: ";
            getline(cin, newPassword);
            if (newPassword.empty()) {
                cout << "Password cannot be empty.\n";
                return;
            }

            // Update employee
            employees[i] = Employee(newName, newId, newUsername, newPassword, employees[i].getRole());
            cout << "Employee modified successfully.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

// Deletes an employee by ID
void deleteEmployee() {
    int id;
    cout << "Enter ID to delete: ";
    while (!(cin >> id) || id < 0) {
        cout << "Invalid ID. Enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->getId() == id) {
            employees.erase(it);
            cout << "Employee deleted successfully.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

// =======================================
// Menu Helper Functions
// =======================================

// Displays HR menu and reads choice
void displayHRMenu(int& choice) {
    cout << "\n--- HR Menu ---\n";
    cout << "1. Add Employee\n2. View All\n3. Search\n4. Modify\n5. Delete\n6. Logout\nChoice: ";
    cin >> choice;
}

// Handles HR menu actions
void handleHRChoice(int choice) {
    switch (choice) {
        case 1: addEmployee(); break;
        case 2: viewAllEmployees(); break;
        case 3: searchEmployee(); break;
        case 4: modifyEmployee(); break;
        case 5: deleteEmployee(); break;
        case 6: break; // Logout handled in employeeMenu
        default: cout << "Invalid choice. Try again.\n"; break;
    }
}

// Displays Manager menu and reads choice
void displayManagerMenu(int& choice) {
    cout << "\n--- Manager Menu ---\n";
    cout << "1. View All\n2. Search\n3. Logout\nChoice: ";
    cin >> choice;
}

// Handles Manager menu actions
void handleManagerChoice(int choice) {
    switch (choice) {
        case 1: viewAllEmployees(); break;
        case 2: searchEmployee(); break;
        case 3: break; // Logout handled in employeeMenu
        default: cout << "Invalid choice. Try again.\n"; break;
    }
}

// Displays Employee menu and reads choice
void displayEmployeeMenu(int& choice) {
    cout << "\n--- Employee Menu ---\n";
    cout << "1. View My Info\n2. Logout\nChoice: ";
    cin >> choice;
}

// Handles Employee menu actions
void handleEmployeeChoice(int choice, int userId) {
    switch (choice) {
        case 1:
            for (const auto& e : employees) {
                if (e.getId() == userId) {
                    e.viewInfo();
                    break;
                }
            }
            break;
        case 2: break; // Logout handled in employeeMenu
        default: cout << "Invalid choice. Try again.\n"; break;
    }
}

// Displays role-specific menu and handles user actions
// Parameters: role - user role (HR, Manager, Employee); userId - current user's ID
void employeeMenu(const string& role, int userId = -1) {
    int choice = 0;
    bool logout = false;

    while (!logout) {
        if (role == "HR") {
            displayHRMenu(choice);
            if (choice == 6) logout = true;
            else handleHRChoice(choice);
        } else if (role == "Manager") {
            displayManagerMenu(choice);
            if (choice == 3) logout = true;
            else handleManagerChoice(choice);
        } else if (role == "Employee") {
            displayEmployeeMenu(choice);
            if (choice == 2) logout = true;
            else handleEmployeeChoice(choice, userId);
        }

        if (!logout) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear residual input
        }
    }
    cout << "Logged out successfully.\n"; // Confirms successful menu exit
}

// =======================================
// Authentication
// =======================================

// Handles user login with credential validation
void login() {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear residual newline

    for (const auto& e : employees) {
        if (e.getUsername() == username && e.getPassword() == password) {
            cout << "Login successful! Welcome, " << e.getName() << ".\n";
            employeeMenu(e.getRole(), e.getId());
            return;
        }
    }
    cout << "Invalid credentials.\n";
}

// =======================================
// Main Program
// =======================================

// Main program loop for menu navigation
int main() {
    cout << "Welcome to Employee Management System\n";

    while (true) {
        cout << "\n1. Login\n2. Exit\nChoice: ";
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: login(); break;
            case 2: cout << "Exiting system.\n"; return 0;
            default: cout << "Invalid choice. Try again.\n"; break;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Returned to main menu.\n"; // Confirms return to main menu
    }

    return 0;
}