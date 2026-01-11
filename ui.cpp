#include "ui.h"

void displayMenu(){
  std::cout << "\n=== МИНИ-СУБД  -  МЕНЮ ===\n";
  std::cout << "1.  Добавить новую запись\n";
  std::cout << "2.  Показать все записи\n";
  std::cout << "3.  Удалить запись по ID\n";
  std::cout << "4.  Поиск записей\n";
  std::cout << "5.  Сортировка записей\n";
  std::cout << "6.  Сохранить данные в файл\n";
  std::cout << "7.  Загрузить данные из файла\n";
  std::cout << "8.  Очистить базу данных\n";
  std::cout << "9.  Выход из программы\n";
  std::cout << "----------------------------------\n";
  std::cout << "Выберите действие: ";
}

int getUserInput(){
  int choice;
  std::cin >> choice;

  if(std::cin.fail()){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return -1;
  }

  return choice;
}

void addRecordHandler(Database& db){
  std::string name;
  int age, salary;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Введите имя нового пользователя: ";
  std::getline(std::cin, name);

  while(true){
    std::cout << "Введите возраст нового пользователя: ";
    std::cin >> age;

    if(std::cin.fail() or age < 0){
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Оишбка! Возраст должен быть целым положительным числом.\n";
    }
    else{
      break;
    }
  }

  while(true){
    std::cout << "Введите зарплату нового пользователя: ";
    std::cin >> salary;

    if(std::cin.fail() or salary < 0){
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Ошибка! Зарплата должна быть целым положительным числом.\n";
    }
    else{
      break;
    }
  }

  db.addRecord(Record(name,age,salary));
}

void deleteRecordHandler(Database& db){
  int id;
  std::cout << "Текущие записи в базе:\n";
  db.viewDb();

  std::cout << "\nВведите ID записи для удаления:";
  std::cin >> id;

  db.deleteRecord(id);
}

void searchRecordsHandler(Database& db){
  int choice;
  std::string value;
  std::cout << "Выберите поле для поиска:\n";
  std::cout << "1. По ID\n";
  std::cout << "2. По имени\n";
  std::cout << "3. По возрасту\n";
  std::cout << "4. По зарплате\n";
  std::cout << "Выберите действие: ";

  std::cin >> choice;

  if(choice < 1 or choice > 4){
    std::cout << "Ошибка! Неверный выбор.\n";
    return;
  }
  
  std::cout << "Введите значение для поиска: ";
  std::cin >> value;

  SearchField field;
  switch(choice){
    case 1:{
      field = SEARCH_BY_ID;
      break;
    }
    case 2:{
      field = SEARCH_BY_NAME;
      break;
    }
    case 3:{
      field = SEARCH_BY_AGE;
      break;
    }
    case 4:{
      field = SEARCH_BY_SALARY;
      break;
    }
  }

  std::vector <Record> result = db.search(field, value);
  
  if(result.empty()){
    std::cout << "Записи не найдены.\n";
    return;
  }

  std::cout << "Найдено " << result.size() << " записей.\n";
  std::cout << std::left << std::setw(5) << "ID" << std::setw(18) << "ИМЯ" << std::setw(22) << "ВОЗРАСТ" << std::setw(15) << "ЗАРПЛАТА" << "\n" << std::string(50,'-') << "\n";
  for(auto record : result){
    record.display();
  }
}

void sortRecordsHandler(Database& db){
  int choice;

  std::cout << "Выберите поле для сортировки:\n";
  std::cout << "1. По ID\n";
  std::cout << "2. По имени\n";
  std::cout << "3. По возрасту\n";
  std::cout << "4. По зарплате\n";
  std::cout << "Выберите действие: ";

  std::cin >> choice;

  if(choice < 1 or choice > 4){
    std::cout << "Ошибка! Неверный выбор.\n";
    return;
  }

  SortField field;
  switch(choice){
    case 1:{
      field = SORT_BY_ID;
      break;
    }
    case 2:{
      field = SORT_BY_NAME;
      break;
    }
    case 3:{
      field = SORT_BY_AGE;
      break;
    }
    case 4:{
      field = SORT_BY_SALARY;
      break;
    }
  }

  db.sort(field);
  char confirm;
  std::cout << "Показать результат? (y/n):";
  std::cin >> confirm;

  if(confirm == 'y' or confirm == 'Y'){
    db.viewDb();
  }
}

void saveToFileHandler(Database& db){
  std::string filename;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "Введите имя файла:";
  std::getline(std::cin, filename);

  if(filename.empty()){
    filename = "savetest.txt";
  }
  if(db.saveToFile(filename)){
    std::cout << "Данные сохранены в файл: " << filename << "\n";
  }
  else{
    std::cout << "Ошибка открытия файла для записи.\n";
  }
}

void loadFromFileHandler(Database& db) {
  std::string filename;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
  if (db.getRecordCount() > 0) {
    char confirm;
    std::cout << "ВНИМАНИЕ: Текущие данные будут потеряны!\n";
    std::cout << "Продолжить? (y/n): ";
    std::cin >> confirm;
    
    if (confirm != 'y' and confirm != 'Y') {
      std::cout << "Загрузка отменена.\n";
      return;
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  
  std::cout << "Введите имя файла для загрузки: ";
  std::getline(std::cin, filename);
  
  if (db.loadFromFile(filename)) {
    std::cout << "Данные успешно загружены из файла: " << filename << "\n";
    std::cout << "Загружено записей: " << db.getRecordCount() << "\n";
  } else {
    std::cout << "Ошибка! Не удалось открыть файл " << filename << " для чтения.\n";
  }
}

void clearDatabaseHandler(Database& db){
  char confirm;
  if(db.getRecordCount() == 0){
    std::cout << "База данных уже пуста.\n";
    return;
  }

  std::cout << "Вы уверены, что хотите очистить все данные? (y/n):";
  std::cin >> confirm;

  if(confirm == 'y' or confirm == 'Y'){
    db.clear();
    std::cout << "База данных очищена.\n";
  }
  else{
    std::cout << "Очистка отменена.\n";
  }
}

void inputHandler(int choice, Database& db, bool& status){
  switch (choice)
  {
  case 1:{
    addRecordHandler(db);
    break;
  }
  case 2:{
    db.viewDb();
    break;
  }
  case 3:{
    deleteRecordHandler(db);
    break;
  }
  case 4:{
    searchRecordsHandler(db);
    break;
  }
  case 5:{
    sortRecordsHandler(db);
    break;
  }
  case 6:{
    saveToFileHandler(db);
    break;
  }
  case 7:{
    loadFromFileHandler(db);
    break;
  }
  case 8:{
    clearDatabaseHandler(db);
    break;
  }
  case 9:{
    char confirm;
    std::cout << "Вы увереный что хотите выйти из программы?(y/n)\n";
    std::cin >> confirm;
    if(confirm == 'y' or confirm == 'Y')
    {
      std::cout << "Завершение работы программы.\n";
      status = false;
      break;
    }
    break;
  }
  default:{
    std::cout << "\nОшибка! Введите число от 1 до 10.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    break;
  }
  }
}