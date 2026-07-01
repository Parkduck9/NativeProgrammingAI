# Stage 1: 콘솔 채팅 껍데기 (DummyChatModel)

## 빌드 & 실행
```
g++ -std=c++17 -Wall -Wextra main.cpp ChatApp.cpp DummyChatModel.cpp -o chatapp
./chatapp
```

## 설계 결정: 인터페이스(IChatModel)를 쓰지 않는 이유
구현체가 DummyChatModel 하나뿐인 시점에 인터페이스를 만드는 것은
조기 추상화다. 2단계(Ollama 연동)에서 두 번째 구현체가 실제로
필요해지는 시점에 리팩토링으로 도입한다.

## 파일 구조
- Message.h          : 대화 한 줄을 표현하는 struct
- DummyChatModel.h/.cpp : 고정 응답을 반환하는 클래스 (단일 책임: 응답 생성)
- ChatApp.h/.cpp     : 입력→응답→저장 루프를 관리하는 클래스
- main.cpp           : ChatApp을 생성하고 실행만 담당

## 실행 예시
```
User > 안녕
AI > 아직 실제 LLM은 연결되지 않았습니다. 테스트 응답입니다.

User > exit
프로그램을 종료합니다.
```

## 이번 단계에서 배우는 C++ 개념
1. struct vs class — 데이터만 담을 때는 struct (Message.h)
2. 헤더(.h)/구현부(.cpp) 분리 — 선언과 구현을 나누는 이유
3. private 멤버 함수로 단일 책임 쪼개기 (ChatApp의 readUserInput/handleTurn/isExitCommand)
4. const 두 번 사용 (매개변수 const&, 함수 뒤 const) — 각각 다른 의미
5. vector<Message>와 push_back으로 동적 목록 관리
6. while 조건식으로 루프 종료 처리 (break 대신)
7. main()의 책임을 최소화하는 설계

## 직접 수정해보면 좋은 부분
- DummyChatModel::getResponse가 input 내용에 따라 다른 문자열을
  반환하도록(if문으로 "안녕"이면 다른 응답 등) 바꿔보기 — 지금은
  input을 아예 안 쓰고 있다는 것을 확인하고, 실제로 써보는 연습
- history_에 쌓인 대화를 "/history" 같은 명령어로 다시 출력하는
  기능을 ChatApp에 추가해보기 (private 함수를 하나 더 추가하는 연습)
- Message 구조체에 timestamp 같은 필드를 추가하고, 이를 위해
  어떤 표준 라이브러리가 필요한지 조사해보기

## 다음 단계에서 구현할 기능
- 대화 기록 저장/불러오기 (파일 입출력) — 아직 없음
- DummyChatModel과 나란히 둘 두 번째 구현체가 필요해지는 시점에
  맞춰 공통 인터페이스(IChatModel)로 리팩토링
- 그 다음에 실제 Ollama HTTP 연동
