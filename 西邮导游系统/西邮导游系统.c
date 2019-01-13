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

int stack[100]; //����2����Ҫ��ȫ�ֱ���
int top = -1;
int visited[100] = {0};
int edge2[100][100]; //����3����Ҫ��ȫ�ֱ���
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
    system("��ͼ.png");
    MGraph G;
    CreateMGraph(&G);
    // system("����ͼ.png");
    menuOperation(G);
    return 0;
}

void menu() {
    printf("\t\t**********************���ʵ���ϵͳ**********************\n");
    printf("\t\t*    1. ��ѯ���о������Ϣ                             *\n");
    printf("\t\t*    2. ��ѯ��������֮�������·��                     *\n");
    printf("\t\t*    3. ��ѯ��������֮������·��                     *\n");
    printf("\t\t*    4. ��ѯ��������֮������·��                     *\n");
    printf("\t\t*    5. �˳�                                           *\n");
    printf("\t\t********************************************************\n");
}

void menuOperation(MGraph G) {
    int x;
    menu();
    printf("��ѡ��");
    scanf("%d", &x);
    getchar();
    while (x != 5) {
        if (x > 5 || x < 1) {
            system("cls");
            menu();
            printf("��ѡ��");
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
            printf("��ѡ��");
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
    if ((fp = fopen("У԰����.txt", "r")) == NULL) {
        printf("�ļ��򿪳���\n");
        exit(1);
    }
    fscanf(fp, "%d %d", &G->numVertexes, &G->numEdges);
    for (i = 0; i < G->numVertexes; i++) {
        fscanf(fp, "%d %s %s", &G->vexs[i].num, G->vexs[i].name, G->vexs[i].info);
    }
    // ��ʼ��
    for (i = 0; i < G->numVertexes; i++) {
        for (j = 0; j < G->numVertexes; j++)
            G->arc[i][j] = INFINITY;
        G->arc[i][i] = 0;
    }
    for (i = 0; i < G->numEdges; i++) {
        fgetc(fp);  // ���� "\n"
        fgetc(fp);  // ���� "<"
        fscanf(fp, "%s %s %d", vex1, vex2, &w);
        x = finVex(vex1, *G);
        y = finVex(vex2, *G);
        G->arc[x][y] = w;
        G->arc[y][x] = w;
        fgetc(fp);  // ���� ">"
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
    printf("���������\n");
    scanf("%s", str1);
    start = finVex(str1, G);
    if (start == -1)
        return;
    printf("�������յ�\n");
    scanf("%s", str2);
    end = finVex(str2, G);
    if (end == -1)
        return;
    Dijkstra(G, start, end);
}

void Dijkstra(MGraph G, int start, int end) {
    int v, w, k = 0, min;
    int path[MAxVex], D[MAxVex]; //P[v]��ֵΪǰ�������±꣬D[v]��ʾv0��v�����·�����Ⱥ�
    int final[MAxVex]; //final[w] = 1��ʾ��Ķ���v0��vw�����·��
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
    printf("\t���룺%d\n", D[end]);
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
    printf("���������\n");
    scanf("%s", str1);
    a = finVex(str1, g);
    if (a == -1)
        return -1;
    printf("�������յ�\n");
    scanf("%s", str2);
    b = finVex(str2, g);
    if (b == -1)
        return -1;
    visited[a] = 1;
    stack[++top] = g.vexs[a].num;
    dfs(g, a, b);
    top = -1;                                                 //��ջ��visited�����ʼ��
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
    printf("���������\n");
    scanf("%s", str1);
    a = finVex(str1, g);
    if (a == -1)
        return;
    printf("�������յ�\n");
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
