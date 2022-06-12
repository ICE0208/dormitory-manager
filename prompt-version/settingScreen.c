#include "settingScreen.h"

void settingScreen() {
	int selected;
	while (1) {
		setTitle(L"설정 화면");
		system(CLEAR);
		settingShowOption(); // 옵션 보여주기
		selected = settingGetUserInput(); // input -> selected
		if (selected == 0) return;// 0이면 return
		settingMoveTo(selected); // moveTo
	}
}

void settingMoveTo(int option) {
	switch (option) {
	case 1:
		checkVersion(); // 버전 확인
		break;
	case 2:
		tryChangePw(); // 비밀번호 변경
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

void checkVersion() {
	setTitle(L"버전 확인 화면");
	system(CLEAR);
	textcolor(11);
	printf("[버전 확인 화면]\n\n");
	textcolor(15);
	printf("현재 버전: ver %s (%s)\n\n\n", CUR_VER, UPDATE_DATE);
	printf("아무 키나 누르면 돌아갑니다.");
	getch();
}

void tryChangePw() {
	// 현재 비밀번호 확인 취소 or 실패
	if (confirmPassword("뒤로 가기") == 0) return;

	// 비밀번호 재설정 취소 or 실패
	if (setPassword("[비밀번호 재설정]", "뒤로 가기") == 0) return;

}