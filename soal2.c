/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2025/2026
 *   Modul               : 05 – Foundation of Algorithm
 *   Hari dan Tanggal    : Senin, 11 Mei 2026
 *   Nama (NIM)          : Beatrice Corryn Pangestu (13224038)
 *   Nama File           : soal2.c
 *   Deskripsi           : Sebuah pusat komando memiliki daftar misi yang saling bergantung. Beberapa misi baru dapat 
dijalankan jika misi lain telah selesai terlebih dahulu. Sebelum menyusun jadwal final, sistem harus 
memastikan bahwa seluruh misi memang dapat diselesaikan tanpa konflik ketergantungan melingkar. 
Anda diminta menentukan apakah susunan prasyarat yang diberikan masih memungkinkan semua 
misi dijalankan. 
Tentukan apakah semua misi dapat diselesaikan jika tiap misi memiliki prasyarat.
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Graph {
    int v;
    int** array;
};

struct Graph* create(int vertices)
{
    struct Graph* graph= (struct Graph*)malloc(sizeof(struct Graph));
    graph->v = vertices;

    graph->array= (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->array[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->array[i][j] = 0;
        }
    }
    return graph;
}

void edge(struct Graph* graph, int src, int dest)
{
    graph->array[src][dest] = 1;
}

int dfs(struct Graph* graph, int vertex,
                      int* visited, int* stack)
{
    if (!visited[vertex]) {
        visited[vertex] = 1;
        stack[vertex] = 1;
        for (int v = 0; v < graph->v; v++) {
            if (graph->array[vertex][v]) {
                if (!visited[v]&& dfs(graph, v, visited,stack)) {
                    return 1;
                }
                else if (stack[v]) {
                    return 1;
                }
            }
        }
    }
    stack[vertex]= 0; 
    return 0;
}
int detect(struct Graph* graph)
{
    int* visited = (int*)malloc(graph->v * sizeof(int));
    int* stack = (int*)malloc(graph->v * sizeof(int));

    for (int i = 0; i < graph->v; i++) {
        visited[i] = 0;
        stack[i] = 0;
    }

    for (int i = 0; i < graph->v; i++) {
        if (dfs(graph, i, visited,
                              stack)) {
            return 1;
        }
    }
    return 0;
}

int main()
{
     int V;
    int M;
    int a;
    int b;
    scanf("%d %d ",&V,&M);
    struct Graph* graph = create(V);
    for (int i=0; i<M; i++){
            scanf("%d %d",&a,&b);
            edge(graph, a, b);
        }   
    if (detect(graph)) {
        printf("TIDAK BISA");
    }
    else {
        printf("BISA");
    }

    return 0;
}
