#ifndef HEDGE_H
#define HEDGE_H

typedef struct Point {
	char symbol;
	int row;
	int col;
	int dist;
  int visited;
} Point;

typedef struct Queue {
	int *elements;
	int rear;
	int front;
	int size;
} Queue;

typedef struct Height {
	int player;
	int gate;
	int flowerbed;
} Height;

#endif
