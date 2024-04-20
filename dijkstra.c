#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  
#include <limits.h>
#include "common.h"

extern int w[N][N]; //matrix
extern bool S[N]; //an array that shows which verticles have been accessed
extern int Scount;                      
extern int d[N]; //an array that shows distance fron 1 verticle to others

int parent[N][N];


/**
  * Add vertex u to vertex set S.
  * @to add param u Vertex 
  * @param S vertex set
  * @no return
  */
  
void add(int u, bool S[]) {
	S[u] = true;
}

/**
  * Check whether there are vertices in the vertex set that have not been added to S.
  * @return true if there are vertices that have not been added to S, false otherwise
  */
static bool remain() {
    for (int i = 0; i < N; i++) {
        if (!S[i]) {
            return true; 
        }
    }
    return false;  
}

/**
  * Among the vertices whose shortest distance from p is not determined, select the vertex with the minimum d[]
  * return.
  * @param None
  * @return vertices with minimum undetermined d[]
  */
int select_min() {
	int min = -1;
	int temp = M;
	for (int i = 0; i < N; i++) {
		if (S[i] == false ) { //the verticle that its distance from p is not determined  
			if (d[i] <= temp) {
				temp = d[i];
				min = i;
			}
		}
	}
	
	return min;
}



/**
  * True if there is an edge connecting vertex u to vertex x, otherwise returns false.
  * @param u vertex
  * @param x vertex
  * @return true if edge exists, false otherwise
  */
bool member(int u, int x) {
	if (w[u][x] != M) {
		return true;
	}	
	return false;
}


/**
  * Calculate the weight of the shortest path from vertex p to each vertex using Dijkstra's method.
  * @param p starting point
  * @no return
  */
void dijkstra(int p) {	
  add(p, S);

  for (int i = 0; i < N; i++) {
    d[i] = w[p][i];
    if (d[i] != M) { //which verticles can be accessed directly from the start
      parent[i][0] = p; 
    }
  }

  while (remain()) {
    int u = select_min();
    printf("%d\n", u); //check which verticles is being accessed
    if (u == -1) //no path => break 
      break;
    else
      add(u, S);

    for (int x = 0; x < N; x++) {
      if (member(u, x)) {
        int k = d[u] + w[u][x]; //add path
    //avoid overflow (M plus something will cause overflow)
    if (k < 0) {
    	k = M;
    }
    
    if (d[x] == M) {
      d[x] = k;
      if (x != u) {
        parent[x][0] = u; // Update parent
        }
      }
    else if (k < d[x]) {
      d[x] = k;
      if (x != u) {
        parent[x][0] = u; // Update parent
        }      
      }

      printf("parent of %d \n", x);
		for (int checkx = 0; checkx < N; checkx++) {
			printf("%d ", parent[x][checkx]);
		}
		printf("\n");
      }
    }
   printf("\n");
  }
  
}

/****************************************/
//Show Shortest Path   
/***/

int STACK[N];

int top = 0; //pointer of the stack 

void push(int stack[], int verticle) {
	if (top > N-1) {
		printf("top is %d\n", top);
		printf("Stack Overflow at push\n");
		exit(EXIT_FAILURE);
	}
	stack[top] = verticle;
	top++;	
}

int pop(int stack[]) {
	if (top < 0) {
		printf("Stack Overflow at pop\n");
	}
	top--;
	return stack[top];
}

void shortest_path(int start, int destination) {
	int x;
	
	if (d[destination] == M) {
		printf("There is no path to %d.\n", destination);
	}
	else {
		x = destination;
		printf("Shortest path to %d \n", x);
		push(STACK, x);
		while (x != start) {			
			x = parent[x][0];
			push(STACK, x);
		}
		while (top > 0) {
			printf("%d->", pop(STACK));
		}
		printf("END\n");
	}
}

/*************/


/**
  * Display the contents of the array to standard output. For outputting results and debugging.
  * @param name Label (variable name, etc.)
  * @param ary array
  * @no return
  */
void display(char* name, int* ary, int length) {
  printf("%s: [", name);
  for (int i = 0; i < length; i++) {
    if (ary[i] == M)
      printf(" M");
    else
      printf(" %d", ary[i]);
  }
  
  printf(" ]\n");
}


