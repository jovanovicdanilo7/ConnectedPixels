#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#define ROW 8
#define COL 10

struct Node;
struct Queue;
struct Node* createNode(int_least8_t data_cn);
struct Queue* createQueue(void);
void addElement(struct Queue* queue_e, int_least8_t data_e);
int_least8_t deleteElement(struct Queue* queue_d);
int_least8_t isEmpty(const struct Queue* queue_ie);
void display(const struct Queue* queue_di);

void createMatrix(int_least8_t matrix[ROW][COL]);
void findConnectedPixels(int_least8_t startRow, int_least8_t startColumn);
void BFS(int_least8_t matrix[ROW][COL], int_least8_t startRow, int_least8_t startColumn, int_least8_t targetValue);

#endif /*MATRIX_H*/
