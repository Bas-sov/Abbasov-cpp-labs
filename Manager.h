#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"


class Manager
{
private:
	std::unordered_map <int, Pipe> pipes = {};
	std::unordered_map <int, Station> css = {};
	int maxPipeID = 1;
	int maxStationID = 1;
public:
	void addPipe();
	void addStation();
	void showAll() const;
	void saveToFile() const;
	void loadFromFile();
	void searchPipes();
	void searchStations();
};

template<typename Item>
void inputObjects(std::unordered_map<int, Item>& items, int maxObjectID) {
	Item item;
	item.setID(maxObjectID);
	std::cin >> item;
	items.emplace(item.getID(), item);
}

template <typename Item>
void outputObjects(const std::unordered_map<int, Item>& items, const std::string& prompt) {
	if (!items.empty()) {
		std::cout << prompt << std::endl;
		for (const auto& item : items) {
			std::cout << item.second;
			std::cout << std::endl;
		}
	}
}

template <typename Item>
void writeContainer(std::ofstream& outFile, const std::unordered_map<int, Item>& items) {
	outFile << items.size() << '\n';
	for (const auto& item : items) {
		outFile << item.second;
	}
}

template <typename Container1, typename Container2>
void savedDataToFile(const std::string& file_name, const Container1& pipes, const Container2& css) {
	std::ofstream outFile(file_name);
	if (!outFile.is_open()) {
		std::cout << "Ошибка: не удалось открыть файл" << std::endl;
		return;
	}
	writeContainer(outFile, pipes);
	writeContainer(outFile, css);
	std::cout << "Объект(ы) добавлен(ы) в файл" << std::endl;
	outFile.close();
}

template <typename Item>
void loadContainer(std::ifstream& inFile, std::unordered_map<int, Item>& items, int& maxObjectID) {
	int count = 0;
	inFile >> count;
	if (count == 0) {
		return;
	}
	items.clear();
	Item item;
	for (int i = 0; i < count; i++) {
		inFile >> item;
		items.emplace(item.getID(), item);
		maxObjectID = std::max(maxObjectID, item.getID() + 1);
	}
}

template <typename Container1, typename Container2>
void loadDataFromFile(const std::string& file_name, Container1& pipes, Container2& css, int& maxPipeID, int& maxStationID) {
	std::ifstream inFile(file_name);
	if (!inFile.is_open()) {
		std::cout << "Ошибка: не удалось открыть файл" << std::endl;
		return;
	}
	else if (inFile.peek() == EOF) {
		std::cout << "Предупреждение: файл пуст" << std::endl;
		return;
	}
	else {
		loadContainer(inFile, pipes, maxPipeID);
		loadContainer(inFile, css, maxStationID);
		std::cout << "Данные успешно считаны!" << std::endl;
	}
	inFile.close();
}


template <typename Item>
bool checkByName(const Item& item, const std::string& name) {
	return item.getName().find(name) != std::string::npos;
}

inline bool checkByRepair(const Pipe& p, bool underRepair) {
	return p.getUnderRepair() == underRepair;
}

inline bool checkByWorkshops(const Station& cs, double unusedWorkshops) {
	return cs.getUnusedWorkshops() <= unusedWorkshops;
}

template<typename Item, typename Filter, typename T>
std::vector<int> findAndoutputObjectsByFilter(const std::unordered_map<int, Item>& items, Filter filter, const T& parametr) {
	std::vector <int> result;
	for (const auto& item : items) {
		if (filter(item.second, parametr)) {
			result.push_back(item.first);
		}
	}
	for (int id : result) {
		std::cout << items.at(id) << std::endl;
	}
	return result;
}

inline bool isFound(int id, const std::vector<int>& found_result) {
	bool is_found = false;
	for (int valid_id : found_result) {
		if (id == valid_id) {
			is_found = true;
		}
	}
	if (!is_found) {
		return false;
	}
	return true;
}

inline bool isDuplicate(int id, const std::vector<int>& selected_ids) {
	bool is_duplicate = false;
	for (int existing_id : selected_ids) {
		if (existing_id == id) {
			is_duplicate = true;
		}
	}
	if (is_duplicate) {
		return true;
	}
	return false;
}

