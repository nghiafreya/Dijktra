#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "common.h"

int w[N][N] = {
  { 0, M,  M, 8, 15, M},
  {10, 0, 24, M,  8, M},
  { M, M,  0, M,  M, 6},
  { M, M,  M, 0,  5, M},
  { M, M, 12, M,  0, 7},
  { M, M,  3, M,  M, 0}};
  
  /*******
  Different matrix form sample code
  
int w[N][N] = {
  { 0, 3,  23, 20, 8, 5},
  {10, 0, M, M,  M, 7},
  { M, 2,  0, M,  M, M},
  { M, M,  15, 0,  M, M},
  { M, M, M, 13,  0, M},
  { M, M,  M, M,  9, 0}};
  *******/

bool S[N];
int Scount = 0;                      // 頂点集合Sの要素数
int d[N];

void add(int, bool[]);
bool remain();
int dijkstra(int);
void display(char *, int *, int);

void push(int[], int);
int pop(int[]);
void shortest_path(int, int);


int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./main <node ID>\n");
    return 1;
  }

  int p = atoi(argv[1]);
  if (p < 0 || N <= p) {
    fprintf(stderr, "Node ID %d is out of range: [0, %d].\n", p, N);
    return 1;
  }

  for (int i = 0; i < N; i++)
    S[i] = false;


  dijkstra(p);              // ダイクストラ法による最短路の計算
  display("Result", d, N);  // 結果表示

  for (int u = 0; u < N; u++)
   shortest_path(p, u);
  
  return 0;
}