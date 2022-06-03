#define _CRT_NONSTDC_NO_WARNINGS    // 비표준 함수를 사용했을 때 에러 방지

#include "dongScreen.h"
#include "studentManager.h"
#include "mainScreen.h"
#include <conio.h>

void dongScreen() {
    int selected;
    while (1) {
        dongShowOption();
        selected = dongGetUserInput();
        if (selected == 0) {
            break;
        }
        dongMoveTo(selected);
    }
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
    case 22:
        deleteDong();
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

// 동을 삭제하는 화면입니다.
void deleteDong() {
    system(CLEAR);
    int selected;
    printf("[동 삭제 화면]\n\n");
    showAllDong();
    printf("\n[0] 초기 화면\n\n");
    printf("<삭제할 동의 번호를 입력해주세요.>\n");
    printf("입력 > ");
    
    while (1) {
        scanf("%d", &selected);
        clearBuffer();

        if ((0 <= selected && selected <= getDongCount())) break;

        system(CLEAR);
        printf("[동 삭제 화면]\n\n");
        showAllDong();
        printf("\n[0] 초기 화면\n\n");
        printf("<잘못된 값을 입력하셨습니다. 다시 입력해주세요.>\n");
        printf("입력 > ");
    }

    if (selected == 0) { // 메인화면 옵션 선택
        return;
    }

    char dongName[20] = {'\0',};
    strcpy(dongName, getDongName(selected));
    printf("%s를 삭제하시겠습니다?\n[y] 예   [다른값] 아니오\n\n입력 > ", dongName);
    char confirm;
    scanf("%c", &confirm);
    clearBuffer();

    if (confirm == 'y') {
        removeDong(selected); // 지우고
        saveAllInfo(); // 파일에 저장
        printf("%s를 삭제했습니다.\n아무 키나 누르면 돌아갑니다.", dongName);
        getch();
        return;
    }

    printf("삭제를 취소했습니다.\n아무 키나 누르면 돌아갑니다.");
    getch();
    return;
}