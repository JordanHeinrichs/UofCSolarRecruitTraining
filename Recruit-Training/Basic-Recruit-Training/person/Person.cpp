//
// Created by Johnny on 10/25/2023.
//
#include "Person.h"
#include <iostream>

//Constructors
Person::Person() { // No param make age 0 and name a blank string
    age_ = new int(0);
    name_ = "";
};
Person::Person(const std::string &name, int age) {
    name_ = name;
    age_ = new int(age);
};
Person::~Person(){ // ~Person Refers to deconstructor, what happens when out of scope
    delete age_;
};
//Setters and Getters
int Person::getAge() const {
    return *age_; // Returns value of age_ constant
}
const std::string& Person::getName() const {
    return name_;
}
void Person::setAge(int newAge) {
    *age_ = newAge;
}
void Person::setName(const std::string &newName) {
    name_ = newName;
}

// Functions
void Person::printInfo() const {
    std::cout<<"Name: "<< getName();
    std::cout<<"Age: "<< getAge() <<std::endl;
}
int Person::combinedAge(Person **personArray, int size) {
    int total = 0;
    for (int i = 0; i < size ; ++i) {
        total += personArray[i]->getAge(); // add that person class at index i age to total
    }
    return total;
}
void Person::birthday(Person &x) {
    *x.age_+=1;
}


