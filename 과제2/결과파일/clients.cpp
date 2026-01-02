// 
// CSE3081-1/AIE3051-1 Design and Analysis of Algorithm
// (c) 2024 Soang University
//
// Example: Using min heap to manage clients with priority
// clients.cpp
//

#include "clients.h"

CLIENTS::CLIENTS() {
	n_max_clients = DEFAULT_MAX_CLIENTS;
	clients = new CLIENT_RECORD[n_max_clients];
	min_heap_initialize();
}

CLIENTS::CLIENTS(int n_max_clients) {
	this->n_max_clients = n_max_clients;
	clients = new CLIENT_RECORD[n_max_clients];
	min_heap_initialize();
}

CLIENTS::~CLIENTS() {
	if (!clients)
		delete[] clients;
}

//
// client management
//
void CLIENTS::reset() {
	for (int i = 0; i < n_max_clients; i++) {
		clients[i].priority = INT_MAX;
		clients[i].index_to_heap = -1;
		clients[i].client_data = nullptr;
	}
	min_heap_initialize();
}

void CLIENTS::reset(int n_max_clients) {
	if (!clients)
		delete[] clients;
	this->n_max_clients = n_max_clients;
	clients = new CLIENT_RECORD[n_max_clients];
	min_heap_initialize();
}

bool CLIENTS::active_client_ID(unsigned int client_ID) {
	if ((client_ID < n_max_clients) && (clients[client_ID].priority != INT_MAX))
		return true;
	else
		return false;
}

void CLIENTS::add_client(unsigned int client_ID, int priority, CLIENT_DATA* client_data) {
	if (active_client_ID(client_ID)) 
		return;
	clients[client_ID].priority = priority;
	clients[client_ID].index_to_heap = -1;
	clients[client_ID].client_data = client_data;
	min_heap_insert(client_ID);
}

unsigned int CLIENTS::delete_client(int* priority, CLIENT_DATA** client_data) {
	unsigned int client_ID = min_heap_delete();
	*priority = clients[client_ID].priority;
	*client_data = clients[client_ID].client_data;

	clients[client_ID].priority = INT_MAX; // no more in the system
	clients[client_ID].index_to_heap = -1;
	clients[client_ID].client_data = nullptr;
	return client_ID;
}

void CLIENTS::adjust_client_priority(unsigned int client_ID, int priority_increment) {
	if (active_client_ID(client_ID) && (priority_increment != 0)) {
		int index_to_heap = clients[client_ID].index_to_heap;
		min_heap_adjust_priority(index_to_heap, priority_increment);
	}
}

void CLIENTS::print_clients(const char* header) {
	fprintf(stdout, "\n/****************** %s ******************/\n", header);
	fprintf(stdout, "[CLIENTS]\n");
	fprintf(stdout, "  The number of current clients = %d\n",
		_heap.size() - 1);
	for (int i = 0; i < n_max_clients; i++)
		if (clients[i].priority != INT_MAX) {
			fprintf(stdout, "  [%5d] priority = %3d, index_to_heap = %3d\n",
				i, clients[i].priority, clients[i].index_to_heap);
		}
}

void CLIENTS::print_clients_into_file(const char* filename) {
	FILE* fp = fopen(filename, "w");
	if (!fp) {
		fprintf(stderr, "*** Error: cannot open the file %s...\n", filename);
		exit(-1);
	}
	fprintf(fp, "%d\n", (int) _heap.size() - 1);
	for (int i = 0; i < n_max_clients; i++)
		if (clients[i].priority != INT_MAX) {
			fprintf(fp, "%7d %7d %7d\n", i, clients[i].priority, clients[i].index_to_heap);
		}
	fclose(fp);
}

void CLIENTS::print_min_heap(const char* header) {
	fprintf(stdout, "\n/****************** %s ******************/\n", header);
	fprintf(stdout, "[MIN HEAP]\n");
	fprintf(stdout, "  The number of elements in min heap = %d\n",
		_heap.size() - 1);
	for (int i = 1; i < _heap.size(); i++) {
		fprintf(stdout, "  [%3d] priority = %3d, client_ID = %5d\n", i,
			clients[_heap[i].client_ID].priority,
			_heap[i].client_ID);
	}
	fprintf(stdout, "\n");
}

void CLIENTS::print_min_heap_into_file(const char* filename) {
	FILE* fp = fopen(filename, "w");
	if (!fp) {
		fprintf(stderr, "*** Error: cannot open the file %s...\n", filename);
		exit(-1);
	}
	fprintf(fp, "%d\n", (int) _heap.size() - 1);
	for (int i = 1; i < _heap.size(); i++) {
		fprintf(fp, "%7d %7d %7d\n", i, clients[_heap[i].client_ID].priority,
			_heap[i].client_ID);
	}
	fclose(fp);
}

// 
// min heap management
//
void CLIENTS::min_heap_initialize() {
	_heap.clear();
	_heap.emplace_back(-1);
}

