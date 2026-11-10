#include <iostream>
#include <vector>
#include "GTS.h"
#include "Utils.h"

using namespace std;

void GTS::addPipe()
{
	inputObjects(pipes, maxPipeID++);
}

void GTS::addStation()
{
	inputObjects(css, maxStationID++);
}

void GTS::showAll() const
{
	if (pipes.empty() && css.empty()) {
		cout << "Предупреждение: Труба и КС не созданы" << endl;
		return;
	}
	outputObjects(pipes, "Вывод данных для трубы:");
	outputObjects(css, "Вывод данных для станции:");
	outputConnections(connections);
}

void GTS::editPipes(const std::vector<int>& result)
{
	for (const auto& i : result) {
		pipes[i].editUnderRepair();
	}
}

void GTS::editStations(const std::vector<int>& result)
{
	double workshopPercentage = 0;
	readValidNumber(workshopPercentage, "Введите процент рабочих цехов от общего кол-ва цехов: ", 0.0, 100.0);
	for (const auto& i : result) {
		css[i].editTotalWorkingShops(workshopPercentage);
	}
}

void GTS::saveToFile() const
{
	if (pipes.empty() && css.empty()) {
		cout << "Предупреждение: Труба и КС не созданы" << endl;
		return;
	}
	string file_name;
	cout << "Укажите название файла: ";
	getline(cin, file_name);
	savedDataToFile(file_name, pipes, css, connections);
}

void GTS::loadFromFile()
{
	string file_name;
	cout << "Укажите название файла: ";
	getline(cin, file_name);
	loadDataFromFile(file_name, pipes, css, connections, maxPipeID, maxStationID);
}

bool GTS::isPipeConnected(int id) const
{
	for (const auto& [key, value] : connections) {
		if (id == key) {
			return true;
		}
	}
	return false;
}

bool GTS::isStationConnected(int id) const
{
	for (const auto& [key, value] : connections) {
		if (id == value.first || id == value.second) {
			return true;
		}
	}
	return false;
}

void GTS::deletePipes(const std::vector<int>& result)
{
	for (const auto& id : result) {
		if (isPipeConnected(id)) {
			cout << "\nПредупреждение: Труба с ID " << id << " подключена к газотранспортной сети" << endl;
			int choice;
			readValidNumber(choice, "Удалить трубу с ID и соответствующее соединение? (1 - да, 0 - нет) : ", 0, 1);
			if (choice == 1) {
				connections.erase(id);
				pipes.erase(id);
				cout << "Труба с ID " << id << " и соответствующее соединение удалены" << endl;
			}
			else {
				continue;
			}
		}
		else {
			pipes.erase(id);
			cout << "Труба с ID " << id << " удалена" << endl;
		}
	}
}

void GTS::deleteStations(const std::vector<int>& result)
{
	for (const auto& id : result) {
		if (isStationConnected(id)) {
			int choice;
			cout << "\nПредупреждение: Станция с ID " << id << " подключена к газотранспортной сети" << endl;
			readValidNumber(choice, "Удалить станцию с ID и соответствующее соединение? (1 - да, 0 - нет) : ", 0, 1);
			if (choice == 1) {
				vector<int> toErase = {};
				for (const auto& [key, value] : connections) {
					if (value.first == id || value.second == id) {
						toErase.push_back(key);
					}
				}
				for (const auto& pipeID : toErase) {
					connections.erase(pipeID);
				}
				css.erase(id);
				cout << "Станция с ID " << id << " и соответствующее соединение удалены" << endl;
			}
			else {
				continue;
			}
		}
		else {
			css.erase(id);
			cout << "Станция с ID " << id << " удалена" << endl;
		}
	}
}

int GTS::findFreePipeByDiameter(int diameter) const
{
	for (const auto& [key, item] : pipes) {
		if (!isPipeConnected(key) && item.getDiameter() == diameter && !item.getUnderRepair()) {
			return key;
		}
	}
	return 0;
}

int GTS::inputStationId(const std::string& prompt, int excludeID) const
{
	int csID;
	while (true) {
		readValidNumber(csID, prompt, 1);
		if (css.count(csID) == 0) {
			cout << "Станции с таким ID не существует" << endl;
		}
		else if (!css.at(csID).hasWorkingShops()) {
			cout << "У станции нет рабочих цехов, соединение невозможно" << endl;
		}
		else if (csID == excludeID) {
			cout << "Нельзя соединить станцию саму с собой" << endl;
		}
		else {
			break;
		}
	}
	return csID;
}

