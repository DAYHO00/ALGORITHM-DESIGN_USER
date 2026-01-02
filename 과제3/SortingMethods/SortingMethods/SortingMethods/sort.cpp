#include "records.h"

void RECORDS::sort_records_insertion(int start_index, int end_index) {
	// Insertion sort
	for (int i = start_index + 1; i <= end_index; i++) {
		RECORD tmp = records[i];
		int j = i;
		while ((j > 0) && (compare_keys((const void*)&tmp, (const void*)(&records[j - 1])) < 0)) {
			records[j] = records[j - 1];
			j--;
		}
		records[j] = tmp;
	}
}

void RECORDS::sort_records_heap(int start_index, int end_index) {
	// Classic heap sort
}

void RECORDS::sort_records_weird(int start_index, int end_index) {
	// A weird sort with a make-heap operation followed by insertion sort
}

void RECORDS::sort_records_quick_classic(int start_index, int end_index) {
	// Classic quick sort without any optimization techniques applied
}

void RECORDS::sort_records_intro(int start_index, int end_index) {
	// Introsort described in https://en.wikipedia.org/wiki/Introsort
}

void RECORDS::sort_records_merge_with_insertion(int start_index, int end_index) {
	// Merge sort optimized by insertion sort only
}