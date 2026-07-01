#pragma once
#include <string>
#include <vector>
#include "Message.h"
#include "DummyChatModel.h"

class ChatApp {
public:
    void run();

private:
    std::string readUserInput();
    void handleTurn(const std::string& userInput);
    bool isExitCommand(const std::string& input) const;

    // [배우는 개념: vector<Message>]
    // 크기를 미리 정하지 않아도 push_back()으로 자동으로 늘어나는 동적 배열.
    std::vector<Message> history_;

    // [배우는 개념: 멤버로 직접 소유]
    // 포인터 없이 값으로 들고 있으면 ChatApp이 소멸될 때 자동으로 정리된다.
    // 나중에 모델을 교체해야 할 때 unique_ptr로 바꾸면 된다.
    DummyChatModel model_;
};
