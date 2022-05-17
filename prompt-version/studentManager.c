#include "studentManager.h"

void setDongList() {
	head = (DONG*)malloc(sizeof(DONG));
	tail = head;
	head->next = NULL;
}

void setNewDong(char* dongName) {
	DONG* newDong = (DONG*)malloc(sizeof(DONG));
	newDong->next = NULL;
	newDong->name = dongName;
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
		printf("%s", cur->students[0][0][0].name);
		printf("%s\n", cur->name);
		cur = cur->next;
	}
	printf("\n");
}

void setDefaultInfo(DONG* dong) {
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 20; y++) {
			for (int z = 0; z < 3; z++) {
				dong->students[x][y][z].name = "홍길동";
				dong->students[x][y][z].snum = 123;
			}
		}
	}
}

void saveAllStudent() {
	FILE* fp = fopen("c:\\temp\\info.txt", "wb");
	DONG* cur = head->next;
	while (cur != NULL) {
		saveDong(cur, fp);
		cur = cur->next;
	}
	fclose(fp);
	printf("저장 완료");
}

void saveDong(DONG* dong, FILE* fp) {
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 20; y++) {
			for (int z = 0; z < 3; z++) {
				STUDENT stu = dong->students[x][y][z];
				fwrite(&stu, sizeof(STUDENT), 1, fp);
			}
		}
	}
}