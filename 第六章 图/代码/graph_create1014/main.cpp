#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;
#define MaxNum 100 //顶点数目的最大值
#define INFINITY   65535  // 表示权值的无穷
typedef char VertexType;    // 顶点的数据类型
typedef int EdgeType;   // 边的数据类型

typedef struct ArcNode{  // 边表结点
    int adjvex; // 邻接点域，记录该点的下标, i->j ,也就是记录j的下标
    struct ArcNode *next;
    //  EdgeType weight;  存储权值
}ArcNode;
typedef struct VNode{      // 顶点表结点
    VertexType data;    //顶点名称
    ArcNode *first;     // 第一个指向其他结点的 弧
}VNode,AdjList[MaxNum];
typedef struct{
    AdjList vertices;   //邻接表
    int vexnum,arcnum;  //图的顶点数和弧数
}ALGraph;   // 以邻接表存储的图

typedef struct {
    VertexType Vex[MaxNum];     //顶点表
    EdgeType Edge[MaxNum][MaxNum];  //邻接矩阵
    int vexnum,edgenum; // 图当前的顶点数和边数
}MGraph;


// 创建邻接表 图
void createALGraph(ALGraph *alGraph);

// 创建邻接矩阵 图
void createMGraph(MGraph *mGraph);

void printMGraph(MGraph mGraph);

int main() {
    MGraph mGraph;
    createMGraph(&mGraph);
    printMGraph(mGraph);
    return 0;
}

// 创建邻接表图
void createALGraph(ALGraph *alGraph){
    int v_i,v_j = 0;
    ArcNode *arcNode;
    cout<<"输入顶点数 边数"<<endl;
    cin>>alGraph->vexnum>>alGraph->arcnum;
    // 输入顶点 并对 顶点的 first进行初始化
    for (int i = 0; i < alGraph->vexnum; ++i) {
        cout<<"输入第"<<i+1<<"个顶点信息"<<endl;
        cin>>alGraph->vertices[i].data;
        alGraph->vertices[i].first = NULL;
    }
    // 建立边表
    for (int i = 0; i < alGraph->arcnum; ++i) {
        cout<<"输入边(vi,vj)的顶点序号i,j（空格分隔）:"<<endl;
        cin>>v_i>>v_j;
        arcNode = (ArcNode *)malloc(sizeof(ArcNode));
        arcNode->adjvex = v_j;
        // 使用头插法 将当前i所指的first -> arcNode ， arcNode -> first
        arcNode->next = alGraph->vertices[v_i].first;
        alGraph->vertices[v_i].first = arcNode;

        // 无向图为对称的 i->j j->i, 若为有向图 则可省略以下步骤
        arcNode = (ArcNode *)malloc(sizeof(ArcNode));
        arcNode->adjvex = v_i;
        arcNode->next = alGraph->vertices[v_j].first;
        alGraph->vertices[v_j].first = arcNode;
        free(arcNode);
    }
}

// 创建邻接矩阵图
void createMGraph(MGraph *mGraph){
    cout<<"输入顶点数和边数(使用空格分隔)"<<endl;
    cin>>mGraph->vexnum>>mGraph->edgenum;
    for (int i = 0; i < mGraph->vexnum; ++i) {
        cout<<"请输入第" <<i+1<<"个顶点名"<<endl;
        cin>>mGraph->Vex[i];
    }

    // 邻接矩阵初始化
    for (int i = 0; i < mGraph->vexnum; ++i) {
        for (int j = 0; j < mGraph->vexnum; ++j) {
            if (i == j)
                mGraph->Edge[i][j] = 0;
            mGraph->Edge[i][j] = INFINITY;
        }
    }
    //对邻接矩阵赋值
    for (int i = 0; i < mGraph->edgenum; ++i) {
        cout<<"请输入边（vi, vj)的i，j和权值w（空格分隔）:"<<endl;
        int edge_i,edge_j,weight = 0;
        cin>>edge_i>>edge_j>>weight;
        mGraph->Edge[edge_i][edge_j] = weight;
        mGraph->Edge[edge_j][edge_i] = mGraph->Edge[edge_i][edge_j] ;   // 无向图 对称
    }
}

// 打印邻接矩阵图
void printMGraph(MGraph mGraph){
    for (int i = 0; i < mGraph.vexnum; ++i) {
        for (int j = 0; j < mGraph.vexnum; ++j) {
            cout<<mGraph.Edge[i][j]<<"  ";
        }
        cout<<endl;
    }
}