void CLIENTS::min_heap_insert(unsigned int client_ID) {
	int cur_priority = clients[client_ID].priority;
	_heap.emplace_back(client_ID);
	int cur_index = _heap.size() - 1;

	while (1) {
		if ((cur_index == 1) || (cur_priority >= clients[_heap[cur_index / 2].client_ID].priority))
			/* terminate when the root is reached or the element
			is in its correct place */
			break;
		else {
			/* check the next lower level of the _heap */
			_heap[cur_index] = _heap[cur_index / 2];
			clients[_heap[cur_index / 2].client_ID].index_to_heap = cur_index;
			cur_index /= 2;
		}
	}
	_heap[cur_index] = client_ID;
	clients[client_ID].index_to_heap = cur_index;
}

unsigned int CLIENTS::min_heap_delete() {
	if (_heap.size() <= 1) return NULL_CLIENT_ID;

	int client_ID_first = _heap[1].client_ID;
	HEAP_ELEMENT _heap_element_last = _heap[_heap.size() - 1];
	int priority_last = clients[_heap_element_last.client_ID].priority;
	_heap.pop_back();

	int parent_index = 1;
	int child_index = 2;
	int last_index = _heap.size() - 1;
	while (child_index <= last_index) {
		if ((child_index < last_index)
			&& (clients[_heap[child_index].client_ID].priority >
				clients[_heap[child_index + 1].client_ID].priority))
			child_index++;

		if (priority_last <= clients[_heap[child_index].client_ID].priority)
			/*correct position has been found */
			break;
		else {
			/* move to the next lower level */
			_heap[parent_index] = _heap[child_index];
			clients[_heap[child_index].client_ID].index_to_heap = parent_index;
			parent_index = child_index;
			child_index *= 2;
		}
	}
	_heap[parent_index] = _heap_element_last;
	clients[_heap_element_last.client_ID].index_to_heap = parent_index;

	return client_ID_first;
}

void CLIENTS::min_heap_adjust_priority(int index_to_heap, int priority_increment) {
	// this function adjusts the priority of a min heap node pointed by "index_to_heap"  
	//   to the new priority which is the sum of its current priority and "priority_increment"
	// currently in its form, this function does not work
	if (priority_increment == 0) return;
	
	int client_ID = _heap[index_to_heap].client_ID;
	int priority_client = clients[client_ID].priority += priority_increment;

	if (priority_increment > 0) {
		int parent_index = index_to_heap;
		// 현재 노드의 인덱스
		int child_index = parent_index * 2;
		// 현재 노드의 왼쪽 자식의 인덱스
		int last_index = _heap.size() - 1;
		// min heap에서 마지막 요소의 인데스

		while (child_index <= last_index) {
			
			if (child_index < last_index &&
				clients[_heap[child_index].client_ID].priority > clients[_heap[child_index + 1].client_ID].priority) {
				child_index++;
			}
			// 오른쪽 자식이 존재하는 경우에는 오른쪽 자식과도 비교해 더 작은 우선순위를 가진 자식을 선택
			
			if (clients[client_ID].priority <= clients[_heap[child_index].client_ID].priority)
				break;
			// 현재 노드의 우선순위가 자식들보다 작거나 같으면 min heap의 특성이 만조되므로 더 이상 이동할 필요가 없다.
			_heap[parent_index] = _heap[child_index];
			clients[_heap[child_index].client_ID].index_to_heap = parent_index;
			parent_index = child_index;
			child_index *= 2;
			// 부모 노드와 자식 노드 위치 교환
		}

		_heap[parent_index] = client_ID;
		clients[client_ID].index_to_heap = parent_index;
		// 현재 클라이언트를 최종적으로 재배치된 위치에 놓는다.
		// 클라이언트가 min heap에서 차지하는 위치 정보를 업데이트
	}

	else if (priority_increment < 0) {
		int current_index = index_to_heap;
		// 우선 순위가 감소한 노드의 현재 인덱스를 의미
	
		while (current_index > 1) { // 루프 노드가 아닌 동안 계속 실행된다.
			int parent_index = current_index / 2;
			// 현재 노드의 부모 노드를 가리키는 인덱스를 계산한다.
			if (clients[_heap[parent_index].client_ID].priority <= clients[client_ID].priority)
				break;
			//부모 노드의 우선순위가 현재 노드보다 작거나 같으면, 
			// Min Heap의 특성이 유지되므로 더 이상 상향 재정렬이 필요 없고 루프를 종료합니다
			_heap[current_index] = _heap[parent_index];
			clients[_heap[parent_index].client_ID].index_to_heap = current_index;
			current_index = parent_index;
			// 부모와 자식 노드의 위치 교환
		}

		_heap[current_index] = client_ID;
		clients[client_ID].index_to_heap = current_index;
	}
	//현재 노드를 재배치된 최종 인덱스에 놓는다.
	// 클라이언트가 최종적으로 위치하게 된 인덱스를 업데이트한다.

}
