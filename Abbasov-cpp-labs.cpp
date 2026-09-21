#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Pipe {
	string name;
	double length = {}; // в километрах
	int diameter = {}; // в миллиметрах
	bool underRepair = {}; // true - труба на ремонте, false - труба в рабочем состоянии
};

struct CS {
	string name;
	int totalShops = {}; // количество цехов
	int totalWorkingShops = {}; // количество рабочих цехов
	char classStation = {}; // класс станции (a,b,c)
};

template <typename T>
void readValid(T& value, const string& prompt) {
	while (true) {
		cout << prompt;
		if (cin.peek() == ' ' || cin.peek() == '\t' || cin.peek() == '\n') {
			cerr << "Ошибка: нельзя начинать с пробела/таба/переноса строки" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		cin >> value;
		if (cin.fail() || cin.peek() != '\n') {
			cerr << "Ошибка: некорректный ввод" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		cin.ignore(100, '\n');
		return;
	}
}

Pipe inputPipe(Pipe& p) {
	while (true) {
		cout << "Введите название трубы: ";
		getline(cin, p.name);
		if (p.name.empty() || p.name[0] == ' ' || p.name[0] == '\t' ||
			p.name[p.name.size() - 1] == ' ' || p.name[p.name.size() - 1] == '\t') {
			cerr << "Ошибка: некорректный ввод" << endl;
			continue;
		}
		break;
	}
	while (true) {
		readValid(p.length, "Введите длину трубы (в километрах): ");
		if (p.length <= 0) {
			cerr << "Ошибка: длина должна быть положительной" << endl;
			continue;
		}
		break;
	}
	while (true) {
		readValid(p.diameter, "Введите диаметр трубы (в миллиметрах): ");
		if (p.diameter <= 0) {
			cerr << "Ошибка: диаметр должен быть положительным" << endl;
			continue;
		}
		break;
	}
	while (true) {
		readValid(p.underRepair, "Введите состояние трубы (1 - на ремонте, 0 - в рабочем состоянии): ");
		if (p.underRepair != 0 && p.underRepair != 1) {
			cerr << "Ошибка: введите 0 или 1" << endl;
			continue;
		}
		break;
	}
	return p;
}


CS inputCS(CS& cs) {
	while (true) {
		cout << "Введите название станции: ";
		getline(cin, cs.name);
		if (cs.name.empty() || cs.name[0] == ' ' || cs.name[0] == '\t' ||
			cs.name[cs.name.size() - 1] == ' ' || cs.name[cs.name.size() - 1] == '\t') {
			cerr << "Ошибка: некорректный ввод" << endl;
			continue;
		}
		break;
	}
	while (true) {
		readValid(cs.totalShops, "Введите количество цехов: ");
		if (cs.totalShops <= 0) {
			cerr << "Ошибка: кол-во цехов должно быть положительной" << endl;
			continue;
		}
		break;
	}
	while (true) {
		readValid(cs.totalWorkingShops, "Введите количество рабочих цехов: ");
		if (cs.totalWorkingShops <= 0 || cs.totalWorkingShops > cs.totalShops) {
			cerr << "Ошибка: кол-во рабочих цехов должно быть положительным числом и не может быть больше общего числа цехов" << endl;
			continue;
		}
		break;
	}
	while (true) {
		readValid(cs.classStation, "Введите класс станции (a,b,c): ");
		if (cs.classStation != 'a' && cs.classStation != 'b' && cs.classStation != 'c') {
			cerr << "Ошибка: класс станции - только a,b,c" << endl;
			continue;
		}
		break;
	}
	return cs;
}

bool isvalidPipe(Pipe& p) {
	if (p.diameter == 0) {
		return false;
	}
	return true;
}

bool isvalidCS(CS& cs) {
	if (cs.totalShops == 0) {
		return false;
	}
	return true;
}

void editPipe(Pipe& p) {
	int t = 0;
	cout << "Редактирование признака в ремонте:" << endl;
	cout << "Текущее состояние: " << p.underRepair << endl;
	while (true) {
		readValid(t, "Изменить?(1-да/0-нет): ");
		if (t != 0 && t != 1) {
			cerr << "Ошибка: введите 1 - изменить, 0 - нет" << endl;
			continue;
		}
		else {
			p.underRepair = t == 1 ? !(p.underRepair) : p.underRepair;
			break;
		}
	}
}

void editCS(CS& cs) {
	int k = 0;
	cout << "Редактирование кол-ва рабочих цехов:" << endl;
	cout << "Общее кол-во цехов: " << cs.totalShops << endl;
	cout << "Текущее состояние: " << cs.totalWorkingShops << endl;
	while (true) {
		readValid(k, "Введите новое кол-во рабочих цехов: ");
		if (k <= 0 || k > cs.totalShops) {
			cerr << "Ошибка: кол-во рабочих цехов должно быть положительным числом и не может быть больше общего числа цехов" << endl;
			continue;
		}
		else {
			cs.totalWorkingShops = k;
			break;
		}
	}
}

void outputPipe(Pipe p) {
	cout << "Вывод данных для трубы:" << endl;
	cout << "Название трубы: " << p.name << endl;
	cout << "Длина трубы: " << p.length << " км" << endl;
	cout << "Диаметр трубы: " << p.diameter << " мм" << endl;
	cout << "Состояние трубы: " << (p.underRepair ? "На ремонте" : "В рабочем состоянии") << endl;
}

void outputCS(CS cs) {
	cout << "Вывод данных для станции:" << endl;
	cout << "Название станции: " << cs.name << endl;
	cout << "Количество цехов: " << cs.totalShops << endl;
	cout << "Количество рабочих цехов: " << cs.totalWorkingShops << endl;
	cout << "Класс станции: " << cs.classStation << endl;
}

void savedPipe(ofstream& outFile, Pipe p) {
	outFile << "Pipe:" << endl;
	outFile << p.name << endl;
	outFile << p.length << endl;
	outFile << p.diameter << endl;
	outFile << p.underRepair << endl;
}

void savedCS(ofstream& outFile, CS cs) {
	outFile << "CS:" << endl;
	outFile << cs.name << endl;
	outFile << cs.totalShops << endl;
	outFile << cs.totalWorkingShops << endl;
	outFile << cs.classStation << endl;
}

void read(ifstream& inFile, Pipe& p, CS& cs) {
	string header;
	while (getline(inFile, header)) {
		if (header == "Pipe:") {
			getline(inFile, p.name);
			inFile >> p.length;
			inFile >> p.diameter;
			inFile >> p.underRepair;
			inFile.ignore(100, '\n');
		}
		else if (header == "CS:") {
			getline(inFile, cs.name);
			inFile >> cs.totalShops;
			inFile >> cs.totalWorkingShops;
			inFile >> cs.classStation;
			inFile.ignore(100, '\n');
		}
		else {
			cerr << "Файл поврежден" << endl;
			break;
		}
	}
}

void command(int action, Pipe& p, CS& cs) {
	if (action == 1) {
		cout << "Введите данные для трубы:" << endl;
		inputPipe(p);
	}
	else if (action == 2) {
		cout << "Введите данные для станции:" << endl;
		inputCS(cs);
	}
	else if (action == 3) {
		if (isvalidPipe(p)) {
			outputPipe(p);
			cout << endl;
		}
		if (isvalidCS(cs)) {
			outputCS(cs);
			cout << endl;
		}
	}
	else if (action == 4) {
		if (isvalidPipe(p)) {
			editPipe(p);
		}
	}
	else if (action == 5) {
		if (isvalidCS(cs)) {
			editCS(cs);
		}
	}
	else if (action == 6) {
		ofstream outFile;
		outFile.open("result.txt");
		if (!outFile.is_open()) {
			cerr << "Ошибка: не удалось открыть файл" << endl;
		}
		else {
			if (isvalidPipe(p)) {
				savedPipe(outFile, p);
				cout << "Труба добавлена в файл!" << endl;
			}
			if (isvalidCS(cs)) {
				savedCS(outFile, cs);
				cout << "КС добавлена в файл!" << endl;
			}
		}
		outFile.close();
	}
	else if (action == 7) {
		ifstream inFile;
		inFile.open("result.txt");
		if (!inFile.is_open()) {
			cerr << "Ошибка: не удалось открыть файл" << endl;
		}
		else if (inFile.peek() == EOF) {
			cout << "Предупреждение: файл пуст" << endl;
		}
		else {
			read(inFile, p, cs);
			cout << "Данные успешно считаны!" << endl;
		}
		inFile.close();
	}
	else {
		cerr << "Ошибка: введите номер команды из списка (0-7)" << endl;
	}
}

int main() {
	string menu = "Меню\n1.Добавить трубу\n2.Добавить КС\n3.Просмотр всех объектов\n4.Редактировать трубу\n5.Редактировать КС\n6.Сохранить\n7.Загрузить\n0.Выход\n";
	Pipe p = {};
	CS cs = {};
	while (true) {
		int action;
		readValid(action, menu);
		if (action == 0) {
			return 0;
		}
		else {
			command(action, p, cs);
		}
	}
	return 0;
}