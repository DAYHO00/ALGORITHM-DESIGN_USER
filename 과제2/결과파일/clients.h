// 
// CSE3081-1/AIE3051-1 Design and Analysis of Algorithm
// (c) 2024 Soang University
//
// Example: Using min heap to manage clients with priority
// clients.h
//

#pragma once
#pragma warning(disable:4996)

#include <vector>

#define DEFAULT_MAX_CLIENTS 1024
#define NULL_CLIENT_ID UINT_MAX

struct CLIENT_DATA { // 클라이언트와 관련된 데이터를 저장
	int dummy; 
	// more data fields for a client 
};

struct CLIENT_RECORD { 
	int priority; //각 클라이언트의 우선순위
	int index_to_heap; // 힙에서의 index
	CLIENT_DATA* client_data; // 클라이언트 데이터를 가리키는 포인터 변수
	CLIENT_RECORD() { // 생성자 (초기화) -> 동적 메모리 할당
		priority = INT_MAX; // when priority has value INT_MAX, the client is not in the system
		index_to_heap = -1;
		client_data = nullptr; // 포인터 초기화
	}
	~CLIENT_RECORD() { // 소멸자 -> 동적 메모리 할당 해제 -> 포인터가 nullprt일때 소멸자에서 client_data 포인터를 해제한다.
		if (!client_data)
			delete client_data;
	}
};

struct HEAP_ELEMENT { // client_id만 저장
	unsigned int client_ID; 
	HEAP_ELEMENT() {
		client_ID = UINT_MAX; // 생성자에서 유효하지 않은 클라이언트 초기화
	}
	HEAP_ELEMENT(int client_ID) {
		this->client_ID = client_ID;  // 매개변수로 전달된 client_ID값을 현재 객체의 멤버 변수에 저장
	}
};

class CLIENTS {
	int n_max_clients; // maximum possible number of clients
	CLIENT_RECORD *clients; // 각 client의 정보를 저장
	std::vector<HEAP_ELEMENT> _heap; //min heap을 구현하는 데 사용. 4byte크기의  _heap 벡터

	void min_heap_initialize(); // min heap 초기화
	void min_heap_insert(unsigned int client_ID); // client id를 min heap에 삽입
	unsigned int min_heap_delete(); // root node에 있는 가장 작은 값을 삭제
	void min_heap_adjust_priority(int index_to_heap, int delta); 
	// min heap에서 특정 클라이언트의 우선순위를 조정

public:
	CLIENTS(); // 기본 생성자
	CLIENTS(int n_max_clients); // paramemter를 받는 생성자
	~CLIENTS(); // 동적으로 할당된 clients 배열을 해제

	void reset(); // client system 초기화
	void reset(int n_max_clients); // 최대 클라이언트 수를 새롭게 설정
	bool active_client_ID(unsigned int client_ID); //주어진 client가 현재 활성화된 client인지 여부 확인
	void add_client(unsigned int client_ID, int priority, CLIENT_DATA* client_data); 
	// 새로운 클라이언트를 시스템에 추가 
	unsigned int delete_client(int* priority, CLIENT_DATA** client_data);
	// 시스템에서 우선순위가 가장 높은 클라이언트 삭제
	void adjust_client_priority(unsigned int client_ID, int priority_increment);
	// Note: priority_increment may be either positive, zero, or negative!!!
	// 클라이언트의 우선순위를 증가, 감소, 유지 3개 중에 하나로 조정한 후, Min heap을 다시 정렬해 구조를 유지

	void print_clients(const char* header);
	// 현재 시스템에 등록된 모든 클라이언트 목록 출력
	void print_clients_into_file(const char* filename); // this file will be used to grade HW2
	void print_min_heap(const char* header);
	void print_min_heap_into_file(const char* filename); // this file will be used to grade HW2
};


