#include "CommandHandler.h"
#include "ChatApp.h"
#include <iostream>

CommandHandler::CommandHandler() {
    registerCommands();
}

bool CommandHandler::isCommand(const std::string& input) const {
    return !input.empty() && input[0] == '/';
}

std::string CommandHandler::extractCommandName(const std::string& input) {
    size_t spacePos = input.find(' ');
    return (spacePos == std::string::npos) ? input : input.substr(0, spacePos);
}

std::string CommandHandler::extractArgs(const std::string& input) {
    size_t spacePos = input.find(' ');
    if (spacePos == std::string::npos) return "";
    return input.substr(spacePos + 1);
}

void CommandHandler::execute(const std::string& input, ChatApp& app) {
    std::string name = extractCommandName(input);
    std::string args = extractArgs(input);

    auto it = handlers_.find(name);
    if (it == handlers_.end()) {
        std::cout << "알 수 없는 명령어: " << name << " (도움말: /help)\n\n";
        return;
    }

    it->second(app, args);
}

void CommandHandler::registerCommands() {
    // [배우는 개념: 람다를 std::function에 담기]
    // 각 명령어의 동작을 그 자리에서 람다로 정의해서 맵에 넣는다.
    // 명령어가 늘어나도 새 클래스가 필요 없고, 여기 한 줄만 추가하면 된다.

    handlers_["/help"] = [](ChatApp& app, const std::string& args) {
        (void)app;
        (void)args;
        std::cout << "사용 가능한 명령어:\n"
                  << "  /help          - 명령어 목록 출력\n"
                  << "  /clear         - 대화 기록 초기화\n"
                  << "  /history       - 지금까지의 대화 출력\n"
                  << "  /save <파일명> - 대화 기록을 파일로 저장 (예: /save chat1.txt)\n"
                  << "  /load <파일명> - 파일에서 대화 기록 불러오기\n\n";
    };

    handlers_["/clear"] = [](ChatApp& app, const std::string& args) {
        (void)args;
        app.clearHistory();
        std::cout << "대화 기록을 초기화했습니다.\n\n";
    };

    handlers_["/history"] = [](ChatApp& app, const std::string& args) {
        (void)args;
        app.printHistory();
    };

    handlers_["/save"] = [](ChatApp& app, const std::string& args) {
        if (args.empty()) {
            std::cout << "사용법: /save <파일명>\n\n";
            return;
        }
        app.saveHistory(args);
    };

    handlers_["/load"] = [](ChatApp& app, const std::string& args) {
        if (args.empty()) {
            std::cout << "사용법: /load <파일명>\n\n";
            return;
        }
        app.loadHistory(args);
    };
}
