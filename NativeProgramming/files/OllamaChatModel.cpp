#include "OllamaChatModel.h"
#include "httplib.h"
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

// 라이브러리 헤더는 크기가 너무 커서 컨텍스트에서 제외한다.
static const std::vector<std::string> EXCLUDED_FILES = {
    "httplib.h", "json.hpp"
};

OllamaChatModel::OllamaChatModel(const std::string& modelName, const std::string& sourceDir)
    : modelName_(modelName), sourceDir_(sourceDir) {}

std::string OllamaChatModel::buildSystemPrompt() const {
    std::ostringstream prompt;
    prompt << "너는 시니어 C++ 멘토이자 게임 개발자 성장 파트너야.\n"
           << "학습자가 작업 중인 프로젝트 코드를 보고 질문에 답해줘.\n"
           << "코드를 직접 수정하거나 개선점을 제안할 때는 왜 그렇게 하는지 반드시 설명해줘.\n\n"
           << "=== 현재 프로젝트 코드 ===\n";

    // [배우는 개념: std::filesystem]
    // C++17부터 표준으로 제공되는 파일 시스템 라이브러리.
    // 디렉터리 안의 파일 목록을 순회할 때 사용한다.
    for (const auto& entry : fs::directory_iterator(sourceDir_)) {
        if (!entry.is_regular_file()) continue;

        std::string filename = entry.path().filename().string();
        std::string ext = entry.path().extension().string();

        // .h, .cpp 파일만 포함
        if (ext != ".h" && ext != ".cpp") continue;

        // 라이브러리 헤더 제외
        bool excluded = false;
        for (const auto& ex : EXCLUDED_FILES) {
            if (filename == ex) { excluded = true; break; }
        }
        if (excluded) continue;

        std::ifstream file(entry.path());
        if (!file) continue;

        std::ostringstream content;
        content << file.rdbuf();

        prompt << "--- " << filename << " ---\n"
               << content.str() << "\n\n";
    }

    return prompt.str();
}

std::string OllamaChatModel::getResponse(const std::string& input,
                                          const std::vector<Message>& history) const {
    httplib::Client cli("localhost", 11434);

    // 매 요청마다 최신 코드를 읽어 시스템 프롬프트를 만든다.
    std::string systemPrompt = buildSystemPrompt();

    // [배우는 개념: JSON messages 배열]
    // /api/chat은 대화 흐름 전체를 messages 배열로 받는다.
    // system → 이전 대화 순서대로 → 현재 입력 순으로 쌓는다.
    nlohmann::json messages = nlohmann::json::array();

    messages.push_back({{"role", "system"}, {"content", systemPrompt}});

    // 이전 대화 기록을 순서대로 추가
    for (const auto& msg : history) {
        std::string role = (msg.role == "user") ? "user" : "assistant";
        messages.push_back({{"role", role}, {"content", msg.content}});
    }

    // 현재 입력 추가
    messages.push_back({{"role", "user"}, {"content", input}});

    nlohmann::json body = {
        {"model",    modelName_},
        {"messages", messages},
        {"stream",   false}
    };

    auto res = cli.Post("/api/chat", body.dump(), "application/json");

    if (!res) {
        return "[오류] Ollama에 연결할 수 없습니다. Ollama가 실행 중인지 확인하세요.";
    }
    if (res->status != 200) {
        return "[오류] Ollama 응답 오류 (status: " + std::to_string(res->status) + ")";
    }

    auto json = nlohmann::json::parse(res->body);
    return json["message"].value("content", "[오류] 응답을 파싱할 수 없습니다.");
}
