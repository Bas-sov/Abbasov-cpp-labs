#pragma once
#include <string>

class Station
{
private:
	static int NextId;
	int id = {};
	std::string name;
	int totalShops = {}; // количество цехов
	int totalWorkingShops = {}; // количество рабочих цехов
	char classStation = {}; // класс станции (a,b,c)
public:
	Station();
	int getID() const;
	friend std::istream& operator >> (std::istream& in, Station& cs);
	friend std::ifstream& operator >> (std::ifstream& inF, Station& cs);
	friend std::ofstream& operator << (std::ofstream& outF, const Station& cs);
	friend std::ostream& operator << (std::ostream& out, const Station& cs);
};