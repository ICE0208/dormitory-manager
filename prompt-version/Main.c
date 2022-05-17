#include <stdio.h>
#include "fileManager.h"
#include "mainScreen.h"
#include "studentManager.h"

int main() {

	setDongList();
	setNewDong("1동");
	setNewDong("2동");
	setNewDong("3동");
	setNewDong("4동");
	setNewDong("5동");
	setNewDong("6동");
	showAllDong();
	saveAllStudent();

	// mainScreen();

	system("pause");

	return 0;
}