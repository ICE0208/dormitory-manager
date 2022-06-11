#include "password.h"

char password[PW_MAX+1] = { '\0', };

void setPassword(char* msg) {
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
			printf("%s\n\n[0] 뒤로 가기\n\n", msg);

			if (err == 1) printf("<비밀번호는 4글자 이상이어야 합니다.>\n");
			else printf("\n");
			err = 0;

			printf("입력 (숫자, 알파벳만 가능, 최대 20자) > ");
		}
		printMsg = 0;

		ic = getch();
		if (ic == '0') { // 뒤로 가기 옵션
			return;
		}

		if (ic == -32 || ic == 0) { // 방향키, 옵션키 제외 (F1, F2, .. , F12)
			getch();
			continue;
		}
		if (ic == 92 || ic == 96 || ic == 61) continue; // 백슬래시, 물결, 플러스 제외

		if (('a' <= ic && 'z') || ('A' <= ic && 'Z') ||
			('0' <= ic && '9')) { // 정상적인 값 입력
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
	strcpy(password, temp);
	return;
}