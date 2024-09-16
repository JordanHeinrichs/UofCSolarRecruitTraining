    #include <iostream>
    #include "Person.h"
    
    using namespace std;
    
    Person::Person(){
        name_ = "";
        age_ = new int(-1);
    }

    Person::~Person(){
        free(age_);
    }
    
    Person::Person(const std::string& name, int age):name_(name),age_(new int(age)){
    }

    // setters and getters
    int Person::getAge() const{
        return *(this->age_);
    }

    const std::string& Person::getName() const{
        return name_;
    }

    void Person::setName(const std::string& newName){
        name_ = newName;
        
        return;
    }

    void Person::setAge(int newAge){
        free(age_);
        age_ = new int(newAge);

        return;
    }

    // Print out the name and age of the person
    void Person::printInfo() const{
        cout << "Name: " << name_ << endl;
        cout << "Age: " << *age_ << endl;

        return;
    }
    // Print the combined age of everyone pointed to by personArray
    int Person::combinedAge(Person** personArray, int size){
        int total_age = 0;
        for(int i = 0; i < size; i++){
            total_age += personArray[i]->getAge();
        }

        return total_age;
    }

    // Increases the Person's Age by 1
    void Person::birthday(Person& x){
        x.setAge(x.getAge() + 1);

        return;
    }