#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[20];
	int snum;
} STUDENT;

typedef struct dong {
	char *name;
	STUDENT students[15][30][3];
	struct dong* next;
} DONG;

DONG* head;
DONG* tail;

void setDongList();
DONG* setNewDong(char* dongName);
int removeDong(int index);
void showAllDong();