#include "searchScreen.h"

void searchScreen() {
	int selected;
	while (1) {
		setTitle(L"검색 화면");
		system(CLEAR);
		searchShowOption();
        selected = searchGetUserInput();
        if (selected == 0) return;
        searchMoveTo(selected);
	}
}

void searchMoveTo(int option) {
    switch (option) {
    case 1:
        // 이름으로 찾기 이동
        break;
    case 2:
        // 학번으로 찾기 이동
        break;
    }
}

void searchShowOption() {
	printf("[검색 화면]\n\n");
	printf("[1] 이름으로 찾기\n");
	printf("[2] 학번으로 찾기\n");
	printf("[0] 뒤로 가기\n\n");
}

int searchGetUserInput() {
    int value;
    printf("\n");
    while (1) {
        printf("입력 > ");
        scanf("%d", &value);
        clearBuffer();

        if (0 <= value && value <= 2) return value;

        system(CLEAR);
        searchShowOption();
        printInputErrMsg();
    }
}