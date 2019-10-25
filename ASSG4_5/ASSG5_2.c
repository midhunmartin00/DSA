#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define SIZE 100

int n_vertices,n_edges;
int G[SIZE][SIZE];

void initialize()
{
   for(int i=0;i<SIZE;i++)
    for(int j=0;j<SIZE;j++)
      G[i][j]=0;
}

typedef struct Node_bin_heap * node_bin_heap; 


struct Node_bin_heap{
  int data;
  int deg;
  node_bin_heap parent,child,sibling;
};



void link(node_bin_heap y, node_bin_heap z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->deg = z->deg + 1;
}

node_bin_heap root=NULL;

node_bin_heap newNode_bin_heap(int key){
  node_bin_heap temp = (node_bin_heap)malloc(sizeof(struct Node_bin_heap));
  temp->child = temp->parent = temp->sibling = NULL;
  temp->deg = 0;
  temp->data = key;
  return temp;
}

node_bin_heap unify(node_bin_heap heap, node_bin_heap h)
{

  node_bin_heap heap1 = heap;
  node_bin_heap heap2 = h;
  node_bin_heap new_heap;
  node_bin_heap final_heap;
 
  //Code for merging
  if (heap1!=NULL && heap2!=NULL)
  {
    if (heap1->deg <= heap2->deg)
    {
      new_heap = heap1;
      heap1 = heap1->sibling;
    }
    else
    {
      new_heap = heap2;
      heap2 = heap2->sibling;
    }
  }
  else
  {
    if (heap2==NULL)
      new_heap = heap1;
    else
      new_heap = heap2;
  }

  final_heap = new_heap;

  while(heap1!=NULL && heap2!=NULL)
  {
    if (heap1->deg <= heap2->deg)
    {
      new_heap->sibling=heap1;
      new_heap = new_heap->sibling;
      heap1=heap1->sibling;
    }
    else
    {
      new_heap->sibling=heap2;
      new_heap = new_heap->sibling;
      heap2=heap2->sibling;
    }
  }

   while(heap2!=NULL)
   {
      new_heap->sibling=heap2;
      new_heap = new_heap->sibling;
      heap2=heap2->sibling;
   } 

   while(heap1!=NULL)
   {
      new_heap->sibling=heap1;
      new_heap = new_heap->sibling;
      heap1=heap1->sibling;
   } 


  new_heap=final_heap;
  //node_bin_heap H = new_heap;
  //Code for arranging after merged
  node_bin_heap prev_x,next_x,x;
    if (new_heap == NULL)
        return new_heap;
    prev_x = NULL;
    x = new_heap;
    next_x = x->sibling;
    while (next_x != NULL) 
    {
      if ((x->deg != next_x->deg) || ((next_x->sibling != NULL) && (next_x->sibling)->deg == x->deg)) 
      {
            prev_x = x;
            x = next_x;
            next_x = x->sibling;
      } 
      else 
      {
        if (x->data <= next_x->data) 
        {
          x->sibling = next_x->sibling;
          link(next_x, x);
          next_x = x->sibling;
        }
        else
        {
          if (prev_x == NULL)
            new_heap = next_x;
          else
            prev_x->sibling = next_x;
          link(x, next_x);
          x = next_x;
          next_x = x->sibling;
        }
      }
    }
    return new_heap;
}

node_bin_heap insert(node_bin_heap heap,int key){
  node_bin_heap h = newNode_bin_heap(key);
  if (heap==NULL)
    return h;
  heap = unify(heap,h);
  return heap;
}

void revertList(node_bin_heap h) 
{ 
    if (h->sibling != NULL) 
    { 
        revertList(h->sibling); 
        (h->sibling)->sibling = h; 
    } 
    else
        root = h; 
}

node_bin_heap extractMin(node_bin_heap heap_root) 
{ 
    node_bin_heap h = heap_root;
    if (h == NULL) 
       return NULL; 
  
    node_bin_heap min_node_bin_heap_prev = NULL; 
    node_bin_heap min_node_bin_heap = h; 
  
    // Find minimum value 
    int min = h->data; 
    node_bin_heap curr = h; 

    while (curr->sibling != NULL) 
    { 
        if ((curr->sibling)->data < min) 
        { 
            min = (curr->sibling)->data; 
            min_node_bin_heap_prev = curr; 
            min_node_bin_heap = curr->sibling; 
        } 
        curr = curr->sibling; 
    } 
    

    // If there is a single Node_bin_heap 
    if (min_node_bin_heap_prev == NULL && min_node_bin_heap->sibling == NULL)
        h = NULL; 
    else if (min_node_bin_heap_prev == NULL) 
        h = min_node_bin_heap->sibling; 
    // Remove min node_bin_heap from list 
    else
        min_node_bin_heap_prev->sibling = min_node_bin_heap->sibling; 
  
    // Set root (which is global) as children 
    // list of min node_bin_heap 
    if (min_node_bin_heap->child != NULL) 
    { 
        revertList(min_node_bin_heap->child); 
        (min_node_bin_heap->child)->sibling = NULL; 
    } 
  
    if (h==NULL)
      return root;
    else
      return unify(root,h); 
}

int getmaxdegree(node_bin_heap h){
  node_bin_heap temp = h;
  while(temp->sibling)
  {
    temp=temp->sibling;
  }
  return temp->deg;
}

int minDistance(int dist[], int check_set[]) 
{ 
   // Initialize min value 
   int min = INT_MAX, min_index; 
   
   for (int v = 0; v < n_vertices; v++) 
     if (check_set[v] == 0 && dist[v] <= min) 
         { min = dist[v]; min_index = v;} 
   
   return min_index; 
} 

void dijkstra(int start,FILE * ft)
{
  int distance[n_vertices],check_set[n_vertices];
  for(int i=0;i<n_vertices;++i)
  {
    distance[i]=INT_MAX;
    check_set[i]=0;
  }
  distance[start]=0;

  for (int count = 0; count < n_vertices-1; count++) 
     { 
       // Pick the minimum distance vertex from the set of vertices not 
       // yet processed. u is always equal to src in the first iteration. 
       int u = minDistance(distance, check_set); 
   
       // Mark the picked vertex as processed 
       check_set[u] = 1; 
   
       // Update dist value of the adjacent vertices of the picked vertex. 
       for (int v = 0; v < n_vertices; v++) 
        { // Update distance[v] only if is not in check_set, there is an edge from  
         // u to v, and total weight of path from src to  v through u is  
         // smaller than current value of distance[v] 
         if (!check_set[v] && G[u][v] && distance[u] != INT_MAX && distance[u]+G[u][v] < distance[v])
            distance[v] = distance[u] + G[u][v];
        }
     }
    for(int i=0;i<n_vertices;++i)
    {
      if (distance[i]==INT_MAX)
        fprintf(ft,"%d INF\n",i);
      else
        fprintf(ft,"%d %d\n",i,distance[i]);
    }
    return;
}

int main(void) {
  FILE * fp = fopen("input.txt","r");
  FILE * ft = fopen("output.txt","w");
  initialize();
  fscanf(fp,"%d%d",&n_vertices,&n_edges);
  for (int i=0;i<n_edges;++i)
  {
    int src,dest,wt;
    fscanf(fp,"%d%d%d",&src,&dest,&wt);
    G[src][dest] = wt;
  }
  int src;
  fscanf(fp,"%d",&src);
  dijkstra(src,ft);
  fclose(fp);
  fclose(ft);
  return 0;
}
