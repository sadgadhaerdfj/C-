#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "ctype.h"
#include "limits.h"

#define MaxVertex 30

typedef char E;

// 普通节点
typedef struct Node {
    int nextVertex;
    struct Node *next;
} *Node;

// 头节点
struct HeadNode {
    E element;  // 存放的字符
    int time;   // 使用时间
    int input;    // 入度数量
    struct Node *next;
};

// 邻接表
typedef struct AdjacencyGraph {
    int vertexCount;    // 顶点数
    int edgeCount;  // 边数
    struct HeadNode vertex[MaxVertex];
} *Graph;

// 初始化
Graph create() {
    Graph graph = malloc(sizeof(struct AdjacencyGraph));
    graph->vertexCount = graph->edgeCount = 0;
    int i;
    for (i = 0; i < MaxVertex; ++i) {
        graph->vertex[i].input = 0;
        graph->vertex[i].time = INT_MAX;
    }
    return graph;
}

// 添加头节点
void addVertex(Graph graph, E element) {
    if (graph->vertexCount >= MaxVertex) return;
    graph->vertex[graph->vertexCount].element = element;
    graph->vertex[graph->vertexCount].next = NULL;
    graph->vertexCount++;
}

// 添加边
void addEdge(Graph graph, int a, int b) {
    Node node = graph->vertex[a].next;

    // 申请新节点
    Node newNode = (Node) malloc(sizeof(struct Node));
    newNode->nextVertex = b;
    newNode->next = NULL;

    // 如果头节点下一个是空指针，那么直接连上去
    if (!node) {
        graph->vertex[a].next = newNode;
    } else {     // 否则说明当前顶点已经连接了至少一个其他顶点
        while (node->next) {
            // 如果已经连接过对应的顶点，直接返回
            if (node->nextVertex == b) {
                free(newNode);
                return;
            }
            node = node->next;
        }
        // 到达链表尾部，未找到重复边，添加新节点
        node->next = newNode;
    }

    // 成功添加边后，增加目标顶点的入度
    graph->vertex[b].input += 1;
    graph->edgeCount++;
}

// 打印邻接表
void printGraph(Graph graph) {
    printf("邻接表为：\n");
    printf("序号\t入度数\t时间\t字符名\n");
    int i;
    for (i = 0; i < graph->vertexCount; ++i) {
        printf("%d\t%d\t%d\t%c\t", i, graph->vertex[i].input, graph->vertex[i].time, graph->vertex[i].element);
        Node node = graph->vertex[i].next;
        while (node) {
            printf(" -> %d", node->nextVertex);
            node = node->next;
        }
        printf("^\n");
    }
}

// 读取数据
void ReadData(Graph graph, char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("打开文件失败");
        return;
    }
    char line[20];

    // 添加头节点
    while (fgets(line, sizeof(line), file)) {
        //添加头节点
        char *token = strtok(line, ",^\n");
        if (token == NULL) return;
        addVertex(graph, *token);
    }

    // 文件指针重置到开头
    rewind(file);

    // 添加普通节点
    while (fgets(line, sizeof(line), file)) {
        //跳过第一个头节点
        char *token = strtok(line, ",^\n");
        if (token == NULL) return;
        int b = (int) *token - 'A';

        //添加前置节点
        while (1) {
            token = strtok(NULL, ",^\n");
            if (token == NULL || *token == '^') break;
            if (isdigit(*token)) {
                graph->vertex[b].time = *token - '0';
            } else {
                int a = (int) *token - 'A';
                addEdge(graph, a, b);
            }
        }
    }
}

// 栈
typedef struct Stack {
    int *array;
    int capacity;
    int top;
} *ArrayStack;

// 初始化栈
bool initStack(ArrayStack stack, int capacity) {
    stack->array = (int *) malloc(sizeof(E) * capacity);
    if (stack->array == NULL) {
        printf("内存分配失败");
        return 0;
    }
    stack->capacity = capacity;
    stack->top = -1;
    return 1;
}

// 栈是否为空
bool isEmpty(ArrayStack stack) {
    return stack->top == -1;
}

// 入栈
bool push(ArrayStack stack, int element) {
    //如果栈已满，对栈进行扩容
    if (stack->top + 1 == stack->capacity) {
        int newCapacity = stack->capacity + (stack->capacity >> 1); //通过位操作，对栈扩容为原来的1.5倍
        int *newArray = realloc(stack->array, sizeof(E) * newCapacity);
        if (newArray == NULL) return 0;
        stack->array = newArray;
        stack->capacity = newCapacity;
    }
    stack->array[++stack->top] = element;
    return 1;
}

// 出栈
int pop(ArrayStack stack) {
    if (isEmpty(stack))return 0;
    return stack->array[stack->top--];
}

