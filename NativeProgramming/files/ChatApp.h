#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Message.h"
#include "IChatModel.h"
#include "CommandHandler.h"

class ChatApp {
public:
    // [배우는 개념: unique_ptr 이전 (move)]
    // unique_ptr는 복사가 안 된다 — 소유권이 하나여야 하기 때문.
    // std::move로 소유권을 ChatApp 안으로 넘긴다.
    explicit ChatApp(std::unique_ptr<IChatModel> model);

    void run();

    void clearHistory();
    void printHistory() const;
    void saveHistory(const std::string& path) const;
    void loadHistory(const std::string& path);

private:
    std::string readUserInput();
    void handleTurn(const std::string& userInput);
    bool isExitCommand(const std::string& input) const;

    std::vector<Message> history_;

    // [배우는 개념: unique_ptr<IChatModel>]
    // DummyChatModel이든 OllamaChatModel이든 IChatModel로만 다룬다.
    // ChatApp은 안에 뭐가 들었는지 모른다 — 교체해도 이 파일은 안 바뀐다.
    std::unique_ptr<IChatModel> model_;

    CommandHandler commandHandler_;
};
