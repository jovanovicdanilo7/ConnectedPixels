#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "matrix.h"

struct Node
{
    int_least8_t data_n;
    struct Node* next;
};

struct Queue
{
    struct Node* front;
    struct Node* rear;
};

struct Node* createNode(int_least8_t data_cn)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory error!\n");
        exit(EXIT_FAILURE);
    }

    newNode->data_n = data_cn;
    newNode->next = NULL;
    return newNode;
}

struct Queue* createQueue(void)
{
    struct Queue* queue_cq = (struct Queue*)malloc(sizeof(struct Queue));
    if (queue_cq == NULL)
    {
        printf("Memory error!\n");
        exit(EXIT_FAILURE);
    }

    queue_cq->front = queue_cq->rear = NULL;
    return queue_cq;
}

void addElement(struct Queue* queue_e, int_least8_t data_e)
{
    struct Node* newNode_e = createNode(data_e);
    if (queue_e->rear == NULL)
    {
        queue_e->front = queue_e->rear = newNode_e;
    } else
    {
        queue_e->rear->next = newNode_e;
        queue_e->rear = newNode_e;
    }
}

int_least8_t deleteElement(struct Queue* queue_d)
{
    if (queue_d->front == NULL)
    {
        printf("Queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    int_least8_t data_d = queue_d->front->data_n;
    struct Node* temp = queue_d->front;
    queue_d->front = queue_d->front->next;

    if (queue_d->front == NULL)
    {
        queue_d->rear = NULL;
    }

    free(temp);
    return (int_least8_t)data_d;
}

int_least8_t isEmpty(const struct Queue* queue_ie)
{
    return queue_ie->front == NULL;
}

void display(const struct Queue* queue_di)
{
    struct Node* temp_d = queue_di->front;
    while (temp_d != NULL)
    {
        printf("%d ", temp_d->data_n);
        temp_d = temp_d->next;
    }
    printf("\n");
}

int_least8_t rowNeighbors[] = {-1, 1, 0, 0};
int_least8_t columnNeighbors[] = {0, 0, -1, 1};

void BFS(int_least8_t matrix[ROW][COL], int_least8_t startRow, int_least8_t startColumn, int_least8_t targetValue)
{
    struct Queue* queue = createQueue();
    int_least8_t visited[ROW][COL];
    int_least8_t i;
    int_least8_t j;

    for (i = 0; i < ROW; ++i)
    {
         for(j = 0; j < COL; ++j)
         {
             visited[i][j] = 0;
         }
    }

    addElement(queue, startRow * COL + startColumn);

    visited[startRow][startColumn] = 1;

    printf("Connected pixels with value %d starting from (%d, %d): ", targetValue, startRow, startColumn);

    while (!isEmpty(queue))
    {
        int_least8_t cellIndex = deleteElement(queue);
        int_least8_t currentRow = cellIndex / COL;
        int_least8_t currentColumn = cellIndex % COL;
        printf(" (%d, %d) ", currentRow, currentColumn);
        for (i = 0; i < 4; ++i)
        {
            int_least8_t newRow = currentRow + rowNeighbors[i];
            int_least8_t newColumn = currentColumn + columnNeighbors[i];

            if ((newRow >= 0) && (newRow < ROW) && (newColumn >= 0) && (newColumn < COL) && (matrix[newRow][newColumn] == targetValue) && (!visited[newRow][newColumn]))
            {
                addElement(queue, newRow * COL + newColumn);
                visited[newRow][newColumn] = 1;
            }
        }
    }
    printf("\n");
    free(queue);
}


void findConnectedPixels(int_least8_t startRow, int_least8_t startColumn)
{
    int_least8_t matrix_fcp[ROW][COL];
    createMatrix(matrix_fcp);
    int_least8_t targetValue_fcp = matrix_fcp[startRow][startColumn];
    BFS(matrix_fcp, startRow, startColumn, targetValue_fcp);
}

void createMatrix(int_least8_t matrix[ROW][COL])
{
    int_least8_t i_cm;
    int_least8_t j_cm;
    int_least8_t row_cm;
    int_least8_t column_cm;
    for (i_cm = 0; i_cm < ROW; ++i_cm)
    {
        for (j_cm = 0; j_cm < COL; ++j_cm)
        {
            matrix[i_cm][j_cm] = 0;
        }
    }

    int_least8_t positions[][2] =
    {
        {0, 0}, {3, 0}, {4, 1}, {5, 1}, {2, 2},
        {2, 3}, {3, 3}, {4, 3}, {7, 3}, {3, 4},
        {4, 4}, {5, 4}, {6, 4}, {7, 4}, {2, 5},
        {3, 5}, {4, 5}, {5, 5}, {2, 6}, {3, 6},
        {6, 6}, {4, 8}, {5, 8}, {4, 9}, {5, 9}
    };

    for (i_cm = 0; i_cm < sizeof(positions) / sizeof(positions[0]); ++i_cm)
    {
        row_cm = positions[i_cm][0];
        column_cm = positions[i_cm][1];
        matrix[row_cm][column_cm] = 1;
    }

    printf("8x10 Matrix:\n");
    for (i_cm = 0; i_cm < ROW; ++i_cm)
    {
        for (j_cm = 0; j_cm < COL; ++j_cm)
        {
            printf("%2d ", matrix[i_cm][j_cm]);
        }
        printf("\n");
    }
}