#include "Utils.h"
#include "Manager.h"
#include <chrono>
#include <format>

using namespace std;

int main() {
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", std::chrono::system_clock::now());
	ofstream logfile("Logs\\log_" + time + ".txt");
	redirect_output_wrapper cerr_out(cerr);
	if (logfile) {
		cerr_out.redirect(logfile);
	}
	string menu = "Меню\n1.Добавить трубу\n2.Добавить КС\n3.Просмотр всех объектов\n4.Сохранить\n5.Загрузить\n6.Пакетная обработка труб\n7.Пакетная обработка КС\n0.Выход\n";
	Manager manager;
	while (true) {
		int action;
		readValidNumber(action, menu, 0, 7);
		if (action == 0) {
			return 0;
		}
		switch (action) {
		case 1: { manager.addPipe(); break; }
		case 2: { manager.addStation(); break; }
		case 3: { manager.showAll(); break; }
		case 4: { manager.saveToFile(); break; }
		case 5: { manager.loadFromFile(); break; }
		case 6: { manager.searchPipes(); break; }
		case 7: { manager.searchStations(); break; }
		}
	}
	return 0;
}