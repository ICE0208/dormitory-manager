#pragma once
#include "extraFunc.h"
#include "studentManager.h"

void stuInfoScreen(DONG* dong, int floor, int ho, int stu_i);
void printStuInfo(DONG* dong, int floor, int ho, int stu_i);
void stuInfoShowOption();
int stuInfoGetUserInput(DONG* dong, int floor, int ho, int stu_i);
void stuInfoMoveTo(DONG* dong, int floor, int ho, int stu_i, int option);
void addNewStu(DONG* dong, int floor, int ho, int stu_i);
void removeCurStu(DONG* dong, int floor, int ho, int stu_i);