#pragma once
#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "extraFunc.h"

typedef struct {
	char name[TEXTMAX]; // 이름
	int isMan; // 성별 (1: 남자, 2: 여자)
	int snum; // 학번
	int grade; // 학년
	char major[TEXTMAX]; // 전공
	char phoneNum[TEXTMAX]; // 전화 번호
	int breakfast; // 조식 여부 (0: x, 1: o)
	int outDate[3]; // 퇴실 날짜 ([0]: year, [1]: month, [2]: day)
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
void changeDong(int t_1, int t_2);
void showAllDong();
int getDongCount();
char* getDongName(int index);
DONG* getDONG(int index);
void setDefaultInfo(DONG* dong);
void setDefaultStu(STUDENT* stu);
void saveAllInfo();
void saveInfo(DONG* dong, FILE* fp);
void loadAllInfo();
DONG* loadInfo(FILE* fp);