#include "extraFunc.h"

int clearBuffer() {
    int c;
    int isOver = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        isOver = 1;
    }
    return isOver;
}