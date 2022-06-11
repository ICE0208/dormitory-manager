#include "searchScreen.h"
#include "stuInfoScreen.h"

void searchScreen() {
	int selected;
	while (1) {
		setTitle(L"검색 화면");
		system(CLEAR);
		searchShowOption();
        selected = searchGetUserInput();
        if (selected == 0) return;
        searchMoveTo(selected);
	}
}

void searchMoveTo(int option) {
    switch (option) {
    case 1:
        // 이름으로 찾기 이동
        searchName();
        break;
    case 2:
        // 학번으로 찾기 이동
        searchSnum();
        break;
    }
}

void searchShowOption() {
    textcolor(11);
	printf("[검색 화면]\n\n");
    textcolor(15);
	printf("[1] 이름으로 찾기\n");
	printf("[2] 학번으로 찾기\n");
	printf("[0] 뒤로 가기\n\n");
}

int searchGetUserInput() {
    int value;
    printf("\n");
    while (1) {
        printf("입력 > ");
        scanf("%d", &value);
        clearBuffer();

        if (0 <= value && value <= 2) return value;

        system(CLEAR);
        searchShowOption();
        printInputErrMsg();
    }
}

void searchName() {
    setTitle(L"검색 화면 - 이름 검색");
    system(CLEAR);
    textcolor(11);
    printf("[이름으로 검색하기]\n\n");
    textcolor(15);
    printf("[0] 뒤로 가기\n\n입력 > ");

    char searchingName[TEXTMAX] = { '\0', };
    while (1) {
        scanf_s("%[^\n]s", searchingName, sizeof(searchingName));
        // 뒤로 가기 옵션
        if (strcmp(searchingName, "0") == 0) {
            clearBuffer();
            return;
        }

        // 글자 수 초과
        if (clearBuffer() == 1 || strlen(searchingName) == 0) {
            system(CLEAR);
            textcolor(11);
            printf("[이름으로 검색하기]\n\n");
            textcolor(15);
            printf("[0] 뒤로 가기\n");
            printf("\n<학생의 이름이 너무 깁니다.>\n입력 > ");
            continue;
        }
        break;
    }

    // 찾아진 이름을 저장할 연결리스트
    typedef struct foundStu {
        DONG* dong;
        int path[3]; // floor, ho, stu
        struct foundStu* next;
    } FOUND_STU;

    FOUND_STU* head = (FOUND_STU*)malloc(sizeof(FOUND_STU));
    FOUND_STU* tail = head;
    head->next = NULL;

    // 같은 이름 모두 연결리스트에 넣기
    int check = -1;
    for (int i = 1; i <= getDongCount(); i++) {
        DONG* curDong = getDONG(i);
        if (curDong == NULL) continue; // 혹시 모를 예외 처리
        for (int x = 0; x < FLOORMAX; x++) {
            for (int y = 0; y < HOMAX; y++) {
                for (int z = 0; z < STUMAX; z++) {
                    check = strcmp(searchingName, curDong->students[x][y][z].name);
                    if (check == 0) { // 이름이 같다면
                        tail->next = (FOUND_STU*)malloc(sizeof(FOUND_STU));
                        tail = tail->next;
                        tail->dong = curDong;
                        tail->path[0] = x;
                        tail->path[1] = y;
                        tail->path[2] = z;
                        tail->next = NULL;
                    }
                }
            }
        }
    }

    int selected;
    while (1) {
        selected = -1;
        system(CLEAR);
        textcolor(11);
        printf("[이름으로 검색하기]\n\n");
        textcolor(15);

        // 연결리스트에 저장된 값 모두 출력
        FOUND_STU* cur = head->next;
        int index = 0;
        while (cur != NULL) {
            index++;
            printf("[%02d] %s (%s %d층 %d%02d호 %d번 학생)\n",
                index, searchingName, (cur->dong)->name, cur->path[0] + 1,
                cur->path[0] + 1, cur->path[1] + 1, cur->path[2] + 1);
            cur = cur->next;
        }
        if (index == 0) {
            printf("<%s 학생을 찾을 수 없습니다.>\n", searchingName);
        }

        printf("\n[0] 뒤로 가기\n\n\n입력 > ");
        while (1) { // 올바른 값 입력받을 때 까지
            scanf("%d", &selected);
            clearBuffer();
            if (selected == 0) return;

            if (selected < 1 || selected > index) {
                system(CLEAR);
                textcolor(11);
                printf("[이름으로 검색하기]\n\n");
                textcolor(15);
                // 연결리스트에 저장된 값 모두 출력
                FOUND_STU* cur = head->next;
                int index = 0;
                while (cur != NULL) {
                    index++;
                    printf("[%02d] %s (%s %d층 %d%02d호 %d번 학생)\n",
                        index, searchingName, (cur->dong)->name, cur->path[0] + 1,
                        cur->path[0] + 1, cur->path[1] + 1, cur->path[2] + 1);
                    cur = cur->next;
                }
                if (index == 0) {
                    printf("<%s 학생을 찾을 수 없습니다.>\n", searchingName);
                }
                printf("\n[0] 뒤로 가기\n\n");
                printInputErrMsg();
                printf("입력 > ");
                continue;
            }
            break;
        }

        // 입력한 학생의 정보 화면으로 이동하기
        cur = head;
        for (int i = 0; i < selected; i++) {
            cur = cur->next;
        }
        stuInfoScreen(cur->dong, cur->path[0] + 1, cur->path[1] + 1, cur->path[2] + 1);

        // 연결 리스트 업데이트
        // - 연결 리스트 초기화
        cur = head->next;
        FOUND_STU* last;
        while (cur != NULL) {
            last = cur;
            cur = cur->next;
            free(last);
        }
        head->next = NULL;
        tail = head;
        // - 다시 연결 리스트에 추가
        int check = -1;
        for (int i = 1; i <= getDongCount(); i++) {
            DONG* curDong = getDONG(i);
            if (curDong == NULL) continue; // 혹시 모를 예외 처리
            for (int x = 0; x < FLOORMAX; x++) {
                for (int y = 0; y < HOMAX; y++) {
                    for (int z = 0; z < STUMAX; z++) {
                        check = strcmp(searchingName, curDong->students[x][y][z].name);
                        if (check == 0) { // 이름이 같다면
                            tail->next = (FOUND_STU*)malloc(sizeof(FOUND_STU));
                            tail = tail->next;
                            tail->dong = curDong;
                            tail->path[0] = x;
                            tail->path[1] = y;
                            tail->path[2] = z;
                            tail->next = NULL;
                        }
                    }
                }
            }
        }
    }
}

