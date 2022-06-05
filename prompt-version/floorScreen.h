#pragma once
#include "extraFunc.h"
#include "studentManager.h"
#include "hoScreen.h"


void floorScreen(int dongIndex);
void floorShowOption(char* dongName);
int floorGetUserInput(char* dongName);
void floorMoveTo(int dongIndex, int option);