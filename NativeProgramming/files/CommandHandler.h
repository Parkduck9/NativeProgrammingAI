#pragma once
#include <string>
#include <unordered_map>
#include <functional>

class ChatApp; // 전방 선언: CommandHandler는 ChatApp의 존재만 알면 되고, 내부 구현은 몰라도 된다

// [설계 노트: 왜 명령어마다 클래스를 만들지 않는가]
// 지금은 명령어가 5개(help/clear/history/save/load)이고 각각 로직이 짧다.
// "문자열 -> 실행할 함수" 매핑 테이블 하나면 충분하다.
// 명령어별 클래스(Command 패턴)는 지금 규모에선 조기 추상화다.
// 새 명령어 추가 = registerCommands()에 한 줄 추가, 그게 유일한 경로다.
class CommandHandler {
public:
    CommandHandler();

    // "/"로 시작하면 명령어로 판단한다
    bool isCommand(const std::string& input) const;

    // 등록된 명령어면 실행하고, 없으면 "알 수 없는 명령어" 안내만 출력한다.
    // (throw하지 않는다: 잘못된 명령어 입력은 프로그램 버그가 아니라
    //  사용자가 흔히 하는 실수이므로, 안내하고 루프는 계속 돌아야 한다)
    void execute(const std::string& input, ChatApp& app);

private:
    // ChatApp&를 받는 이유: 명령어가 실제로 할 일(history_ 초기화, 파일 저장 등)은
    // 전부 ChatApp이 소유한 데이터에 대한 작업이기 때문이다.
    // CommandHandler는 "무슨 명령어인지 판단"만 책임지고, "무엇을 할지"는 ChatApp에 위임한다.
    using Handler = std::function<void(ChatApp&, const std::string& args)>;

    void registerCommands();
    static std::string extractCommandName(const std::string& input);
    static std::string extractArgs(const std::string& input);

    std::unordered_map<std::string, Handler> handlers_;
};
