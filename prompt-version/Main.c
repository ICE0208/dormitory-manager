#include <stdio.h>
#include "mainScreen.h"
#include "studentManager.h"
#include "password.h"

int main() {

	loadPassword();
	if (password[0] == '\0') {
		setPassword("[초기 비밀번호 세팅]");
	}
	savePassword();
	printf("\npw: %s\n", password);

	system("pause");

	return;

	setDongList(); // 동 연결리스트를 만듭니다.
	loadAllInfo(); // 저장된 파일로부터 정보를 불러와서 연결리스트에 추가합니다.

	mainScreen(); // 초기 화면을 보여줍니다.

	system("pause");

	return 0;
}