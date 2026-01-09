#ifndef UI_H
#define UI_H

#include "database.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

void displayMenu();
int getUserInput();
void inputHandler(int input, Database& db, bool& status);
void addRecordHandler(Database& db);
void deleteRecordHandler(Database& db);
void searchRecordsHandler(Database& db);
void sortRecordsHandler(Database& db);
void saveToFileHandler(Database& db);
void loadFromFileHandler(Database& db);
void databaseClearHandler(Database& db);

#endif