#pragma once
#include <string>
#include <vector>
#include "Message.h"
#include "DummyChatModel.h"
#include "CommandHandler.h"

class ChatApp {
public:
    void run();

    // [설계 노트: 왜 이 4개만 public인가]
    // CommandHandler가 history_에 직접 접근하지 않고 이 메서드들을 통해서만
    // 작업하게 함으로써, history_의 소유권과 무결성은 여전히 ChatApp만 책임진다.
    void clearHistory();
    void printHistory() const;
    void saveHistory(const std::string& path) const;
    void loadHistory(const std::string& path);

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

    // "/"로 시작하는 입력을 판단하고 실행을 위임하는 역할.
    // ChatApp은 여전히 데이터(history_)를 소유하고, CommandHandler는 판단만 한다.
    CommandHandler commandHandler_;
};
