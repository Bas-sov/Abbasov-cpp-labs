#include "Utils.h"
#include "GTS.h"
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
	string menu = "Меню\n1.Добавить трубу\n2.Добавить КС\n3.Просмотр всех объектов\n4.Сохранить\n5.Загрузить\n6.Пакетная обработка труб\n7.Пакетная обработка КС\n8.Соединить\n9.Отсоединить\n10.Отсортировать\n0.Выход\n";
	GTS gts;
	while (true) {
		int action;
		readValidNumber(action, menu, 0, 10);
		if (action == 0) {
			return 0;
		}
		switch (action) {
		case 1: { gts.addPipe(); break; }
		case 2: { gts.addStation(); break; }
		case 3: { gts.showAll(); break; }
		case 4: { gts.saveToFile(); break; }
		case 5: { gts.loadFromFile(); break; }
		case 6: { gts.searchPipes(); break; }
		case 7: { gts.searchStations(); break; }
		case 8: { break; }
		case 9: { break; }
		case 10: { break; }
		}
	}
	return 0;
}