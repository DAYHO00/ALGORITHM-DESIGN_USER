#pragma once

#include <random>
#include <stdlib.h>

struct RECORD {
	int key;
	char others[12]; 
};

class RECORDS {
	int n_records; // maximum possible number of clients
	RECORD* records;

public:
	RECORDS() {
		n_records = 0;
		records = nullptr;
	}

	RECORDS(int n) {
		if (n > 0) {
			n_records = n;
			records = new RECORD[n];
		}
		else {
			n_records = 0;
			records = nullptr;
		}
	}

	~RECORDS() {
		delete[] records;
	}

	int get_size() {
		return n_records;
	}

	RECORD* get_record(int i) {
		return &records[i];
	}

	void initialize() {
		for (int i = 0; i < n_records; i++)
			records[i].key = i;
		std::random_device rd;
	//	std::mt19937 gen(rd());  
		std::mt19937 gen(20241031); // to generate the same sequences
		std::uniform_int_distribution<> random_index(0, n_records - 1);
		for (int i = 0; i < 100 * n_records; i++) {
			int p, q;
			p = random_index(gen);
			q = random_index(gen);

			int tmp = records[p].key;
			records[p].key = records[q].key;
			records[q].key = tmp;
		}
	}

	int compare_keys(const void* a, const void* b) {
		RECORD* rec_a = (RECORD*)a;
		RECORD* rec_b = (RECORD*)b;
		return rec_a->key - rec_b->key;
	}

	void SWAP(RECORD& a, RECORD& b) {
		RECORD temp = a;
		a = b;
		b = temp;
	}

	void print_keys() {
		printf("\n");
		for (int i = 0; i < n_records; i++)
			printf("[%d] %d\n", i, records[i].key);
	}

	void check_sorting_result_part(int start_index, int end_index) {
		for (int i = start_index; i < end_index; i++)
			if (records[i].key >= records[i+1].key) {
				printf("*** Something wrong with sorting!\n");
				return;
			}
		printf("*** Sorting complete!\n");
	}

	void check_sorting_result_whole() {
		for (int i = 0; i < n_records; i++)
			if (records[i].key != i) {
				printf("*** Something wrong with sorting!\n");
				return;
			}
		printf("*** Sorting complete!\n");
	}

	void sort_records_insertion(int start_index, int end_index);
	void adjust_max_heap(int root, int end_index);
	void sort_records_heap(int start_index, int end_index);
	void adjust_min_heap(int root, int end_index);
	void sort_records_weird(int start_index, int end_index);
	int partition(int left, int right);
	void sort_records_quick_classic(int start_index, int end_index);
	int introsort_partition(int left, int right);
	void introsort(int start_index, int end_index, int max_depth);
	void sort_records_intro(int start_index, int end_index);
	void merge(int start, int mid, int end);
	void sort_records_merge_with_insertion(int start_index, int end_index);
	void print_records() const;
};

