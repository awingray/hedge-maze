#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hedge.h"

/* Queues */
Queue *newEmptyQueue(int size) {
	Queue *q;
	q = (Queue *)malloc(sizeof(Queue));
	assert(q != NULL);
	q->elements = (int *)malloc(sizeof(int)*size);
	assert(q->elements != NULL);
	q->rear = -1;
	q->front = 0;
	q->size = 0;
	return q;
}

int isQueueEmpty(Queue *qp) {
	return (qp->size == 0);
}

int dequeue(Queue *qp) {
	if(isQueueEmpty(qp)) {
		exit(0);
	}
	qp->size--;
	return qp->elements[qp->front++];
}

void enqueue(Queue *qp, int item) {
	qp->elements[++qp->rear] = item;
	qp->size++;
}

void freeQueue(Queue *qp){
	free(qp->elements);
	free(qp);
}

/* BFS */
int isUnvisitedPath(Point s, Height h) {
	if(s.visited == 1) {
		return 0;
	}
	return (s.symbol == '.' || (s.symbol == '%' && h.player >= h.flowerbed) || (s.symbol == '^' && h.player <= h.gate));
}

int breadthFirstSearch(int row, int col, Point *mazeArray, Height h) {
	Queue *q = newEmptyQueue(row*col);
	int i = (row*col)/2;
	mazeArray[i].dist = 0;
	mazeArray[i].visited = 1;
	enqueue(q, i);
	while (!isQueueEmpty(q)) {
		i = dequeue(q);
		int pos[4] = {i-col, i+col, i-1, i+1};
		if(mazeArray[i].row == 0 || mazeArray[i].col == 0 || mazeArray[i].row == row - 1 || mazeArray[i].col == col - 1) {
			freeQueue(q);
			return (++mazeArray[i].dist);
		}
		for(int t = 0; t < 4; t++) {
			if(isUnvisitedPath(mazeArray[pos[t]], h)) {
				mazeArray[pos[t]].dist = mazeArray[i].dist + 1;
				enqueue(q, pos[t]);
				mazeArray[pos[t]].visited = 1;
			}
		}
	}
	return row*col;
}

int main(int argc, char *argv[]) {
	int row, col, n;
	int idx, team_size, min, new;
	int height, hg, hf;
	char ch;
	scanf("%d", &n);
	for(int n1 = 0; n1 < n; n1++) {
		Height *heights = NULL;
		Point *mazeArray = NULL;
		scanf("%d %d", &hg, &hf);
		scanf("%d", &team_size);
		heights = (Height *)malloc(sizeof(Height)*team_size);
		assert(heights != NULL);
		for(int i = 0; i < team_size; i++) {
			scanf("%d", &height);
			heights[i].player = height;
			heights[i].gate = hg;
			heights[i].flowerbed = hf;
		}
		scanf("%d %d", &row, &col);
		mazeArray = (Point *)malloc(sizeof(Point)*row*col);
		assert(mazeArray != NULL);
		idx = 0;
		for(int r = 0; r < row; r++) {
			getchar();
			for(int c = 0; c < col; c++) {
				ch = getchar();
				mazeArray[idx].symbol = ch;
				mazeArray[idx].row = r;
				mazeArray[idx].col = c;
				mazeArray[idx].visited = 0;	
				idx++;
			}
		}
		min = breadthFirstSearch(row, col, mazeArray, heights[0]);
		for(int player_no = 1; player_no < team_size; player_no++) {
			for(int j = 0; j < row*col; j++) {
				mazeArray[j].visited = 0;
			}
			new = breadthFirstSearch(row, col, mazeArray, heights[player_no]);
			min = (min < new ? min : new);
		}
		printf("%d\n", min);
		free(heights);
		free(mazeArray);
	}
	return 0;
}
