#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
#define INF 65535
#define MaxSize 100
typedef struct {
    char Vex[MaxSize];
    int Edge[MaxSize][MaxSize];
    int vexNum, edgeNum;
} MGraph;
typedef struct {
    char start; // 起始
    char end;   // 结束
    int weight; // 权重
} edge;

// 创建一个 图
void CreateGraph(MGraph &mGraph, char vexs[], int len, int matrix[][9]);

void prim(MGraph mGraph, int start);   // prim 算法

void Kruskal(MGraph mGraph,edge *E);       // Kruskal算法
edge *getEdge(MGraph mGraph);

void sortEdge(edge *e, int num);

int getposition(char ch);

int getPosition(MGraph graph, char ch);

int getEnd(int vends[], int i);

int main() {
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int matrix[][9] = {
                     /*A*//*B*//*C*//*D*//*E*//*F*//*G*/
            /*A*/ {   0,  12, INF, INF, INF,  16,  14},
            /*B*/ {  12,   0,  10, INF, INF,   7, INF},
            /*C*/ { INF,  10,   0,   3,   5,   6, INF},
            /*D*/ { INF, INF,   3,   0,   4, INF, INF},
            /*E*/ { INF, INF,   5,   4,   0,   2,   8},
            /*F*/ {  16,   7,   6, INF,   2,   0,   9},
            /*G*/ {  14, INF, INF, INF,   8,   9,   0}};
    int len = sizeof(vexs) / sizeof(vexs[0]);
    MGraph mGraph;
    CreateGraph(mGraph, vexs, len, matrix);
//    prim(mGraph, 0);  A  B  F  E  D  C  G
   edge *Edge = getEdge(mGraph);
    Kruskal(mGraph,Edge);
   return 0;
}

void CreateGraph(MGraph &mGraph, char vexs[], int len, int matrix[][9]) {
    mGraph.vexNum = len;
    for (int i = 0; i < mGraph.vexNum; ++i) {
        mGraph.Vex[i] = vexs[i];
    }
    int edges = 0;
    for (int i = 0; i < mGraph.vexNum; ++i) {
        for (int j = 0; j < mGraph.vexNum; ++j) {
            mGraph.Edge[i][j] = matrix[i][j];
            if (i != j && matrix[i][j] != INF)
                edges++;
        }
    }
    mGraph.edgeNum = edges / 2;
}

void prim(MGraph mGraph, int start) {
    int index = 0;          // 存放下标
    int count = 0;          // 总权值
    char prims[MaxSize];     // 存放结果数组
    int weights[MaxSize];       // 到各点权值

    prims[index++] = mGraph.Vex[start]; // 先把start这个点存进去

    // 初始化weights数组
    for (int i = 0; i < mGraph.vexNum; ++i) {
        weights[i] = mGraph.Edge[start][i];
    }
    weights[start] = 0;
    for (int i = 0; i < mGraph.vexNum; ++i) {   //这一层仅仅是控制循环次数
        if (i == start) // 如果
            continue;
        int min = INF;
        int k = 0;
        for (int j = 0; j < mGraph.vexNum; ++j) {
            if (weights[j] != 0 && weights[j] < min) { // 寻找最小权值的边
                min = weights[j];
                k = j;
            }
        }
        // 找到了 加入到 结果中 ，weights[k] = 0 也就是标记为被用过了
        prims[index++] = mGraph.Vex[k];
        weights[k] = 0;
        count += min;   // 计算总权值
        // 更新weights数组
        for (int j = 0; j < mGraph.vexNum; ++j) {
            if (weights[j] != 0 && mGraph.Edge[k][j] < weights[j])
                weights[j] = mGraph.Edge[k][j];
        }

    }

    cout << "PRIM(" << mGraph.Vex[start] << ")=" << count << ": ";
    for (int i = 0; i < index; ++i) {
        cout << prims[i] << "  ";
    }
    cout << endl;

}

void Kruskal(MGraph mGraph,edge *E){
    sortEdge(E,mGraph.edgeNum);
    int index = 0;
    int vend[MaxSize] = {0};    // 并查集
    edge *result = new edge[MaxSize];      // 存放结果

    for (int i = 0; i < mGraph.edgeNum; ++i) {   // 将所有的边都遍历一遍
        int p1 = getPosition(mGraph,E[i].start);
        int p2 = getPosition(mGraph,E[i].end);

        int n = getEnd(vend,p1);    // 找到n的好大哥
        int m = getEnd(vend,p2);    // 找到m的好大哥
        if (n != m){    // 不属于同一个 并查集
            vend[n] = m;    // 前任大哥被 m 替换，帮派合并了
            result[index++] =E[i];
        }
    }

    // 统计并打印"kruskal最小生成树"的信息
    int length = 0;
    for (int i = 0; i < index; i++)
        length += result[i].weight;
    cout << "Kruskal=" << length << ": ";
    for (int i = 0; i < index; i++)
        cout << "(" << result[i].start << "," << result[i].end << ") ";
    cout << endl;


}

int getEnd(int vends[], int i) {
    while (vends[i] > 0)
        i = vends[i];

    return i;
}

int getPosition(MGraph graph, char ch) {
    for (int i = 0; i < graph.vexNum; ++i) {
        if (ch == graph.Vex[i])
            return i;
    }
    return -1;
}


void sortEdge(edge *e, int num) {
    for (int i = 0; i < num; ++i) {
        for (int j = i+1; j <num ; ++j) {
            if (e[i].weight > e[j].weight){ // 冒泡排序
                edge temp = e[j];
                e[j] = e[i];
                e[i] = temp;
            }
        }
    }
}

edge *getEdge(MGraph mGraph){
    int index = 0;
    edge *e = new edge[MaxSize];

    for (int i = 0; i < mGraph.vexNum; ++i) {
        for (int j = i+1; j < mGraph.vexNum; ++j) {
            if (mGraph.Edge[i][j] != INF && mGraph.Edge[i][j] != 0){
                e[index].start = mGraph.Vex[i];
                e[index].end = mGraph.Vex[j];
                e[index].weight = mGraph.Edge[i][j];
                index++;
            }
        }
    }
    return e;
}