#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

/**
 * @brief Represents a single student with personal and academic information
 * 
 * This class encapsulates all data related to a student and provides
 * methods to access and modify that data following OOP principles.
 */
class Student {
private:
    int rollNumber;
    std::string name;
    int age;
    std::string grade;
    std::string email;

public:
    // Constructors
    Student();
    Student(int roll, const std::string& name, int age, 
            const std::string& grade, const std::string& email);
    
    // Getters (accessors)
    int getRollNumber() const;
    std::string getName() const;
    int getAge() const;
    std::string getGrade() const;
    std::string getEmail() const;
    
    // Setters (mutators)
    void setName(const std::string& name);
    void setAge(int age);
    void setGrade(const std::string& grade);
    void setEmail(const std::string& email);
    
    // Utility methods
    void display() const;
    std::string toString() const;
    static Student fromString(const std::string& data);
    
    // Operator overloading for comparison
    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
};

#endif // STUDENT_H
