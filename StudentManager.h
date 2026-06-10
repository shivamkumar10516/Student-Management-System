#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include <vector>
#include <string>

/**
 * @brief Manages a collection of Student objects
 * 
 * This class handles all operations related to student management
 * including CRUD operations, file I/O, and data persistence.
 */
class StudentManager {
private:
    std::vector<Student> students;
    const std::string filename;
    
    // Helper methods
    int findStudentIndex(int rollNumber) const;
    void sortStudentsByRollNumber();
    
public:
    // Constructor
    StudentManager(const std::string& file = "students.txt");
    
    // File operations
    void loadFromFile();
    void saveToFile() const;
    
    // Student management operations
    bool addStudent(const Student& student);
    bool deleteStudent(int rollNumber);
    Student* searchStudent(int rollNumber);
    bool updateStudent(int rollNumber, const Student& updatedStudent);
    void displayAllStudents() const;
    int getStudentCount() const;
    
    // Validation
    bool isRollNumberExists(int rollNumber) const;
    
    // Statistics
    double getAverageAge() const;
    void displayStatistics() const;
};

#endif // STUDENTMANAGER_H
