#include "Student.h"
#include <sstream>
#include <iomanip>

// Default constructor
Student::Student() : rollNumber(0), name(""), age(0), grade(""), email("") {}

// Parameterized constructor
Student::Student(int roll, const std::string& name, int age, 
                 const std::string& grade, const std::string& email)
    : rollNumber(roll), name(name), age(age), grade(grade), email(email) {}

// Getters
int Student::getRollNumber() const { return rollNumber; }
std::string Student::getName() const { return name; }
int Student::getAge() const { return age; }
std::string Student::getGrade() const { return grade; }
std::string Student::getEmail() const { return email; }

// Setters with validation
void Student::setName(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
    this->name = name;
}

void Student::setAge(int age) {
    if (age < 1 || age > 120) {
        throw std::invalid_argument("Age must be between 1 and 120");
    }
    this->age = age;
}

void Student::setGrade(const std::string& grade) {
    if (grade.empty()) {
        throw std::invalid_argument("Grade cannot be empty");
    }
    this->grade = grade;
}

void Student::setEmail(const std::string& email) {
    // Basic email validation
    if (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
        throw std::invalid_argument("Invalid email format");
    }
    this->email = email;
}

// Display student information in formatted way
void Student::display() const {
    std::cout << "\n┌─────────────────────────────────────────┐\n";
    std::cout << "│ Student Information                     │\n";
    std::cout << "├─────────────────────────────────────────┤\n";
    std::cout << "│ Roll Number: " << std::setw(30) << std::left << rollNumber << "│\n";
    std::cout << "│ Name:        " << std::setw(30) << name << "│\n";
    std::cout << "│ Age:         " << std::setw(30) << age << "│\n";
    std::cout << "│ Grade:       " << std::setw(30) << grade << "│\n";
    std::cout << "│ Email:       " << std::setw(30) << email << "│\n";
    std::cout << "└─────────────────────────────────────────┘\n";
}

// Convert student data to string for file storage
std::string Student::toString() const {
    return std::to_string(rollNumber) + "|" + name + "|" + 
           std::to_string(age) + "|" + grade + "|" + email;
}

// Create Student object from file string
Student Student::fromString(const std::string& data) {
    std::stringstream ss(data);
    std::string token;
    int roll, age;
    std::string name, grade, email;
    
    std::getline(ss, token, '|');
    roll = std::stoi(token);
    
    std::getline(ss, name, '|');
    
    std::getline(ss, token, '|');
    age = std::stoi(token);
    
    std::getline(ss, grade, '|');
    std::getline(ss, email, '|');
    
    return Student(roll, name, age, grade, email);
}

// Equality operator
bool Student::operator==(const Student& other) const {
    return rollNumber == other.rollNumber;
}

bool Student::operator!=(const Student& other) const {
    return !(*this == other);
}
