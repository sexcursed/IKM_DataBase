#include "ui.h"

#include <windows.h>

void setConsoleToUTF8() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif
}

int main(){
  setConsoleToUTF8();
  Database database;
  bool programStatus = true;
  while(programStatus){
    try{
      displayMenu();
      int userInput = getUserInput();
      inputHandler(userInput, database, programStatus);
    }
    catch(std::exception& e){
      std::cerr << "\nОшибка! " << e.what() << "\n";
      std::cerr << "Очистка буфера ввода...\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return 0;
}