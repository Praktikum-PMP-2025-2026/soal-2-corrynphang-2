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

 typedef struct node{
    int dest;
    struct node*next;
 }node;

 typedef struct graf{
    int v;
    struct node** array;
 }graf;

 node* new(int dest){
    node* new =(node*)malloc(sizeof(node));
    new ->dest = dest;
    new ->next = NULL;
    return new;
 }

 graf* create(int v){
    graf* graph=(graf*) malloc(sizeof(graf));
    graph -> v = v;
    graph -> array=calloc (v,sizeof(node*));
    return graph;
 }

 void edge(graf* graph, int src, int dest){
    node* node = new(dest);
    node->next= graph->array[src];
    graph->array[src]= node;
    node = new(src);
    node -> next = graph-> array[dest];
    graph -> array[dest]=node;
 }

 int dfs(graf* graph,int v, int* visit, int*stack){
    if(!visit[v]){
        visit[v]=1;
        stack[v]=1;
        for (int i =0; i < graph->v;i++){
            if (graph->array[v]&& graph->array[i]){
                if(!visit[i] && dfs(graph,v,visit,stack)){
                    return 1;
                }else if (stack[i]){
                    return 1;
                }
            }
        }
    }
    stack[v]=0;
    return 0;
 }

 int detect(graf* graph){
    int*visit= (int*) malloc(graph->v* sizeof(int));
    int* stack=(int*) malloc(graph->v* sizeof(int));
    for (int i=0;i<graph->v;i++){
        visit[i]=0;
        stack[i]=0;
    }
    for (int i=0; i< graph->v;i++){
        if(dfs(graph,i,visit,stack)){
            return 1;
        }
    }
    return 0;
 }
 int main(){
    int V;
    int M;
    int a;
    int b;
    scanf("%d %d ",&V,&M);
    graf* graph = create(V);
    for (int i=0; i<M; i++){
        scanf("%d %d",&a,&b);
        edge(graph, a, b);
    }
    if (detect(graph)){
        printf("TIDAK BISA");
    }else{
        printf("BISA");
    }
    return 0;
 }
