#include "Pipe.h"
#include <iostream>
#include "Utils.h"

using namespace std;

int Pipe::NextId = 1;

Pipe::Pipe()
{
	id = NextId++;
}

int Pipe::getID() const
{
	return id;
}

std::istream& operator>>(istream& in, Pipe& p)
{
	readValidName(p.name, "Введите название трубы: ");
	readValidNumber(p.length, "Введите длину трубы (в километрах): ", 1.0);
	readValidNumber(p.diameter, "Введите диаметр трубы (в миллиметрах): ", 1);
	readValidNumber(p.underRepair, "Введите состояние трубы (1 - на ремонте, 0 - в рабочем состоянии): ", false, true);
	return in;
}

std::ifstream& operator>>(ifstream& inF, Pipe& p) {
	inF >> p.id;
	inF.ignore(100, '\n');
	getline(inF, p.name);
	inF >> p.length;
	inF >> p.diameter;
	inF >> p.underRepair;
	Pipe::NextId = p.id + 1;
	return inF;
}

std::ostream& operator << (ostream& out, const Pipe& p) {
	out << "ID трубы: " << p.id << endl;
	out << "Название трубы: " << p.name << endl;
	out << "Длина трубы: " << p.length << " км" << endl;
	out << "Диаметр трубы: " << p.diameter << " мм" << endl;
	out << "Состояние трубы: " << (p.underRepair ? "На ремонте" : "В рабочем состоянии") << endl;
	return out;
}

std::ofstream& operator << (ofstream& outF, const Pipe& p) {
	outF << p.id << endl;
	outF << p.name << endl;
	outF << p.length << endl;
	outF << p.diameter << endl;
	outF << p.underRepair << endl;
	return outF;
}