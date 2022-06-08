#define _CRT_NONSTDC_NO_WARNINGS    // 비표준 함수를 사용했을 때 에러 방지

#include "dongScreen.h"
#include "extraFunc.h"
#include "floorScreen.h"
#include "studentManager.h"
#include "mainScreen.h"
#include <conio.h>

void dongScreen() {
    int selected;
    while (1) {
        setTitle(L"동 선택 화면");
        system(CLEAR);
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
    printf("\n[21] 동 추가\n[22] 동 삭제\n[23] 동 순서 변경\n[0] 초기 화면\n\n");
}

void dongMoveTo(int option) {
    // 동을 선택했을 때
    if (1 <= option && option <= getDongCount()) {
        floorScreen(option);
        return; //
    }

    // 동이 아닌 다른 옵션을 선택했을 때
    switch (option) {
    case 21:
        setTitle(L"동 선택 화면 - 동 추가");
        addDong();
        break;
    case 22:
        setTitle(L"동 선택 화면 - 동 삭제");
        deleteDong();
        break;
    case 23:
        setTitle(L"동 선택 화면 - 동 순서 변경");
        changeDongIndex(); // 동 순서 변경 함수
        break;
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
    printf("\n[0] 뒤로 가기\n\n");
    printf("<삭제할 동의 번호를 입력해주세요.>\n");
    printf("입력 > ");
    
    while (1) {
        scanf("%d", &selected);
        clearBuffer();

        if ((0 <= selected && selected <= getDongCount())) break;

        system(CLEAR);
        printf("[동 삭제 화면]\n\n");
        showAllDong();
        printf("\n[0] 뒤로 가기\n\n");
        printf("<잘못된 값을 입력하셨습니다. 다시 입력해주세요.>\n");
        printf("입력 > ");
    }

    if (selected == 0) { // 뒤로 가기 옵션 선택
        return;
    }

    char dongName[TEXTMAX] = {'\0',};
    strcpy(dongName, getDongName(selected));
    printf("\n%s를 삭제하시겠습니다?\n[y] 예   [다른값] 아니오\n\n입력 > ", dongName);
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

    printf("\n삭제를 취소했습니다.\n아무 키나 누르면 돌아갑니다.");
    getch();
    return;
}

void addDong() {
    system(CLEAR);
    // 동이 이미 20개면 종료
    if (getDongCount() >= 20) {
        printf("[동 추가 화면]\n\n");
        printf("<동을 더이상 추가할 수 없습니다.>\n\n");
        printf("아무 키나 누르면 돌아갑니다.");
        getch();
        return;
    }

    char newDongName[TEXTMAX] = { '\0', };
    printf("[동 추가 화면]\n\n[0] 뒤로 가기\n\n");
    printf("추가할 동의 이름을 입력하세요\n\n입력 > ");
    while (1) {
        scanf_s("%[^\n]s", newDongName, sizeof(newDongName));
        // 뒤로 가기 옵션
        if (strcmp(newDongName, "0") == 0) return;

        // 글자 수 초과
        if (clearBuffer() == 1 || strlen(newDongName) == 0) {
            system(CLEAR);
            printf("[동 추가 화면]\n\n");
            printf("추가할 동의 이름을 입력하세요\n\n");
            printf("<동의 이름이 너무 깁니다.>\n입력 > ");
            continue;
        }
        break;
    }
    system(CLEAR);
    printf("[동 추가 화면]\n\n");
    printf("%s를 추가하시겠습니까?\n[y] 예   [다른값] 아니오\n\n입력 > ", newDongName);
    char confirm;
    scanf("%c", &confirm);
    clearBuffer();

    if (confirm == 'y') {
        setNewDong(newDongName); // 추가하고
        saveAllInfo(); // 파일에 저장
        printf("%s를 추가했습니다.\n아무 키나 누르면 돌아갑니다.", newDongName);
        getch();
        return;
    }

    printf("\n추가를 취소했습니다.\n아무 키나 누르면 돌아갑니다.");
    getch();
    return;
}

void changeDongIndex() {
    // 순서를 바꿀 첫 번째 동 입력받기
    system(CLEAR);
    int target_1;
    printf("[동 순서 변경 화면]\n\n");
    showAllDong();
    printf("\n[0] 뒤로 가기\n\n");
    printf("[순서를 바꿀 동의 번호를 입력해주세요.]\n\n");
    printf("입력 > ");

    while (1) {
        scanf("%d", &target_1);
        clearBuffer();

        if ((0 <= target_1 && target_1 <= getDongCount())) break;

        system(CLEAR);
        printf("[동 순서 변경 화면]\n\n");
        showAllDong();
        printf("\n[0] 뒤로 가기\n\n");
        printf("[순서를 바꿀 동의 번호를 입력해주세요.]\n");
        printInputErrMsg();
        printf("입력 > ");
    }

    if (target_1 == 0) { // 뒤로 가기 옵션 선택
        return;
    }

    // 순서를 바꿀 두 번째 동 입력받기
    system(CLEAR);
    int target_2;
    printf("[동 순서 변경 화면]\n\n");
    showAllDong();
    printf("\n[0] 뒤로 가기\n\n");
    printf("[%d번의 동과 순서를 바꿀 동의 번호를 입력해주세요.]\n\n", target_1);
    printf("입력 > ");

    while (1) {
        scanf("%d", &target_2);
        clearBuffer();

        if ((0 <= target_2 && target_2 <= getDongCount())) {
            if (target_1 != target_2) break;
            // 입력을 정상적이지만 순서를 바꿀 대상이 같을 때
            system(CLEAR);
            printf("[동 순서 변경 화면]\n\n");
            showAllDong();
            printf("\n[0] 뒤로 가기\n\n");
            printf("[%d번의 동과 순서를 바꿀 동의 번호를 입력해주세요.]\n", target_1);
            printf("<바꿀 대상과 다른 동을 선택해주세요.>\n");
            printf("입력 > ");
            continue;
        }
        system(CLEAR);
        printf("[동 순서 변경 화면]\n\n");
        showAllDong();
        printf("\n[0] 뒤로 가기\n\n");
        printf("[%d번의 동과 순서를 바꿀 동의 번호를 입력해주세요.]\n", target_1);
        printInputErrMsg();
        printf("입력 > ");
    }

    if (target_2 == 0) { // 뒤로 가기 옵션 선택
        return;
    }

    system(CLEAR);
    printf("[동 순서 변경 화면]\n\n");
    printf("[%d]%s과 [%d]%s의 순서를 변경하시겠습니까?\n[y] 예   [다른값] 아니오\n\n입력 > ",
        target_1, getDongName(target_1), target_2, getDongName(target_2));
    char confirm;
    scanf("%c", &confirm);
    clearBuffer();

    if (confirm == 'y') {
        changeDong(target_1, target_2); // 변경하고
        saveAllInfo(); // 파일에 저장
        printf("변경이 완료되었습니다..\n아무 키나 누르면 돌아갑니다.");
        getch();
        return;
    }

    printf("\n변경을 취소했습니다.\n아무 키나 누르면 돌아갑니다.");
    getch();
    return;
}