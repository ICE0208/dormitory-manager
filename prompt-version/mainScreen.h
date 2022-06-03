#pragma once
#include <stdio.h>
#include <stdlib.h>

#define PATH_SEPARATOR '\\'
#define CLEAR "cls"

void mainScreen();
void mainShowOption();
int mainGetUserInput();
int clearBuffer();
void mainMoveTo(int option);