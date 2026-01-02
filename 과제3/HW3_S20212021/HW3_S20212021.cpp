#include "HW3_S20212021.h"

void RECORDS::sort_records_insertion(int start_index, int end_index) {
	// 교과서적인insertionsort방법
	for (int i = start_index + 1; i <= end_index; i++) {
		// records[0]는 고정한다.
        RECORD tmp = records[i]; 
        
		int j = i;
		while ((j > start_index) && (compare_keys((const void*)&tmp, (const void*)(&records[j - 1])) < 0)) {
			
            records[j] = records[j - 1];
            //왼쪽이 오른쪽보다 크면 자리를 바꾼다.
			j--;

		}
		records[j] = tmp;
        //insertion 대상 자리 세팅
	}
}

void RECORDS::adjust_max_heap(int internal_node, int end_index) {
    // adjust the binary tree to establish the  max heap
    int child;
    
    RECORD temp = records[internal_node];
    
    child = 2 * internal_node + 1;
    //왼쪽 자식의 인덱스 설정

    while (child <= end_index) {
        
        if (child < end_index && compare_keys((const void*)(&records[child]), (const void*)(&records[child + 1])) < 0) {
            child++;
        }
        // 오른쪽 자식이 왼쪽 자식보다 크면 child를 오른쪽 자식으로 setting

        
        if (compare_keys((const void*)(&temp), (const void*)(&records[child])) >= 0) {
            break;
            // 부모노드가 자식노드보다 크거나 같으면 break!
        } 
        else {
            
            records[(child - 1) / 2] = records[child];
            // 자식을 부모노드로 이동시킨다.
            child = 2 * child + 1;
        }
    }
    // 최종 위치에 temp 값 저장
    records[(child - 1) / 2] = temp;
}


void RECORDS::sort_records_heap(int start_index, int end_index) {
    // 교과서적인 heapsort방법
    
    for (int i = (start_index + end_index) / 2; i >= start_index; i--) {
        adjust_max_heap(i, end_index);
    }
    // 자식노드가 있는 internal 노드를 검사하면서 max_heap을 구축한다.


    for (int i = end_index; i > start_index; i--) {
        
        SWAP(records[start_index], records[i]);
        // 루트노드와 제일 끝 노드를 바꾼다.
        adjust_max_heap(start_index, i - 1);
        // max_heap 과정을 반복한다.
    }
}

void RECORDS::adjust_min_heap(int internal_node, int end_index) {
    int child;
    RECORD temp = records[internal_node];

    child = 2 * internal_node + 1;

    while (child <= end_index) {
        if (child < end_index && compare_keys(&records[child], &records[child + 1]) > 0) {
            child++;
        }

        if (compare_keys(&temp, &records[child]) <= 0) {
            break;
        }
        else {
            records[internal_node] = records[child];
            internal_node = child;
            child = 2 * internal_node + 1;
        }
    }
    records[internal_node] = temp;
}

void RECORDS::sort_records_weird(int start_index, int end_index) {
	// A weird sort with a make-heap operation followed by insertion sort
    
    // min_heap을 만든다.
    for (int i = (start_index + end_index) / 2; i >= start_index; i--) {
        adjust_min_heap(i, end_index);
    }

    sort_records_insertion(start_index, end_index);
}

int RECORDS::partition(int left, int right) {
    int pivot = left;  
    for (int i = left; i < right; i++) {
        
        if (compare_keys(&records[i], &records[right]) < 0) {
            SWAP(records[i], records[pivot]);
            pivot++;
        }
    }
    
    SWAP(records[pivot], records[right]);
    return pivot;
}


void RECORDS::sort_records_quick_classic(int start_index, int end_index) {
	// Classic quick sort without any optimization techniques applied
    if (end_index-start_index>0) {
        
        int pivot = partition(start_index, end_index);

        sort_records_quick_classic(start_index, pivot - 1);
        sort_records_quick_classic(pivot + 1, end_index);
    }
}

int RECORDS::introsort_partition(int left, int right) {
    int mid = left + (right - left) / 2;

    if (compare_keys(&records[left], &records[mid]) > 0){
        SWAP(records[left], records[mid]);
    }

    if (compare_keys(&records[left], &records[right]) > 0) {
        SWAP(records[left], records[right]);
    }

    if (compare_keys(&records[mid], &records[right]) > 0) {
        SWAP(records[mid], records[right]);
    }

    SWAP(records[mid], records[right]);

    int pivot = left;
    for (int i = left; i < right; i++) {
        if (compare_keys(&records[i], &records[right]) < 0) {
            SWAP(records[i], records[pivot]);
            pivot++;
        }
    }

    SWAP(records[pivot], records[right]);
    return pivot;
}

void RECORDS::introsort(int start_index, int end_index, int max_depth) {
    int len = end_index - start_index + 1;
    if (len < 16) {
        sort_records_insertion(start_index, end_index);
        return;
    }
    else if (max_depth == 0) {
        sort_records_heap(start_index, end_index);
        return;
    }
    else {
        int pivot = introsort_partition(start_index, end_index);
        introsort(start_index, pivot - 1, max_depth - 1);
        introsort(pivot + 1, end_index, max_depth - 1);
    }
}

void RECORDS::sort_records_intro(int start_index, int end_index) {
	// Introsort described in https://en.wikipedia.org/wiki/Introsort
    int max_depth = 2 * static_cast<int>(log2(end_index - start_index + 1));
    introsort(start_index, end_index, max_depth);
}

void RECORDS::merge(int start, int mid, int end) {
    int L_size = mid - start + 1;
    int R_size = end - mid;

    RECORD* left = new RECORD[L_size];
    RECORD* right = new RECORD[R_size];

    for (int i = 0; i < L_size; i++) {
        left[i] = records[start + i];
    }

    for (int i = 0; i < R_size; i++) {
        right[i] = records[mid + 1 + i];
    }

    int i_left = 0, j_right = 0;
    int key = start;

    while (i_left < L_size && j_right < R_size) {
        if (compare_keys(&left[i_left], &right[j_right]) <= 0) {
            records[key] = left[i_left];
            i_left++;
        }
        else {
            records[key] = right[j_right];
            j_right++;
        }
        key++;
    }

    while (i_left < L_size) {
        records[key] = left[i_left];
        i_left++;
        key++;
    }
    while (j_right < R_size) {
        records[key] = right[j_right];
        j_right++;
        key++;
    }

    delete[] left;
    delete[] right;
}

void RECORDS::sort_records_merge_with_insertion(int start_index, int end_index) {
	// Merge sort optimized by insertion sort only
    if (end_index - start_index < 16) {
        sort_records_insertion(start_index, end_index);
        return;
    }

    if (start_index < end_index) {
        int middle = start_index + (end_index - start_index) / 2;

        sort_records_merge_with_insertion(start_index, middle);
        sort_records_merge_with_insertion(middle + 1, end_index);

        merge(start_index, middle, end_index);
    }
}