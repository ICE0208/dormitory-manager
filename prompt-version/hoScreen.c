#include "hoScreen.h"

void hoScreen(DONG* dong, int floor) {
	int selected;

	while (1) {
		setTitle(L"호 선택 화면");
		system(CLEAR);
		hoShowOption(dong, floor);
		selected = hoGetUserInput(dong, floor);
		if (selected == 0) return; // 뒤로 가기 옵션
		hoMoveTo(dong, floor, selected);
	}
}

void hoShowOption(DONG* dong, int floor) {
	system(CLEAR);
	textcolor(11);
	printf("[%s %d층 - ", dong->name, floor);
	printf("호 선택 화면]\n\n");
	textcolor(15);

	// xx01호 부터 xx20호까지 인덱스와 함께 출력
	for (int i = 1; i <= HOMAX; i++) {
		printf("[%02d] %d%02d호\t", i, floor, i);
		if (i % 4 == 0) printf("\n");
	}
	printf("[0] 뒤로 가기\n\n");
}

int hoGetUserInput(DONG* dong, int floor) {
	int value = -1;
	printf("\n");
	// 올바른 값이 입력될 때까지 반복합니다.
	while (1) {
		printf("입력 > ");
		scanf("%d", &value);
		clearBuffer();

		// 올바른 값 입력했을 때 그 값을 리턴
		if (0 <= value && value <= HOMAX) return value;

		// 잘못된 값 입력했을 때
		system(CLEAR);
		hoShowOption(dong, floor);
		printInputErrMsg();
	}
}

void hoMoveTo(DONG* dong, int floor, int option) {
	// 호를 선택했을 때
	if (1 <= option && option <= HOMAX) {
		// 이 동의 이 층의 이 호로 이동
		stuScreen(dong, floor, option);
		return;
	}
	// 다른 값이 들어올 수 없음
}