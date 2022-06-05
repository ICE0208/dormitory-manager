#pragma once
#include "extraFunc.h"
#include "studentManager.h"

void stuScreen(DONG* dong, int floor, int ho);
void stuShowOption(DONG* dong, int floor, int ho);
int stuGetUserInput(DONG* dong, int floor, int ho);
void stuMoveTo(DONG* dong, int floor, int ho, int option);