template <typename Item>
std::vector<int> inputSpecificIDs(const std::unordered_map<int, Item>& items, const std::vector<int>& found_result) {
	std::vector<int> selected_ids;
	int id = 0;
	while (true) {
		readValidNumber(id, "Введите ID (0 - чтобы закончить ввод): ", 0);
		if (id == 0) {
			if (!selected_ids.empty()) {
				break;
			}
			std::cout << "Вы не выбрали ни одного ID. Действие отменено" << std::endl;
			continue;
		}
		if (!isFound(id, found_result)) {
			std::cout << "Ошибка: ID " << id << " отсутствует в результатах поиска" << std::endl;
			continue;
		}
		if (isDuplicate(id, selected_ids)) {
			std::cout << "Этот ID уже выбран\n";
			continue;
		}
		selected_ids.push_back(id);
		std::cout << "ID " << id << " выбран\n";
	}
	return selected_ids;
}

template<typename Item>
void deleteObjectsByFilter(std::unordered_map<int, Item>& items, const std::vector<int>& result) {
	for (const auto& i : result) {
		items.erase(i);
	}
}

inline void editPipes(std::unordered_map<int, Pipe>& pipes, const std::vector<int>& result) {
	for (const auto& i : result) {
		pipes[i].editUnderRepair();
	}
}

inline void editStations(std::unordered_map<int, Station>& css, const std::vector<int>& result) {
	double workshopPercentage = 0;
	readValidNumber(workshopPercentage, "Введите процент рабочих цехов от общего кол-ва цехов: ", 0.0, 100.0);
	for (const auto& i : result) {
		css[i].editTotalWorkingShops(workshopPercentage);
	}
}

template<typename Item, typename EditFun>
void executeByFilter(std::unordered_map<int, Item>& items, const std::vector<int>& result, EditFun editFun) {
	int value = {};
	readValidNumber(value, "Действие: 1-удалить, 2-редактировать: ", 1, 2);
	if (value == 1) {
		deleteObjectsByFilter(items, result);
	}
	else {
		editFun(items, result);
	}
}

template <typename Item, typename ExecuteFun>
void clarifyByFilter(std::unordered_map<int, Item>& items, const std::vector<int>& result, ExecuteFun executeFun) {
	int value = {};
	readValidNumber(value, "Уточнить: 1-все найденные, 2-конкретные id: ", 1, 2);
	if (value == 1) {
		executeByFilter(items, result, executeFun);
	}
	else {
		std::vector<int> selected_ids = inputSpecificIDs(items, result);
		executeByFilter(items, selected_ids, executeFun);
	}
}

template <typename Item>
void searchByName(const std::unordered_map<int, Item>& items, std::vector<int>& foundObjects) {
	std::string name;
	while (true) {
		readValidName(name, "Введите название трубы: ");
		foundObjects = findAndoutputObjectsByFilter(items, checkByName<Item>, name);
		if (!foundObjects.empty()) {
			break;
		}
		std::cout << "Предупреждение: объектов с таким признаком не существует" << std::endl;
	}
}

template <typename T, typename Item, typename Filter >
void searchByValue(const std::unordered_map<int, Item>& items, std::vector<int>& foundObjects, const std::string& prompt, T a, T b, Filter function) {
	T searchValue;
	while (true) {
		readValidNumber(searchValue, prompt, a, b);
		foundObjects = findAndoutputObjectsByFilter(items, function, searchValue);
		if (!foundObjects.empty()) {
			break;
		}
		std::cout << "Предупреждение: объектов с таким признаком не существует" << std::endl;
	}
}

inline void searchPipes(std::unordered_map<int, Pipe>& pipes) {
	std::vector<int> foundPipes;
	int value = {};
	readValidNumber(value, "Найти по: 1-названию, 2-признаку «в ремонте»: ", 1, 2);
	if (value == 1) {
		searchByName(pipes, foundPipes);
	}
	else {
		searchByValue(pipes, foundPipes, "Введите 1-труба на ремонте, 0-труба в рабочем состоянии: ", false, true, checkByRepair);
	}
	clarifyByFilter(pipes, foundPipes, editPipes);
}

inline void searchStations(std::unordered_map<int, Station>& css) {
	std::vector<int> foundStations;
	int value = {};
	readValidNumber(value, "Найти по: 1-названию, 2-по проценту незадействованных цехов: ", 1, 2);
	if (value == 1) {
		searchByName(css, foundStations);
	}
	else {
		searchByValue(css, foundStations, "Введите процент незадействованных цехов (<=): ", 0.0, 100.0, checkByWorkshops);
	}
	clarifyByFilter(css, foundStations, editStations);
}