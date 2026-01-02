// 
// CSE3081-1/AIE3051-1 Design and Analysis of Algorithm
// (c) 2024 Soang University
//
// Example: Using min heap to manage clients with priority
// main.cpp
//

#include "clients.h"

CLIENTS my_clients(65536); // 최대 65536며의 클라이언트를 저장할 수 있다.

void example_1() {
	my_clients.add_client(10037, 59, nullptr);
	my_clients.add_client(10128, 14, nullptr);
	my_clients.add_client(10055, 13, nullptr);
	my_clients.add_client(10355, 77, nullptr);
	my_clients.add_client(10152, 19, nullptr);
	my_clients.add_client(10015, 66, nullptr);
	my_clients.add_client(10111, 54, nullptr);
	my_clients.add_client(10125, 37, nullptr);
	my_clients.add_client(10512, 25, nullptr);
	my_clients.add_client(10001, 2, nullptr);

	my_clients.print_clients("example_1");
	// 현재 등록된 클라이언트 목록 출력
	my_clients.print_min_heap("example_1");
	// Min heap 구조를 출력
	my_clients.print_min_heap_into_file("result_mh_ex_1.txt");
	// min heap을 파일에 저장
	my_clients.print_clients_into_file("result_cl_ex_1.txt");
	// 클라이언트 목록을 파일에 저장
}
// 10명의 클라이언트를 추가한다.
// 각 클라이언트는 고유의 ID, 우선순위, 클라언트와 관련된 추가적인 데이터를 가리키는 데이터 포인터를 갖는다.


void example_2() {
	int client_ID, priority;
	CLIENT_DATA* client_data;

	my_clients.add_client(10037, 59, nullptr);
	my_clients.add_client(10128, 14, nullptr);
	my_clients.add_client(10055, 13, nullptr);
	my_clients.add_client(10355, 77, nullptr);
	my_clients.add_client(10152, 19, nullptr);
	my_clients.add_client(10015, 66, nullptr);
	my_clients.add_client(10111, 54, nullptr);
	my_clients.add_client(10125, 37, nullptr);
	my_clients.add_client(10512, 25, nullptr);
	my_clients.add_client(10001, 2, nullptr);
	// 10명의 클라이언트 추가 
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	// 값이 가장 작은 클라이언트 삭제 -> 10001, 10128, 10055

	my_clients.print_clients("example_2");
	// 나머지 클라이언트 7명만 출력
	my_clients.print_min_heap("example_2");
	// 나머지  클라이언트 7명 제외하고 min heap 출력
	my_clients.print_min_heap_into_file("result_mh_ex_2.txt");
	// min heap의 현재 상태 파일에 저장
	my_clients.print_clients_into_file("result_cl_ex_2.txt");
	// 현재 클라이언트 목록을 저장
}

void example_3() {
	int client_ID, priority;
	CLIENT_DATA* client_data;

	my_clients.add_client(10037, 59, nullptr);
	my_clients.add_client(10128, 14, nullptr);
	my_clients.add_client(10055, 13, nullptr);
	my_clients.add_client(10355, 77, nullptr);
	my_clients.add_client(10152, 19, nullptr);
	my_clients.add_client(10015, 66, nullptr);
	my_clients.add_client(10111, 54, nullptr);
	my_clients.add_client(10125, 37, nullptr);
	my_clients.add_client(10512, 25, nullptr);
	my_clients.add_client(10001, 2, nullptr);
	// 10명의 클라이언트 추가

	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	client_ID = my_clients.delete_client(&priority, &client_data);
	// 가장 작은 값을 가진 3명을 삭제

	my_clients.add_client(20125, 18, nullptr);
	my_clients.add_client(20537, 49, nullptr);
	// 새로운 클라이언트 추가
	my_clients.adjust_client_priority(10125, +35);
	// 클라이언트 10125의 우선순위를 35만큼 증가
	my_clients.add_client(20299, 22, nullptr);
	// 새로운 클라이언트 추가
	my_clients.adjust_client_priority(20537, -40);
	// 20375의 우선순위를 40만큼 감소

	my_clients.print_clients("example_3");
	my_clients.print_min_heap("example_3");
	my_clients.print_min_heap_into_file("result_mh_ex_3.txt");
	my_clients.print_clients_into_file("result_cl_ex_3.txt");
}

int main() {
	example_1(); 

	my_clients.reset();
	example_2();

	my_clients.reset();
	example_3();

	return 0;
}