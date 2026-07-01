#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <memory>
#include "ChatApp.h"
#include "OllamaChatModel.h"
// #include "DummyChatModel.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 두 번째 인자: 소스 파일이 있는 디렉터리.
    // 매 요청마다 이 경로의 .h/.cpp 파일을 읽어 AI에게 컨텍스트로 전달한다.
    auto model = std::make_unique<OllamaChatModel>(
        "qwen2.5-coder:14b",
        "C:/Users/User/Desktop/NativeProgramming/files"
    );
    // auto model = std::make_unique<DummyChatModel>();

    ChatApp app(std::move(model));
    app.run();
    return 0;
}
