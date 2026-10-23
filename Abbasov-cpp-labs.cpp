#include <iostream>
#include <unordered_map>
#include <fstream>
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"
#include <chrono>
#include <format>

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
		if (pipes.empty() && css.empty()) {
			cout << "Предупреждение: Труба и КС не созданы" << endl;
		}
		else {
			string file_name;
			cout << "Укажите название файла: ";
			getline(cin, file_name);
			savedDataToFile(file_name, pipes, css);
		}
		break;
	}
	case 5: {
		string file_name;
		cout << "Укажите название файла: ";
		getline(cin, file_name);
		loadDataFromFile(file_name, pipes, css);
		break;
	}
	case 6: {
		if (!pipes.empty()) {
			searchPipes(pipes);
		}
		else {
			cout << "Предупреждение: Труба не создана" << endl;
		}
		break;
	}
	case 7: {
		if (!css.empty()) {
			searchStations(css);
		}
		else {
			cout << "Предупреждение: КС не создана" << endl;
		}
		break;
	}
	}
}

int main() {
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", std::chrono::system_clock::now());
	ofstream logfile("Logs\\log_" + time + ".txt");
	redirect_output_wrapper cerr_out(cerr);
	if (logfile) {
		cerr_out.redirect(logfile);
	}
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