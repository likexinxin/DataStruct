#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define MAXEDGE  20
#define MAXVEX  14
#define INFINITY  65535


/* 邻接矩阵结构 */
typedef  struct{
    int vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

/**邻接表**/
#define MaxNum 100
typedef int VertexType;
typedef int EdgeType;


//栈
typedef struct {
    int data[MaxNum];
    int top;
}Stack;

typedef struct ArcNode{
    int adjvex;
    EdgeType weight;    // 权值
    struct ArcNode *next;
}ArcNode;
typedef struct VNode{
    int in; // 顶点入度
    VertexType data;    // 顶点名称
    ArcNode * first;
}VNode,AdjList[MaxNum];
typedef struct {
    AdjList vertices;
    int vexNum,edgeNum;
}ALGraph,*GraphAdjList;

bool TopologicalSort(GraphAdjList graph);

void initStack(Stack s);

void Push(Stack s, int i);

bool StackEmpty(Stack s);

void Pop(Stack s, int &v);

/* 构建有向图   */
void CreateMGraph(MGraph *G) {
    int i, j;
    /* printf("请输入边数和顶点数:"); */
    G->numEdges = 20;
    G->numVertexes = 14;
    cout<<G->numEdges<<G->numVertexes;
    for (i =  0; i < G->numVertexes; i++){/* 初始化图 */
        G->vexs[i] = i;
    }

    for (i =  0; i < G->numVertexes; i++){/* 初始化图 */
        for ( j =  0; j < G->numVertexes; j++){
            G->arc[i][j] =  0;
        }
    }

    G->arc[ 0][ 4] =  1;
    G->arc[ 0][ 5] =  1;
    G->arc[ 0][ 11] =  1;
    G->arc[ 1][ 2] =  1;
    G->arc[ 1][ 4] =  1;
    G->arc[ 1][ 8] =  1;
    G->arc[ 2][ 5] =  1;
    G->arc[ 2][ 6] =  1;
    G->arc[ 2][ 9] =  1;
    G->arc[ 3][ 2] =  1;
    G->arc[ 3][ 13] =  1;
    G->arc[ 4][ 7] =  1;
    G->arc[ 5][ 8] =  1;
    G->arc[ 5][ 12] =  1;
    G->arc[ 6][ 5] =  1;
    G->arc[ 8][ 7] =  1;
    G->arc[ 9][ 10] =  1;
    G->arc[ 9][ 11] =  1;
    G->arc[ 10][ 13] =  1;
    G->arc[ 12][ 9] =  1;

}

// 利用邻接矩阵构建邻接表
void CreateALGraph(MGraph G,GraphAdjList *graph){
    ArcNode *arcNode;
    *graph = (GraphAdjList)malloc(sizeof(ALGraph));
    (*graph)->vexNum = G.numVertexes;
    (*graph)->edgeNum = G.numEdges;
    
    // 初始化
    for (int i = 0; i < G.numVertexes; ++i) {
        (*graph)->vertices[i].in = 0;
        (*graph)->vertices[i].data = G.vexs[i];
        (*graph)->vertices[i].first = NULL;    // 将边表置位空表
    }
    
    for (int i = 0; i < G.numVertexes; ++i) {
        for (int j = 0; j < G.numVertexes; ++j) {
            if (G.arc[i][j] == 1){   // 说明有一条路径 使用头插法插入
                arcNode = (ArcNode *)malloc(sizeof(ArcNode));
                arcNode->adjvex = j;
                arcNode->next = (*graph)->vertices[i].first;
                (*graph)->vertices[i].first = arcNode;
                // j的入度 + 1
                (*graph)->vertices[i].in++;
            }
        }
    }

}


int main() {
    MGraph G;
    GraphAdjList graph;
    CreateMGraph(&G);
    CreateALGraph(G,&graph);
    bool isAOV = TopologicalSort(graph);
    if (isAOV){
        cout<<"true";
    }else{
        cout<<"false";
    }
    return 0;
}

bool TopologicalSort(GraphAdjList graph) {
    Stack S;
    initStack(S);
    int results[MaxNum];
    int count = 0;
    int v ;
    ArcNode *arcNode ;
    for (int i = 0; i < graph->vexNum; ++i) {
        if (graph->vertices[i].in == 0)   // 入度为0
                Push(S,i);  // 顶点入栈
    }


    while (!StackEmpty(S)){
        Pop(S,v); // 栈顶元素出栈
        results[count++] = v;
        arcNode = (ArcNode *)malloc(sizeof (ArcNode));
        arcNode = graph->vertices[v].first;
        while (arcNode != NULL){
            if (graph->vertices[arcNode->adjvex].in - 1 == 0){    // 如果-1后入度为0就入栈
                Push(S,arcNode->adjvex);
            }
            arcNode = arcNode->next;
        }
    }


    if (count<graph->vexNum){
        return false;
    }else{
        return true;
    }

}

void Pop(Stack s, int &v) {
    v = s.data[s.top--];
}

bool StackEmpty(Stack s) {
    if (s.top == -1)
        return true;
    return false;
}

void Push(Stack s, int i) {
    s.data[++s.top] = i;
}

void initStack(Stack s) {
    s.top = -1;
}
