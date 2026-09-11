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
	}
	return 0;
}
