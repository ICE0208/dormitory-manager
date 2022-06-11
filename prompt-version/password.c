#include "password.h"

char password[PW_MAX+1] = { '\0', };

int confirmPassword(char* zeroMsg) {
	setTitle(L"비밀번호 확인 화면");
	int printMsg = 1;
	int err = 0;
	char ic;
	int index = 0;
	char temp[PW_MAX + 1] = { '\0', };
	char init[PW_MAX + 1] = { '\0', };
	while (1) {
		if (printMsg == 1) {
			system(CLEAR);
			textcolor(11);
			printf("[비밀번호 확인]\n\n");
			textcolor(15);
			printf("[0] %s\n\n", zeroMsg);

			if (err == 1) printf("<비밀번호가 일치하지 않습니다.>\n");
			else printf("\n");
			err = 0;

			printf("입력 (숫자, 알파벳만 가능, 최대 20자) > ");
		}
		printMsg = 0;

		ic = getch();
		if (ic == '0') { // 뒤로 가기 옵션
			return 0;
		}

		if (ic == -32 || ic == 0) { // 방향키, 옵션키 제외 (F1, F2, .. , F12)
			getch();
			continue;
		}
		if (ic == 92 || ic == 96 || ic == 61) continue; // 백슬래시, 물결, 플러스 제외

		if (('a' <= ic && 'z') || ('A' <= ic && 'Z') ||
			('0' <= ic && '9')) { // 정상적인 값 입력
			if (index >= 20) continue; // 20 글자 넘을 때 입력 안되게
			printf("*");
			temp[index] = ic;
			index++;
			continue;
		}

		if (ic == '\r') { // 엔터
			if (strlen(temp) < 4 || strcmp(password, temp) != 0) {
				printMsg = 1;
				err = 1;
				strcpy(temp, init);
				index = 0;
				continue;
			}
			break;
		}

		if (ic == 8) { // 백스페이스
			if (index <= 0) continue; // 지울게 없을 때
			printf("\b \b");
			index--;
			temp[index] = '\0';
			continue;
		}
	}
	return 1;
}

void savePassword() {
	mkdir("c:\\dormanager");
	FILE* fp = fopen("c:\\dormanager\\dorpw.bin", "wb");
	fwrite(password, PW_MAX+1, 1, fp); // 비밀번호 저장
	fclose(fp);
}

void loadPassword() {
	FILE* fp = fopen("c:\\dormanager\\dorpw.bin", "rb");
	if (fp == NULL) {
		printf("파일을 찾을 수 없음\n");
		return;
	}
	char temp[PW_MAX + 1] = { '\0', };
	int check = fread(temp, PW_MAX + 1, 1, fp);
	strcpy(password, temp);
	fclose(fp);
}

int setPassword(char* msg, char* zeroMsg) {
	setTitle(L"비밀번호 설정 화면");
	int printMsg = 1;
	int err = 0;
	char ic;
	int index = 0;
	char temp[PW_MAX+1] = { '\0', };
	char init[PW_MAX + 1] = { '\0', };
	while (1) {
		if (printMsg == 1) {
			system(CLEAR);
			textcolor(11);
			printf("%s\n\n", msg);
			textcolor(15);
			printf("[0] %s\n\n", zeroMsg);

			if (err == 1) printf("<비밀번호는 4글자 이상이어야 합니다.>\n");
			else printf("\n");
			err = 0;

			printf("입력 (숫자, 알파벳만 가능, 최대 20자) > ");
		}
		printMsg = 0;

		ic = getch();
		if (ic == '0') { // 뒤로 가기 옵션
			return 0;
		}

		if (ic == -32 || ic == 0) { // 방향키, 옵션키 제외 (F1, F2, .. , F12)
			getch();
			continue;
		}
		if (ic == 92 || ic == 96 || ic == 61) continue; // 백슬래시, 물결, 플러스 제외

		if (('a' <= ic && 'z') || ('A' <= ic && 'Z') ||
			('0' <= ic && '9')) { // 정상적인 값 입력
			if (index >= 20) continue; // 20 글자 넘을 때 입력 안되게
			printf("*");
			temp[index] = ic;
			index++;
			continue;
		}

		if (ic == '\r') { // 엔터
			if (strlen(temp) < 4) {
				printMsg = 1;
				err = 1;
				strcpy(temp, init);
				index = 0;
				continue;
			}
			break;
		}

		if (ic == 8) { // 백스페이스
			if (index <= 0) continue; // 지울게 없을 때
			printf("\b \b");
			index--;
			temp[index] = '\0';
			continue;
		}
	}

	// 비밀번호 확인
	printMsg = 1;
	err = 0;
	index = 0;
	char temp2[PW_MAX + 1] = { '\0', };
	while (1) {
		if (printMsg == 1) {
			system(CLEAR);
			textcolor(11);
			printf("%s\n\n", msg);
			textcolor(15);
			printf("[0] %s\n\n", zeroMsg);

			if (err == 1) printf("<비밀번호가 일치하지 않습니다.>\n");
			else printf("\n");
			err = 0;

			printf("비밀번호 확인 > ");
		}
		printMsg = 0;

		ic = getch();
		if (ic == '0') { // 뒤로 가기 옵션
			return 0;
		}

		if (ic == -32 || ic == 0) { // 방향키, 옵션키 제외 (F1, F2, .. , F12)
			getch();
			continue;
		}
		if (ic == 92 || ic == 96 || ic == 61) continue; // 백슬래시, 물결, 플러스 제외

		if (('a' <= ic && 'z') || ('A' <= ic && 'Z') ||
			('0' <= ic && '9')) { // 정상적인 값 입력
			if (index >= 20) continue; // 20 글자 넘을 때 입력 안되게
			printf("*");
			temp2[index] = ic;
			index++;
			continue;
		}

		if (ic == '\r') { // 엔터
			if (strlen(temp2) < 4 || strcmp(temp, temp2) != 0) {
				printMsg = 1;
				err = 1;
				strcpy(temp2, init);
				index = 0;
				continue;
			}

			break;
		}

		if (ic == 8) { // 백스페이스
			if (index <= 0) continue; // 지울게 없을 때
			printf("\b \b");
			index--;
			temp2[index] = '\0';
			continue;
		}
	}

	strcpy(password, temp);
	savePassword();
	printf("\n\n[비밀번호 설정이 완료되었습니다.]\n<아무키나 누르면 돌아갑니다.>");
	getch();

	return 1;
}