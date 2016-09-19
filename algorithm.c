#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

//Structure to store an edge of adjacency List
typedef struct adjListEdge{
	int node;
	int capacity;
	int residualCapacity;
	struct adjListEdge *next;
}Edge;

//Structure to store a node of Queue
struct queueNode{
	int data;
	struct queueNode *ptr;
}*front, *rear, *temp;

// Function declarations
Edge* addEdge(Edge*, int, int);
void createQueue();
void enqueue(int);
int dequeue();
bool queueEmpty();
bool BFS( Edge**, int, int, int, int**);
void maximumFlowAlg( Edge**, int, int, int);

/*Initialises the Queue*/
void createQueue(){
	front = NULL;
	rear = NULL;
}

/*Input
	node - node to be inserted
  Description
	Inserts the node to the queue*/
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

/*Return
	int - the node which is removed from queue
  Description
	Removes a node from the queue*/
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

/*Return
	bool - TRUE  = Queue empty
	       FALSE = Queue not empty
  Description
	Check whether the queue is empty or not*/
bool queueEmpty()
{
     if ((front == NULL) && (rear == NULL))
	return true;
    else
	return false;
}

/*Input
	currentHead 	- the pointer from where a new node is to be inserted
	newNode	    	- the vertex value of newNode
	newCapacity 	- the vertex capacity of newNode
	residualCapacity- by Default the value is 0
  Return
	Edge*		- the pointer to the current node
  Description
	Inserts an new edge from the pointer where it is pointed*/
Edge* addEdge( Edge* currentHead, int newNode, int newCapacity){
	Edge* head = (Edge*) malloc (sizeof(Edge));
	head->node = newNode;
	head->capacity = newCapacity;
	head->residualCapacity = 0;
	head->next = currentHead;
	return head;
}

/*Input
	rAdjList	- adjacency list of the residual graph
	nodes		- Number of nodes of residual graph
	source		- the source vertex to start bfs
	sink		- the end vertex to find path
	parent		- used to track the parent node of the path
  Return
	bool		- whether a path is available to end vertex or not
  Description
	To check whether there exists a path from source to end vertex*/
bool BFS(Edge** rAdjList, int nodes, int source, int sink, int** parent){
	
	bool visited[nodes];
	Edge* temp;
	int node, i;
	//Initialize visited array with FALSE
	memset(visited, 0, sizeof(visited));

	createQueue();
	
	enqueue(source);
	visited[source] = true;
	/*Parent
		To track the parent node of every node in the BFS path
		[0] - stores the parent node index
		[1] - stores the edge capacity to reach the parent node*/
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
	}

	return (visited[sink] == true);
}

/*Input
	adjList	- adjacency list of the input graph
	nodes	- number of nodes of the input graph
	source	- source vertex to find network flow
	sink	- End vertex to find network flow
  Description
	To find the maximum network flow between source and end vertex*/
void maximumFlowAlg(Edge** adjList, int nodes, int source, int sink){

	int i, j, index, maxFlow = 0, flow, maxCluster=0, cluster=0;
	int** parent;
	int **output;
	bool flag=false;

	Edge *temp, *temp1;
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
		// To find the bottleNeck in the BFS path
		for(i=nodes-1; parent[i][0]!=-1; i=parent[i][0]){
			flow = (parent[i][1]<flow?parent[i][1]:flow);
		}
		flag = false;
		//Cluster - To track the maximum no of edges in a single node
		cluster = 0;
		for(i=nodes-1; parent[i][0]!=-1; i=parent[i][0]){
			//index - index of parent node
			index = parent[i][0];
			//temp 	- pointer to residual graph's index node
			temp = rAdjList[index];
			//temp1	- pointer to input graph's index node
			temp1 = adjList[index];
			
			while(temp!= NULL){
				while(temp1!=NULL){
					if(temp1->node != i)
						temp1 = temp1->next;
					else
						break;
				}
				if(temp->node != i){
					cluster++;
					temp = temp->next;
					continue;
				}else{
					//Decrement the capacity in residual graph
					temp->capacity -= flow;
					//To track the flow through network in input graph to print output
					if(temp->residualCapacity != -1)
						temp1->residualCapacity += flow;
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
				//Create a backedge in residual graph
				rAdjList[i] = addEdge(rAdjList[i], index, flow);
				temp = rAdjList[i];
				temp->residualCapacity = -1;
			}
			if(maxCluster < cluster)
				maxCluster = cluster;
		}
		maxFlow += flow;
	}
	/*To retain the order of input edges in output,
	  we store the edges in an array and then print in reverse order*/
	output = (int **) malloc (nodes-1 * sizeof(int*));
	for(i=0; i<nodes-1; i++)
		output[i] = (int*) malloc (3 * sizeof(int));

	printf("%d\n", maxFlow);
	for(i=0, j=0; i<nodes; i++){
		Edge* traverse = adjList[i];
		j=0;
		while(traverse != NULL){
			output[j][0] = i;
			output[j][1] = traverse->node;
			output[j++][2] = traverse->residualCapacity;
			traverse = traverse->next;
		}
		for(j=j-1; j>=0; j--)
			printf("%d %d %d\n", output[j][0], output[j][1], output[j][2]);
	}
	free(output);
	free(parent);
	free(rAdjList);
}

int main(){
	
	int nodes, edges, i, maxFlow=0;
	int node1, node2, capacity;
	Edge** adjList;

	//Input no of nodes and edges
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

	free(adjList);
	
	return 0;
}
