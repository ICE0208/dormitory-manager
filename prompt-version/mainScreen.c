#include "mainScreen.h"
#include "studentManager.h"
#include "dongScreen.h"

void mainScreen() {
    int selected;
    while (1) {
        system(CLEAR);
        mainShowOption();
        selected = mainGetUserInput();
        mainMoveTo(selected);
    }
}

void mainMoveTo(int option) {
    printf("%d로 이동합니다.\n", option);
    switch (option) {
    case 1:
        dongScreen();
    }
}

void mainShowOption() {
    printf("[초기 화면]\n\n");
    printf("[1]. 동 선택\n");
    printf("[2]. 학생 찾기\n");
    printf("[3]. 프로그램 설정\n");
    printf("[0]. 프로그램 종료\n\n");
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

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}