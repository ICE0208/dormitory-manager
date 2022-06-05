#include "extraFunc.h"

int clearBuffer() {
    int c;
    int isOver = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        isOver = 1;
    }
    return isOver;
}

void setTitle(wchar_t* title) {
    int size = wcslen(DEFAULT_TITLE) + wcslen(title) + 1;
    wchar_t* t = (wchar_t*)malloc(sizeof(wchar_t) * size);
    wsprintf(t, L"%s%s", DEFAULT_TITLE, title);
    SetConsoleTitle(t);
}

void printInputErrMsg() {
    printf("<잘못된 값을 입력하셨습니다. 다시 입력해주세요.>\n");
}