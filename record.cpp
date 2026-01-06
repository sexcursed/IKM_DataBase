#include "record.h"


Record::Record(): id(0), name(""), age(0), salary(0) {}
Record::Record(std::string name, int age, int salary): name(name), age(age), salary(salary) {}

void Record::display(){
  std::cout << std::left << std::setw(5) << id << std::setw(20) << name << std::setw(10) << age << std::setw(15) << salary << "\n";
}