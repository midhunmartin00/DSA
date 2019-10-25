#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100

struct Edge
{
    int src, dest, weight;
};

int V;
int E;
struct Edge * graph;

void initialize_graph(){
  graph = (struct Edge *)malloc(E*sizeof(struct Edge));
//   for(int i=0;i<E;++i)
//   {
//     graph[i]=NULL;
//   }
}

struct subset 
{ 
    int parent; 
    int rank; 
}; 

int find(struct subset subsets[], int i) 
{ 
    // find root and make root as parent of i  
    // (path compression) 
    if (subsets[i].parent != i) 
        subsets[i].parent = find(subsets, subsets[i].parent); 
  
    return subsets[i].parent; 
}

void Union(struct subset subsets[], int x, int y) 
{ 
    int xroot = find(subsets, x); 
    int yroot = find(subsets, y); 
  
    // Attach smaller rank tree under root of high  
    // rank tree (Union by Rank) 
    if (subsets[xroot].rank < subsets[yroot].rank) 
        subsets[xroot].parent = yroot; 
    else if (subsets[xroot].rank > subsets[yroot].rank) 
        subsets[yroot].parent = xroot; 
  
    // If ranks are same, then make one as root and  
    // increment its rank by one 
    else
    { 
        subsets[yroot].parent = xroot; 
        subsets[xroot].rank++; 
    } 
} 
 
int comp(const void * a, const void * b) 
{ 
    struct Edge* a1 = (struct Edge*)a; 
    struct Edge* b1 = (struct Edge*)b; 
    return a1->weight > b1->weight; 
}

int KruskalMST() 
{ 
    int ver = V;
    struct Edge result[V];  // Tnis will store the resultant MST 
    int e = 0;  // An index variable, used for result[] 
    int i = 0;  // An index variable, used for sorted edges 
  
    // Step 1:  Sort all the edges in non-decreasing  
    // order of their weight. If we are not allowed to  
    // change the given graph, we can create a copy of 
    // array of edges 
    qsort(graph, E, sizeof(graph[0]), comp);
    // Allocate memory for creating V ssubsets 
    struct subset *subsets = (struct subset*) malloc(ver * sizeof(struct subset)); 
  
    // Create V subsets with single elements
    for (int v = 0; v < ver; ++v)
    {
        subsets[v].parent = v; 
        subsets[v].rank = 0; 
    }  
    // Number of edges to be taken is equal to V-1 
    while (e < ver - 1) 
    { 
        // Step 2: Pick the smallest edge. And increment  
        // the index for next iteration 
        struct Edge next_edge = graph[i++]; 
  
        int x = find(subsets, next_edge.src); 
        int y = find(subsets, next_edge.dest); 
  
        // If including this edge does't cause cycle, 
        // include it in result and increment the index  
        // of result for next edge 
        if (x != y) 
        { 
            result[e++] = next_edge; 
            Union(subsets, x, y); 
        } 
        // Else discard the next_edge 
    }
  
    // print the contents of result[] to display the 
    // built MST 
    // printf("Following are the edges in the constructed MST\n"); 
    // for (i = 0; i < e; ++i) 
    //     printf("%d -- %d == %d\n", result[i].src, result[i].dest,result[i].weight); 
    int sum=0;
    for(int i=0;i<e;++i)
      sum+=result[i].weight;

    return sum; 
}

int G[SIZE][SIZE];

int main() 
{ 
  FILE * fp = fopen("input.txt","r");
  FILE * ft = fopen("output.txt","w");
  char waste;
  fscanf(fp,"%d%c",&V,&waste);
  char c;
  int ki=0;
  for (int i=0;i<V;++i)
  {
    fscanf(fp,"%c",&c);
    if (c!='\n')
    {
      fseek(fp,-1,SEEK_CUR);
      while(1)
      {
        char ch;
        int data;
        fscanf(fp,"%d%c",&data,&ch);
        ki++;
        G[i][data] = 1;        
        if (ch=='\n')
          break;
      }
    }    
  }
  E=ki;
  for (int i=0;i<V;++i)
  {
    int count=0;
    fscanf(fp,"%c",&c);
    if (c!='\n')
    {
      fseek(fp,-1,SEEK_CUR);
      while(1)
      {
        char ch;
        int data;
        fscanf(fp,"%d%c",&data,&ch);
        while(count<V)
        {
          if (G[i][count]==1)
            break;
          else
            count++;
        }
        G[i][count] = data;
        count++;        
        if (ch=='\n')
          break;
      }
    }    
  }
  initialize_graph();
  int k =0;
  for (int i=0;i<V;++i)
    for (int j=0;j<V;++j)
      if (G[i][j]!=0)
      {
        graph[k].src = i; 
        graph[k].dest = j;
        graph[k].weight = G[i][j];
        ++k;
      }
    
    // V = 4;  // Number of vertices in graph 
    // E = 5;  // Number of edges in graph 
    // initialize_graph();
  
  
    // // add edge 0-1 
    // graph[0].src = 0; 
    // graph[0].dest = 1; 
    // graph[0].weight = 10; 
  
    // // add edge 0-2 
    // graph[1].src = 0; 
    // graph[1].dest = 2; 
    // graph[1].weight = 6; 
  
    // // add edge 0-3 
    // graph[2].src = 0; 
    // graph[2].dest = 3; 
    // graph[2].weight = 5; 
  
    // // add edge 1-3 
    // graph[3].src = 1; 
    // graph[3].dest = 3; 
    // graph[3].weight = 15; 
  
    // // add edge 2-3 
    // graph[4].src = 2; 
    // graph[4].dest = 3; 
    // graph[4].weight = 4; 
  
    int ans = KruskalMST(); 
    fprintf(ft,"%d",ans);
    fclose(fp);
    fclose(ft);  
    return 0; 
}
