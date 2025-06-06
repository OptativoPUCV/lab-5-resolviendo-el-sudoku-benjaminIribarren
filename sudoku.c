#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i, j, k;
  int seen[10];

  for(i = 0; i < 9; i++){
    for(k = 1; k <= 9; k++) seen[k] = 0;
    for(j = 0; j < 9; j++){
      int val = n->sudo[i][j];
      if(val == 0) continue;
      if(seen[val]) return 0;
      seen[val] = 1;
    }
  }

  for(j = 0; j < 9; j++){
    for(k = 1; k <= 9; k++) seen[k] = 0;
    for(i = 0; i < 9; i++){
      int val = n->sudo[i][j];
      if(val == 0) continue;
      if(seen[val]) return 0;
      seen[val] = 1;
    }
  }

  for(int p = 0; p < 9; p += 3){
    for(int l = 0; l < 9; l += 3){
      for(k = 1; k <= 9; k++) seen[k] = 0;
      for(i = p; i < p + 3; i++){
        for(j = l; j < l + 3; j++){
          int val = n->sudo[i][j];
          if(val == 0) continue;
          if(seen[val]) return 0;
          seen[val] = 1;
        }
      }
    }
  }

  return 1;
}

List* get_adj_nodes(Node* n){
  List* lista = createList();

  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){
        for(int val = 1; val <= 9; val++){
          Node* new = copy(n);
          new->sudo[i][j] = val;
          if(is_valid(new)){
            pushBack(lista, new);
          } else {
            free(new);
          }
        }
        return lista; 
      }
    }
  }

  return lista;
}

int is_final(Node* n){
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      if(n->sudo[i][j] == 0)
        return 0;  
  return -1; 
}

Node* DFS(Node* inicial, int* contador){
  Stack* pila = createStack();
  push(pila, inicial);

  while(!is_empty(pila)){
    Node* current = top(pila);
    pop(pila);
    (*contador)++;

    if(is_final(current))
      return current;

    List* adj = get_adj_nodes(current);
    Node* hijo= first(adj);
    while(hijo){
      push(pila, hijo);
      hijo = next(adj);
    }
  }
  return NULL;
}

/*int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0; 
} */