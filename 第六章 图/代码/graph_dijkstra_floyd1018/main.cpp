#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef int VertexType;
typedef int EdgeType;
#define MaxSize 100
#define INFINITY 65535      //表示权值的无穷
typedef struct {
    VertexType Vex[MaxSize];
    EdgeType Edge[MaxSize][MaxSize];
    int vexNum,edgeNum;
}MGraph;

void CreateGraph(MGraph &mGraph);
void ShortPath_Dijkstra(MGraph mGraph,int start);
void printDijkstraResult(MGraph mGraph,int path[],int start);

void ShortPath_Floyd(MGraph graph);

void printFloyd(int i, int j, int p[100][100]);

int main() {
    MGraph  mGraph;
    CreateGraph(mGraph);
    cout<<"---------Create Graph----------------"<<endl;

    cout<<"----------------Dijkstra Start----------------"<<endl;
    ShortPath_Dijkstra(mGraph,2);
    cout<<"----------------Dijkstra Finish----------------\n\n"<<endl;

    cout<<"----------------Floyd Start----------------\n\n"<<endl;
    ShortPath_Floyd(mGraph);
    cout<<"----------------Floyd End----------------"<<endl;
    return 0;
}
/**
 *  Floyd算法是一个DP
 *   通过找中间顶点的方式 来寻找 每对顶点之间的最短长度路径
 * @param graph 邻接矩阵的图
 */
void ShortPath_Floyd(MGraph graph) {
    // 初始化
    int path[MaxSize][MaxSize];
    int A[MaxSize][MaxSize];       // 带权长度
    for (int i = 0; i < graph.vexNum; ++i) {
        for (int j = 0; j < graph.vexNum; ++j) {
            A[i][j] = graph.Edge[i][j];
            path[i][j] = -1;  // 表示直达
        }
    }

    // 核心代码
    for (int v = 0; v < graph.vexNum; ++v) {
        for (int i = 0; i < graph.vexNum; ++i) {
            for (int j = 0; j < graph.vexNum; ++j) {
                if (A[i][j] > A[i][v] + A[v][j]){    // 加入中间点  距离更短
                    A[i][j] = A[i][v] + A[v][j];       // 更换距离
                    path[i][j] = v;         //记录中间顶点
                }
            }
        }
    }
    for (int i = 0; i < graph.vexNum; ++i) {
        for (int j = i+1; j <graph.vexNum ; ++j) {
            printFloyd(i, j, path);
            cout<<endl;
        }
        cout<<"\n";
    }
}
/**
 *  使用递归的方法 打印Floyd的最终结果
 * @param i
 * @param j
 * @param p
 */
void printFloyd(int i, int j, int p[100][100]) {
    if (p[i][j] == -1)
        cout<<"V"<<i<<" -> "<<"V"<<j<<"  ";
    else{
        int mid = p[i][j];
        printFloyd(i,mid,p);
        printFloyd(mid,j,p);
    }
}


void CreateGraph(MGraph &mGraph){
    mGraph.vexNum = 9;  // 9个顶点
    mGraph.edgeNum = 16;    // 16条边

    // 图的初始化 就不使用 cin 进行输入了
    for (int i = 0; i <mGraph.vexNum ; ++i) {
        mGraph.Vex[i] = i;      // 顶点名称 0 1 2 3 ...
    }
    // 边的初始化
    for (int i = 0; i < mGraph.vexNum; ++i) {
        for (int j = 0; j < mGraph.vexNum; ++j) {
            if (i == j)
                mGraph.Edge[i][j] = 0;
            else
                mGraph.Edge[i][j] = mGraph.Edge[j][i] = INFINITY;
        }
    }

    // 上图
    mGraph.Edge[0][1] = 1;
    mGraph.Edge[0][2] =  5;
    mGraph.Edge[1][2] =  3;
    mGraph.Edge[1][3] =  7;
    mGraph.Edge[1][4] =  5;

    mGraph.Edge[ 2][ 4] =  1;
    mGraph.Edge[ 2][ 5] =  7;
    mGraph.Edge[ 3][ 4] =  2;
    mGraph.Edge[ 3][ 6] =  3;
    mGraph.Edge[ 4][ 5] =  3;

    mGraph.Edge[ 4][ 6] =  6;
    mGraph.Edge[ 4][ 7] =  9;
    mGraph.Edge[ 5][ 7] =  5;
    mGraph.Edge[ 6][ 7] =  2;
    mGraph.Edge[ 6][ 8] =  7;

    mGraph.Edge[ 7][ 8] =  4;

    // 对称的 只给了一半 将另一半补全
    cout<<"邻接矩阵："<<endl;
    for (int i = 0; i < mGraph.vexNum; ++i) {
        for (int j = 0; j < mGraph.vexNum; ++j) {
            mGraph.Edge[j][i] = mGraph.Edge[i][j];
            printf("%5d  ",mGraph.Edge[i][j]);

        }
        cout<<endl;
    }
}

/**
 * Dijkstra算法 ，从起始顶点出发，找到顶点的邻接顶点，并找到最短长度的顶点。再从该顶点开始更新dict[]
 * 循环n-1次 start 到其余各点的最短路径
 * @param mGraph 邻接矩阵的图
 * @param start 出发点下标
 */
void ShortPath_Dijkstra(MGraph mGraph,int start){
    VertexType path[MaxSize];  // 存放上一顶点的数组
    EdgeType dict[MaxSize]; // 存放最短路径的数组
    EdgeType final[MaxSize]; // 记录顶点是否已经被采用     0：未被采用  1：被采用
    int min = 0;    // 最小值
    int min_position; // 记录最小值的下标
    // 初始化
    for (int i = 0; i < mGraph.vexNum; ++i) {
        final[i] = 0;
        dict[i] = mGraph.Edge[start][i];    // 第一次对dict数组进行更新
        if (dict[i] != INFINITY)        // 如果 i是 start的邻接顶点
            path[i] = start;
        else        //不是
            path[i] = -1;
    }

    // 开始进行循环 使用 n-1 轮循环即可将所有的最短路径找到。
    for (int i = 1; i < mGraph.vexNum; ++i) {
        // 进行核心操作， 找到 最短长度的点 && 没有被采用过的顶点
        min = INFINITY;
        for (int j = 0; j < mGraph.vexNum; ++j) {   // 我们从头遍历到尾 一定能找到
            if (final[j]==0 && dict[j] < min){
                min_position = j;
                min = dict[j];
            }
        }
        // 找到了我们need的 最短长度点
        final[min_position] = 1;    // 标记被采用过了
        // 检查是否可以更新dict[] 以及 path[]
        // 若 min + min_position -> i 的距离 < dict[i] 而且 final[i] = 0
        // 则可以进行修改
        for (int k = 0; k < mGraph.vexNum; ++k) {
            if (final[k] == 0 && (min + mGraph.Edge[min_position][k]) < dict[k]){
                dict[k] = min + mGraph.Edge[min_position][k];      // 修改当前路径长度
                path[k] = min_position;         // 修改path数组
            }
        }
    }

    printDijkstraResult(mGraph,path,start);
}

void printDijkstraResult(MGraph mGraph,int path[],int start){
    int position = -1;
    int temp[MaxSize];
    int count = 0;
    for (int i = 0; i < mGraph.vexNum; ++i) {
        count = 0;
        position = i;
        temp[count++] = position;
        while (position != start){
            position = path[position];
            temp[count++] = position;
        }
        for (int j = count-1; j >=0 ; --j) {
            cout<<"V"<<temp[j]<<" ";
            if (j != 0)
                cout<<" -> ";
        }
        cout<<endl;
    }
}