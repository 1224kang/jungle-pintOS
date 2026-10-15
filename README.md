# 🖥️ Pintos Project 1 · Threads

KAIST Pintos의 Project 1(Threads)을 3인 팀으로 구현하는 프로젝트입니다.

## 🎯 프로젝트 목표

- Project 1의 필수 요구사항 구현 (Alarm Clock, Priority Scheduling, Priority Donation)
- 최종 `main` 브랜치에서 필수 테스트 통과
- 구현 과정과 트러블슈팅을 정리하여 주간 공유 발표 진행

## 👥 팀 구성

| 프로필 | 이름 | GitHub |
|:---:|:---:|:---:|
| <img src="https://github.com/1224kang.png" width="80" height="80"> | 강민서 | [@1224kang](https://github.com/1224kang)|
| <img src="https://github.com/sikhesung.png" width="80" height="80"> | 강혜성 | [@sikhesung](https://github.com/sikhesung) |
| <img src="https://github.com/nica7410.png" width="80" height="80"> | 권창현 | [@nica7410](https://github.com/nica7410) |

## 🛠️ 개발 환경

| 항목 | 환경 |
|---|---|
| OS | Ubuntu 22.04 LTS (x86_64) |
| Language | C |
| Development | Docker, VS Code Dev Containers |
| Version Control | Git, GitHub |

- Docker 사용 시 교육 과정에서 안내한 환경을 사용합니다.
- 개발 환경 구성 및 빌드·테스트 명령은 아래 자료를 참고합니다.

📖 [Pintos Docker 개발 환경 가이드](https://github.com/krafton-jungle/pintos_22.04_lab_docker)

## 🤝 협업 방식

### 사전 합의

- 작업 시작 전에 **커밋 컨벤션, 브랜치 전략, 레포 전략**을 정했습니다.
- 작업별 브랜치에서 개발하고, Pull Request(PR)로 코드를 공유한 뒤 `main`에 병합합니다.
- 세부 규칙은 팀 개발 규칙 문서를 따릅니다.

📋 **[팀 개발 규칙 확인하기](./pintos/README.md)**

### 문제 유형별 진행 방식

**시도1. Alarm Clock — 각자 풀고, 설명하고, 머지**

1. 테스트 하나씩 담당을 나누고 시간을 정해 각자 구현
2. 구현이 끝나면 서로의 코드를 설명
3. 설명과 확인을 마친 코드를 `main`에 병합

**시도2. Priority Donation~ — 함께 분석하고, 나눠서 구현**

1. 테스트 코드와 `.ck` 파일을 비교하며 기대 동작을 함께 파악
2. 락, 세마포어 등 관련 개념을 각자 학습
3. 전체 설계와 공통 자료구조를 함께 결정
4. 역할을 나눠 구현

## 📚 참고 자료

- [KAIST Pintos 공식 매뉴얼](https://casys-kaist.github.io/pintos-kaist/)
- [KAIST Pintos GitHub](https://github.com/casys-kaist/pintos-kaist)
- [Pintos Docker 개발 환경](https://github.com/krafton-jungle/pintos_22.04_lab_docker)
- [팀 개발 규칙](./pintos/README.md)

---

**Pintos Project 1 · Threads**
