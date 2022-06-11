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

// https://stackoverflow.com/questions/15316455/how-to-change-font-size-in-console-application-using-c
void setFontSize(int a, int b)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = (CONSOLE_FONT_INFOEX*)malloc(sizeof(CONSOLE_FONT_INFOEX));

    lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);

    GetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);

    lpConsoleCurrentFontEx->dwFontSize.X = a;

    lpConsoleCurrentFontEx->dwFontSize.Y = b;

    SetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
}

void textcolor(int color_number) //콘솔창 출력색상을 나타내는 함수
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}