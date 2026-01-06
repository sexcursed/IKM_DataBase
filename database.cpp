#include "database.h"

Database::Database(): nextId(1) {};

void Database::addRecord(Record& record){
  Record newRecord = record;
  newRecord.id = nextId++;
  db.push_back(newRecord);
  std::cout << "Добавлена запись с ID:" << newRecord.id << "\n";
}

void Database::viewDb(){
  if(db.empty()){
    std::cout << "База данных пуста" << "\n";
    return;
  }
  std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "ИМЯ" << std::setw(10) << "ВОЗРАСТ" << std::setw(15) << "ЗАРПЛАТА" << "\n" << std::string(50,'-') << "\n";
  for(auto record : db){
    record.display();
  }
  std::cout << "Кол-во записей:" << db.size() << "\n";
}

int Database::findIndex(int id){
  for(size_t i = 0; i < db.size(); ++i){
    if(db[i].id == id){
      return static_cast<int>(i);
    }
  }
  return -1;
}

bool Database::deleteRecord(int id){
  int index = findIndex(id);
  if(index != -1){
    db.erase(db.begin() + index);
    std::cout << "Запись с ID " << id << " удалена.\n";
    return 1;
  }
  std::cout << "Запись с ID " << id << " не найдена.\n";
  return 0;
}

std::vector <Record> Database::search(SearchField field, std::string value){
  std::vector<Record> result;

  for(auto record : db){
    bool match = false;

    switch(field){
      case SEARCH_BY_ID:{
        if(std::to_string(record.id) == value) match = true;
        break;
      }
      case SEARCH_BY_NAME:{
        if(record.name == value) match = true;
        break;
      }
      case SEARCH_BY_AGE:{
        if(std::to_string(record.age) == value) match = true;
        break;
      }
      case SEARCH_BY_SALARY:{
        if(std::to_string(record.salary) == value) match = true;
        break;
      }
    }

    if(match) result.push_back(record);
  }

  return result;
}

void Database::sort(SortField field){
  switch(field){
    case SORT_BY_ID:{
      std::sort(db.begin(),db.end(),[](Record a, Record b){return a.id < b.id;});
      break;
    }
    case SORT_BY_NAME:{
      std::sort(db.begin(),db.end(),[](Record a, Record b){return a.id < b.id;});
      break;
    }
    case SORT_BY_AGE:{
      std::sort(db.begin(),db.end(),[](Record a, Record b){return a.age < b.age;});
      break;
    }
    case SORT_BY_SALARY:{
      std::sort(db.begin(),db.end(),[](Record a, Record b){return a.salary < b.salary;});
      break;
    }
  }
  std::cout << "Успешно остортировано.\n";
}

bool Database::saveToFile(std::string& filename){
  std::ofstream file(filename);
  
  if (!file.is_open()) {
    std::cerr << "Ошибка открытия файла для записи.\n";
    return false;
  }
  
  for (auto record : db) {
      file << record.id << "," << record.name << "," << record.age << "," << record.salary << "\n";
  }
  
  file.close();
  std::cout << "Данные сохранены в файл: " << filename << "\n";
  return true;
}

bool Database::loadFromFile(std::string& filename) {
  std::ifstream file(filename);
  
  if (!file.is_open()) {
    std::cerr << "Ошибка открытия файла для чтения.\n";
    return false;
  }
  
  db.clear();
  nextId = 1;
  
  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    
    std::stringstream ss(line);
    std::string temp;
    Record record;
    
    std::getline(ss, temp, ',');
    record.id = std::stoi(temp);
    std::getline(ss, record.name, ',');
    std::getline(ss, temp, ',');
    record.age = std::stoi(temp);
    std::getline(ss, temp, ',');
    record.salary = std::stod(temp);
    db.push_back(record);

    if (record.id >= nextId) {
        nextId = record.id + 1;
    }
  }
  
  file.close();
  std::cout << "Данные загружены из файла: " << filename << "\n";

  return true;
}

size_t Database::getRecordCount(){
  return db.size();
}

void Database::clear(){
  db.clear();
  nextId = 1;
  std::cout << "База данных очищена.\n";
}