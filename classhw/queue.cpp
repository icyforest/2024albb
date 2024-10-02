#include<cstdio>


const int MAX = 10000;


typedef struct Queue {
	int node[MAX];
	
	int head, tail;

	void start() {
		head = 0;
		tail = -1;
		return;
	}

	bool isFull() {
		if (tail == MAX)
			return 1;
		return 0;
	}

	void append(int add) {
		if (! isFull()) {
			node[++tail] = add;
		}
		return;
	}

	bool isEmpty() {
		if (head >= tail)
			return 0;
		return 1;
	}

	void pop() {
		if (!isEmpty()) {
			head++;
		}
		return;
	}

	void print() {
		for (int i = head; i <= tail; i++) {
			printf("%d ", node[i]);
		}
		return;
	}
}queue;


int main() {
	
	return;
}
