//Name: Joshua Rony
//UserID: jrony
//Assignment Name: pa5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

#define WHITE 'w'

#define BLACK 'b'

#define GRAY 'g'

#define NIL -1

#define INF -2

int time = 0;

typedef struct GraphObject{ //GraphObject Struct - this is used in Graph.h to export the 'Graph' type to this as well as other clients.
	
		int order; //number of vertices in graph
		
		int size;//number of edges in graph
	
		int source;
		
		List *listOfAdjacencies;
		
		char *color;
		
		int *distance;
		
		int *parent;
		
		int *discover;
		
		int *finish;
		
		int time;
		
		
}GraphObject;

//Constructors-Destructors

Graph newGraph(int n){
	
	//here you must dynamically create "order" number of Lists; 1 List for each vertex  (as the instructions state, it is good practice to create 'order+1' vertices as well as 'order+1' size of array for all the other graph attributes that require attachment to a single vertex.  Each one of these Lists serves as the adjacency list for each one of 	
	//the vertices of the graph.

	Graph thisGraph = malloc(sizeof(GraphObject));
	
	thisGraph->order = n;
	
	thisGraph->source = NIL;
	
	thisGraph->size = 0;
	
	thisGraph->time = 0;
	
	thisGraph->distance = (int*)malloc((thisGraph->order + 1) * sizeof(int)); //allocates enough memory to hold '(n + 1)' times 4 bytes or '(n + 1)' times 32 bits.
	
	thisGraph->parent = (int*)malloc((thisGraph->order + 1) * sizeof(int));
	
	thisGraph->color = (char*)malloc((thisGraph->order + 1) * sizeof(char));
	
	thisGraph->discover = (int*)malloc((thisGraph->order + 1) * sizeof(int));
	
	thisGraph->finish = (int*)malloc((thisGraph->order + 1) * sizeof(int));
	
	thisGraph->listOfAdjacencies = malloc((thisGraph->order + 1) * sizeof(List)); //does the same for List type.
	
	for(int x = 0; x < thisGraph->order + 1; x++){
		
		thisGraph->listOfAdjacencies[x] = newList();//This line, in combination with line 56, dynamically allocates memory for 'order + 1' Lists.
		
		thisGraph->color[x] = WHITE;
		
		thisGraph->distance[x] = INF;
		
		thisGraph->parent[x] = NIL;
		
		thisGraph->discover[x] = UNDEF;
		
		thisGraph->finish[x] = UNDEF;
		
	}
	
	return thisGraph;
	
}

void freeGraph(Graph *pG){
	
	int z = (*pG)->order;
	
	Graph thisGraph = *pG;
	
	for(int x = 0; x < z + 1; x++){
		
		freeList(&thisGraph->listOfAdjacencies[x]);
	}
	
	free(thisGraph->listOfAdjacencies);
	free(thisGraph->color);
	free(thisGraph->distance);
	free(thisGraph->parent);
	free(thisGraph->finish);
	free(thisGraph->discover);
	
	free(*pG);
	*pG = NULL;
	
}



//Access Functions

int getOrder(Graph G){
	
	return G->order;
}

int getSize(Graph G){
	
	return G->size;
}

int getSource(Graph G){
	
	return G->source;
	
}

int getDist(Graph G, int u){
	
	return(G->distance[u]);
}

int getParent(Graph G, int u){
	
	return(G->parent[u]);
}

int getDiscover(Graph G, int u){
	
	if(u < 1){
		
		printf("Graph module getDiscover() function cannot output discovery time of undefined vertex.\n");
		exit(1);
	}
	
	if(u > getOrder(G)){
		
		printf("Graph module getDiscover() function cannot output discovery time of undefined vertex.\n");
		exit(1);
		
	}
	
	return(G->discover[u]);
}

