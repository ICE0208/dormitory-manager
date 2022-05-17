#pragma once
#include <stdio.h>
#include <stdlib.h>

// check window or mac
#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#define CLEAR "cls"
#elif __APPLE__
#define PATH_SEPARATOR '/'
#define CLEAR "clear"
#endif

void mainScreen();
void mainShowOption();
int mainGetUserInput();
void clearBuffer();
void mainMoveTo(int option);