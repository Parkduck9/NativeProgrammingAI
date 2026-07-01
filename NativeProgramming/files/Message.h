#pragma once
#include <string>

// [배우는 개념: struct]
// 로직(함수) 없이 데이터만 담을 때는 class 대신 struct를 쓰는 것이 관례.
struct Message {
    std::string role;    // "user" 또는 "ai"
    std::string content; // 실제 대화 내용
};
