#include <iostream>
#include <fstream>
#include "ChatApp.h"

void ChatApp::run() {
    std::string input = readUserInput();

    while (!isExitCommand(input)) {
        // [핵심 분기점]
        // "/"로 시작하면 명령어 처리로, 아니면 기존 AI 대화 처리로 보낸다.
        // exit는 명령어 체계 밖(별도 isExitCommand)에 그대로 둔다 -
        // "/"가 없는 특수 케이스라 명령어 맵에 억지로 넣지 않는다.
        if (commandHandler_.isCommand(input)) {
            commandHandler_.execute(input, *this);
        } else {
            handleTurn(input);
        }
        input = readUserInput();
    }

    std::cout << "프로그램을 종료합니다.\n";
}

std::string ChatApp::readUserInput() {
    std::cout << "User > ";
    std::string line;
    std::getline(std::cin, line);
    return line;
}

bool ChatApp::isExitCommand(const std::string& input) const {
    return input == "exit";
}

void ChatApp::handleTurn(const std::string& userInput) {
    if (userInput.empty()) return;

    std::string aiResponse = model_.getResponse(userInput);
    std::cout << "AI > " << aiResponse << "\n\n";

    history_.push_back(Message{"user", userInput});
    history_.push_back(Message{"ai",   aiResponse});
}

void ChatApp::clearHistory() {
    history_.clear();
}

void ChatApp::printHistory() const {
    if (history_.empty()) {
        std::cout << "대화 기록이 없습니다.\n\n";
        return;
    }
    for (const auto& msg : history_) {
        std::cout << (msg.role == "user" ? "User > " : "AI > ") << msg.content << "\n";
    }
    std::cout << "\n";
}

void ChatApp::saveHistory(const std::string& path) const {
    std::ofstream file(path);
    if (!file) {
        // 파일을 못 여는 건 프로그래머의 precondition 위반이 아니라
        // 잘못된 경로/권한 같은 "정상적으로 발생 가능한 사용자 입력 오류"다.
        // throw하지 않고 안내만 출력한다.
        std::cout << "파일을 열 수 없습니다: " << path << "\n\n";
        return;
    }

    for (const auto& msg : history_) {
        file << msg.role << "\t" << msg.content << "\n";
    }
    std::cout << "저장했습니다: " << path << " (" << history_.size() << "개 메시지)\n\n";
}

void ChatApp::loadHistory(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cout << "파일을 열 수 없습니다: " << path << "\n\n";
        return;
    }

    std::vector<Message> loaded;
    std::string line;
    while (std::getline(file, line)) {
        size_t tabPos = line.find('\t');
        if (tabPos == std::string::npos) continue; // 형식이 깨진 줄은 건너뛴다
        loaded.push_back(Message{line.substr(0, tabPos), line.substr(tabPos + 1)});
    }

    history_ = loaded;
    std::cout << "불러왔습니다: " << path << " (" << loaded.size() << "개 메시지)\n\n";
}
