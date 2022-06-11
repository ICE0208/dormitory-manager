
#include "floorScreen.h"

void floorScreen(int dongIndex) {
	// 현재 선택된 동의 이름을 가리키는 포인터
	char* curDongName = getDongName(dongIndex);
	int selected;

	while (1) {
		setTitle(L"층 선택 화면");
		system(CLEAR);
		floorShowOption(curDongName);
		selected = floorGetUserInput(curDongName);
		if (selected == 0) break; // 뒤로 가기 옵션
		floorMoveTo(dongIndex, selected);
	}
}

void floorShowOption(char* dongName) {
	system(CLEAR);
	textcolor(11);
	printf("[%s - ", dongName);
	printf("층 선택 화면]\n\n");
	textcolor(15);

	// 1층부터 15층까지 인덱스와 함께 출력
	for (int i = 1; i <= FLOORMAX; i++) {
		printf("[%02d] %2d층\t", i, i);
		if (i % 3 == 0) printf("\n");
	}
	printf("[0] 뒤로 가기\n\n");
}

int floorGetUserInput(char* dongName) {
	int value;
	printf("\n");
	// 올바른 값이 입력될 때까지 반복합니다.
	while (1) {
		printf("입력 > ");
		scanf("%d", &value);
		clearBuffer();

		// 올바른 값 입력했을 때 그 값을 리턴
		if (0 <= value && value <= FLOORMAX) return value;

		// 잘못된 값 입력했을 때
		system(CLEAR);
		floorShowOption(dongName);
		printInputErrMsg();
	}
}

// 층 화면에서 선택한 옵션에 따라 할 것들
void floorMoveTo(int dongIndex, int option) {
	// 층을 선택했을 때
	if (1 <= option && option <= FLOORMAX) {
		DONG* curDONG = getDONG(dongIndex);
		// 이 동의 층으로 이동
		hoScreen(curDONG, option);
		return;
	}
	// 1 <= option <= FLOORMAX 외에 다른 값이 들어올 수 없음

}