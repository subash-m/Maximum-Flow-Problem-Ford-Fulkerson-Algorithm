#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct adjListEdge{
	int node;
	int capacity;
	struct adjListEdge *next;
}Edge;

struct queueNode{
	int data;
	struct queueNode *ptr;
}*front, *rear, *temp;

Edge* addEdge(Edge*, int, int);
void createQueue();
void enqueue(int);
int dequeue();
bool BFS(Edge**, int, int, int, int*);

void createQueue(){
	front = NULL;
	rear = NULL;
}

void enqueue(int node){
	if(rear == NULL){
		rear = (struct queueNode*) malloc (sizeof(struct queueNode));
		rear->ptr = NULL;
		rear->data = node;
		front = rear;
	}else{
		temp = (struct queueNode*) malloc (sizeof(struct queueNode));
		rear->ptr = temp;
		temp->data = node;
		temp->ptr = NULL;
		
		rear = temp;
	}
}

int dequeue(){
	struct queueNode* front1 = front;
	int node;
	
	if(front1 == NULL)
		return -1;
	else{
		if(front1->ptr != NULL){
			node = front1->data;
			front1 = front1->ptr;
			free(front);
			front = front1;
		}else{
			node = front->data;
			free(front);
			front = NULL;
			rear = NULL;
		}
		return node;
	}
}

Edge* addEdge( Edge* currentHead, int newNode, int newCapacity){
	Edge* head = (Edge*) malloc (sizeof(Edge));
	head->node = newNode;
	head->capacity = newCapacity;
	head->next = currentHead;
	return head;
}

bool BFS(Edge** rAdjList, int nodes, int source, int sink, int* parent){
	
	bool visited[nodes];
	memset(visited, 0, sizeof(visited));

	createQueue();
	enqueue(source);
	visited[source] = true;
	parent[source] = -1;
	
}

int main(){
	
	int nodes, edges, i;
	int node1, node2, capacity;
	int *parent;
	Edge** adjList;

	scanf("%d", &nodes);
	scanf("%d", &edges);

	adjList = (Edge**) malloc(nodes * sizeof(Edge*));
	parent = (int*) malloc(nodes * sizeof(int));

	//Initialization
	for(i=0; i<nodes; i++){
		adjList[i] = NULL;
		parent[i] = 0;
	}

	for(i=0; i<edges; i++){
		scanf("%d %d %d", &node1, &node2, &capacity);

		//Adding edge node1 --> node2
		adjList[node1] = addEdge(adjList[node1], node2, capacity);
	}

	for(i=0; i<nodes; i++){
		Edge* traverse = adjList[i];
		printf("adjList[%d] -> ", i);
		while(traverse != NULL){
			printf("(%d %d)->", traverse->node, traverse->capacity);
			traverse = traverse->next;
		}
		printf("\n");
	}
	
	return 0;
}
