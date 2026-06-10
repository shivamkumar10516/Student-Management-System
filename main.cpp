#include "StudentManager.h"
#include <iostream>
#include <limits>
#include <cstdlib>

// Function prototypes
void displayMenu();
void addStudentMenu(StudentManager& manager);
void deleteStudentMenu(StudentManager& manager);
void searchStudentMenu(StudentManager& manager);
void updateStudentMenu(StudentManager& manager);
void clearInputBuffer();

int main() {
    StudentManager manager;
    int choice;
    
    std::cout << "\n╔════════════════════════════════════════╗\n";
    std::cout << "║   STUDENT MANAGEMENT SYSTEM v1.0      ║\n";
    std::cout << "╚════════════════════════════════════════╝\n";
    
    do {
        displayMenu();
        std::cout << "Enter your choice (1-7): ";
        std::cin >> choice;
        
        // Validate input
        if (std::cin.fail()) {
            clearInputBuffer();
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                addStudentMenu(manager);
                break;
            case 2:
                deleteStudentMenu(manager);
                break;
            case 3:
                searchStudentMenu(manager);
                break;
            case 4:
                updateStudentMenu(manager);
                break;
            case 5:
                manager.displayAllStudents();
                break;
            case 6:
                manager.displayStatistics();
                break;
            case 7:
                std::cout << "\nThank you for using Student Management System!\n";
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice! Please enter number between 1 and 7.\n";
        }
        
    } while (choice != 7);
    
    return 0;
}

void displayMenu() {
    std::cout << "\n========== MAIN MENU ==========\n";
    std::cout << "1. Add New Student\n";
    std::cout << "2. Delete Student\n";
    std::cout << "3. Search Student by Roll Number\n";
    std::cout << "4. Update Student Information\n";
    std::cout << "5. Display All Students\n";
    std::cout << "6. Display Statistics\n";
    std::cout << "7. Exit\n";
    std::cout << "==============================\n";
}

void addStudentMenu(StudentManager& manager) {
    std::cout << "\n--- Add New Student ---\n";
    
    int rollNumber, age;
    std::string name, grade, email;
    
    std::cout << "Enter Roll Number: ";
    std::cin >> rollNumber;
    
    if (std::cin.fail()) {
        clearInputBuffer();
        std::cout << "Invalid roll number!\n";
        return;
    }
    
    clearInputBuffer();
    
    std::cout << "Enter Name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter Age: ";
    std::cin >> age;
    
    if (std::cin.fail()) {
        clearInputBuffer();
        std::cout << "Invalid age!\n";
        return;
    }
    
    clearInputBuffer();
    
    std::cout << "Enter Grade: ";
    std::getline(std::cin, grade);
    
    std::cout << "Enter Email: ";
    std::getline(std::cin, email);
    
    try {
        Student newStudent(rollNumber, name, age, grade, email);
        manager.addStudent(newStudent);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void deleteStudentMenu(StudentManager& manager) {
    std::cout << "\n--- Delete Student ---\n";
    int rollNumber;
    std::cout << "Enter Roll Number to delete: ";
    std::cin >> rollNumber;
    
    if (std::cin.fail()) {
        clearInputBuffer();
        std::cout << "Invalid roll number!\n";
        return;
    }
    
    manager.deleteStudent(rollNumber);
}

void searchStudentMenu(StudentManager& manager) {
    std::cout << "\n--- Search Student ---\n";
    int rollNumber;
    std::cout << "Enter Roll Number to search: ";
    std::cin >> rollNumber;
    
    if (std::cin.fail()) {
        clearInputBuffer();
        std::cout << "Invalid roll number!\n";
        return;
    }
    
    Student* student = manager.searchStudent(rollNumber);
    if (student) {
        student->display();
    } else {
        std::cout << "Student with Roll Number " << rollNumber << " not found!\n";
    }
}

void updateStudentMenu(StudentManager& manager) {
    std::cout << "\n--- Update Student Information ---\n";
    int rollNumber;
    std::cout << "Enter Roll Number to update: ";
    std::cin >> rollNumber;
    
    if (std::cin.fail()) {
        clearInputBuffer();
        std::cout << "Invalid roll number!\n";
        return;
    }
    
    Student* existing = manager.searchStudent(rollNumber);
    if (!existing) {
        std::cout << "Student not found!\n";
        return;
    }
    
    std::cout << "\nCurrent Student Information:\n";
    existing->display();
    
    std::cout << "\nEnter new information (press Enter to keep current value):\n";
    clearInputBuffer();
    
    int newRollNumber, newAge;
    std::string newName, newGrade, newEmail;
    std::string input;
    
    std::cout << "New Roll Number [" << existing->getRollNumber() << "]: ";
    std::getline(std::cin, input);
    newRollNumber = input.empty() ? existing->getRollNumber() : std::stoi(input);
    
    std::cout << "New Name [" << existing->getName() << "]: ";
    std::getline(std::cin, input);
    newName = input.empty() ? existing->getName() : input;
    
    std::cout << "New Age [" << existing->getAge() << "]: ";
    std::getline(std::cin, input);
    newAge = input.empty() ? existing->getAge() : std::stoi(input);
    
    std::cout << "New Grade [" << existing->getGrade() << "]: ";
    std::getline(std::cin, input);
    newGrade = input.empty() ? existing->getGrade() : input;
    
    std::cout << "New Email [" << existing->getEmail() << "]: ";
    std::getline(std::cin, input);
    newEmail = input.empty() ? existing->getEmail() : input;
    
    try {
        Student updatedStudent(newRollNumber, newName, newAge, newGrade, newEmail);
        manager.updateStudent(rollNumber, updatedStudent);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
