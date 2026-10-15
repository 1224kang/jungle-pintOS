## 1. Git Workflow

**Forking Workflow + Feature Branch 전략**을 사용합니다.

- 원본 Pintos 저장소를 Fork하여 팀 공통 저장소를 생성합니다.
- 각 팀원은 팀 공통 저장소를 개인 계정으로 Fork한 후 로컬에 Clone합니다.
- 모든 기능 개발 및 버그 수정은 별도의 브랜치에서 진행합니다.
- 작업 완료 후 개인 Fork에 Push하고, 팀 공통 저장소의 `main` 브랜치로 Pull Request를 생성합니다.
- 코드 리뷰 및 테스트를 통과한 PR만 `main`에 Merge합니다.

### Repository 구조

```

팀 공통 Fork 저장소
        │
        └── main
        └── develop
             ▲
             │ Pull Request
     ┌───────┼───────┐
     │       │       │
  팀원 A   팀원 B   팀원 C
   Fork     Fork     Fork
     ▲       ▲       ▲
     │ Push  │ Push  │ Push
   로컬 A   로컬 B   로컬 C
```

**기본 원칙:** 개인 Fork에서 개발하고,  공통 저장소에서 코드를 통합합니다.

---

## 2. Branch Convention

Issue 번호를 브랜치 이름에 포함합니다.

**형식**

```
<type>/<issue-number>-<description>
```

**예시**

```
feature/12-priority-scheduling
feature/15-alarm-clock
fix/21-priority-donation
```

---

## 3. Commit Convention

커밋 메시지에 Issue 번호를 포함하여 관련 작업을 추적합니다.

**형식**

```
<type>: <description> (#이슈번호)
```

**예시**

```
git commit -m "feat: 우선순위 스케줄링 구현 (#12)"
```

| Type | 설명 | 커밋 메시지 예시 |
| --- | --- | --- |
| `feat` | 새로운 기능 구현 | `feat: implement priority scheduling (#12)` |
| `fix` | 버그 및 오류 수정 | `fix: resolve priority donation bug (#13)` |
| `refactor` | 기능 변경 없이 코드 구조 개선 | `refactor: simplify thread scheduling logic (#14)` |
| `docs` | README, 설계 문서, 주석 수정 | `docs: update Pintos design document (#15)` |
| `chore` | 빌드 설정, 개발 환경 등 기타 작업 | `chore: update Makefile configuration (#18)` |
- 하나의 커밋에는 하나의 논리적인 변경 사항만 포함합니다.
- 관련 Issue 번호를 명시합니다.
- Issue 종료는 커밋이 아닌 PR Merge를 통해 처리합니다.

---

## 4. Pull Request Convention

**PR 제목**

```
feat: implement priority scheduling (#12)
```

**PR 본문 템플릿**

```
## 📌 관련 Issue

- 구현: #36 
- 관련 테스트 : 
  - #9 
  - #10 
  - #11 
  - #12
  - #13 
  - #14

## 🛠 작업 내용

- **`struct thread` 수정**: 스레드가 깨어나야 할 시점을 저장하는 `wake_tick` 필드 추가
- **`thread_sleep()` 구현**: 현재 스레드를 `sleep_list`에 추가하고 `BLOCKED` 상태로 전환
- **`thread_awake()` 구현**: 현재 틱이 `wake_tick` 이상인 스레드를 깨워 `READY` 상태로 전환
- **`timer_sleep()` 수정**: 기존 Busy Waiting 방식을 제거하고 `thread_sleep()`을 호출하도록 변경
- **`timer_interrupt()` 수정**: 매 타이머 인터럽트마다 `thread_awake()`를 호출하여 대기 시간이 지난 스레드를 깨우도록 구현

## 🧪 테스트 결과

- 관련 Pintos 테스트 통과 (통과한 것만 체크하기)
  - [ ]  #9 
  - [ ] #10 
  - [ ] #11 
  - [ ] #12
  - [ ] #13 
  - [ ] #14
      
- [ ] 기존 기능 정상 동작 확인

## 🔍 리뷰 요청 사항

- 

## 📝 기타 참고 사항

- 

```

**Issue 자동 종료 키워드**

| 키워드 | 역할 |
| --- | --- |
| `Closes #12` | PR Merge 시 Issue #12 종료 |
| `Fixes #12` | 버그 수정 Issue 자동 종료 |
| `Resolves #12` | 관련 Issue 자동 종료 |
| `Refs #12` | Issue 참조만 수행 |

※ 자동 종료는 PR이 해당 Issue가 속한 저장소의 기본 브랜치에 병합되는 경우를 기준으로 동작합니다. 다른 저장소의 Issue를 참조하는 경우에는 자동 종료가 지원되지 않을 수 있으므로, 팀 공통 저장소에서 Issue와 PR을 관리하는 것을 권장합니다.

---

## 5. GitHub Project Convention

GitHub Project의 칸반 보드를 사용하여 작업 상태를 관리합니다.

| Status | 의미 |
| --- | --- |
| `Todo` | 작업 예정 |
| `In Progress` | 개발 진행 중 |
| `In Review` | PR 생성 및 코드 리뷰 진행 중 |
| `Done` | PR Merge 및 작업 완료 |

**작업 흐름**

```
Issue 생성
    ↓
GitHub Project 등록 (Todo)
    ↓
담당자 지정 및 브랜치 생성
    ↓
개발 시작 (In Progress)
    ↓
Commit & Push
    ↓
Pull Request 생성 (In Review)
    ↓
코드 리뷰 및 테스트
    ↓
PR Merge → Issue Close
    ↓
GitHub Project (Done)
```

Brand new pintos for Operating Systems and Lab (CS330), KAIST, by Youngjin Kwon.

The manual is available at https://casys-kaist.github.io/pintos-kaist/.
