#include <stdio.h>
#include "mainScreen.h"
#include "studentManager.h"
#include "password.h"

int main() {
	// 콘솔 세팅
	setFontSize(24, 24);
	system("mode con cols=100 lines=24");
	textcolor(15);

	// 비밀번호 관련
	loadPassword(); // 파일에 저장되어 있는 비밀번호를 불러옵니다.
	if (password[0] == '\0') { // 비밀번호가 비어있을 때 다시 설정
		if (setPassword("[비밀번호 초기 설정]", "프로그램 종료") == 0) return;
	}
	
	if (confirmPassword("프로그램 종료") == 0) {
		return 0;
	}

	setDongList(); // 동 연결리스트를 만듭니다.
	loadAllInfo(); // 저장된 파일로부터 정보를 불러와서 연결리스트에 추가합니다.

	mainScreen(); // 초기 화면을 보여줍니다.

	system("pause");

	return 0;
}