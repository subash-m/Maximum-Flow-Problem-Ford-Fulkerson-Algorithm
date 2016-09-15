#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef struct adjListEdge{
	int node;
	int capacity;
	int residualCapacity;
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
bool queueEmpty();
bool BFS( Edge**, int, int, int, int**);
int maximumFlowAlg( Edge**, int, int, int);

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

bool queueEmpty()
{
     if ((front == NULL) && (rear == NULL))
	return true;
    else
	return false;
}

Edge* addEdge( Edge* currentHead, int newNode, int newCapacity){
	Edge* head = (Edge*) malloc (sizeof(Edge));
	head->node = newNode;
	head->capacity = newCapacity;
	head->residualCapacity = 0;
	head->next = currentHead;
	return head;
}

bool BFS(Edge** rAdjList, int nodes, int source, int sink, int** parent){
	
	bool visited[nodes];
	Edge* temp;
	int node, i;
	memset(visited, 0, sizeof(visited));

	createQueue();
	
	enqueue(source);
	visited[source] = true;
	parent[source][0] = -1;
	parent[source][1] = 0;

	while(!queueEmpty()){
		//Dequeue a node from queue
		node = dequeue();

		temp = rAdjList[node];
		while(temp!= NULL){
			if(visited[temp->node] == true || temp->capacity==0){
				temp = temp->next;
				continue;
			}else{
				enqueue(temp->node);
				parent[temp->node][0] = node;
				parent[temp->node][1] = temp->capacity;
				visited[temp->node] = true;
			}
		}
		/*for(i=0; i<nodes; i++){
			if(visited[i] == false && rAdjList[node][i] > 0){
				enqueue(i);
				parent[i] = node;
				visited[i] = true;
			}
		}*/
	}

	return (visited[sink] == true);
}

int maximumFlowAlg(Edge** adjList, int nodes, int source, int sink){

	int i, index, maxFlow = 0, flow;
	int** parent;
	bool flag=false;

	Edge *temp, *temp1;
	Edge* newEdge;
	Edge** rAdjList;

	rAdjList = (Edge**) malloc(nodes * sizeof(Edge*));
	parent = (int**) malloc( nodes * sizeof(int*));

	//Initialization
	for(i=0; i<nodes; i++){
		parent[i] = (int*) malloc( 2 * sizeof(int));
		parent[i][0] = -1;
		parent[i][1] = 0;

		rAdjList[i] = NULL;
		temp = adjList[i];
		while(temp != NULL){
			rAdjList[i] = addEdge(rAdjList[i], temp->node, temp->capacity);
			temp = temp->next;
		}
	}

	while(BFS(rAdjList, nodes, source, sink, parent)){
		flow = INT_MAX;
		for(i=nodes-1; parent[i][0]!=-1; i=parent[i][0]){
			flow = (parent[i][1]<flow?parent[i][1]:flow);
		}
		flag = false;
		for(i=nodes-1; parent[i][0]!=-1; i=parent[i][0]){
			index = parent[i][0];
			temp = rAdjList[index];
			printf("i - %d index = %d, temp - %d", i, index, temp->node);
			temp1 = adjList[index];
			printf("i - %d index = %d, temp1 - %d", i, index, temp1->node);
			
			while(temp!= NULL){
				if(temp->node != i){
					temp = temp->next;
					temp1 = temp1->next;
					continue;
				}else{
					if(temp->capacity == flow){
						temp->capacity -= flow;
						temp1->residualCapacity += flow;
						//rAdjList[i] = addEdge(rAdjList[i], index, flow);
					}else{
						temp->capacity -= flow;
						temp1->residualCapacity += flow;
						//rAdjList[i] = addEdge(rAdjList[i], index, flow);
					}
					break;
				}
			}
			temp = rAdjList[i];
			flag = false;
			while(temp!= NULL){
				if(temp->node != index){
					temp = temp->next;
					continue;
				}else{
					flag=true;
					temp->capacity += flow;
					break;
				}
			}
			if(flag == false){
				rAdjList[i] = addEdge(rAdjList[i], index, flow);
			}
		}
		maxFlow += flow;
	}
	printf("%d\n", maxFlow);
	for(i=0; i<nodes; i++){
		Edge* traverse = adjList[i];
		while(traverse != NULL){
			//if(traverse->capacity!=0)
			printf("%d %d %d\n", i, traverse->node, traverse->residualCapacity);
			traverse = traverse->next;
		}
		printf("\n");
	}
	/*for(i=0; i<nodes; i++)}{
		
	}*/
}

int main(){
	
	int nodes, edges, i, maxFlow=0;
	int node1, node2, capacity;
	Edge** adjList;

	scanf("%d", &nodes);
	scanf("%d", &edges);

	adjList = (Edge**) malloc(nodes * sizeof(Edge*));

	//Initialization
	for(i=0; i<nodes; i++){
		adjList[i] = NULL;
	}

	for(i=0; i<edges; i++){
		scanf("%d %d %d", &node1, &node2, &capacity);

		//Adding edge node1 --> node2
		adjList[node1] = addEdge(adjList[node1], node2, capacity);
	}
	maximumFlowAlg(adjList, nodes, 0, nodes-1);

	/*for(i=0; i<nodes; i++){
		Edge* traverse = adjList[i];
		printf("adjList[%d] -> ", i);
		while(traverse != NULL){
			printf("(%d %d)->", traverse->node, traverse->capacity);
			traverse = traverse->next;
		}
		printf("\n");
	}*/
	
	return 0;
}
