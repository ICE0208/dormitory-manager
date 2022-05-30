#include "dongScreen.h"
#include "studentManager.h"
#include "mainScreen.h"

void dongScreen() {
    int selected;
    dongShowOption();
    selected = dongGetUserInput();
    dongMoveTo(selected);
}

void dongShowOption() {
    system(CLEAR);
    printf("[동 선택 화면]\n\n");
    showAllDong();
    printf("\n[21] 동 추가\n[22] 동 삭제\n[23]동 순서 변경\n[0] 초기 화면\n\n");
}

void dongMoveTo(int option) {
    printf("%d로 이동합니다.\n", option);
    switch (option) {
    case 0:
        mainScreen();
    }
}

int dongGetUserInput() {
    int value;
    printf("\n");
    while (1) {
        printf("입력 > ");
        scanf("%d", &value);
        clearBuffer();

        if ( (0 <= value && value <= getDongCount()) || 
            (21 <= value && value <= 23) ) return value;

        system(CLEAR);
        dongShowOption();
        printf("<잘못된 값을 입력하셨습니다. 다시 입력해주세요.>\n");
    }
}