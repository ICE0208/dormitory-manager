#include "stuInfoScreen.h"

// stu_i는 1부터 3까지
void stuInfoScreen(DONG* dong, int floor, int ho, int stu_i) {
	int selected;

	while (1) {
		setTitle(L"학생 정보 화면");
		system(CLEAR);
		printStuInfo(dong, floor, ho, stu_i); // 학생 정보 출력
		stuInfoShowOption(); // 학생 정보 관련 옵션 보여주기
		selected = stuInfoGetUserInput(dong, floor, ho, stu_i); // 사용자의 옵션 선택
		if (selected == 0) return; // 뒤로 가기 옵션 선택했을 때
		stuInfoMoveTo(dong, floor, ho, stu_i, selected); // 선택한 옵션의 명령어 수행
	}
}

void printStuInfo(DONG* dong, int floor, int ho, int stu_i) {
	STUDENT* stu = &(dong->students[floor-1][ho-1][stu_i-1]);
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("정보 출력 화면]\n");

	// 출력할 학생 정보가 없을 때
	if (stu->snum == 0) {
		printf("\n<등록된 학생이 없습니다.>\n");
		return;
	}

	printf("학생 이름 : %s\n", stu->name);
	printf("학생 성별: %s\n", stu->isMan == 2 ? "여자" : "남자");
	printf("학번: %d\n", stu->snum);
	printf("학년: %d\n", stu->grade);
	printf("전공: %s\n", stu->major);
	printf("전화 번호: %s\n", stu->phoneNum);
	printf("조식 여부: ");
	printf("%s", stu->breakfast == 1 ? "O\n" : "X\n");
	printf("퇴실 날찌: %04d년 %02d월 %02d일\n",
		stu->outDate[0], stu->outDate[1], stu->outDate[2]);
}

void stuInfoShowOption() {
	printf("\n[1] 새로운 학생으로 추가");
	printf("\n[2] 현재 학생 정보 수정");
	printf("\n[3] 현재 학생 정보 삭제");
	printf("\n[0] 뒤로 가기\n\n");
}

int stuInfoGetUserInput(DONG* dong, int floor, int ho, int stu_i) {
	int value;
	printf("\n");
	// 올바른 값이 입력될 때까지 반복합니다.
	while (1) {
		printf("입력 > ");
		scanf("%d", &value);
		clearBuffer();

		// 올바른 값 입력했을 때 그 값을 리턴
		if (0 <= value && value <= 3) return value;

		// 잘못된 값 입력했을 때
		system(CLEAR);
		printStuInfo(dong, floor, ho, stu_i);
		stuInfoShowOption();
		printInputErrMsg(); // 에러 메세제를 출력
	}
}

void stuInfoMoveTo(DONG* dong, int floor, int ho, int stu_i, int option) {
	// 1 ~ 3
	if (1 <= option && option <= 3) {
		if (option == 1) { // 새로운 학생 정보 추가
			addNewStu(dong, floor, ho, stu_i);
			clearBuffer();
			return;
		}
		if (option == 2) { // 현재 학생 정보 수정
			modifyCurStu(dong, floor, ho, stu_i);
			clearBuffer();
			return;
		}
		if (option == 3) { // 현재 학생 정보 삭제
			removeCurStu(dong, floor, ho, stu_i);
			clearBuffer();
			return;
		}
		return;
	}
}

void printCurStu(STUDENT* stu, int count) {
	if (count < 1) return;
	printf("-- 현재 학생의 정보 --\n");
	printf("이름: %s\n", stu->name);
	if (count < 2) { printf("-----------------------------\n\n"); return; }
	printf("성별: %s\n", stu->isMan == 2 ? "여자" : "남자");
	if (count < 3) { printf("-----------------------------\n\n"); return; }
	printf("학번: %d\n", stu->snum);
	if (count < 4) { printf("-----------------------------\n\n"); return; }
	printf("학년: %d\n", stu->grade);
	if (count < 5) { printf("-----------------------------\n\n"); return; }
	printf("전공: %s\n", stu->major);
	if (count < 6) { printf("-----------------------------\n\n"); return; }
	printf("전화번호: %s\n", stu->phoneNum);
	if (count < 7) { printf("-----------------------------\n\n"); return; }
	printf("조식 여부: ");
	printf("%s", stu->breakfast == 1 ? "O\n" : "X\n");
	if (count < 8) { printf("-----------------------------\n\n"); return; }
	printf("퇴실 날찌: %04d년 %02d월 %02d일\n",
		stu->outDate[0], stu->outDate[1], stu->outDate[2]);
	printf("-----------------------------\n\n");
}

