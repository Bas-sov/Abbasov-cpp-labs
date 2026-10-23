#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <limits>
#include "Pipe.h"
#include "Station.h"

template <typename T>
void readValidNumber(T& value, const std::string& prompt, const T& a, const T& b = std::numeric_limits<T>::max()) {
	while (true) {
		std::cout << prompt;
		if (std::cin.peek() == ' ' || std::cin.peek() == '\t' || std::cin.peek() == '\n') {
			std::cout << "Ошибка: значение начинается с пробела/табуляции/переноса строки" << std::endl;
			std::cin.ignore(100, '\n');
			continue;
		}
		std::cin >> value;
		if (std::cin.fail() || std::cin.peek() != '\n') {
			std::cout << "Ошибка: значение должно быть без лишних символов" << std::endl;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			continue;
		}
		else if (value < a || value > b) {
			std::cout << "Ошибка: значение должно быть от " << a << " до " << b << std::endl;
			std::cin.ignore(100, '\n');
			continue;
		}
		else {
			std::cin.ignore(100, '\n');
			break;
		}
	}
}

inline void readValidName(std::string& str, const std::string& prompt) {
	while (true) {
		std::cout << prompt;
		getline(std::cin, str);
		if (str.empty() || str[0] == ' ' || str[0] == '\t' ||
			str[str.size() - 1] == ' ' || str[str.size() - 1] == '\t') {
			std::cout << "Ошибка: некорректный ввод" << std::endl;
			continue;
		}
		else {
			break;
		}
	}
}

template<typename Item>
void inputObjects(std::unordered_map<int, Item>& items) {
	Item item;
	std::cin >> item;
	items.emplace(item.getID(), item);
}

template <typename Item>
void outputOdjects(const std::unordered_map<int, Item>& items, const std::string& prompt) {
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
void loadContainer(std::ifstream& inFile, std::unordered_map<int, Item>& items) {
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
	}
}

template <typename Container1, typename Container2>
void loadDataFromFile(const std::string& file_name, Container1& pipes, Container2& css) {
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
		loadContainer(inFile, pipes);
		loadContainer(inFile, css);
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