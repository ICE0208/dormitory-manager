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
	STUDENT* stu = &(dong->students[floor][ho][stu_i]);
	system(CLEAR);
	printf("[%s %d층 %d%02d호 학생%d - ", dong->name, floor, floor, ho, stu_i);
	printf("정보 출력 화면\n\n");

	// 출력할 학생 정보가 없을 때
	if (stu->snum == 0) {
		printf("<등록된 학생이 없습니다.>\n");
		return;
	}

	printf("학생 이름 : %s\n", stu->name);
	printf("학번: %d\n", stu->snum);
	printf("전화 번호: %s\n", stu->phoneNum);
	printf("조식 여부: ");
	printf("O\n") ? stu->breakfast == 1 : printf("X\n");
}

void stuInfoShowOption() {
	printf("\n[1] 새로운 학생으로 추가");
	printf("\n[2] 현재 학생 정보 수정");
	printf("\n[3] 현재 학생 정보 학생");
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
		// 특정 명령어 수행
		return;
	}
}