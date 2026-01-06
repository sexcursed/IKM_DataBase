#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>
#include <iomanip>

struct Record{

  int id;
  std::string name;
  int age;
  int salary;

  Record();
  Record(std::string name, int age, int salary);
  void display();

};

#endif