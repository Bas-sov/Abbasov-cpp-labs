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
	}
	else {
		outputObjects(pipes, "Вывод данных для трубы:");
		outputObjects(css, "Вывод данных для станции:");
		outputConnections(connections);
	}
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
	}
	else {
		string file_name;
		cout << "Укажите название файла: ";
		getline(cin, file_name);
		savedDataToFile(file_name, pipes, css, connections);
	}
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
	for (const auto& i : connections) {
		if (id == i.first) {
			return true;
		}
	}
	return false;
}

bool GTS::isStationConnected(int id) const
{
	for (const auto& i : connections) {
		if (id == i.second.first || id == i.second.second) {
			return true;
		}
	}
	return false;
}

void GTS::deletePipes(const std::vector<int>& result)
{
	for (const auto& id : result) {
		if (isPipeConnected(id)) {
			cout << "Трубу с ID " << id << " нельзя удалить, так как она подключена к газотранспортной сети" << endl;
			continue;
		}
		else {
			pipes.erase(id);
			cout << "Труба с ID " << id << " была успешно удалена" << endl;
		}
	}
}

void GTS::deleteStations(const std::vector<int>& result)
{
	for (const auto& id : result) {
		if (isStationConnected(id)) {
			cout << "Станцию с ID " << id << " нельзя удалить, так как она подключена к газотранспортной сети" << endl;
			continue;
		}
		else {
			css.erase(id);
			cout << "Станция с ID " << id << " была успешно удалена" << endl;
		}
	}
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