#include <stdio.h>
#include "fileManager.h"
#include "mainScreen.h"
#include "studentManager.h"

int main() {

	setDongList(); // 동 연결리스트를 만듭니다.
	loadAllInfo(); // 저장된 파일로부터 정보를 불러와서 연결리스트에 추가합니다.

	

	mainScreen(); // 초기 화면을 보여줍니다.

	system("pause");

	return 0;
}