int getFinish(Graph G, int u){
	
	if(u < 1){
		
		printf("Graph module getFinish() function cannot output discovery time of undefined vertex.\n");
		exit(1);
	}
	
	if(u > getOrder(G)){
		
		printf("Graph module getFinish() function cannot output discovery time of undefined vertex.\n");
		exit(1);
		
	}
	
	return(G->finish[u]);
	
	
}

void getPath(List L, Graph G, int u){
	
	//u is the destination vertex
	
	if(getSource(G) == NIL){
		
		printf("Graph module getPath() function cannot determine shortest path before BFS algorithm is implemented.\n");
		exit(1);
	}
	
	else if(u < 1 || u > G->order){
		
		
		printf("Graph module getPath() function cannot determine shortest path from undefined vertex to source.\n");
		
		//append(L, -1);
		//exit(1);
	}
	
	else if(getDist(G, u) == INF){
		
		append(L, NIL);
	}
	
	else{
	
		int temp = u;
	
		append(L, u);
	
		moveFront(L);
	
		while(getParent(G, temp) != NIL){
		
			prepend(L, getParent(G, get(L)));
			
			movePrev(L);
		
			temp = get(L);
		}
		
	}
	
}

//Manipulation Procedures

void makeNull(Graph G){
	
	for(int x = 1; x < G->order + 1; x++){
		
		clear(G->listOfAdjacencies[x]);
		
	}
	
	//G->order = 0;
	
	G->size = 0;
	
	G->source = NIL;
	
	G->time = 0;
		
}

void addEdge(Graph G, int u, int v){
	
	if((u > getOrder(G) || u < 1) || (v > getOrder(G) || v < 1 )){
		
		printf("%s", "Cannot add edge to undefined vertex.");
	}
	
	else{
		
		if(length(G->listOfAdjacencies[u]) == 0 && length(G->listOfAdjacencies[v]) != 0){ //Main condition 1: List[u] is empty but List[v] is not.
			
			append(G->listOfAdjacencies[u], v);
			
			if(u > back(G->listOfAdjacencies[v])){
				
				append(G->listOfAdjacencies[v], u);
			}
			
			else{
				
				moveFront(G->listOfAdjacencies[v]);
				
				while(u > get(G->listOfAdjacencies[v])){
					
					moveNext(G->listOfAdjacencies[v]);
				}
				
				insertBefore(G->listOfAdjacencies[v], u);
			}
			
			G->size++;
			
		}
		
		else if(length(G->listOfAdjacencies[v]) == 0 && length(G->listOfAdjacencies[u]) != 0){//Main condition 2: List[v] is empty but List[u] is not.
			
			append(G->listOfAdjacencies[v], u);
			
			if(v > back(G->listOfAdjacencies[u])){
				
				append(G->listOfAdjacencies[u], v);
			}
			
			else{
				
				moveFront(G->listOfAdjacencies[u]);
				
				while(v > get(G->listOfAdjacencies[u])){
					
					moveNext(G->listOfAdjacencies[u]);
				}
				
				insertBefore(G->listOfAdjacencies[u], v);
			}
			
			G->size++;
			
		}
		
		else if(length(G->listOfAdjacencies[u]) == 0 && length(G->listOfAdjacencies[v]) == 0){ //Main condition 3: Both List[u] and List[v] are empty.
			
			append(G->listOfAdjacencies[u], v);
			
			append(G->listOfAdjacencies[v], u);
			
			G->size++;
		}
		
		else if(length(G->listOfAdjacencies[u]) != 0 && length(G->listOfAdjacencies[v]) != 0){ //Main condition 4:  Neither List[u] nor List[v] are empty.
		
			if(v > back(G->listOfAdjacencies[u])){
				
				append(G->listOfAdjacencies[u], v);
			}
			
			else{
			
				moveFront(G->listOfAdjacencies[u]);
			
				while(v > get(G->listOfAdjacencies[u])){
				
					moveNext(G->listOfAdjacencies[u]);
				}
				
				insertBefore(G->listOfAdjacencies[u], v);
				
			}
		
		
			if(u > back(G->listOfAdjacencies[v])){
				
				append(G->listOfAdjacencies[v], u);
			}
			
			else{
			
				moveFront(G->listOfAdjacencies[v]);
			
				while(u > get(G->listOfAdjacencies[v])){
				
					moveNext(G->listOfAdjacencies[v]);
				}
				
				insertBefore(G->listOfAdjacencies[v], u);
				
			}
			
			G->size++;
			
		}
	
	}
	
	
}

