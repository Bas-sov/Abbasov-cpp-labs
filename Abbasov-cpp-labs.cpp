#include <iostream>
#include <unordered_map>
#include <fstream>
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"

using namespace std;

void command(int action, unordered_map <int, Pipe>& pipes, unordered_map <int, Station>& css) {
	switch (action) {
	case 1: {
		inputObjects(pipes);
		break;
	}
	case 2: {
		inputObjects(css);
		break;
	}
	case 3: {
		if (pipes.empty() && css.empty()) {
			cout << "Предупреждение: Труба и КС не созданы" << endl;
		}
		else {
			outputOdjects(pipes, "Вывод данных для трубы:");
			outputOdjects(css, "Вывод данных для станции:");
		}
		break;
	}
	case 4: {
		break;
	}
	case 5: {
		break;
	}
	case 6: {
		break;
	}
	case 7: {
		break;
	}
	}
}

int main() {
	string menu = "Меню\n1.Добавить трубу\n2.Добавить КС\n3.Просмотр всех объектов\n4.Сохранить\n5.Загрузить\n6.Пакетная обработка труб\n7.Пакетная обработка КС\n0.Выход\n";
	unordered_map <int, Pipe> pipes = {};
	unordered_map <int, Station> css = {};
	while (true) {
		int action;
		readValidNumber(action, menu, 0, 7);
		if (action == 0) {
			return 0;
		}
		else {
			command(action, pipes, css);
		}
	}
	return 0;
}