#pragma once
#include <string>
#include "IChatModel.h"

class OllamaChatModel : public IChatModel {
public:
    // modelName : 사용할 Ollama 모델 이름 (예: "qwen2.5-coder:14b")
    // sourceDir : 매 요청마다 읽을 소스 파일 디렉터리 경로
    OllamaChatModel(const std::string& modelName, const std::string& sourceDir);

    std::string getResponse(const std::string& input,
                            const std::vector<Message>& history) const override;

private:
    // 소스 디렉터리의 .h/.cpp 파일을 읽어 시스템 프롬프트 문자열로 만든다.
    std::string buildSystemPrompt() const;

    std::string modelName_;
    std::string sourceDir_;
};