void addArc(Graph G, int u, int v){
	
	if((u > getOrder(G) || u < 1) || (v > getOrder(G) || v < 1 )){
		
		printf("%s", "Graph module addArc() function cannot add edge to undefined vertex.\n");
		exit(1);
	}
	
	else{
	
		if(length(G->listOfAdjacencies[u]) == 0){
			
			append(G->listOfAdjacencies[u], v);
			
			G->size++;
			
		}
		
		else if(length(G->listOfAdjacencies[u]) != 0){
			
			if(v > back(G->listOfAdjacencies[u])){
				
				append(G->listOfAdjacencies[u], v);
				
				G->size++;
			}
			
			else{
				
				moveFront(G->listOfAdjacencies[u]);
				
				while(v > get(G->listOfAdjacencies[u])){
					
					moveNext(G->listOfAdjacencies[u]);
				}
				
				insertBefore(G->listOfAdjacencies[u], v);
				
				G->size++;
			}
		}
	
	}
	
}

void printDFSLists(Graph G){
	
	printf("The discovery List is:\n");
	
	for(int x = 1; x < getOrder(G) + 1; x++){
		
		printf("%d%s", G->discover[x], " ");
	}
	
	printf("\n");
	
	printf("The finish List is:\n");
	
	for(int x = 1; x < getOrder(G) + 1; x++){
		
		printf("%d%s", G->finish[x], " ");
	}
	
	printf("\n");
	
	printf("The parent List is:\n");
	
	for(int x = 1; x < getOrder(G) + 1; x++){
		
		printf("%d%s", G->parent[x], " ");
		
		
	}
	
	printf("\n");
	
	printf("The color List is:\n");
	
	for(int x = 1; x < getOrder(G) + 1; x++){
		
		printf("%c%s", G->color[x], " ");
		
		
	}
	
	printf("\n");
	
	printf("The time is:\n");
	
	printf("%d%s", G->time, "\n");
	
	
	
		

	
}

void Visit(Graph G, int u, List S){
	
	G->time = G->time + 1;
	
	//printf("%s%d%s%d%s", "The discovery time of ", u, " is: ", G->time, "\n");
	
	G->discover[u] = G->time;
	
	G->color[u] = GRAY;
	
	moveFront(G->listOfAdjacencies[u]);
	
	for(int x = 0; x < length(G->listOfAdjacencies[u]); x++){
		
		int temp = get(G->listOfAdjacencies[u]);
		
		if(G->color[temp] == WHITE){
			
			G->parent[temp] = u;
			
			Visit(G, temp, S);
		}
		
		moveNext(G->listOfAdjacencies[u]);
		
	}
		
	G->color[u] = BLACK;
	
	G->time = G->time + 1;
	
	G->finish[u] = G->time;
	
	prepend(S, u);
		
}

void DFS(Graph G, List S){
	
	for(int x = 1; x < getOrder(G) + 1; x++){
		
		if(x == 1){
			
			G->time = 0;
		}
		
		G->color[x] = WHITE;
		
		G->parent[x] = NIL;
		
		G->discover[x] = UNDEF;
		
		G->finish[x] = UNDEF;
		
	}
	
	moveFront(S);
	
	for(int y = 1; y < getOrder(G) + 1; y++){ //y is the root vertex to be sent to Visit
	    
	    if(G->color[get(S)] == WHITE){
			
			Visit(G, get(S), S);
		}
		
		moveNext(S);
	}
}

