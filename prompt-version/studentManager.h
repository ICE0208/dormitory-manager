#pragma once
#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>


typedef struct {
	char name[20];
	int snum;
} STUDENT;

typedef struct dong {
	char name[20];
	STUDENT students[15][20][3];
	struct dong* next;
} DONG;

DONG* head;
DONG* tail;

void setDongList();
void setNewDong(char* dongName);
int removeDong(int index);
void showAllDong();
void setDefaultInfo(DONG* dong);
void saveAllInfo();
void saveInfo(DONG* dong, FILE* fp);
void loadAllInfo();
DONG* loadInfo(FILE* fp);