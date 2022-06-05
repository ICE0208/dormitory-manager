#include "extraFunc.h"
#include "mainScreen.h"
#include "studentManager.h"
#include "dongScreen.h"

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
    printf("%d로 이동합니다.\n", option);
    switch (option) {
    case 0:
        exit(0);
        break;
    case 1:
        dongScreen();
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
        printf("<잘못된 값을 입력하셨습니다. 다시 입력해주세요.>\n");
    }
}