int GTS::findOrCreatePipe(int diameter)
{
	int pipeID = findFreePipeByDiameter(diameter);
	if (pipeID == 0) {
		cout << "Нет свободной трубы с таким диаметром, добавим новую:" << endl;
		Pipe newPipe;
		newPipe.setID(maxPipeID++);
		newPipe.inputForConnection(diameter);
		pipes.emplace(newPipe.getID(), newPipe);
		pipeID = maxPipeID - 1;
	}
	return pipeID;
}

int GTS::countWorkStations() const
{
	int workingStations = 0;
	for (const auto& [key, item] : css) {
		if (item.hasWorkingShops()) {
			++workingStations;
		}
		else {
			continue;
		}
	}
	return workingStations;
}

void GTS::searchPipes()
{
	if (pipes.empty()) {
		cout << "Предупреждение: Труба не создана" << endl;
		return;
	}
	std::vector<int> foundPipes;
	int value = {};

	readValidNumber(value, "Найти по: 1-названию, 2-признаку «в ремонте»: ", 1, 2);
	if (value == 1) {
		searchByName(pipes, foundPipes);
	}
	else {
		searchByValue(pipes, foundPipes, "Введите 1-труба на ремонте, 0-труба в рабочем состоянии: ", false, true, checkByRepair);
	}

	readValidNumber(value, "Уточнить: 1-все найденные, 2-конкретные id: ", 1, 2);
	if (value == 2) {
		foundPipes = inputSpecificIDs(pipes, foundPipes);
	}

	readValidNumber(value, "Действие: 1-удалить, 2-редактировать: ", 1, 2);
	if (value == 1) {
		deletePipes(foundPipes);
	}
	else {
		editPipes(foundPipes);
	}
}

void GTS::searchStations()
{
	if (css.empty()) {
		cout << "Предупреждение: КС не создана" << endl;
		return;
	}
	std::vector<int> foundStations;
	int value = {};
	readValidNumber(value, "Найти по: 1-названию, 2-по проценту незадействованных цехов: ", 1, 2);
	if (value == 1) {
		searchByName(css, foundStations);
	}
	else {
		searchByValue(css, foundStations, "Введите процент незадействованных цехов (<=): ", 0.0, 100.0, checkByWorkshops);
	}

	readValidNumber(value, "Уточнить: 1-все найденные, 2-конкретные id: ", 1, 2);
	if (value == 2) {
		foundStations = inputSpecificIDs(css, foundStations);
	}

	readValidNumber(value, "Действие: 1-удалить, 2-редактировать: ", 1, 2);
	if (value == 1) {
		deleteStations(foundStations);
	}
	else {
		editStations(foundStations);
	}
}

void GTS::connect()
{
	if (countWorkStations() < 2) {
		cout << "Предупреждение: нельзя соединить объекты в газотранспортную сеть" << endl;
		return;
	}
	int inputCSID = inputStationId("Введите ID станции входа: ");
	int outputCSID = inputStationId("Введите ID станции выхода: ", inputCSID);
	int pipeDiameter = 0;
	readValidNumber(pipeDiameter, "Введите диаметр трубы: ", 1);
	int pipeID = findOrCreatePipe(pipeDiameter);
	connections.emplace(pipeID, pair{ inputCSID, outputCSID });
	cout << "Станция " << inputCSID << " соединена со станцией " << outputCSID << " трубой " << pipeID << endl;
}

void GTS::disconnect()
{
	if (connections.empty()) {
		cout << "Предупреждение: в газотранспортной сети отсутствуют объекты" << endl;
		return;
	}
	while (true) {
		int pipeID;
		readValidNumber(pipeID, "Введите ID трубы: ", 1);
		if (isPipeConnected(pipeID)) {
			cout << "Газотранспортная сеть " << connections[pipeID].first << "->" << connections[pipeID].second << " отсоединена" << endl;
			connections.erase(pipeID);
			break;
		}
		else {
			cout << "Такого соединения не существует" << endl;
		}
	}
}

void GTS::sort()
{
}
