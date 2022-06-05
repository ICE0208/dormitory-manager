#pragma once
#include "extraFunc.h"
#include "studentManager.h"
#include "stuScreen.h"

void hoScreen(DONG* dong, int floor);
void hoShowOption(DONG* dong, int floor);
int hoGetUserInput(DONG* dong, int floor);
void hoMoveTo(DONG* dong, int floor, int option);