void BFS(Graph G, int s){
	
	for(int x = 1; x < G->order + 1; x++){//At first I thought this was unnecessary, and it is - if you're only planning on calling BFS once for a single source and a single destination.
											//If you need to call BFS more than once, however, as we do in this assignment, these arrays need to be re-set to their original
		G->color[x] = WHITE;				//default values every time BFS is called, otherwise, the algorithm won't work (duh I'm a moron).
		
		G->distance[x] = INF;
		
		G->parent[x] = NIL;
	}
	
	G->source = s;
	
	G->color[s] = GRAY; //initializing the source vertext as having been visited, but not examined.
	
	G->distance[s] = 0;//setting the distance element of the source to 0 - it is this value that will be used to build the distances from the source of every other vertex,
						//so if this is not initialized at 0, good luck.
	
	List queue = newList(); //creating the queue used for keeping track of the visited vertices.
	
	append(queue, s); //sticking the source vertex into the queue.
	
	while(length(queue) != 0){//Beginning BFS algorithm
		
		int tail = back(queue);

		moveFront(G->listOfAdjacencies[tail]);
		
		for(int x = 0; x < length(G->listOfAdjacencies[tail]); x++){//reassigning the array elements appropriately.
			
			if(G->color[get(G->listOfAdjacencies[tail])] == WHITE){
				
				G->color[get(G->listOfAdjacencies[tail])] = GRAY;
				
				G->distance[get(G->listOfAdjacencies[tail])] = G->distance[tail] + 1;
				
				G->parent[get(G->listOfAdjacencies[tail])] = tail;
				
				prepend(queue, get(G->listOfAdjacencies[tail]));
				
			}
			
			moveNext(G->listOfAdjacencies[tail]);//Moving to the next element of the List.  Without this line of code, good luck, buddy.  Hope you like segmentation faults.
		}
		

		G->color[tail] = BLACK; //once the entire adjacency list of "tail" has been visited, it gets marked as 'black'.
		
		if(length(queue) == 1){ //deleting the last element of the queue.  Again, without these lines of code, get ready for segmentation faults. 
			
			deleteFront(queue);
			
		}
		
		else{
			
			deleteBack(queue);
		}
		

	}
	
	
	
	freeList(&queue);
	//free(queue);
	
}




//Other operations:

void printGraph(FILE *out, Graph G){
	
	for(int x = 1; x < getOrder(G) + 1; x++){
		
		if(length(G->listOfAdjacencies[x]) > 0){
			
			fprintf(out, "%d%s", x, ": ");
		
			printList(out, G->listOfAdjacencies[x]);
			
			fprintf(out, "%s", "\r\n");
			
		}
			
		
	}
			
		
	fprintf(out, "%s", "\r\n");
			
}

Graph transpose(Graph G){
	
	Graph transpose = newGraph(getOrder(G));
	
	for(int x = 1; x < getOrder(G) + 1; x++){
		
		if(length(G->listOfAdjacencies[x]) != 0){
		
			moveFront(G->listOfAdjacencies[x]);
		
			for(int y = 0; y < length(G->listOfAdjacencies[x]); y++){
				
				int temp = get(G->listOfAdjacencies[x]);
			
				append(transpose->listOfAdjacencies[temp], x);
			
				moveNext(G->listOfAdjacencies[x]);
			
				
			}
			
		}
	}
	
	return(transpose);
	
	
}

Graph copyGraph(Graph G){
	
	Graph copy = newGraph(getOrder(G));
	
	for(int x = 1; x < getOrder(G) + 1; x++){
		
		if(length(G->listOfAdjacencies[x]) != 0){
		
        	moveFront(G->listOfAdjacencies[x]);
        	
        	for(int y = 0; y < length(G->listOfAdjacencies[x]); y++){
			
				append(copy->listOfAdjacencies[x], get(G->listOfAdjacencies[x]));
			
				moveNext(G->listOfAdjacencies[x]);
			
			}
			
		}
	}
	
	return(copy);
}

