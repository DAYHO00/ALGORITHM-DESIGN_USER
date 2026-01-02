#include <stdio.h>
#include "records.h"
#include "measure_cpu_time.h"

//typedef int _Cmpfun(const void*, const void*);
//void qsort(void* base, size_t n, size_t size, _Cmpfun* cmp);

void test_sorting_methods(int input_size) {
	RECORDS input_data(input_size);
	printf("\n\n[[[[[[[[[[ Input Size = %d ]]]]]]]]]]\n", input_size);

	input_data.initialize();
	CHECK_TIME_START(_start, _freq);
	input_data.sort_records_insertion(0, input_data.get_size() - 1);
	CHECK_TIME_END(_start, _end, _freq, _compute_time);
	printf("\n*** Time for sorting with insertion sort = %.3fms\n", _compute_time);
	input_data.check_sorting_result_whole();

	input_data.initialize();
	CHECK_TIME_START(_start, _freq);
	input_data.sort_records_heap(0, input_data.get_size() - 1);
	CHECK_TIME_END(_start, _end, _freq, _compute_time);
	printf("\n*** Time for sorting with heap sort = %.3fms\n", _compute_time);
	input_data.check_sorting_result_whole();

	input_data.initialize();
	CHECK_TIME_START(_start, _freq);
	input_data.sort_records_weird(0, input_data.get_size() - 1);
	CHECK_TIME_END(_start, _end, _freq, _compute_time);
	printf("\n*** Time for sorting with weird sort = %.3fms\n", _compute_time);
	input_data.check_sorting_result_whole();

	input_data.initialize();
	CHECK_TIME_START(_start, _freq);
	input_data.sort_records_quick_classic(0, input_data.get_size() - 1);
	CHECK_TIME_END(_start, _end, _freq, _compute_time);
	printf("\n*** Time for sorting with classic quick sort = %.3fms\n", _compute_time);
	input_data.check_sorting_result_whole();

	input_data.initialize();
	CHECK_TIME_START(_start, _freq);
	input_data.sort_records_intro(0, input_data.get_size() - 1);
	CHECK_TIME_END(_start, _end, _freq, _compute_time);
	printf("\n*** Time for sorting with intro sort = %.3fms\n", _compute_time);
	input_data.check_sorting_result_whole();

	input_data.initialize();
	CHECK_TIME_START(_start, _freq);
	input_data.sort_records_merge_with_insertion(0, input_data.get_size() - 1);
	CHECK_TIME_END(_start, _end, _freq, _compute_time);
	printf("\n*** Time for sorting with merge+insertion sort = %.3fms\n", _compute_time);
	input_data.check_sorting_result_whole();
}
 
int main() {
	for (int i = 14; i <= 20; i++) // use a proper range
		test_sorting_methods(1 << i);
	return 0;
}