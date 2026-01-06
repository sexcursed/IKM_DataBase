#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "record.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

enum SortField{ SORT_BY_ID, SORT_BY_NAME, SORT_BY_AGE, SORT_BY_SALARY};
enum SearchField{ SEARCH_BY_ID, SEARCH_BY_NAME, SEARCH_BY_AGE, SEARCH_BY_SALARY};

class Database{
  private:
    std::vector <Record> db;
    int nextId;
    int findIndex(int id);
  public:
    Database();

    void addRecord(Record& record);
    void viewDb();
    bool deleteRecord(int id);

    std::vector <Record> search(SearchField field, std::string value);
    void sort(SortField field);

    bool saveToFile(std::string& filename);
    bool loadFromFile(std::string& filename);

    size_t getRecordCount();
    void clear();
};

#endif