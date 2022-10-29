#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define MaxSize 100
typedef int ElemType;
typedef int EdgeType;
typedef char VertexType;

typedef struct {
    ElemType data[MaxSize];
    int front,rear;
}Queue;

typedef struct{
    ElemType data[MaxSize];
    int top;
}Stack;

typedef struct {
    VertexType Vex[MaxSize];
    EdgeType edgeList[MaxSize][MaxSize];
    int verNum,edgeNum;
}MGraph;

bool visited[MaxSize];      // 顶点是否被访问 记录数组
Queue  queue;       // 队列
Stack stack;         //栈
void BFS_fun(MGraph graph);             // BFS
void BFS_core(MGraph graph,int v);            // BFS
void InitQueue(Queue &Q){
    Q.rear = Q.front = 0 ;
}               // 初始化队列
void visit(int v){
    cout<<"已经被访问"<<endl;
}                   // 对顶点v进行访问
bool EnQueue(Queue &Q,int x);              // 入队
bool DeQueue(Queue &Q,int &x);          // 出队 赋值给x
bool isEmpty(Queue Q);                      // 队列是否为空
int FirstNeighbor(MGraph graph, int v);         // 寻找第一个邻接顶点
int NextNeighbor(MGraph graph, int v, int w);   // 寻找下一个邻接顶点
void DFSTraverse(MGraph graph);     // DFS
void DFS(MGraph graph,int v);       // DFS
void DFS_Non_Recursion(MGraph graph);    // DFS 的非递归算法

void InitStack(Stack stack);

void Push(Stack stack, int &v);

void Pop(Stack s, int &v);

bool isStackEmpty(Stack s);

int main() {

    return 0;
}

/**
 * BFS 算法
 * @param graph
 */
void BFS_fun(MGraph graph){
    for (int i = 0; i < graph.verNum; ++i) {
        visited[i] = false;
    }
    InitQueue(queue);
    // 从第一个顶点进行广度优先遍历
    for (int i = 0; i < graph.verNum; ++i) {
        if (!visited[i]){      // 如果没有被访问过
            BFS_core(graph,i);  // 进行访问 并将邻接点放入队列中
        }
    }
}

void BFS_core(MGraph graph,int v){
    visit(v);
    visited[v] = true;
    EnQueue(queue,v);   // 顶点入队
    while (!isEmpty(queue)){    // 队列非空 就一直进行循环
        DeQueue(queue,v);   // 先进入的顶点出队
        for (int w =FirstNeighbor(graph,v);w>=0;w = NextNeighbor(graph,v,w)){
            if (!visited[w]){// 如果邻接点w没有被访问过
                visit(w);       // 访问w
                visited[w] = true;
                EnQueue(queue,w);    // 入队
            }
        }
    }
}

/**
 * DFS 算法
 * @param graph
 */
void DFSTraverse(MGraph graph){
    for (int i = 0; i < graph.verNum; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < graph.verNum; ++i) {
        if (!visited[i]){
            DFS(graph,i);
        }
    }
}
void DFS(MGraph graph,int v){
    visit(v);
    visited[v] = true;
    for (int w= FirstNeighbor(graph,v);w>=0;w = NextNeighbor(graph,v,w)){
        if (!visited[w]){
            DFS(graph,w);
        }
    }
}

/**
 *  DFS 的非递归，利用栈
 * @param graph
 */
void DFS_Non_Recursion(MGraph graph,int v){
    int k = 0;
    for (int i = 0; i < graph.verNum; ++i) {
        visited[i] = false;     // visited 数组 初始化
    }
    InitStack(stack);

    Push(stack,v);
    visit(v);
    visited[v] = true;
    while (!isStackEmpty(stack)){
        Pop(stack,k);  // 栈中顶点退出
        visit(k);
        visited[k] = true;
        for (int w = FirstNeighbor(graph,k); w>=0; w = NextNeighbor(graph,k,w)) {
            if (!visited[w]){
                visit(w);
                visited[w] = true;
                Push(stack,w);
            }
        }
    }
    Pop(stack,v);
}

bool isStackEmpty(Stack s) {
    if (s.top == -1){
        return true;
    }
    return false;
}

void Pop(Stack s, int &v) {
    if (s.top == -1)
        return;
    v = s.data[s.top--];
}

void Push(Stack s, int &v) {
    if(s.top == MaxSize- 1)
        return;
    s.data[++s.top] = v;
}


void InitStack(Stack stack) {

}

// 找到下一个邻接点的顶点号，如果没有下一个邻接点则返回-1
int NextNeighbor(MGraph graph, int v, int w) {
    return 0;
}

// 找到第一个邻接点
int FirstNeighbor(MGraph graph, int v) {
    return 0;
}
