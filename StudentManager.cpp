#include "StudentManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

// Constructor
StudentManager::StudentManager(const std::string& file) : filename(file) {
    loadFromFile();
}

// Find student index by roll number
int StudentManager::findStudentIndex(int rollNumber) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].getRollNumber() == rollNumber) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Sort students by roll number
void StudentManager::sortStudentsByRollNumber() {
    std::sort(students.begin(), students.end(), 
        [](const Student& a, const Student& b) {
            return a.getRollNumber() < b.getRollNumber();
        });
}

// Load student records from file
void StudentManager::loadFromFile() {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cout << "No existing data file found. Starting with empty database.\n";
        return;
    }
    
    std::string line;
    int loadedCount = 0;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            try {
                Student s = Student::fromString(line);
                students.push_back(s);
                loadedCount++;
            } catch (const std::exception& e) {
                std::cerr << "Error loading record: " << e.what() << std::endl;
            }
        }
    }
    
    inFile.close();
    sortStudentsByRollNumber();
    std::cout << "Loaded " << loadedCount << " student records from " << filename << "\n";
}

// Save student records to file
void StudentManager::saveToFile() const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Cannot open file for writing!\n";
        return;
    }
    
    for (const auto& student : students) {
        outFile << student.toString() << "\n";
    }
    
    outFile.close();
    std::cout << "Data saved successfully to " << filename << "\n";
}

// Add new student
bool StudentManager::addStudent(const Student& student) {
    if (isRollNumberExists(student.getRollNumber())) {
        std::cout << "Error: Student with roll number " << student.getRollNumber() 
                  << " already exists!\n";
        return false;
    }
    
    students.push_back(student);
    sortStudentsByRollNumber();
    saveToFile();
    std::cout << "Student added successfully!\n";
    return true;
}

// Delete student
bool StudentManager::deleteStudent(int rollNumber) {
    int index = findStudentIndex(rollNumber);
    if (index == -1) {
        std::cout << "Error: Student with roll number " << rollNumber << " not found!\n";
        return false;
    }
    
    students.erase(students.begin() + index);
    saveToFile();
    std::cout << "Student deleted successfully!\n";
    return true;
}

// Search student by roll number
Student* StudentManager::searchStudent(int rollNumber) {
    int index = findStudentIndex(rollNumber);
    if (index != -1) {
        return &students[index];
    }
    return nullptr;
}

// Update student information
bool StudentManager::updateStudent(int rollNumber, const Student& updatedStudent) {
    int index = findStudentIndex(rollNumber);
    if (index == -1) {
        std::cout << "Error: Student with roll number " << rollNumber << " not found!\n";
        return false;
    }
    
    // Check if new roll number conflicts (if roll number changed)
    if (updatedStudent.getRollNumber() != rollNumber && 
        isRollNumberExists(updatedStudent.getRollNumber())) {
        std::cout << "Error: New roll number already exists!\n";
        return false;
    }
    
    students[index] = updatedStudent;
    sortStudentsByRollNumber();
    saveToFile();
    std::cout << "Student information updated successfully!\n";
    return true;
}

// Display all students
void StudentManager::displayAllStudents() const {
    if (students.empty()) {
        std::cout << "\nNo students in the database.\n";
        return;
    }
    
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << std::setw(10) << "Roll No" 
              << std::setw(25) << "Name"
              << std::setw(10) << "Age" 
              << std::setw(15) << "Grade"
              << std::setw(20) << "Email" << "\n";
    std::cout << std::string(80, '-') << "\n";
    
    for (const auto& student : students) {
        std::cout << std::setw(10) << student.getRollNumber()
                  << std::setw(25) << student.getName()
                  << std::setw(10) << student.getAge()
                  << std::setw(15) << student.getGrade()
                  << std::setw(20) << student.getEmail() << "\n";
    }
    std::cout << std::string(80, '=') << "\n";
    std::cout << "Total students: " << students.size() << "\n\n";
}

// Get total student count
int StudentManager::getStudentCount() const {
    return students.size();
}

// Check if roll number exists
bool StudentManager::isRollNumberExists(int rollNumber) const {
    return findStudentIndex(rollNumber) != -1;
}

// Calculate average age
double StudentManager::getAverageAge() const {
    if (students.empty()) return 0.0;
    
    int totalAge = 0;
    for (const auto& student : students) {
        totalAge += student.getAge();
    }
    return static_cast<double>(totalAge) / students.size();
}

// Display statistics
void StudentManager::displayStatistics() const {
    std::cout << "\n========== SYSTEM STATISTICS ==========\n";
    std::cout << "Total Students: " << getStudentCount() << "\n";
    
    if (getStudentCount() > 0) {
        std::cout << "Average Age: " << std::fixed << std::setprecision(2) 
                  << getAverageAge() << " years\n";
        
        // Find youngest and oldest
        int minAge = 999, maxAge = 0;
        for (const auto& student : students) {
            minAge = std::min(minAge, student.getAge());
            maxAge = std::max(maxAge, student.getAge());
        }
        std::cout << "Age Range: " << minAge << " - " << maxAge << " years\n";
    }
    std::cout << "=======================================\n";
}
