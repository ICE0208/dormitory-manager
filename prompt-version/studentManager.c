#include "studentManager.h"

void setDongList() {
	head = (DONG*)malloc(sizeof(DONG));
	tail = head;
	head->next = NULL;
}

void setNewDong(char* dongName) {
	DONG* newDong = (DONG*)malloc(sizeof(DONG));
	newDong->next = NULL;
	strncpy(newDong->name, dongName, strlen(dongName));
	newDong->name[strlen(dongName)] = '\0';
	setDefaultInfo(newDong);
	tail->next = newDong;
	tail = tail->next;
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

void showAllDong() {
	DONG* cur = head->next;
	while (cur != NULL) {
		printf("%s\n", cur->students[0][0][0].name);
		printf("%s\n", cur->name);
		cur = cur->next;
	}
	printf("\n");
}

void setDefaultInfo(DONG* dong) {
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 20; y++) {
			for (int z = 0; z < 3; z++) {
				strcpy(dong->students[x][y][z].name, "미지정");
				dong->students[x][y][z].snum = 000;
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
	printf("저장 완료\n");
}

void saveInfo(DONG* dong, FILE* fp) {
	fwrite(dong->name, sizeof(20), 1, fp);
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
	check = fread((tempInfo->name), sizeof(20), 1, fp);
	if (check != 1) {
		free(tempInfo);
		return NULL;
	}
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