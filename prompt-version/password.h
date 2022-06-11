#pragma once
#include "extraFunc.h"
#include <string.h>
#include <direct.h>

#define PW_MAX 20

extern char password[PW_MAX + 1];

int setPassword(char* msg, char* zeroMsg);
void savePassword();
void loadPassword();
int confirmPassword(char* zeroMsg);