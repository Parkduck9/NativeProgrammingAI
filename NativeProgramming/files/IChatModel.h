#pragma once
#include <string>
#include <vector>
#include "Message.h"

class IChatModel {
public:
    // history: 지금까지의 대화 기록 — AI가 맥락을 이어받을 수 있도록 전달한다.
    // DummyChatModel은 무시하고, OllamaChatModel은 messages 배열로 변환해 사용한다.
    virtual std::string getResponse(const std::string& input,
                                    const std::vector<Message>& history) const = 0;

    // unique_ptr<IChatModel>로 관리할 때 자식 소멸자가 올바르게 호출되도록 필요.
    virtual ~IChatModel() = default;
};
