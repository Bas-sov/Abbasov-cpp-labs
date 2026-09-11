#include <iostream>
#include <string>

using namespace std;

struct Pipe {
	string name;
	double length; // в километрах
	unsigned int diameter; // в миллиметрах
	bool underRepair; // true - труба на ремонте, false - труба в рабочем состоянии
	bool created = false; // true - труба создана, false - труба не создана
};

struct CS {
	string name;
	int totalShops; // количество цехов
	int totalWorkingShops; // количество рабочих цехов
	char classStation; // класс станции (a,b,c)
	bool created = false; // true - КС создана, false - КС не создана
};

Pipe inputPipe() {
	Pipe p;
	cout << "Введите название трубы: ";
	getline(cin, p.name);
	cout << "Введите длину трубы (в километрах): ";
	cin >> p.length;
	cout << "Введите диаметр трубы (в миллиметрах): ";
	cin >> p.diameter;
	cout << "Введите состояние трубы (1 - на ремонте, 0 - в рабочем состоянии): ";
	cin >> p.underRepair;
	p.created = true;
	return p;
};

CS inputCS() {
	CS cs;
	cout << "Введите название станции: ";
	getline(cin, cs.name);
	cout << "Введите количество цехов: ";
	cin >> cs.totalShops;
	cout << "Введите количество рабочих цехов: ";
	cin >> cs.totalWorkingShops;
	cout << "Введите класс станции (a,b,c): ";
	cin >> cs.classStation;
	cs.created = true;
	return cs;
};

void outputPipe(Pipe p) {
	if (p.created) {
		cout << "Вывод данных для трубы:" << endl;
		cout << "Название трубы: " << p.name << endl;
		cout << "Длина трубы: " << p.length << " км" << endl;
		cout << "Диаметр трубы: " << p.diameter << " мм" << endl;
		cout << "Состояние трубы: " << (p.underRepair ? "На ремонте" : "В рабочем состоянии") << endl;
	}
	else {
		cout << "Труба еще не создана" << endl;
	}
	cout << endl;
};

void outputCS(CS cs) {
	if (cs.created) {
		cout << "Вывод данных для станции:" << endl;
		cout << "Название станции: " << cs.name << endl;
		cout << "Количество цехов: " << cs.totalShops << endl;
		cout << "Количество рабочих цехов: " << cs.totalWorkingShops << endl;
		cout << "Класс станции: " << cs.classStation << endl;
	}
	else {
		cout << "КС еще не создана" << endl;
	}
	cout << endl;
};


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
		outputPipe(p);
		outputCS(cs);
	}
	else if (action == 4) {

	}
	else if (action == 5) {

	}
	else if (action == 6) {

	}
	else if (action == 7) {

	}
	else {
		cout << "Ошибка: введите номер команды из списка (0-7)" << endl;
	}
};

int main() {
	string menu = "Меню\n1.Добавить трубу\n2.Добавить КС\n3.Просмотр всех объектов\n4.Редактировать трубу\n5.Редактировать КС\n6.Сохранить\n7.Загрузить\n0.Выход\n";
	Pipe p;
	CS cs;
	while (true) {
		int action;
		cout << menu;
		cin >> action;
		cin.ignore(100, '\n');
		if (action == 0) {
			return 0;
		}
		command(action, p, cs);
	}
	return 0;
}
