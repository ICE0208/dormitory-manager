
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
		floorMoveTo(selected);
	}
}

void floorShowOption(char* dongName) {
	system(CLEAR);
	printf("[%s - ", dongName);
	printf("층 선택 화면]\n\n");

	// 1층부터 15층까지 인덱스와 함께 출력
	for (int i = 1; i <= FLOORMAX; i++) {
		printf("[%02d] %2d층\t", i, i);
		if (i % 3 == 0) printf("\n");
	}
	printf("[0] 뒤로 가기\n");
	printf("\n");
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
		if (0 <= value && value <= 15) return value;

		system(CLEAR);
		floorShowOption(dongName);
		printf("<잘못된 값을 입력하셨습니다. 다시 입력해주세요.>\n");
	}
}

// 층 화면에서 선택한 옵션에 따라 할 것들
void floorMoveTo(int option) {
	// 층을 선택했을 때
	if (1 <= option && option <= FLOORMAX) {
		// 이 동의 층으로 이동
		return;
	}
	// 1 <= option <= FLOORMAX 외에 다른 값이 들어올 수 없음

}