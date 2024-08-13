# MiniShell

---

#### 목차
1. [프로젝트 개요](#프로젝트-개요)
2. [기능](#기능)
3. [요구사항](#요구사항)
4. [설치](#설치)
5. [사용법](#사용법)
6. [지원 명령어](#지원-명령어)
7. [알려진 문제](#알려진-문제)
8. [기여 방법](#기여-방법)
9. [라이선스](#라이선스)

---

### 프로젝트 개요

**MiniShell**은 기본적인 쉘 동작을 모방한 간단하고 가벼운 UNIX 쉘 구현체입니다. 명령어 실행, 리다이렉션 처리, 파이핑 및 프로세스 관리를 지원하며, UNIX와 같은 시스템에서 쉘 환경과 프로세스 관리의 작동 원리를 이해하기 위한 학습 목적으로 만들어졌습니다.

### 기능

- 기본 쉘 명령어 실행
- 입출력 리다이렉션('>', '<')
- 명령어 간 파이핑 ('|')
- 'cd', 'echo', 'exit', 'env'와 같은 내장 명령어
- 환경 변수 관리
- 시그널 처리 (예: 'Ctrl+C', 'Ctrl+D')
- 명령어 히스토리 (옵션 기능)

### 요구사항

- **운영체제:** Linux 또는 macOS
- **컴파일러:** GCC 또는 Clang
- **라이브러리:** 표준 C 라이브러리, POSIX 준수

### 설치

1. **저장소 클론**
   '''bash
   git clone https://github.com/Ares-10/42-minishell.git
   cd minishell
   '''

3. **프로젝트 빌드**
   '''bash
   make
   '''
   이 명령은 소스 코드를 컴파일하고 'minishell'이라는 실행 파일을 생성합니다.

4. **추가 Make 명령어**
   - **make re:** 전체 프로젝트를 다시 빌드합니다.
   - **make clean:** 빌드 과정에서 생성된 오브젝트 파일(.o)들을 삭제합니다.
   - **make fclean:** 오브젝트 파일과 함께 'minishell' 실행 파일도 삭제합니다.

### 사용법

1. **쉘 시작**
   '''bash
   ./minishell
   '''
   새로운 쉘 세션이 열리며, 명령어를 입력할 수 있는 프롬프트가 나타납니다.

2. **명령어 실행**
   - 명령어 실행:
     '''bash
     minishell> ls -la
     '''
   - 리다이렉션 사용:
     '''bash
     minishell> echo "Hello, World!" > output.txt
     '''
   - 파이프 사용:
     '''bash
     minishell> cat file.txt | grep "search_term"
     '''

3. **내장 명령어**
   - 'cd [디렉토리]': 현재 디렉토리를 변경합니다.
   - 'echo [문자열]': 문자열을 터미널에 출력합니다.
   - 'exit': 쉘을 종료합니다.
   - 'env': 현재 환경 변수를 출력합니다.
   - 'export [VAR=value]': 환경 변수를 설정합니다.

### 지원 명령어

- 시스템의 '/bin' 또는 '/usr/bin' 디렉토리에 있는 명령어 (예: 'ls', 'grep', 'cat', 'pwd').
- bulit-in 명령어 ('cd', 'echo', 'exit', 'env', 'export').
