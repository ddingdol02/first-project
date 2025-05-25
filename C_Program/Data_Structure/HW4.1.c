#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct AdjNode
{
    int vertex;
    struct AdjNode *next;
} AdjNode;

typedef struct Graph
{
    int numVertex;
    AdjNode **adjLists;
    bool *visited;
} Graph;

AdjNode *createNode(int v)
{
    AdjNode *node = (AdjNode *)malloc(sizeof(AdjNode));
    node->vertex = v;
    node->next = NULL;
    return node;
}

Graph *createGragh(int numVertex)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertex = numVertex;
    graph->adjLists = (AdjNode **)malloc(numVertex * sizeof(AdjNode));
    graph->visited = (bool *)malloc(numVertex * sizeof(bool));
    for (int i = 0; i < numVertex; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

void addEdge(Graph *graph, int first, int second)
{
    AdjNode *node = createNode(second);
    node->next = graph->adjLists[first];
    graph->adjLists[first] = node;
    node = createNode(first);
    node->next = graph->adjLists[second];
    graph->adjLists[second] = node;
}

// DFS를 위한 스택
typedef struct Stack
{
    int top, capacity;
    int *array;
} Stack;

Stack *createStack(unsigned capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(capacity * sizeof(int));
    return stack;
}

bool isStackEmpty(Stack *stack)
{
    return stack->top == -1;
}

void push(Stack *stack, int item)
{
    if (stack->top < stack->capacity - 1)
        stack->array[++stack->top] = item;
}

int pop(Stack *stack)
{
    if (!isStackEmpty(stack))
        return stack->array[stack->top--];
    return -1;
}

// DFS
void DFS(Graph *graph, int startVertex)
{
    Stack *stack = createStack(graph->numVertex);
    push(stack, startVertex);

    while (!isStackEmpty(stack))
    {
        int v = pop(stack);
        if (!graph->visited[v])
        {
            printf("%d ", v);
            graph->visited[v] = true;
            AdjNode *adj = graph->adjLists[v];
            while (adj)
            {
                if (!graph->visited[adj->vertex])
                {
                    push(stack, adj->vertex);
                }
                adj = adj->next;
            }
        }
    }
    printf("\n");
}

int main()
{
    int V = 5;
    Graph *graph = createGragh(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);

    printf("DFS 탐색 결과: ");
    DFS(graph, 0);

    return 0;
}