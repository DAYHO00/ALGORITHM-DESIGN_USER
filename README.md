# Algorithm Design & Analysis 

이 저장소는 Algorithm Design & Analysis과목에서 수행한 총 5개의 과제에 대한 구현 코드와 보고서를 정리한 것입니다.

---

## ✅ Table of Contents

* [Experimental Environment](#-experimental-environment)
* [HW1: Maximum Sum Subrectangle (Alg3/4/5)](#-hw1-maximum-sum-subrectangle-alg345)
* [HW2: MinHeap-based Priority Queue](#-hw2-minheap-based-priority-queue)
* [HW3: Sorting Algorithms & Optimization](#-hw3-sorting-algorithms--optimization)
* [HW4: Dynamic Programming (MT / LPS)](#-hw4-dynamic-programming-mt--lps)
* [HW5: Kruskal MST with Union-Find](#-hw5-kruskal-mst-with-union-find)
* [How to Run](#-how-to-run)
---

## 🖥️ Experimental Environment

* **OS**: Windows 11 Home (23H2)
* **CPU**: Intel Core i7-1260P
* **RAM**: 16 GB
* **Compiler**: Visual Studio 2022 (x64, Release)

---

## 🔹 HW1: Maximum Sum Subrectangle (Alg3/4/5)

### Description

2차원 행렬에서 **합이 최대가 되는 부분 직사각형**을 찾는 문제를  
여러 알고리즘 접근 방식으로 구현합니다.

### Key Points

* Algorithm 3: 브루트포스 기반 기본 알고리즘
* Algorithm 4: 분할 정복을 활용한 최적화
* Algorithm 5: 누적 합(prefix sum)을 이용한 추가 최적화
* 알고리즘별 성능 비교 포함

---

## 🔹 HW2: MinHeap-based Priority Queue

### Description

MinHeap 자료구조를 이용한 **우선순위 큐** 구현 과제입니다.

### Key Points

* 힙 삽입 및 삭제 연산
* 우선순위 조정 기능
* 클라이언트 스케줄링 시나리오 처리
* 시간 복잡도 분석 포함

---

## 🔹 HW3: Sorting Algorithms & Optimization

### Description

여러 정렬 알고리즘을 구현하고,  
입력 크기에 따른 성능을 분석 및 최적화합니다.

### Key Points

* 비교 기반 정렬 알고리즘 구현
* 성능 병목 구간 분석
* 대규모 입력에 대한 최적화 전략

---

## 🔹 HW4: Dynamic Programming (MT / LPS)

### Description

대표적인 두 가지 **동적 계획법(DP)** 문제를 다룹니다.

### Problems

* **Minimal Triangulation** of convex polygons
* **Longest Palindromic Subsequence**

### Key Points

* DP 테이블 구성 방식
* 최적 부분 구조에 대한 설명
* 시간 및 공간 복잡도 분석

---

## 🔹 HW5: Kruskal MST with Union-Find

### Description

Kruskal 알고리즘을 이용한 **최소 신장 트리(MST)** 구성 과제입니다.

### Key Points

* MinHeap을 이용한 간선 선택
* 경로 압축을 적용한 Union-Find
* 사이클 검출
* MST 총 비용 계산

---

## ▶️ How to Run

```bash
# 컴파일 예시
g++ main.cpp -o main

# 실행
./main < input.txt > output.txt