// 학번으로 학생 찾기 함수
void searchSnum() {
    setTitle(L"검색 화면 - 학번 검색");
    system(CLEAR);
    textcolor(11);
    printf("[학번으로 검색하기]\n\n");
    textcolor(15);
    printf("[0] 뒤로 가기\n\n입력 > ");

    // 찾을 학번 입력 받기
    char searchingSnum[TEXTMAX] = { '\0', }; // 찾을 학번 (문자열)
    int searchingSnumInt = 0; // 찾을 학번 (정수)
    while (1) {
        scanf_s("%[^\n]s", searchingSnum, sizeof(searchingSnum));
        // 뒤로 가기 옵션
        if (strcmp(searchingSnum, "0") == 0) {
            clearBuffer();
            return;
        }

        // 글자 수 초과
        if (clearBuffer() == 1 || strlen(searchingSnum) == 0 || strlen(searchingSnum) > 10) {
            system(CLEAR);
            textcolor(11);
            printf("[학번으로 검색하기]\n\n");
            textcolor(15);
            printf("[0] 뒤로 가기\n");
            printf("\n<학번이 너무 깁니다.>\n입력 > ");
            continue;
        }

        // 입력된 값을 정수로 변환할 수 없음
        searchingSnumInt = (int)strtol(searchingSnum, NULL, 10);
        if (searchingSnumInt == 0) {
            system(CLEAR);
            textcolor(11);
            printf("[학번으로 검색하기]\n\n");
            textcolor(15);
            printf("[0] 뒤로 가기\n");
            printf("\n<올바른 학번을 입력해주세요.>\n입력 > ");
            continue;
        }
        break;
    }

    // 찾아진 이름을 저장할 연결리스트
    typedef struct foundStu {
        DONG* dong;
        int path[3]; // floor, ho, stu
        struct foundStu* next;
    } FOUND_STU;

    FOUND_STU* head = (FOUND_STU*)malloc(sizeof(FOUND_STU));
    FOUND_STU* tail = head;
    head->next = NULL;

    // 같은 이름 모두 연결리스트에 넣기
    for (int i = 1; i <= getDongCount(); i++) {
        DONG* curDong = getDONG(i);
        if (curDong == NULL) continue; // 혹시 모를 예외 처리
        for (int x = 0; x < FLOORMAX; x++) {
            for (int y = 0; y < HOMAX; y++) {
                for (int z = 0; z < STUMAX; z++) {
                    // 학번이 같다면 연결리스트에 추가
                    if (searchingSnumInt == curDong->students[x][y][z].snum) {
                        tail->next = (FOUND_STU*)malloc(sizeof(FOUND_STU));
                        tail = tail->next;
                        tail->dong = curDong;
                        tail->path[0] = x;
                        tail->path[1] = y;
                        tail->path[2] = z;
                        tail->next = NULL;
                    }
                }
            }
        }
    }

    // 연결리스트에 있는 목록 보여주고 옵션 선택
    int selected;
    while (1) {
        selected = -1;
        system(CLEAR);
        textcolor(11);
        printf("[학번으로 검색하기]\n\n");
        textcolor(15);

        // 연결리스트에 저장된 값 모두 출력
        FOUND_STU* cur = head->next;
        int index = 0;
        while (cur != NULL) {
            index++;
            printf("[%02d] %d (%s %d층 %d%02d호 %d번 학생, %s)\n",
                index, searchingSnumInt, (cur->dong)->name, cur->path[0] + 1,
                cur->path[0] + 1, cur->path[1] + 1, cur->path[2] + 1, (cur->dong)->students[cur->path[0]][cur->path[1]][cur->path[2]].name);
            cur = cur->next;
        }
        if (index == 0) {
            printf("<%d 학번을 찾을 수 없습니다.>\n", searchingSnumInt);
        }

        printf("\n[0] 뒤로 가기\n\n\n입력 > ");
        while (1) { // 올바른 값 입력받을 때 까지
            scanf("%d", &selected);
            clearBuffer();
            if (selected == 0) return;

            if (selected < 1 || selected > index) {
                system(CLEAR);
                textcolor(11);
                printf("[학번으로 검색하기]\n\n");
                textcolor(15);
                // 연결리스트에 저장된 값 모두 출력
                FOUND_STU* cur = head->next;
                int index = 0;
                while (cur != NULL) {
                    index++;
                    printf("[%02d] %d (%s %d층 %d%02d호 %d번 학생, %s)\n",
                        index, searchingSnumInt, (cur->dong)->name, cur->path[0] + 1,
                        cur->path[0] + 1, cur->path[1] + 1, cur->path[2] + 1, (cur->dong)->students[cur->path[0]][cur->path[1]][cur->path[2]].name);
                    cur = cur->next;
                }
                if (index == 0) {
                    printf("<%d 학번을 찾을 수 없습니다.>\n", searchingSnumInt);
                }
                printf("\n[0] 뒤로 가기\n\n");
                printInputErrMsg();
                printf("입력 > ");
                continue;
            }
            break;
        }

        // 입력한 학생의 정보 화면으로 이동하기
        cur = head;
        for (int i = 0; i < selected; i++) {
            cur = cur->next;
        }
        stuInfoScreen(cur->dong, cur->path[0] + 1, cur->path[1] + 1, cur->path[2] + 1);

        // 연결 리스트 업데이트
        // - 연결 리스트 초기화
        cur = head->next;
        FOUND_STU* last;
        while (cur != NULL) {
            last = cur;
            cur = cur->next;
            free(last);
        }
        head->next = NULL;
        tail = head;
        // - 다시 연결 리스트에 추가
        for (int i = 1; i <= getDongCount(); i++) {
            DONG* curDong = getDONG(i);
            if (curDong == NULL) continue; // 혹시 모를 예외 처리
            for (int x = 0; x < FLOORMAX; x++) {
                for (int y = 0; y < HOMAX; y++) {
                    for (int z = 0; z < STUMAX; z++) {
                        // 학번이 같다면 연결리스트에 추가
                        if (searchingSnumInt == curDong->students[x][y][z].snum) {
                            tail->next = (FOUND_STU*)malloc(sizeof(FOUND_STU));
                            tail = tail->next;
                            tail->dong = curDong;
                            tail->path[0] = x;
                            tail->path[1] = y;
                            tail->path[2] = z;
                            tail->next = NULL;
                        }
                    }
                }
            }
        }
    }
}