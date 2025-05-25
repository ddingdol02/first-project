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

// BFS를 위한 큐
typedef struct Queue
{
    int front, rear, size, capacity;
    int *array;
} Queue;

Queue *createQueue(int capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int *)malloc(capacity * sizeof(int));
    return queue;
}

bool isQueueEmpty(Queue *queue)
{
    return queue->size == 0;
}

void enqueue(Queue *queue, int item)
{
    if (queue->size < queue->capacity)
    {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->array[queue->rear] = item;
        queue->size++;
    }
}

int dequeue(Queue *queue)
{
    if (!isQueueEmpty(queue))
    {
        int item = queue->array[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return item;
    }
    return -1;
}

// BFS
void BFS(Graph *graph, int startVertex)
{
    Queue *queue = createQueue(graph->numVertex);
    graph->visited[startVertex] = true;
    enqueue(queue, startVertex);

    while (!isQueueEmpty(queue))
    {
        int v = dequeue(queue);
        printf("%d ", v);

        AdjNode *adj = graph->adjLists[v];
        while (adj)
        {
            if (!graph->visited[adj->vertex])
            {
                graph->visited[adj->vertex] = true;
                enqueue(queue, adj->vertex);
            }
            adj = adj->next;
        }
    }
    printf("\n");
}

int main()
{
    int V = 6;
    Graph *graph = createGragh(V);

    addEdge(graph, 0, 2);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 5);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 5);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    printf("BFS 탐색 결과: ");
    BFS(graph, 0);

    return 0;
}