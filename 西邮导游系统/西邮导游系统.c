#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAxVex 100
#define INFINITY 65535
typedef struct {
    int num;
    char name[MAxVex];
    char info[MAxVex];
} Ding;
typedef struct {
    Ding vexs[MAxVex];
    int arc[MAxVex][MAxVex];
    int numVertexes, numEdges;
} MGraph;

int stack[100]; //操作2所需要的全局变量
int top = -1;
int visited[100] = {0};
int edge2[100][100]; //操作3所需要的全局变量
int p1[100][100], d1[100][100];

void floyd(MGraph *g);

void showBestPath(MGraph g);

void CreateMGraph(MGraph *G);

int finVex(char vex[], MGraph G);

void showShortestPath(MGraph G);

void Dijkstra(MGraph G, int start, int end);

void showAll(MGraph G);

void menu();

void menuOperation(MGraph G);

int showAllPath(MGraph g);

void dfs(MGraph g, int a, int b);

int main(void) {
    system("地图.png");
    MGraph G;
    CreateMGraph(&G);
    // system("无向图.png");
    menuOperation(G);
    return 0;
}

void menu() {
    printf("\t\t**********************西邮导游系统**********************\n");
    printf("\t\t*    1. 查询所有景点的信息                             *\n");
    printf("\t\t*    2. 查询两个景点之间的所有路径                     *\n");
    printf("\t\t*    3. 查询两个景点之间的最佳路径                     *\n");
    printf("\t\t*    4. 查询两个景点之间的最短路径                     *\n");
    printf("\t\t*    5. 退出                                           *\n");
    printf("\t\t********************************************************\n");
}

void menuOperation(MGraph G) {
    int x;
    menu();
    printf("请选择：");
    scanf("%d", &x);
    getchar();
    while (x != 5) {
        if (x > 5 || x < 1) {
            system("cls");
            menu();
            printf("请选择：");
            scanf("%d", &x);
            getchar();
        } else {
            if (x == 1) {
                showAll(G);
                fflush(stdin);
                getchar();
            }
            if (x == 2) {
                showAllPath(G);
                fflush(stdin);
                getchar();
            }
            if (x == 3) {
                floyd(&G);
                showBestPath(G);
                fflush(stdin);
                getchar();
            }
            if (x == 4) {
                showShortestPath(G);
                fflush(stdin);
                getchar();
            }
            system("cls");
            menu();
            printf("请选择：");
            scanf("%d", &x);
            getchar();
        }
    }
    if (x == 5) {
        exit(0);
    }
}

void showAll(MGraph G) {
    int i;
    for (i = 0; i < G.numVertexes; i++) {
        printf("%03d\t%10s\t%s\n", G.vexs[i].num, G.vexs[i].name, G.vexs[i].info);
    }
    printf("\n");
}

void CreateMGraph(MGraph *G) {
    int i, j, k, w, x, y;
    char vex1[100], vex2[100];
    FILE *fp;
    if ((fp = fopen("校园导游.txt", "r")) == NULL) {
        printf("文件打开出错！\n");
        exit(1);
    }
    fscanf(fp, "%d %d", &G->numVertexes, &G->numEdges);
    for (i = 0; i < G->numVertexes; i++) {
        fscanf(fp, "%d %s %s", &G->vexs[i].num, G->vexs[i].name, G->vexs[i].info);
    }
    // 初始化
    for (i = 0; i < G->numVertexes; i++) {
        for (j = 0; j < G->numVertexes; j++)
            G->arc[i][j] = INFINITY;
        G->arc[i][i] = 0;
    }
    for (i = 0; i < G->numEdges; i++) {
        fgetc(fp);  // 过滤 "\n"
        fgetc(fp);  // 过滤 "<"
        fscanf(fp, "%s %s %d", vex1, vex2, &w);
        x = finVex(vex1, *G);
        y = finVex(vex2, *G);
        G->arc[x][y] = w;
        G->arc[y][x] = w;
        fgetc(fp);  // 过滤 ">"
    }
    fclose(fp);
}

int finVex(char vex[], MGraph G) {
    int i;
    for (i = 0; i < G.numVertexes; i++) {
        if (strcmp(vex, G.vexs[i].name) == 0)
            return i;
    }
    return -1;
}

void showShortestPath(MGraph G) {
    char vex1[100];
    char vex2[100];
    int start;
    int end;
    int dist[MAxVex], path[MAxVex][MAxVex] = {0};
    char str1[MAxVex], str2[MAxVex];
    printf("请输入起点\n");
    scanf("%s", str1);
    start = finVex(str1, G);
    if (start == -1)
        return;
    printf("请输入终点\n");
    scanf("%s", str2);
    end = finVex(str2, G);
    if (end == -1)
        return;
    Dijkstra(G, start, end);
}

