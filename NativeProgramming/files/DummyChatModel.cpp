#include "DummyChatModel.h"

std::string DummyChatModel::getResponse(const std::string& input) const {
    (void)input; // 아직 사용하지 않지만 Ollama 연동 시 쓸 자리
    return "아직 실제 LLM은 연결되지 않았습니다. 테스트 응답입니다.";
}
