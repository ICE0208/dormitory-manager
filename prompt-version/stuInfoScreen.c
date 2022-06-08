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
	printf("학번: %d\n", stu->snum);
	printf("전화 번호: %s\n", stu->phoneNum);
	printf("조식 여부: ");
	printf("%s", stu->breakfast == 1 ? "O\n" : "X\n");
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
			return;
		}
		if (option == 2) { // 현재 학생 정보 수정
			// 구현 예정
			return;
		}
		if (option == 3) { // 현재 학생 정보 삭제
			removeCurStu(dong, floor, ho, stu_i);
			return;
		}
		return;
	}
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

	// 학번
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printf("-- 현재 입력된 학생의 정보 --\n");
	printf("이름: %s\n", newStu.name);
	printf("----------------------------\n\n");
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
			printf("-- 현재 입력된 학생의 정보 --\n");
			printf("이름: %s\n", newStu.name);
			printf("----------------------------\n\n");
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
			printf("-- 현재 입력된 학생의 정보 --\n");
			printf("이름: %s\n", newStu.name);
			printf("----------------------------\n\n");
			printf("[0] 뒤로 가기\n\n새로운 학생의 이름을 입력해주세요.");
			printf("\n<올바른 학번을 입력해주세요.>\n입력 > ");
			continue;
		}
		
		newStu.snum = newSNum;
		break;
	}

	// 전화번호
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printf("-- 현재 입력된 학생의 정보 --\n");
	printf("이름: %s\n", newStu.name);
	printf("학번: %d\n", newStu.snum);
	printf("----------------------------\n\n");
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
			printf("-- 현재 입력된 학생의 정보 --\n");
			printf("이름: %s\n", newStu.name);
			printf("학번: %d\n", newStu.snum);
			printf("----------------------------\n\n");
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
	printf("-- 현재 입력된 학생의 정보 --\n");
	printf("이름: %s\n", newStu.name);
	printf("학번: %d\n", newStu.snum);
	printf("전화번호: %s\n", newStu.phoneNum);
	printf("----------------------------\n\n");
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
			printf("-- 현재 입력된 학생의 정보 --\n");
			printf("이름: %s\n", newStu.name);
			printf("학번: %d\n", newStu.snum);
			printf("전화번호: %s\n", newStu.phoneNum);
			printf("----------------------------\n\n");
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

	// 확인 절차
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printf("-- 현재 입력된 학생의 정보 --\n");
	printf("이름: %s\n", newStu.name);
	printf("학번: %d\n", newStu.snum);
	printf("전화번호: %s\n", newStu.phoneNum);
	printf("조식 여부: ");
	printf("%s", newStu.breakfast == 1 ? "O\n" : "X\n");
	printf("----------------------------\n\n");
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
	stu->snum = newStu.snum;
	strcpy(stu->phoneNum, newStu.phoneNum);
	stu->breakfast = newStu.breakfast;
	saveAllInfo(); // 파일에 저장
	printf("정보를 새로운 값으로 수정 완료했습니다.\n 아무 키나 누르면 돌아갑니다.");
	getch();
	return;
}

void removeCurStu(DONG* dong, int floor, int ho, int stu_i) {
	// 확인 절차
	system(CLEAR);
	STUDENT* stu = &(dong->students[floor - 1][ho - 1][stu_i - 1]);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("새로운 학생으로 추가]\n\n");
	printf("-- 현재 학생의 정보 --\n");
	printf("이름: %s\n", stu->name);
	printf("학번: %d\n", stu->snum);
	printf("전화번호: %s\n", stu->phoneNum);
	printf("조식 여부: ");
	printf("%s", stu->breakfast == 1 ? "O\n" : "X\n");
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
	printf("현재 학생의 정보 삭제를 완료했습니다.\n 아무 키나 누르면 돌아갑니다.");
	getch();
	return;
}