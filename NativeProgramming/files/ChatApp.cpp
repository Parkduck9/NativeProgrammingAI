#include <iostream>
#include "ChatApp.h"

void ChatApp::run() {
    std::string input = readUserInput();

    while (!isExitCommand(input)) {
        handleTurn(input);
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

    // [배우는 개념: push_back]
    // Message{...}처럼 중괄호로 구조체를 즉석에서 만들어 바로 추가할 수 있다.
    history_.push_back(Message{"user", userInput});
    history_.push_back(Message{"ai",   aiResponse});
}
