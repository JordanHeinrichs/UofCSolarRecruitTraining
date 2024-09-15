#include "Person.h"
#include <iostream>

Person::Person() {
    name_ = "";
    age_ = new int(0);
}

// Destructor
Person::~Person() {
    delete age_; 
}

// Parameterized Constructor
Person::Person(const std::string& name, int age) {
    name_ = name;
    age_ = new int(age);
}

// Getter for age
int Person::getAge() const {
    return *age_;
}

// Getter for name
const std::string& Person::getName() const {
    return name_;
}

// Setter for name
void Person::setName(const std::string& newName) {
    name_ = newName;
}

// Setter for age
void Person::setAge(int newAge) {
    *age_ = newAge;
}

// Print out the name and age of the person
void Person::printInfo() const {
    std::cout << "Name: " << name_ << ", Age: " << *age_ << std::endl;
}

// Print the combined age of everyone pointed to by personArray
int Person::combinedAge(Person** personArray, int size) {
    int totalAge = 0;
    for (int i = 0; i < size; i++) {
        totalAge += personArray[i]->getAge();
    }
    return totalAge;
}

// Increases the Person's Age by 1
void Person::birthday(Person& x) {
    (*x.age_)++;
}