void addNewStu(DONG* dong, int floor, int ho, int stu_i) {
	STUDENT newStu;
	setDefaultStu(&newStu);
	setTitle(L"학생 정보 화면 - 새로운 학생으로 추가");

	// 이름
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printf("[0] 뒤로 가기\n\n새로운 학생의 이름을 입력해주세요.\n\n입력 > ");
	char newStuName[TEXTMAX] = { '\0', };
	while (1) {
		scanf_s("%[^\n]s", newStuName, sizeof(newStuName));
		// 뒤로 가기 옵션
		if (strcmp(newStuName, "0") == 0) return;

		// 글자 수 초과
		if (clearBuffer() == 1 || strlen(newStuName) == 0) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printf("[0] 뒤로 가기\n\n새로운 학생의 이름을 입력해주세요.");
			printf("\n<학생의 이름이 너무 깁니다.>\n입력 > ");
			continue;
		}
		strcpy(newStu.name, newStuName);
		break;
	}

	// 성별
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printCurStu(&newStu, 1);
	printf("[0] 뒤로 가기\n\n새로운 학생의 성별을 입력해주세요. (1: 남자, 2: 여자)\n\n입력 > ");
	int isMan = -1;
	while (1) {
		scanf("%d", &isMan);
		// 뒤로 가기 옵션
		if (isMan == 0) return;
		clearBuffer();

		// 다른 값이 입력됐을 때
		if (isMan != 1 && isMan != 2) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printCurStu(&newStu, 1);
			printf("[0] 뒤로 가기\n\n새로운 학생의 성별을 입력해주세요. (1: 남자, 2: 여자)\n");
			printf("올바른 값을 입력해주세요.\n입력 > ");
			continue;
		}

		newStu.isMan = isMan;
		break;
	}

	// 학번
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printCurStu(&newStu, 2);
	printf("[0] 뒤로 가기\n\n새로운 학생의 학번을 입력해주세요.\n\n입력 > ");
	char newStuNum[TEXTMAX] = { '\0', };
	int newSNum = 0;
	while (1) {
		scanf_s("%[^\n]s", newStuNum, sizeof(newStuNum));
		// 뒤로 가기 옵션
		if (strcmp(newStuNum, "0") == 0) return;

		// 글자 수 초과
		if (clearBuffer() == 1 || strlen(newStuNum) == 0 || strlen(newStuNum) > 10) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printCurStu(&newStu, 2);
			printf("[0] 뒤로 가기\n\n새로운 학생의 학번을 입력해주세요.");
			printf("\n<학번이 너무 깁니다.>\n입력 > ");
			continue;
		}

		// 입력된 값을 정수로 변환할 수 없음
		newSNum = (int) strtol(newStuNum, NULL, 10);
		if (newSNum == 0) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printCurStu(&newStu, 2);
			printf("[0] 뒤로 가기\n\n새로운 학생의 이름을 입력해주세요.");
			printf("\n<올바른 학번을 입력해주세요.>\n입력 > ");
			continue;
		}
		
		newStu.snum = newSNum;
		break;
	}

	// 학년
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printCurStu(&newStu, 3);
	printf("[0] 뒤로 가기\n\n새로운 학생의 학년을 입력해주세요.\n\n입력 > ");
	int newStuGrade = -1;
	while (1) {
		scanf("%d", &newStuGrade);
		// 뒤로 가기 옵션
		if (newStuGrade == 0) return;
		clearBuffer();

		// 다른 값이 입력됐을 때
		if (newStuGrade < 1 || newStuGrade > 10) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printCurStu(&newStu, 3);
			printf("[0] 뒤로 가기\n\n새로운 학생의 학년을 입력해주세요.\n");
			printf("올바른 값을 입력해주세요.\n입력 > ");
			continue;
		}

		newStu.grade = newStuGrade;
		break;
	}

	// 전공
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printCurStu(&newStu, 4);
	printf("[0] 뒤로 가기\n\n새로운 학생의 전공을 입력해주세요.\n\n입력 > ");
	char newStuMajor[TEXTMAX] = { '\0', };
	while (1) {
		scanf_s("%[^\n]s", newStuMajor, sizeof(newStuMajor));
		// 뒤로 가기 옵션
		if (strcmp(newStuMajor, "0") == 0) return;

		// 글자 수 초과
		if (clearBuffer() == 1 || strlen(newStuMajor) == 0) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printCurStu(&newStu, 4);
			printf("[0] 뒤로 가기\n\n새로운 학생의 전공을 입력해주세요.");
			printf("\n<전공 글자 수가 너무 깁니다.>\n입력 > ");
			continue;
		}
		strcpy(newStu.major, newStuMajor);
		break;
	}

	// 전화번호
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printCurStu(&newStu, 5);
	printf("[0] 뒤로 가기\n\n새로운 학생의 전화번호를 입력해주세요.\n\n입력 > ");
	char newStuPhoneNum[TEXTMAX] = { '\0', };
	while (1) {
		scanf_s("%[^\n]s", newStuPhoneNum, sizeof(newStuPhoneNum));
		// 뒤로 가기 옵션
		if (strcmp(newStuPhoneNum, "0") == 0) return;

		// 글자 수 초과
		if (clearBuffer() == 1 || strlen(newStuPhoneNum) == 0) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printCurStu(&newStu, 5);
			printf("[0] 뒤로 가기\n\n새로운 학생의 전화번호를 입력해주세요.");
			printf("\n<전화번호가 너무 깁니다.>\n입력 > ");
			continue;
		}
		strcpy(newStu.phoneNum, newStuPhoneNum);
		break;
	}

	// 조식여부
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printCurStu(&newStu, 6);
	printf("[0] 뒤로 가기\n\n새로운 학생의 조식신청 여부 입력해주세요. (o/x)\n\n입력 > ");
	char newStuBreakfast[TEXTMAX] = { '\0', };
	while (1) {
		scanf_s("%[^\n]s", newStuBreakfast, sizeof(newStuBreakfast));
		// 뒤로 가기 옵션
		if (strcmp(newStuBreakfast, "0") == 0) return;

		// 글자 수 초과
		if (clearBuffer() == 1 || strlen(newStuBreakfast) == 0 || 
			(strcmp(newStuBreakfast, "O") != 0 && strcmp(newStuBreakfast, "o") != 0) 
			&& strcmp(newStuBreakfast, "X") != 0 && strcmp(newStuBreakfast, "x") != 0) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printCurStu(&newStu, 6);
			printf("[0] 뒤로 가기\n\n새로운 학생의 조식신청 여부 입력해주세요. (o/x)");
			printf("\n<올바른 값을 입력해주세요.>\n입력 > ");
			continue;
		}

		if (strcmp(newStuBreakfast, "O") == 0 || strcmp(newStuBreakfast, "o") == 0) {
			newStu.breakfast = 1;
		}
		else {
			newStu.breakfast = 0;
		}
		
		break;
	}

	// 퇴실 날짜
	int newStuOutDate[3] = { -1, -1, -1 };
	// 연도
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printCurStu(&newStu, 7);
	printf("[0] 뒤로 가기\n\n새로운 학생의 퇴실 날짜의 연도를 입력해주세요. (____-__-__)\n\n입력 > ");
	while (1) {
		scanf("%d", &newStuOutDate[0]);
		// 뒤로 가기 옵션
		if (newStuOutDate[0] == 0) return;
		clearBuffer();

		// 다른 값이 입력됐을 때
		if (newStuOutDate[0] < 2022 || newStuOutDate[0] > 3000) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printCurStu(&newStu, 7);
			printf("[0] 뒤로 가기\n\n새로운 학생의 퇴실 날짜의 연도를 입력해주세요. (____-__-__)\n");
			printf("올바른 연도를 입력해주세요.\n입력 > ");
			continue;
		}
		newStu.outDate[0] = newStuOutDate[0];
		break;
	}
	// 월
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printCurStu(&newStu, 7);
	printf("[0] 뒤로 가기\n\n새로운 학생의 퇴실 날짜의 월을 입력해주세요. (%04d-__-__)\n\n입력 > ", newStu.outDate[0]);
	while (1) {
		scanf("%d", &newStuOutDate[1]);
		// 뒤로 가기 옵션
		if (newStuOutDate[1] == 0) return;
		clearBuffer();

		// 다른 값이 입력됐을 때
		if (newStuOutDate[1] < 1 || newStuOutDate[1] > 12) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printCurStu(&newStu, 7);
			printf("[0] 뒤로 가기\n\n새로운 학생의 퇴실 날짜의 월을 입력해주세요. (%04d-__-__)\n", newStu.outDate[0]);
			printf("올바른 월을 입력해주세요.\n입력 > ");
			continue;
		}
		newStu.outDate[1] = newStuOutDate[1];
		break;
	}
	// 일
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printCurStu(&newStu, 7);
	printf("[0] 뒤로 가기\n\n새로운 학생의 퇴실 날짜의 일을 입력해주세요. (%04d-%02d-__)\n\n입력 > ", 
		newStu.outDate[0], newStu.outDate[1]);
	while (1) {
		scanf("%d", &newStuOutDate[2]);
		// 뒤로 가기 옵션
		if (newStuOutDate[2] == 0) return;
		clearBuffer();

		// 다른 값이 입력됐을 때
		if (newStuOutDate[2] < 1 || newStuOutDate[2] > 31) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("새로운 학생으로 추가]\n\n");
			printCurStu(&newStu, 7);
			printf("[0] 뒤로 가기\n\n새로운 학생의 퇴실 날짜의 일을 입력해주세요. (%04d-%02d-__)\n",
				newStu.outDate[0], newStu.outDate[1]);
			printf("올바른 일을 입력해주세요.\n입력 > ");
			continue;
		}
		newStu.outDate[2] = newStuOutDate[2];
		break;
	}

	// 확인 절차
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printCurStu(&newStu, 8);
	printf("이 정보를 %s %d층 %d%02d호 학생%d에 추가하시겠습니까?\n",
		dong->name, floor, floor, ho, stu_i);
	printf("[y] 예   [다른값] 아니오\n\n입력 > ");
	char confirm;
	scanf("%c", &confirm);
	clearBuffer();

	if (confirm != 'y') {
		printf("\n추가를 취소했습니다.\n아무 키나 누르면 돌아갑니다.");
		getch();
		return;
	}

	// 정보를 새로운 정보로 수정
	STUDENT* stu = &(dong->students[floor-1][ho-1][stu_i-1]);
	strcpy(stu->name, newStu.name);
	stu->isMan = newStu.isMan;
	stu->snum = newStu.snum;
	stu->grade = newStu.grade;
	strcpy(stu->major, newStu.major);
	strcpy(stu->phoneNum, newStu.phoneNum);
	stu->breakfast = newStu.breakfast;
	for (int i = 0; i < 3; i++) {
		stu->outDate[i] = newStu.outDate[i];
	}
	saveAllInfo(); // 파일에 저장
	printf("정보 등록을 완료했습니다.\n아무 키나 누르면 돌아갑니다.");
	getch();
	return;
}

