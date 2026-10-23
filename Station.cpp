#include "Station.h"
#include <iostream>
#include "Utils.h"

using namespace std;

int Station::NextId = 1;

Station::Station()
{
	id = NextId++;
}

int Station::getID() const
{
	return id;
}

std::string Station::getName() const
{
	return name;
}

double Station::getUnusedWorkshops() const
{
	return 100 * (totalShops - totalWorkingShops) / totalShops;
}

std::istream& operator>>(istream& in, Station& cs)
{
	readValidName(cs.name, "Введите название станции: ");
	readValidNumber(cs.totalShops, "Введите количество цехов: ", 1);
	readValidNumber(cs.totalWorkingShops, "Введите количество рабочих цехов: ", 0, cs.totalShops);
	readValidNumber(cs.classStation, "Введите класс станции (a,b,c): ", 'a', 'c');
	return in;
}

std::ifstream& operator>>(ifstream& inF, Station& cs) {
	inF >> cs.id;
	inF.ignore(100, '\n');
	getline(inF, cs.name);
	inF >> cs.totalShops;
	inF >> cs.totalWorkingShops;
	inF >> cs.classStation;
	Station::NextId = cs.id + 1;
	return inF;
}

void Station::editTotalWorkingShops(double workshopPercentage)
{
	totalWorkingShops = floor(totalShops * workshopPercentage / 100);
}

std::ostream& operator<<(ostream& out, const Station& cs)
{
	out << "ID станции: " << cs.id << endl;
	out << "Название станции: " << cs.name << endl;
	out << "Количество цехов: " << cs.totalShops << endl;
	out << "Количество рабочих цехов: " << cs.totalWorkingShops << endl;
	out << "Класс станции: " << cs.classStation << endl;
	return out;
}

std::ofstream& operator<<(ofstream& outF, const Station& cs)
{
	outF << cs.id << endl;
	outF << cs.name << endl;
	outF << cs.totalShops << endl;
	outF << cs.totalWorkingShops << endl;
	outF << cs.classStation << endl;
	return outF;
}