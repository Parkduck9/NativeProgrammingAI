#include "DummyChatModel.h"

std::string DummyChatModel::getResponse(const std::string& input,
                                        const std::vector<Message>& history) const {
    (void)input;
    (void)history;
    return "아직 실제 LLM은 연결되지 않았습니다. 테스트 응답입니다.";
}
