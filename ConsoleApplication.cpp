#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <locale.h>

using namespace std;

int main() {
	HANDLE hEvent;
	setlocale(LC_ALL, "rus");
	hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, L"MyEvent1");
	if (hEvent == 0) {
		cout << "Ошибка открытия объекта, созданного в другом приложении";
		_getch();
		return 0;
	}
	cout << "Для запуска потоков в другом приложении нажмите любую клавишу" << endl;
	_getch();
	SetEvent(hEvent);
	cout << "Для завершения потоков нажмите любую клавишу" << endl;
	_getch();
	ResetEvent(hEvent);
	cout << "Для завершения нажмите любую клавишу" << endl;
	_getch();
	return 0;
}