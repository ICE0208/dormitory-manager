#include "studentManager.h"

// 동 연결 리스트를 생성합니다.
void setDongList() {
	head = (DONG*)malloc(sizeof(DONG));
	tail = head;
	head->next = NULL;
}

// 새로운 동을 추가합니다.
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

// index의 동을 삭제합니다.
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

// t_1과 t_2의 자리를 바꿔주는 함수입니다.
void changeDong(int target_1, int target_2) {
	// t_1의 전 노드를 before_t_1에 가져오기
	DONG* before_t_1 = head;
	DONG* t_1 = head->next;
	int i = 1;
	while (t_1 != NULL) {
		if (i == target_1) break;
		i += 1;
		before_t_1 = t_1;
		t_1 = t_1->next;
	}
	// t_2의 전 노드를 before_t_2에 가져오기
	DONG* before_t_2 = head;
	DONG* t_2 = head->next;
	i = 1;
	while (t_2 != NULL) {
		if (i == target_2) break;
		i += 1;
		before_t_2 = t_2;
		t_2 = t_2->next;
	}

	DONG* temp = before_t_1->next;
	before_t_1->next = before_t_2->next;
	before_t_2->next = temp;

	if (t_1->next == NULL) {
		t_1->next = t_2->next;
		t_2->next = NULL;
	}
	else if (t_2->next == NULL) {
		t_2->next = t_1->next;
		t_1->next = NULL;
	}
	else {
		temp = t_1->next;
		t_1->next = t_2->next;
		t_2->next = temp;
	}
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

// 등록된 동의 개수를 반환해주는 함수입니다.
int getDongCount() {
	DONG* cur = head->next;
	int count = 0;
	while (cur != NULL) {
		count++;
		cur = cur->next;
	}
	return count;
}

// 특정 인덱스에 저장되어 있는 동의 이름을 리턴해주는 함수입니다.
// 인덱스는 1번부터 시작합니다.
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
	return "<ERROR can't find dong's name>";
}

// 특정 인덱스에 저장되어 있는 동의 구조체 포인터를 리턴해주는 함수입니다.
// 인덱스는 1번부터 시작합니다.
DONG* getDONG(int index) {
	int i = 1;
	DONG* cur = head->next;
	while (cur != NULL) {
		if (i == index) {
			return cur;
		}
		i += 1;
		cur = cur->next;
	}
	return NULL;
}

// 동을 하나 생성할 때 각 학생의 정보의 초깃값을 지정하기 위한 함수입니다.
void setDefaultInfo(DONG* dong) {
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 20; y++) {
			for (int z = 0; z < 3; z++) {
				setDefaultStu(&(dong->students[x][y][z]));
			}
		}
	}
}

// 학생 정보를 초기값으로 세팅해줍니다.
void setDefaultStu(STUDENT* stu) {
	strcpy(stu->name, DEFAULT_NAME);
	stu->isMan = DEFAULT_GENDER;
	stu->snum = DEFAULT_SNUM;
	stu->grade = DEFAULT_GRADE;
	strcpy(stu->major, DEFAULT_MAJOR);
	strcpy(stu->phoneNum, DEFAULT_PHONENUM);
	stu->breakfast = DEFAULT_BREAKFAST;
	int d_o[3] = DEFAULT_OUTDATE;
	for (int i = 0; i < 3; i++) {
		stu->outDate[i] = d_o[i];
	}
}

// 모든 정보를 파일로 저장합니다.
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

// 선택된 동을 파일에 저장합니다.
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

// 파일로부터 모든 정보를 불러옵니다.
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

// 파일로부터 정보를 불러옵니다.
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