void removeCurStu(DONG* dong, int floor, int ho, int stu_i) {
	setTitle(L"학생 정보 화면 - 현재 학생 정보 삭제");
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 삭제]\n\n");
	STUDENT* stu = &(dong->students[floor - 1][ho - 1][stu_i - 1]);
	if (stu->snum == 0) {
		printf("<삭제할 학생의 정보가 없습니다.>\n\n");
		printf("아무 키나 누르면 돌아갑니다.\n");
		getch();
		return;
	}

	// 확인 절차
	printf("-- 현재 학생의 정보 --\n");
	printf("학생 이름 : %s\n", stu->name);
	printf("학생 성별: %s\n", stu->isMan == 2 ? "여자" : "남자");
	printf("학번: %d\n", stu->snum);
	printf("학년: %d\n", stu->grade);
	printf("전공: %s\n", stu->major);
	printf("전화 번호: %s\n", stu->phoneNum);
	printf("조식 여부: ");
	printf("%s", stu->breakfast == 1 ? "O\n" : "X\n");
	printf("퇴실 날찌: %04d년 %02d월 %02d일\n",
		stu->outDate[0], stu->outDate[1], stu->outDate[2]);
	printf("----------------------------\n\n");
	printf("%s %d층 %d%02d호 학생%d에 있는 이 정보를 삭제하시겠습니까?\n",
		dong->name, floor, floor, ho, stu_i);
	printf("[y] 예   [다른값] 아니오\n\n입력 > ");
	char confirm;
	scanf("%c", &confirm);
	clearBuffer();

	if (confirm != 'y') {
		printf("\n삭제를 취소했습니다.\n아무 키나 누르면 돌아갑니다.");
		getch();
		return;
	}

	setDefaultStu(stu); // 이 학생의 정보를 초기화
	saveAllInfo(); // 파일에 저장
	printf("현재 학생의 정보 삭제를 완료했습니다.\n아무 키나 누르면 돌아갑니다.");
	getch();
	return;
}

