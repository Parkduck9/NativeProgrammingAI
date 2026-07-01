#pragma once
#include <string>

// [설계 노트: 왜 IChatModel 인터페이스를 안 쓰는가]
// 지금은 구현체가 DummyChatModel 하나뿐이다.
// 2단계에서 OllamaChatModel이 추가되는 시점에 인터페이스로 리팩터링한다.
class DummyChatModel {
public:
    // const & : input을 복사 없이 받되 수정하지 않겠다는 약속
    // 함수 뒤 const : 멤버 변수를 변경하지 않겠다는 약속
    std::string getResponse(const std::string& input) const;
};
