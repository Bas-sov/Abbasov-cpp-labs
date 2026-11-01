#include <iostream>
#include "Manager.h"
#include "Utils.h"

using namespace std;

void Manager::addPipe()
{
	inputObjects(pipes, maxPipeID++);
}

void Manager::addStation()
{
	inputObjects(css, maxStationID++);
}

void Manager::showAll() const
{
	if (pipes.empty() && css.empty()) {
		cout << "Предупреждение: Труба и КС не созданы" << endl;
	}
	else {
		outputObjects(pipes, "Вывод данных для трубы:");
		outputObjects(css, "Вывод данных для станции:");
	}
}

void Manager::saveToFile() const
{
	if (pipes.empty() && css.empty()) {
		cout << "Предупреждение: Труба и КС не созданы" << endl;
	}
	else {
		string file_name;
		cout << "Укажите название файла: ";
		getline(cin, file_name);
		savedDataToFile(file_name, pipes, css);
	}
}

void Manager::loadFromFile()
{
	string file_name;
	cout << "Укажите название файла: ";
	getline(cin, file_name);
	loadDataFromFile(file_name, pipes, css, maxPipeID, maxStationID);
}

void Manager::searchPipes()
{
	if (!pipes.empty()) {
		::searchPipes(pipes);
	}
	else {
		cout << "Предупреждение: Труба не создана" << endl;
	}
}

void Manager::searchStations()
{
	if (!css.empty()) {
		::searchStations(css);
	}
	else {
		cout << "Предупреждение: КС не создана" << endl;
	}
}