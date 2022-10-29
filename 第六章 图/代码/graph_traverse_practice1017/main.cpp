#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define MaxSize  100
typedef char VertexType;     // 顶点类型
typedef int EdgeType;

/**
 * 邻接矩阵
 */
typedef struct {
    VertexType vex[MaxSize];
    EdgeType edge[MaxSize][MaxSize];
    int vexNum,arcNum;
}MGraph;

typedef struct {
    int data[MaxSize];
    int rear,top;
}Queue;

/**
 * 邻接表
 */
typedef struct ArcNode{
    int adjvex;
    struct ArcNode *next;
}ArcNode;
typedef struct {
    VertexType data;
    ArcNode *first;
}VNode,AdjList[MaxSize];
typedef struct {
    AdjList vertices;
    int vexNum,arcNum;
}ALGraph;

int visited[MaxSize];
Queue queue;

bool isTree(ALGraph alGraph);

void DFS(ALGraph graph, int v, int &vexCount, int &arcCount,int visitedList[]);

int FirstNeighbor(ALGraph graph, int v);

int NextNeighbor(ALGraph graph, int v, int w);

bool BFS_Path(ALGraph alGraph,int i,int j);

bool DFS_Path(ALGraph alGraph,int i,int j);

void InitQueue(Queue queue);

void EnQueue(Queue queue, int i);

bool isEmpty(Queue queue);

void DeQueue(Queue queue, int &v);

void DFS(ALGraph param, int v, int j,bool &isFind);

void DFS_AllSimple_Path(ALGraph alGraph,int v,int j,int path[],int d);
int main() {

    return 0;
}


/**
 *  以图判树可以从两个方面入手：
 *    1.连通图、没有回路    -- 使用DFS 可以判断是否存在回路
 *    2.图为最小生成树 即 n个顶点 n-1条边
 *    树需要是连通的图，所以需要一次DFS就能遍历完所有顶点
 *    我们使用DFS 进行遍历操作，在基础的DFS函数上 增加两个参数 vexCount,arcCount来统计顶点个数和边的个数
 *    由于在递归中会存在回溯 也就会产生 1 -> 2 && 2 -> 1 ，也就是每条边我们都算了两次
 *    最终，我们需要判断的条件也就是  alGraph.vexNum == vexCount && alGraph.arcNum == 2*(alGraph.vexNum-1)
 * @param alGraph 邻接表的图
 * @return 是否为树
 */
bool isTree(ALGraph alGraph){
    int vexCount = 0,arcCount = 0;
    for (int i = 0; i < alGraph.vexNum; ++i) {
        visited[i] = false;
    }
    DFS(alGraph,0,vexCount,arcCount,visited); // DFS 进行统计 顶点个数 和边的个数
    // DFS 结束后 进行最终判断
    if (alGraph.vexNum == vexCount && arcCount == 2*(alGraph.vexNum - 1))
        return true;
    return false;
}

void DFS(ALGraph graph, int v, int &vexCount, int &arcCount,int visitedList[]) {
    // visit(v);
    visited[v] = true;
    // 成功访问一个顶点，不会再有第二次访问，vexCount ++;
    vexCount++;
    for (int w = FirstNeighbor(graph,v); w >= 0 ; w = NextNeighbor(graph,v,w)) {
        // 不管 邻接点是否被访问 都进行了 边的访问
        arcCount++;
        if (!visited[w]){
            DFS(graph,w,vexCount,arcCount,visited);
        }
    }
}

/**
 * 使用 BFS 判断 v_i 和 v_j 之间是否存在路径
 * 使用一次层次遍历 ，如果可以找到j的坐标 则说明 i -> j 之间有路径 否则没有
 * @param alGraph 邻接表的图
 * @param i 下标
 * @param j 下标
 * @return 是否存在路径
 */
bool BFS_Path(ALGraph alGraph,int i,int j){
    int v = 0;
    for (int k = 0; k < alGraph.vexNum; ++k) {
        visited[i] = false;
    }
    InitQueue(queue);   // 初始化队列
    EnQueue(queue,i);   // 顶点i入队
    while (!isEmpty(queue)){
        DeQueue(queue,v); // 顶点出对
        visited[v] = true;
        if (v == j)
            return true;
        // 找v 的邻接点
        for (int w = FirstNeighbor(alGraph,v); w >= 0 ; w = NextNeighbor(alGraph,v,w)) {
            // 邻接点 下标 == j
            if (w == j)
                return true;
            if (!visited[w]){
                EnQueue(queue,w);
                visited[w] = true;
            }
        }
    }
    // 没有找到
    return false;
}


/**
 *  使用DFS 寻找是否存在路径
 *  需要一次DFS，若找到 就让DFS的isFind为true 没找到就继续递归
 * @param alGraph 邻接表的图
 * @param i  下标
 * @param j 下标
 * @return 是否存在路径
 */
bool DFS_Path(ALGraph alGraph,int i,int j){
    bool isFind = false;
    for (int k = 0; k <alGraph.vexNum ; ++k) {
        visited[i] = false;
    }
    DFS(alGraph,i,j,isFind);
    return isFind;
}

void DFS(ALGraph param, int v,int j,bool &isFind) {
    visited[v] = true;
    if (v == j){
        isFind = true;
    }
    for (int w = FirstNeighbor(param,v); w >= 0 ; w = NextNeighbor(param,v,w)) {
        if (!visited[w]){
            DFS(param,w,j,isFind);
        }
    }
}

/**
 *  利用DFS 寻找 v -> j 的 全部简单路径
 * @param alGraph 邻接表的图
 * @param v 起始顶点
 * @param j 最终顶点
 * @param path 存放路径的数组
 * @param d 要被存放的数组下标
 */
void DFS_AllSimple_Path(ALGraph alGraph,int v,int j,int path[],int d){
    for (int i = 0; i < alGraph.vexNum; ++i) {
        visited[i] = false;
    }
    ArcNode *p;
    path[++d] = v;// 输入的d为 -1
    visited[v] = true;
    // 放入path数组之后 进行判断
    if (v == j){     // 如果已经找到了 打印path数组
        for (int i = 0; i <=d ; ++i) {
            cout<<path[i]<<"  ";
        }
        cout<<endl;
    }
    p = alGraph.vertices[v].first;   // p 为v的第一个邻接顶点 弧
    while (p != NULL){
        int w = p->adjvex; // p 指向的 邻接顶点下标
        if (!visited[w]){ // w 没有被访问
            DFS_AllSimple_Path(alGraph,w,j,path,d); // DFS递归
        }
        // 如果这个邻接顶点被访问过了 说明与这个邻接顶点相关的所有边都已经找过了
        // 就要换下一个邻接顶点
        p = p->next;
    }
    // 如果 while循环 退出 就说明 p == NULL 也就是顶点 V的所有邻接顶点都被找过了
    // 把它设置为最初的状态
    visited[v] = false;
}

void DeQueue(Queue queue, int &v) {

}

bool isEmpty(Queue queue) {
    return false;
}

void EnQueue(Queue queue, int i) {

}

void InitQueue(Queue queue) {

}

int NextNeighbor(ALGraph graph, int v, int w) {
    return 0;
}

int FirstNeighbor(ALGraph graph, int v) {
    return 0;
}