void modifyCurStu(DONG* dong, int floor, int ho, int stu_i) {
	setTitle(L"학생 정보 화면 - 현재 학생 정보 수정");
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 수정]\n\n");
	STUDENT* stu = &(dong->students[floor - 1][ho - 1][stu_i - 1]);
	if (stu->snum == 0) {
		printf("<수정할 학생의 정보가 없습니다.>\n\n");
		printf("아무 키나 누르면 돌아갑니다.");
		getch();
		return;
	}

	STUDENT tempStu;
	memcpy(&tempStu, stu, sizeof(STUDENT)); // 구조체 값 복사
	int check = -1;

	// 이름 변경할건지 확인
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 수정]\n\n");
	printCurStu(&tempStu, 8);
	printf("[0] 뒤로 가기\n\n학생의 이름을 변경하시겠습니까? (1: 예 / 2: 아니오)\n\n");
	printf("입력 > ");
	while (1) {
		scanf("%d", &check);
		// 뒤로 가기 옵션
		if (check == 0) return;
		clearBuffer();

		// 다른 값
		if (check != 1 && check != 2) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("현재 학생 정보 수정]\n\n");
			printCurStu(&tempStu, 8);
			printf("[0] 뒤로 가기\n\n학생의 이름을 변경하시겠습니까? (1: 예 / 2: 아니오)\n");
			printf("올바른 값을 입력해주세요.\n입력> ");
			continue;
		}
		break;
	}
	// 이름 변경
	if (check == 1) {
		// 이름
		system(CLEAR);
		printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
		printf("현재 학생 정보 수정]\n\n");
		printCurStu(&tempStu, 8);
		printf("[0] 뒤로 가기\n\n수정할 학생의 이름을 입력해주세요.\n\n입력 > ");
		char newStuName[TEXTMAX] = { '\0', };
		while (1) {
			scanf_s("%[^\n]s", newStuName, sizeof(newStuName));
			// 뒤로 가기 옵션
			if (strcmp(newStuName, "0") == 0) return;

			// 글자 수 초과
			if (clearBuffer() == 1 || strlen(newStuName) == 0) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 이름을 입력해주세요.");
				printf("\n<학생의 이름이 너무 깁니다.>\n입력 > ");
				continue;
			}
			strcpy(tempStu.name, newStuName);
			break;
		}
	}
	check = -1;

	// 성별 변경할건지 확인
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 수정]\n\n");
	printCurStu(&tempStu, 8);
	printf("[0] 뒤로 가기\n\n학생의 성별을 변경하시겠습니까? (1: 예 / 2: 아니오)\n\n");
	printf("입력 > ");
	while (1) {
		scanf("%d", &check);
		// 뒤로 가기 옵션
		if (check == 0) return;
		clearBuffer();

		// 다른 값
		if (check != 1 && check != 2) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("현재 학생 정보 수정]\n\n");
			printCurStu(&tempStu, 8);
			printf("[0] 뒤로 가기\n\n학생의 성별을 변경하시겠습니까? (1: 예 / 2: 아니오)\n");
			printf("올바른 값을 입력해주세요.\n입력> ");
			continue;
		}
		break;
	}
	if (check == 1) {
		// 성별
		system(CLEAR);
		printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
		printf("현재 학생 정보 수정]\n\n");
		printCurStu(&tempStu, 8);
		printf("[0] 뒤로 가기\n\n수정할 학생의 성별을 입력해주세요. (1: 남자, 2: 여자)\n\n입력 > ");
		int isMan = -1;
		while (1) {
			scanf("%d", &isMan);
			// 뒤로 가기 옵션
			if (isMan == 0) return;
			clearBuffer();

			// 다른 값이 입력됐을 때
			if (isMan != 1 && isMan != 2) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 성별을 입력해주세요. (1: 남자, 2: 여자)\n");
				printf("올바른 값을 입력해주세요.\n입력 > ");
				continue;
			}

			tempStu.isMan = isMan;
			break;
		}
	} 
	check = -1;

	// 학번 변경할건지 확인
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 수정]\n\n");
	printCurStu(&tempStu, 8);
	printf("[0] 뒤로 가기\n\n학생의 학번을 변경하시겠습니까? (1: 예 / 2: 아니오)\n\n");
	printf("입력 > ");
	while (1) {
		scanf("%d", &check);
		// 뒤로 가기 옵션
		if (check == 0) return;
		clearBuffer();

		// 다른 값
		if (check != 1 && check != 2) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("현재 학생 정보 수정]\n\n");
			printCurStu(&tempStu, 8);
			printf("[0] 뒤로 가기\n\n학생의 학번을 변경하시겠습니까? (1: 예 / 2: 아니오)\n");
			printf("올바른 값을 입력해주세요.\n입력> ");
			continue;
		}
		break;
	}
	if (check == 1) {
		// 학번
		system(CLEAR);
		printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
		printf("현재 학생 정보 수정]\n\n");
		printCurStu(&tempStu, 8);
		printf("[0] 뒤로 가기\n\n수정할 학생의 학번을 입력해주세요.\n\n입력 > ");
		char newStuNum[TEXTMAX] = { '\0', };
		int newSNum = 0;
		while (1) {
			scanf_s("%[^\n]s", newStuNum, sizeof(newStuNum));
			// 뒤로 가기 옵션
			if (strcmp(newStuNum, "0") == 0) return;

			// 글자 수 초과
			if (clearBuffer() == 1 || strlen(newStuNum) == 0 || strlen(newStuNum) > 10) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 학번을 입력해주세요.");
				printf("\n<학번이 너무 깁니다.>\n입력 > ");
				continue;
			}

			// 입력된 값을 정수로 변환할 수 없음
			newSNum = (int)strtol(newStuNum, NULL, 10);
			if (newSNum == 0) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 이름을 입력해주세요.");
				printf("\n<올바른 학번을 입력해주세요.>\n입력 > ");
				continue;
			}

			tempStu.snum = newSNum;
			break;
		}
	}
	check = -1;

	// 학년 변경할건지 확인
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 수정]\n\n");
	printCurStu(&tempStu, 8);
	printf("[0] 뒤로 가기\n\n학생의 학년을 변경하시겠습니까? (1: 예 / 2: 아니오)\n\n");
	printf("입력 > ");
	while (1) {
		scanf("%d", &check);
		// 뒤로 가기 옵션
		if (check == 0) return;
		clearBuffer();

		// 다른 값
		if (check != 1 && check != 2) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("현재 학생 정보 수정]\n\n");
			printCurStu(&tempStu, 8);
			printf("[0] 뒤로 가기\n\n학생의 학년을 변경하시겠습니까? (1: 예 / 2: 아니오)\n");
			printf("올바른 값을 입력해주세요.\n입력> ");
			continue;
		}
		break;
	}
	if (check == 1) {
		// 학년
		system(CLEAR);
		printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
		printf("현재 학생 정보 수정]\n\n");
		printCurStu(&tempStu, 8);
		printf("[0] 뒤로 가기\n\n수정할 학생의 학년을 입력해주세요.\n\n입력 > ");
		int newStuGrade = -1;
		while (1) {
			scanf("%d", &newStuGrade);
			// 뒤로 가기 옵션
			if (newStuGrade == 0) return;
			clearBuffer();

			// 다른 값이 입력됐을 때
			if (newStuGrade < 1 || newStuGrade > 10) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 학년을 입력해주세요.\n");
				printf("올바른 값을 입력해주세요.\n입력 > ");
				continue;
			}

			tempStu.grade = newStuGrade;
			break;
		}
	}
	check = -1;

	// 전공 변경할건지 확인
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 수정]\n\n");
	printCurStu(&tempStu, 8);
	printf("[0] 뒤로 가기\n\n학생의 전공을 변경하시겠습니까? (1: 예 / 2: 아니오)\n\n");
	printf("입력 > ");
	while (1) {
		scanf("%d", &check);
		// 뒤로 가기 옵션
		if (check == 0) return;
		clearBuffer();

		// 다른 값
		if (check != 1 && check != 2) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("현재 학생 정보 수정]\n\n");
			printCurStu(&tempStu, 8);
			printf("[0] 뒤로 가기\n\n학생의 전공을 변경하시겠습니까? (1: 예 / 2: 아니오)\n");
			printf("올바른 값을 입력해주세요.\n입력> ");
			continue;
		}
		break;
	}
	if (check == 1) {
		// 전공
		system(CLEAR);
		printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
		printf("현재 학생 정보 수정]\n\n");
		printCurStu(&tempStu, 8);
		printf("[0] 뒤로 가기\n\n수정할 학생의 전공을 입력해주세요.\n\n입력 > ");
		char newStuMajor[TEXTMAX] = { '\0', };
		while (1) {
			scanf_s("%[^\n]s", newStuMajor, sizeof(newStuMajor));
			// 뒤로 가기 옵션
			if (strcmp(newStuMajor, "0") == 0) return;

			// 글자 수 초과
			if (clearBuffer() == 1 || strlen(newStuMajor) == 0) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 전공을 입력해주세요.");
				printf("\n<전공 글자 수가 너무 깁니다.>\n입력 > ");
				continue;
			}
			strcpy(tempStu.major, newStuMajor);
			break;
		}
	}
	check = -1;

	// 전화번호 변경할건지 확인
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 수정]\n\n");
	printCurStu(&tempStu, 8);
	printf("[0] 뒤로 가기\n\n학생의 전화번호를 변경하시겠습니까? (1: 예 / 2: 아니오)\n\n");
	printf("입력 > ");
	while (1) {
		scanf("%d", &check);
		// 뒤로 가기 옵션
		if (check == 0) return;
		clearBuffer();

		// 다른 값
		if (check != 1 && check != 2) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("현재 학생 정보 수정]\n\n");
			printCurStu(&tempStu, 8);
			printf("[0] 뒤로 가기\n\n학생의 전화번호룰 변경하시겠습니까? (1: 예 / 2: 아니오)\n");
			printf("올바른 값을 입력해주세요.\n입력> ");
			continue;
		}
		break;
	}
	if (check == 1) {
		// 전화번호
		system(CLEAR);
		printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
		printf("현재 학생 정보 수정]\n\n");
		printCurStu(&tempStu, 8);
		printf("[0] 뒤로 가기\n\n수정할 학생의 전화번호를 입력해주세요.\n\n입력 > ");
		char newStuPhoneNum[TEXTMAX] = { '\0', };
		while (1) {
			scanf_s("%[^\n]s", newStuPhoneNum, sizeof(newStuPhoneNum));
			// 뒤로 가기 옵션
			if (strcmp(newStuPhoneNum, "0") == 0) return;

			// 글자 수 초과
			if (clearBuffer() == 1 || strlen(newStuPhoneNum) == 0) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 전화번호를 입력해주세요.");
				printf("\n<전화번호가 너무 깁니다.>\n입력 > ");
				continue;
			}
			strcpy(tempStu.phoneNum, newStuPhoneNum);
			break;
		}
	}
	check = -1;

	// 조식여부 변경할건지 확인
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 수정]\n\n");
	printCurStu(&tempStu, 8);
	printf("[0] 뒤로 가기\n\n학생의 조식여부를 변경하시겠습니까? (1: 예 / 2: 아니오)\n\n");
	printf("입력 > ");
	while (1) {
		scanf("%d", &check);
		// 뒤로 가기 옵션
		if (check == 0) return;
		clearBuffer();

		// 다른 값
		if (check != 1 && check != 2) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("현재 학생 정보 수정]\n\n");
			printCurStu(&tempStu, 8);
			printf("[0] 뒤로 가기\n\n학생의 조식여부를 변경하시겠습니까? (1: 예 / 2: 아니오)\n");
			printf("올바른 값을 입력해주세요.\n입력> ");
			continue;
		}
		break;
	}
	if (check == 1) {
		// 조식여부
		system(CLEAR);
		printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
		printf("현재 학생 정보 수정]\n\n");
		printCurStu(&tempStu, 8);
		printf("[0] 뒤로 가기\n\n수정할 학생의 조식신청 여부 입력해주세요. (o/x)\n\n입력 > ");
		char newStuBreakfast[TEXTMAX] = { '\0', };
		while (1) {
			scanf_s("%[^\n]s", newStuBreakfast, sizeof(newStuBreakfast));
			// 뒤로 가기 옵션
			if (strcmp(newStuBreakfast, "0") == 0) return;

			// 글자 수 초과
			if (clearBuffer() == 1 || strlen(newStuBreakfast) == 0 ||
				(strcmp(newStuBreakfast, "O") != 0 && strcmp(newStuBreakfast, "o") != 0)
				&& strcmp(newStuBreakfast, "X") != 0 && strcmp(newStuBreakfast, "x") != 0) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 조식신청 여부 입력해주세요. (o/x)");
				printf("\n<올바른 값을 입력해주세요.>\n입력 > ");
				continue;
			}

			if (strcmp(newStuBreakfast, "O") == 0 || strcmp(newStuBreakfast, "o") == 0) {
				tempStu.breakfast = 1;
			}
			else {
				tempStu.breakfast = 0;
			}

			break;
		}
	}
	check = -1;

	// 퇴실날짜 변경할건지 확인
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 수정]\n\n");
	printCurStu(&tempStu, 8);
	printf("[0] 뒤로 가기\n\n학생의 퇴실날짜를 변경하시겠습니까? (1: 예 / 2: 아니오)\n\n");
	printf("입력 > ");
	while (1) {
		scanf("%d", &check);
		// 뒤로 가기 옵션
		if (check == 0) return;
		clearBuffer();

		// 다른 값
		if (check != 1 && check != 2) {
			system(CLEAR);
			printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
			printf("현재 학생 정보 수정]\n\n");
			printCurStu(&tempStu, 8);
			printf("[0] 뒤로 가기\n\n학생의 퇴실날짜를 변경하시겠습니까? (1: 예 / 2: 아니오)\n");
			printf("올바른 값을 입력해주세요.\n입력> ");
			continue;
		}
		break;
	}

	if (check == 1) {
		int newStuOutDate[3] = { -1, -1, -1 };
		// 연도
		system(CLEAR);
		printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
		printf("현재 학생 정보 수정]\n\n");
		printCurStu(&tempStu, 8);
		printf("[0] 뒤로 가기\n\n수정할 학생의 퇴실 날짜의 연도를 입력해주세요. (____-__-__)\n\n입력 > ");
		while (1) {
			scanf("%d", &newStuOutDate[0]);
			// 뒤로 가기 옵션
			if (newStuOutDate[0] == 0) return;
			clearBuffer();

			// 다른 값이 입력됐을 때
			if (newStuOutDate[0] < 2022 || newStuOutDate[0] > 3000) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 퇴실 날짜의 연도를 입력해주세요. (____-__-__)\n");
				printf("올바른 연도를 입력해주세요.\n입력 > ");
				continue;
			}
			tempStu.outDate[0] = newStuOutDate[0];
			break;
		}
		// 월
		system(CLEAR);
		printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
		printf("현재 학생 정보 수정]\n\n");
		printCurStu(&tempStu, 8);
		printf("[0] 뒤로 가기\n\n수정할 학생의 퇴실 날짜의 월을 입력해주세요. (%04d-__-__)\n\n입력 > ", tempStu.outDate[0]);
		while (1) {
			scanf("%d", &newStuOutDate[1]);
			// 뒤로 가기 옵션
			if (newStuOutDate[1] == 0) return;
			clearBuffer();

			// 다른 값이 입력됐을 때
			if (newStuOutDate[1] < 1 || newStuOutDate[1] > 12) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 퇴실 날짜의 월을 입력해주세요. (%04d-__-__)\n", tempStu.outDate[0]);
				printf("올바른 월을 입력해주세요.\n입력 > ");
				continue;
			}
			tempStu.outDate[1] = newStuOutDate[1];
			break;
		}
		// 일
		system(CLEAR);
		printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
		printf("현재 학생 정보 수정]\n\n");
		printCurStu(&tempStu, 8);
		printf("[0] 뒤로 가기\n\n수정할 학생의 퇴실 날짜의 일을 입력해주세요. (%04d-%02d-__)\n\n입력 > ",
			tempStu.outDate[0], tempStu.outDate[1]);
		while (1) {
			scanf("%d", &newStuOutDate[2]);
			// 뒤로 가기 옵션
			if (newStuOutDate[2] == 0) return;
			clearBuffer();

			// 다른 값이 입력됐을 때
			if (newStuOutDate[2] < 1 || newStuOutDate[2] > 31) {
				system(CLEAR);
				printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
				printf("현재 학생 정보 수정]\n\n");
				printCurStu(&tempStu, 8);
				printf("[0] 뒤로 가기\n\n수정할 학생의 퇴실 날짜의 일을 입력해주세요. (%04d-%02d-__)\n",
					tempStu.outDate[0], tempStu.outDate[1]);
				printf("올바른 일을 입력해주세요.\n입력 > ");
				continue;
			}
			tempStu.outDate[2] = newStuOutDate[2];
			break;
		}
	}

	// 확인 절차
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("현재 학생 정보 수정]\n\n");
	printCurStu(&tempStu, 8);
	printf("%s %d층 %d%02d호 학생%d을 이 정보로 수정하시겠습니까?\n",
		dong->name, floor, floor, ho, stu_i);
	printf("[y] 예   [다른값] 아니오\n\n입력 > ");
	char confirm;
	scanf("%c", &confirm);
	clearBuffer();

	if (confirm != 'y') {
		printf("\n수정을 취소했습니다.\n아무 키나 누르면 돌아갑니다.");
		getch();
		return;
	}

	// 수정된 구조체를 원래 구조체에 복사하기
	memcpy(stu, &tempStu, sizeof(STUDENT));
	saveAllInfo(); // 파일에 저장
	printf("정보 수정을 완료했습니다.\n아무 키나 누르면 돌아갑니다.");
	getch();
	return;
}