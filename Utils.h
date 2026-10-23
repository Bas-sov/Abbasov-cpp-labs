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