#pragma once
#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "extraFunc.h"

typedef struct {
	char name[TEXTMAX]; // 이름
	int snum; // 학번
	char phoneNum[TEXTMAX]; // 전화 번호
	int breakfast; // 조식 여부 (0: x, 1: o)
} STUDENT;

typedef struct dong {
	char name[TEXTMAX];
	STUDENT students[FLOORMAX][HOMAX][STUMAX];
	struct dong* next;
} DONG;

DONG* head;
DONG* tail;



void setDongList();
int setNewDong(char* dongName);
int removeDong(int index);
void showAllDong();
int getDongCount();
char* getDongName(int index);
DONG* getDONG(int index);
void setDefaultInfo(DONG* dong);
void saveAllInfo();
void saveInfo(DONG* dong, FILE* fp);
void loadAllInfo();
DONG* loadInfo(FILE* fp);