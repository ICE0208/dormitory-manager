#include "studentManager.h"

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

void showAllDong() {
	DONG* cur = head->next;
	int index = 1;
	while (cur != NULL) {
		printf("[%d]: %s\t", index, cur->students[0][0][0].name);
		cur = cur->next;

		if (index % 3 == 0) printf("\n");
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
	char tempName[20] = { '\0' };
	check = fread(tempName, sizeof(20), 1, fp);
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