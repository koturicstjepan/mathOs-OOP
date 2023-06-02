#include <iostream>

using namespace std;

class Person{
    protected:
        string firstName, lastName;
        unsigned int age;
    public:
        Person();
        Person(const Person&);
        Person(const string&, const string&, unsigned int );
        ~Person();

        friend ostream& operator<<(ostream& os, const Person &p);
};

Person::Person(): firstName{},lastName{}, age{}{}
Person::Person(const Person& p): firstName{p.firstName},lastName{p.lastName}, age{p.age}{}
Person::Person(const string& firstName, const string& lastName, unsigned int age): firstName{firstName},lastName{lastName}, age{age}{}
Person::~Person(){}

ostream& operator<<(ostream& os, const Person &p){
    return os << "First Name: " << p.firstName << "; last name: " << p.lastName << "; age: " << p.age;
}


class Employee: public Person{
protected:
    string company;
public:
    Employee();
    Employee(const Employee&);
    Employee(const string&, const string&, unsigned int, const string&);
    ~Employee();

    friend ostream& operator<<(ostream& os, const Employee &p);
};

Employee::Employee(): Person{}, company{}{}
Employee::Employee(const Employee& e): Person{(Person) e}, company{e.company}{}
Employee::Employee(const string& firstName, const string& lastName, unsigned int age, const string& company):
    Person{firstName, lastName, age}, company{company}{}
Employee::~Employee(){}

ostream& operator<<(ostream& os, const Employee &e){
    return os << (Person) e << "; works at: " << e.company;
}


int main() {
    Person p{"Ivan", "Ivic", 35};
    Employee e{"Marko", "Marić", 37, "HP"};
    
    cout << p << "\n";
    cout << e << "\n";

    return 0;
}
