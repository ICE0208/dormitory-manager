#include "stuScreen.h"
#include "stuInfoScreen.h"

void stuScreen(DONG* dong, int floor, int ho) {
	int selected;

	while (1) {
		setTitle(L"학생 선택 화면");
		system(CLEAR);
		stuShowOption(dong, floor, ho); // 학생 선택 화면 옵션 보여주기
		selected = stuGetUserInput(dong, floor, ho); // 사용자의 옵션 선택
		if (selected == 0) return; // 뒤로 가기 옵션 선택했을 때
		stuMoveTo(dong, floor, ho, selected); // 선택한 옵션의 명령어 수행
	}
}

void stuShowOption(DONG* dong, int floor, int ho) {
	system(CLEAR);
	textcolor(11);
	printf("[%s %d층 %d%02d호- ", dong->name, floor, floor, ho);
	printf("학생 선택 화면]\n\n");
	textcolor(15);

	// 학생1 ~ 학생3 인덱스, 학생 이름과 함께 출력
	for (int i = 1; i <= STUMAX; i++) {
		printf("[%d] 학생 %d", i, i);
		printf(" - (%s)\n", dong->students[floor - 1][ho - 1][i - 1].name);
	}
	printf("[0] 뒤로 가기\n\n");
}

int stuGetUserInput(DONG* dong, int floor, int ho) {
	int value = -1;
	printf("\n");
	// 올바른 값이 입력될 때까지 반복합니다.
	while (1) {
		printf("입력 > ");
		scanf("%d", &value);
		clearBuffer();

		// 올바른 값 입력했을 때 그 값을 리턴
		if (0 <= value && value <= STUMAX) return value;

		// 잘못된 값 입력했을 때
		system(CLEAR);
		stuShowOption(dong, floor, ho);
		printInputErrMsg();
	}
}

void stuMoveTo(DONG* dong, int floor, int ho, int option) {
	// 학생을 선택했을 때
	if (1 <= option && option <= STUMAX) {
		// 이 동의 이 층의 이 호의 이 학생으로 이동
		stuInfoScreen(dong, floor, ho, option);
		return;
	}
	// 다른 값이 들어올 수 없음
}