// 获取拓扑序列
char *sequence(Graph graph) {
    //创建栈并初始化
    struct Stack stack;
    initStack(&stack, 10);

    //拓扑序列指针
    char *result = (char *) malloc(sizeof(char) * (graph->vertexCount));
    int n = 0;

    //选出入度为0的顶点入栈
    int i;
    for (i = 0; i < graph->vertexCount; ++i) {
        if (graph->vertex[i].input == 0) push(&stack, i);
    }

    //拓扑排序
    while (!isEmpty(&stack)) {//当栈不为空时
        int index = pop(&stack);//弹出栈顶元素
        result[n++] = graph->vertex[index].element;//将对应顶点的元素值存入结果数组中，并递增n

        Node node = graph->vertex[index].next;
        while (node) {//遍历当前弹出顶点的邻接节点，在图中将与该顶点相连的顶点的入度减1
            graph->vertex[node->nextVertex].input--;
            if (graph->vertex[node->nextVertex].input == 0) push(&stack, node->nextVertex);//如果减1后入度为0，则将其入栈
            node = node->next;
        }
    }

    //判断是否有环
    for (i = 0; i < graph->vertexCount; ++i) {//遍历图中的每个顶点
        if (graph->vertex[i].input != 0) {//如果入度不为0，则说明该顶点所在的路径形成了一个环
            printf("有环\n");
            printf("环所在位置为：%c <-> ", graph->vertex[i].element);//输出环所在位置的顶点元素
            Node node = graph->vertex[i].next;
            while (node) {
                struct HeadNode headNode = graph->vertex[node->nextVertex];
                Node node2 = headNode.next;
                while (node2) {
                    if (node2->nextVertex == i) {
                        printf("%c\n", headNode.element);
                        return NULL;
                    }
                    node2 = node2->next;
                }
                node = node->next;
            }
        }
    }

    //返回结果
    if (n != graph->vertexCount) return NULL;
    return result;
}

void dijkstra(Graph graph, int source, int dist[], int pred[]) {
    int n = graph->vertexCount;
    bool visited[n]; //记录是否已访问

    // 初始化距离数组和visited
    int i;
    for (i = 0; i < n; i++) {
        dist[i] = INT_MAX, visited[i] = false, pred[i] = -1;
    }

    // 源点到自身的距离是0
    dist[source] = 0;

    // 找到所有顶点的最短路径
    int count;
    for (count = 0; count < n - 1; count++) {
        //找到距离数组中未被访问且距离最小的顶点u
        int u = -1;
        int minDist = INT_MAX;
        int v;
        for (v = 0; v < n; v++) {
            if (!visited[v] && dist[v] <= minDist) {
                minDist = dist[v], u = v;
            }
        }

        // 标记该顶点为已访问
        visited[u] = true;

        // 更新与顶点u相邻的顶点v的距离值
        Node node = graph->vertex[u].next;
        while (node) {//如果通过顶点u到顶点v的路径距离更短，则更新dist[v]和pred[v]
            int v = node->nextVertex;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + graph->vertex[u].time < dist[v]) {
                dist[v] = dist[u] + graph->vertex[u].time;
                pred[v] = u;
            }
            node = node->next;
        }//循环结束后，dist[]数组中存储的即为源点到各顶点的最短距离，pred[]数组中存储的是最短路径上各顶点的前驱
    }
}

void printPath(int pred[], int vertex, Graph graph) {
    // 如果前驱节点的索引为-1，则到达源点
    if (pred[vertex] == -1) {
        printf("%c", graph->vertex[vertex].element);
        return;
    }
    printPath(pred, pred[vertex], graph); // 递归地打印前驱顶点的路径
    printf(" -> %c", graph->vertex[vertex].element); // 打印当前顶点
}

int main() {
    //创建邻接表
    Graph graph = create();

    //读取数据
    char *filename = malloc(sizeof(char) * 10);
    if (filename == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    printf("请输入文件名");
    scanf("%s", filename);
    ReadData(graph, filename);

    //打印邻接表
    printGraph(graph);

    //获取拓扑序列并判断是否有环
    char *result = sequence(graph);
    if (result == NULL) {
        printf("获取拓扑序列失败\n");
        return 1;
    } else {
        printf("拓扑序列为：");
        int i;
        for (i = 0; i < graph->vertexCount; ++i)
            printf("%c", result[i]);
        putchar('\n');
    }

    //获取最短路径
    int source = 0; // 假设从第一个顶点作为源点
    int dist[graph->vertexCount];   //存放最短距离大小
    int pred[graph->vertexCount];   //存放前驱节点的索引
    dijkstra(graph, source, dist, pred);

    printf("\n从顶点 %c 到其他顶点的最短路径:\n", graph->vertex[source].element);
    int i;
    for (i = 0; i < graph->vertexCount; ++i) {
        if (i != source) {
            printf("%c 到 %c 的最短路径长度: %d, 路径: ", graph->vertex[source].element, graph->vertex[i].element,
                   dist[i]);
            printPath(pred, i, graph); // 打印具体路径
            putchar('\n');
        }
    }
    return 0;
}
