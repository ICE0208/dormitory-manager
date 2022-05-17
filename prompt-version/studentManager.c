#include "studentManager.h"

void setDongList() {
	head = (DONG*)malloc(sizeof(DONG));
	tail = head;
	head->next = NULL;
}

DONG* setNewDong(char* dongName) {
	DONG* newDong = (DONG*)malloc(sizeof(DONG));
	newDong->next = NULL;
	newDong->name = dongName;
	// default student settings code position
	tail->next = newDong;
	tail = tail->next;
}

int removeDong(int index) {
	int i = 1;
	DONG* lastCur = head;
	DONG* cur = head->next;
	while (cur != NULL) {
		if (i == index) {
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
		printf("%s\n", cur->name);
		cur = cur->next;
	}
	printf("\n");
}