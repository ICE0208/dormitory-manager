#include "settingScreen.h"

void settingScreen() {
	int selected;
	while (1) {
		setTitle(L"설정 화면");
		system(CLEAR);
		settingShowOption(); // 옵션 보여주기
		selected = settingGetUserInput(); // input -> selected
		if (selected == 0) return;// 0이면 return
		// moveTo
	}
}

void settingMoveTo(int option) {
	switch (option) {
	case 1:
		// 버전 확인
		break;
	case 2:
		// 비밀번호 변경
		break;
	}
}

void settingShowOption() {
	textcolor(11);
	printf("[설정 화면]\n\n");
	textcolor(15);
	printf("[1] 버전 확인\n");
	printf("[2] 비밀번호 변경\n");
	printf("[0] 뒤로 가기\n\n");
}

int settingGetUserInput() {
	int value;
	printf("\n");
	while (1) {
		printf("입력 > ");
		scanf("%d", &value);
		clearBuffer();

		if (0 <= value && value <= 2) return value;

		system(CLEAR);
		settingShowOption();
		printInputErrMsg();
	}
}