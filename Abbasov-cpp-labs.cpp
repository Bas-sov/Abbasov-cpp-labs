#include <iostream>
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

Pipe inputPipe() {
	Pipe p;
	cout << "Введите название трубы: ";
	getline(cin, p.name);
	cout << "Введите длину трубы (в километрах): ";
	cin >> p.length;
	if (cin.fail() || cin.peek() != '\n' || p.length <= 0) {
		cerr << "Ошибка: длина должна быть положительным числом" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		return {};
	}
	cout << "Введите диаметр трубы (в миллиметрах): ";
	cin >> p.diameter;
	if (cin.fail() || cin.peek() != '\n' || p.diameter <= 0) {
		cerr << "Ошибка: диаметр должен быть целым положительным числом" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		return {};
	}
	cout << "Введите состояние трубы (1 - на ремонте, 0 - в рабочем состоянии): ";
	cin >> p.underRepair;
	if (cin.fail() || cin.peek() != '\n' || (p.underRepair != 0 && p.underRepair != 1)) {
		cerr << "Ошибка: состояние трубы — только 0 или 1" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		return {};
	}
	return p;
}


CS inputCS() {
	CS cs;
	cout << "Введите название станции: ";
	getline(cin, cs.name);
	cout << "Введите количество цехов: ";
	cin >> cs.totalShops;
	if (cin.fail() || cin.peek() != '\n' || cs.totalShops <= 0) {
		cerr << "Ошибка: кол-во цехов должно быть целым положительным числом" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		return {};
	}
	cout << "Введите количество рабочих цехов: ";
	cin >> cs.totalWorkingShops;
	if (cin.fail() || cin.peek() != '\n' || cs.totalWorkingShops <= 0 || cs.totalWorkingShops > cs.totalShops) {
		cerr << "Ошибка: кол-во рабочих цехов должно быть положительным числом и не может быть больше общего числа цехов" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		return {};
	}
	cout << "Введите класс станции (a,b,c): ";
	cin >> cs.classStation;
	if (cin.fail() || cin.peek() != '\n' || (cs.classStation != 'a' && cs.classStation != 'b' && cs.classStation != 'c')) {
		cerr << "Ошибка: класс станции — только 'a', 'b' или 'c'" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		return {};
	}
	return cs;
}

bool isvalidPipe(Pipe p) {
	if (p.diameter == 0) {
		return false;
	}
	return true;
}

bool isvalidCS(CS cs) {
	if (cs.totalShops == 0) {
		return false;
	}
	return true;
}

void editPipe(Pipe& p) {
	char t = {};
	cout << "Редактирование признака в ремонте:" << endl;
	cout << "Текущее состояние: " << p.underRepair << endl;
	cout << "Изменить?(1/0): ";
	cin >> t;
	if (cin.fail() || cin.peek() != '\n' || (t != '0' && t != '1')) {
		cerr << "Ошибка: введите 1 (изменить) или 0 (не изменить)" << endl;
		cin.clear();
		cin.ignore(100, '\n');
	}
	else {
		p.underRepair = t == '1' ? !(p.underRepair) : p.underRepair;
	}
}

void editCS(CS& cs) {
	int k = 0;
	cout << "Редактирование кол-ва рабочих цехов:" << endl;
	cout << "Общее кол-во цехов: " << cs.totalShops << endl;
	cout << "Текущее состояние: " << cs.totalWorkingShops << endl;
	cout << "Введите новое кол-во рабочих цехов: ";
	cin >> k;
	if (cin.fail() || cin.peek() != '\n' || k <= 0 || k > cs.totalShops) {
		cerr << "Ошибка: кол-во рабочих цехов должно быть положительным числом и не может быть больше общего числа цехов" << endl;
		cin.clear();
		cin.ignore(100, '\n');
	}
	else {
		cs.totalWorkingShops = k;
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


void command(int action, Pipe& p, CS& cs) {
	if (action == 1) {
		cout << "Введите данные для трубы:" << endl;
		p = inputPipe();
	}
	else if (action == 2) {
		cout << "Введите данные для станции:" << endl;
		cs = inputCS();
	}
	else if (action == 3) {
		if (!isvalidPipe(p) && !isvalidCS(cs)) {
			cout << "Труба еще не создана" << endl;
			cout << endl;
			cout << "КС еще не создана" << endl;
		}
		else if (isvalidPipe(p) && isvalidCS(cs)) {
			outputPipe(p);
			cout << endl;
			outputCS(cs);
		}
		else if (isvalidPipe(p)) {
			outputPipe(p);
		}
		else {
			outputCS(cs);
		}
	}
	else if (action == 4) {
		if (isvalidPipe(p)) {
			editPipe(p);
		}
		else {
			cout << "Труба еще не создана" << endl;
		}
	}
	else if (action == 5) {
		if (isvalidCS(cs)) {
			editCS(cs);
		}
		else {
			cout << "КС еще не создана" << endl;
		}
	}
	else if (action == 6) {

	}
	else if (action == 7) {

	}
}

int main() {
	string menu = "Меню\n1.Добавить трубу\n2.Добавить КС\n3.Просмотр всех объектов\n4.Редактировать трубу\n5.Редактировать КС\n6.Сохранить\n7.Загрузить\n0.Выход\n";
	Pipe p = {};
	CS cs = {};
	while (true) {
		int action;
		cout << menu;
		cin >> action;
		if (cin.fail() || cin.peek() != '\n' || action < 0) {
			cerr << "Ошибка: введите целое положительное число!" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		else if (action == 0) {
			return 0;
		}
		else {
			cin.ignore(100, '\n');
			command(action, p, cs);
		}
	}
	return 0;
}