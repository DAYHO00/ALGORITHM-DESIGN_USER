#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int u;
    int v;
    int w;
} Edge;

typedef struct {
    int V;
    int E;
    Edge* edges;
} Graph;

typedef struct {
    Edge* heap;
    int maxSize;
    int size;
} Min_heap;

typedef struct {
    int rank;
    int parent;
    int64_t weight;
    int size;
} Subset;

typedef struct {
    int size;
    int64_t weight;
} Result;

// 결과 파일을 출력할 때 number of vertices로 오름차순으로 정렬한 후, 
// 같은 것들은 total weight로 정렬하기 위한 함수이다.
int compare(const void* a, const void* b) {

    const Result* result1 = (const Result*)a;
    const Result* result2 = (const Result*)b;

    if (result1->size != result2->size) {

        return result1->size - result2->size;
    }

    return (result1->weight > result2->weight) - (result1->weight < result2->weight);
}


Graph* make_graph(int V, int E) {

    Graph* G = (Graph*)malloc(sizeof(Graph));

    G->V = V;
    G->E = E;

    G->edges = (Edge*)malloc(E * sizeof(Edge));

    return G;
}

int Find(Subset* set, int x) {

    if (x != set[x].parent) {
        set[x].parent = Find(set, set[x].parent);
    }

    return set[x].parent;
}

void Union(Subset* set, int a, int b, int64_t W) {

    int root_A = Find(set, a);
    int root_B = Find(set, b);

    if (set[root_A].rank > set[root_B].rank) {
        set[root_B].parent = root_A;
        set[root_A].weight += set[root_B].weight + W;
        set[root_A].size += set[root_B].size;
    }
    else if (set[root_A].rank < set[root_B].rank) {
        set[root_A].parent = root_B;
        set[root_B].weight += set[root_A].weight + W;
        set[root_B].size += set[root_A].size;
    }
    else {
        set[root_B].parent = root_A;
        set[root_A].rank++;
        set[root_A].weight += set[root_B].weight + W;
        set[root_A].size += set[root_B].size;
    }
}

void insert_edge(Min_heap* minheap, Edge edge) {

    minheap->size++;

    int temp = minheap->size - 1;

    while (temp > 0 && edge.w < minheap->heap[(temp - 1) / 2].w) {

        minheap->heap[temp] = minheap->heap[(temp - 1) / 2];
        temp = (temp - 1) / 2;

    }
    minheap->heap[temp] = edge;
}

Min_heap* make_MINHEAP(int max) {

    Min_heap* min_heap = (Min_heap*)malloc(sizeof(Min_heap));
    min_heap->maxSize = max;
    min_heap->size = 0;
    min_heap->heap = (Edge*)malloc(max * sizeof(Edge));

    return min_heap;
}


void Heap_Sort(Min_heap* minheap, int index) {

    int R = 2 * index + 2;
    int L = 2 * index + 1;
    int SMALL = index;

    if (L < minheap->size && minheap->heap[L].w < minheap->heap[SMALL].w) {
        SMALL = L;
    }

    if (R < minheap->size && minheap->heap[R].w < minheap->heap[SMALL].w) {
        SMALL = R;
    }

    if (SMALL != index) {
        Edge temp = minheap->heap[index];
        minheap->heap[index] = minheap->heap[SMALL];
        minheap->heap[SMALL] = temp;
        Heap_Sort(minheap, SMALL);
    }
}

Edge delete_edge(Min_heap* minheap) {

    Edge MIN = minheap->heap[0];
    minheap->heap[0] = minheap->heap[minheap->size - 1];

    minheap->size--;
    Heap_Sort(minheap, 0);

    return MIN;
}


void Find_MST(const char* output_Path, Graph* graph) {

    int V = graph->V;
    int k_scanned = 0;
    int edge_count = 0;

    Min_heap* minheap = make_MINHEAP(graph->E);

    for (int x = 0; x < graph->E; x++) {

        insert_edge(minheap, graph->edges[x]);
    }

    Subset* set = (Subset*)malloc(V * sizeof(Subset));
    for (int i = 0; i < V; i++) {
        set[i].parent = i;
        set[i].rank = 0;
        set[i].weight = 0;
        set[i].size = 1;
    }

    while (minheap->size > 0 && edge_count<V-1) {
        Edge nextEdge = delete_edge(minheap);
        k_scanned += 1;
        int a = Find(set, nextEdge.u);
        int b = Find(set, nextEdge.v);

        if (a != b) {
            Union(set, a, b, nextEdge.w);
            edge_count++;
        }
    }


    Result* R = (Result*)malloc(V * sizeof(Result));

    int cnt = 0;

    for (int x = 0; x < V; x++) {
        if (set[x].parent == x) {
            R[cnt++] = (Result){ set[x].size, set[x].weight };
        }
    }
    printf("kscanned : %d\n", k_scanned);
    // 결과 파일을 출력할 때 number of vertices로 오름차순으로 정렬한 후, 
    // 같은 것들은 total weight로 정렬하기 위한 함수이다. 
    qsort(R, cnt, sizeof(Result), compare);

    FILE* output = fopen(output_Path, "w");
    if (output) {

        fprintf(output, "%d\n", cnt);

        for (int i = 0; i < cnt; i++) {
            fprintf(output, "%d %lld\n", R[i].size, R[i].weight);
        }
        fclose(output);
    }

    free(R);
    free(set);
    free(minheap->heap);
    free(minheap);
}

int main() {

    char directory[300];
    char input_File[300], output_File[300];
    char input_Path[500], output_Path[500];

    int V, E, max_W;

    FILE* fp = fopen("commands.txt", "r");

    if (!fp) {
        printf("WARNINGS : FILE OPEN ERROR !!");
        return 1;
    }

    fgets(directory, sizeof(directory), fp);
    fgets(input_File, sizeof(input_File), fp);
    fgets(output_File, sizeof(output_File), fp);

    fclose(fp);

    directory[strcspn(directory, "\n")] = '\0';
    input_File[strcspn(input_File, "\n")] = '\0';
    output_File[strcspn(output_File, "\n")] = '\0';

    snprintf(input_Path, sizeof(input_Path), "%s/%s", directory, input_File);
    snprintf(output_Path, sizeof(output_Path), "%s", output_File);

    FILE* input = fopen(input_Path, "r");

    if (!input) {
        printf("WARNINGS : FILE OPEN ERROR !!");
        return 1;
    }

    fscanf(input, "%d %d %d", &V, &E, &max_W);
    Graph* graph = make_graph(V, E);

    for (int j = 0; j < E; j++) {
        fscanf(input, "%d %d %d", &graph->edges[j].u, &graph->edges[j].v, &graph->edges[j].w);
    }

    fclose(input);
    clock_t s_time, e_time;
    double exc_time;
    s_time = clock();

    Find_MST(output_Path, graph);

    e_time = clock();
    exc_time = ((double)(e_time - s_time)) / CLOCKS_PER_SEC;
    printf("수행시간(초) : %.4f\n", exc_time);

    free(graph->edges);
    free(graph);

    return 0;
}