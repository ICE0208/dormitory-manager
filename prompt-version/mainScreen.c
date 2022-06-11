#include "extraFunc.h"
#include "mainScreen.h"
#include "studentManager.h"
#include "dongScreen.h"
#include "searchScreen.h"

void mainScreen() {
    int selected;
    while (1) {
        setTitle(L"메인 화면");
        system(CLEAR);
        mainShowOption();
        selected = mainGetUserInput();
        mainMoveTo(selected);
    }
}

void mainMoveTo(int option) {
    switch (option) {
    case 0:
        exit(0); // 프로그램 종료
        break;
    case 1:
        dongScreen(); // 동 선택 화면으로 이동
        break;
    case 2:
        searchScreen(); // 학생 검색 화면으로 이동
        break;
    }
}

void mainShowOption() {
    printf("[메인 화면]\n\n");
    printf("[1] 동 선택\n");
    printf("[2] 학생 찾기\n");
    printf("[3] 프로그램 설정\n");
    printf("[0] 프로그램 종료\n\n");
}

int mainGetUserInput() {
    int value;
    printf("\n");
    while (1) {
        printf("입력 > ");
        scanf("%d", &value);
        clearBuffer();

        if (0 <= value && value <= 3) return value;

        system(CLEAR);
        mainShowOption();
        printInputErrMsg();
    }
}