void Dijkstra(MGraph G, int start, int end) {
    int v, w, k = 0, min;
    int path[MAxVex], D[MAxVex]; //P[v]的值为前驱顶点下标，D[v]表示v0到v的最短路径长度和
    int final[MAxVex]; //final[w] = 1表示求的顶点v0到vw的最短路径
    for (v = 0; v < G.numVertexes; v++) {
        final[v] = 0;
        D[v] = G.arc[start][v];
        path[v] = 0;
    }
    D[start] = 0;
    final[start] = 1;
    for (v = 1; v < G.numVertexes; v++) {
        min = INFINITY;
        for (w = 0; w < G.numVertexes; w++) {
            if (!final[w] && D[w] < min) {
                k = w;
                min = D[w];
            }
        }
        final[k] = 1;
        for (w = 0; w < G.numVertexes; w++) {
            if (!final[w] && (min + G.arc[k][w] < D[w])) {
                D[w] = min + G.arc[k][w];
                path[w] = k;
            }
        }
    }
    int temp = end, minPath[MAxVex], count = 1;
    minPath[0] = end;
    while (1) {
        if (path[temp] == 0)
            break;
        minPath[count++] = path[temp];
        temp = path[temp];
    }
    minPath[count++] = start;
    printf("%s", G.vexs[start].name);
    for (int i = count - 2; i >= 0; i--)
        printf("-->%s", G.vexs[minPath[i]].name);
    printf("\t距离：%d\n", D[end]);
}

void dfs(MGraph g, int a, int b) {
    int i;
    if (a == b) {
        for (i = 0; i < top; i++)
            // printf("%-5d", stack[i]);
            printf("%s->", g.vexs[stack[i] - 1].name);
        printf("%s", g.vexs[stack[i] - 1].name);
        printf("\n");
        return;
    }
    for (i = 1; i <= g.numVertexes; i++) {
        if (g.arc[a][i] != 0 && g.arc[a][i] != INFINITY && visited[i] == 0) {
            visited[i] = 1;
            stack[++top] = g.vexs[i].num;
            dfs(g, i, b);
            top--;
            visited[i] = 0;
        }
    }
}

int showAllPath(MGraph g) {
    int a, b, i;
    char str1[MAxVex], str2[MAxVex];
    printf("请输入起点\n");
    scanf("%s", str1);
    a = finVex(str1, g);
    if (a == -1)
        return -1;
    printf("请输入终点\n");
    scanf("%s", str2);
    b = finVex(str2, g);
    if (b == -1)
        return -1;
    visited[a] = 1;
    stack[++top] = g.vexs[a].num;
    dfs(g, a, b);
    top = -1;                                                 //将栈和visited数组初始化
    for (i = 1; i <= g.numVertexes; i++)
        visited[i] = 0;
}

void floyd(MGraph *g) {
    int v, w, k;
    for (v = 0; v < g->numVertexes; v++)
        for (w = 0; w < g->numVertexes; w++)
            if (g->arc[v][w] == 0 || g->arc[v][w] == INFINITY)
                edge2[v][w] = g->arc[v][w];
            else
                edge2[v][w] = 1;
    for (v = 0; v < g->numVertexes; v++) {
        for (w = 0; w < g->numVertexes; w++) {
            d1[v][w] = edge2[v][w];
            p1[v][w] = w;
        }
    }
    for (k = 0; k < g->numVertexes; k++) {
        for (v = 0; v < g->numVertexes; v++) {
            for (w = 0; w < g->numVertexes; w++) {
                if (d1[v][w] > d1[v][k] + d1[k][w]) {
                    d1[v][w] = d1[v][k] + d1[k][w];
                    p1[v][w] = p1[v][k];
                }
            }
        }
    }
}

void showBestPath(MGraph g) {
    int a, b, k;
    char str1[MAxVex], str2[MAxVex];
    printf("请输入起点\n");
    scanf("%s", str1);
    a = finVex(str1, g);
    if (a == -1)
        return;
    printf("请输入终点\n");
    scanf("%s", str2);
    b = finVex(str2, g);
    if (b == -1)
        return;
    k = p1[a][b];
    printf("%s->", g.vexs[a].name);
    while (k != b) {
        printf("%s->", g.vexs[k].name);
        k = p1[k][b];
    }
    printf("%s\n", g.vexs[b].name);
}
