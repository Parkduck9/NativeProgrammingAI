#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "ChatApp.h"

int main() {
    SetConsoleOutputCP(CP_UTF8); // 콘솔 출력을 UTF-8로 설정 (한글 깨짐 방지)
    SetConsoleCP(CP_UTF8);       // 콘솔 입력도 UTF-8로 설정

    ChatApp app;
    app.run();
    return 0;
}
