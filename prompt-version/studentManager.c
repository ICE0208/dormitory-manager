﻿#include "studentManager.h"

void setDongList() {
	head = (DONG*)malloc(sizeof(DONG));
	tail = head;
	head->next = NULL;
}

int setNewDong(char* dongName) {
	int curCount = getDongCount();
	if (curCount >= 20) return -1;

	DONG* newDong = (DONG*)malloc(sizeof(DONG));
	newDong->next = NULL;
	strcpy(newDong->name, dongName);
	setDefaultInfo(newDong);
	tail->next = newDong;
	tail = tail->next;
	return 0;
}

int removeDong(int index) {
	int i = 1;
	DONG* lastCur = head;
	DONG* cur = head->next;
	while (cur != NULL) {
		if (i == index) {
			if (cur == tail) {
				tail = lastCur;
			}
			lastCur->next = cur->next;
			free(cur);
			return 1;
		}
		i += 1;
		lastCur = cur;
		cur = cur->next;
	}
	printf("can't remove :( \n");
	return 0;
}

// 등록된 동을 인덱스와 함께 모두 출력해주는 함수입니다.
void showAllDong() {
	DONG* cur = head->next;
	if (cur == NULL) { // 동이 하나도 없을 때
		printf("<등록된 동이 없습니다.>\n");
		return;
	}

	int index = 1;
	while (1) {
		printf("[%02d]: %-20s", index, cur->name);
		cur = cur->next;
		if (cur == NULL) break; // while 문을 빠져나갈 조건

		if (index % 3 == 0) printf("\n");
		else printf(" | ");
		index++;
	}
	printf("\n");
}

int getDongCount() {
	DONG* cur = head->next;
	int count = 0;
	while (cur != NULL) {
		count++;
		cur = cur->next;
	}
	return count;
}

// 특정 인덱스에 저장되어 있는 동의 이름을 리턴해주는 함수이다.
// 인덱스는 1번부터 시작한다.
char* getDongName(int index) {
	int i = 1;
	DONG* cur = head->next;
	while (cur != NULL) {
		if (i == index) {
			return cur->name;
		}
		i += 1;
		cur = cur->next;
	}
	return "<ERROR>";
}

// 동을 하나 생성할 때 각 학생의 정보의 초깃값을 지정하기 위한 함수입니다.
void setDefaultInfo(DONG* dong) {
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 20; y++) {
			for (int z = 0; z < 3; z++) {
				strcpy(dong->students[x][y][z].name, "미지정"); // 이름 미지정
				dong->students[x][y][z].snum = 000; // 학번 초깃값
				strcpy(dong->students[x][y][z].phoneNum, "010-xxxx-xxxx"); // 전화번호 초깃값
				dong->students[x][y][z].breakfast = 0; // 조식 여부 초깃값 (x)
			}
		}
	}
}

void saveAllInfo() {
	mkdir("c:\\dormanager");
	FILE* fp = fopen("c:\\dormanager\\info.bin", "wb");
	DONG* cur = head->next;
	while (cur != NULL) {
		saveInfo(cur, fp);
		cur = cur->next;
	}
	fclose(fp);
	//printf("저장 완료\n");
}

void saveInfo(DONG* dong, FILE* fp) {
	fwrite(dong->name, TEXTMAX, 1, fp);
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 20; y++) {
			for (int z = 0; z < 3; z++) {
				fwrite(&(dong->students[x][y][z]), sizeof(STUDENT), 1, fp);
			}
		}
	}
}

void loadAllInfo() {
	FILE* fp = fopen("c:\\dormanager\\info.bin", "rb");
	if (fp == NULL) {
		printf("파일을 찾을 수 없음\n");
		return;
	}
	while (1) {
		DONG* info;
		if ((info = loadInfo(fp)) == NULL) break;
		tail->next = info;
		tail = tail->next;
	}
	fclose(fp);
}

DONG* loadInfo(FILE* fp) {
	DONG* tempInfo = (DONG*)malloc(sizeof(DONG));
	tempInfo->next = NULL;
	int check;
	char tempName[TEXTMAX] = { '\0' };
	check = fread(tempName, TEXTMAX, 1, fp);
	if (check != 1) {
		free(tempInfo);
		return NULL;
	}
	strcpy(tempInfo->name, tempName);
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 20; y++) {
			for (int z = 0; z < 3; z++) {
				check = fread(&(tempInfo->students[x][y][z]), sizeof(STUDENT), 1, fp);
				if (check != 1) {
					free(tempInfo);
					return NULL;
				}
			}
		}
	}
	return tempInfo;
}