#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

// void FinalSolution(int dist[], int n)
// {
//     // This function prints the final solution
//     printf("\nVertex\tDistance from src Vertex\n");
//     int i;
 
//     for (i = 0; i < n; ++i){
//         printf("%d \t\t %d\n", i, dist[i]);
//     }
// }
 
int BellmanFord(int src)
{
    int StoreDistance[V];
 
    int i,j;
 
    // This is initial step that we know , we initialize all distance to infinity except src.
    // We assign src distance as 0(zero)
 
    for (i = 0; i < V; i++)
        StoreDistance[i] = INT_MAX;
 
    StoreDistance[src] = 0;
 
    //The shortest path of graph that contain V vertices, never contain "V-1" edges. So we do here "V-1" relaxations
    for (i = 1; i <= V-1; i++)
    {
        for (j = 0; j < E; j++)
        {
            int u = graph[j].src;
 
            int v = graph[j].dest;
 
            int weight = graph[j].weight;
 
            if ( (StoreDistance[u]!=INT_MAX) && StoreDistance[u] + weight < StoreDistance[v] )
                StoreDistance[v] = StoreDistance[u] + weight;
        }
    }
 
    // Actually upto now shortest path found. But BellmanFord checks for negative edge cycle. In this step we check for that
    // shortest distances if graph doesn't contain negative weight cycle.
 
    // If we get a shorter path, then there is a negative edge cycle.
    for (i = 0; i < E; i++)
    {
        int u = graph[i].src;
 
        int v = graph[i].dest;
 
        int weight = graph[i].weight;
 
        if ((StoreDistance[u]!=INT_MAX) && StoreDistance[u] + weight < StoreDistance[v])
            return 1;//printf("This graph contains negative edge cycle\n");
    }
 
    //FinalSolution(StoreDistance, V);
 
    return -1;
}

int main()
{
  FILE * fp = fopen("input.txt","r");
  FILE * ft = fopen("output.txt","w");
  fscanf(fp,"%d",&V);
  fscanf(fp,"%d",&E);
  initialize_graph();
  
  for(int i=0;i<E;i++){
    fscanf(fp,"%d",&graph[i].src);
    fscanf(fp,"%d",&graph[i].dest);
    fscanf(fp,"%d",&graph[i].weight);
  }
  // graph[0].src = 0; 
  //   graph[0].dest = 1; 
  //   graph[0].weight = -1; 
  
  //   // add edge 0-2 (or A-C in above figure) 
  //   graph[1].src = 0; 
  //   graph[1].dest = 2; 
  //   graph[1].weight = 4; 
  
  //   // add edge 1-2 (or B-C in above figure) 
  //   graph[2].src = 1; 
  //   graph[2].dest = 2; 
  //   graph[2].weight = 3; 
  
  //   // add edge 1-3 (or B-D in above figure) 
  //   graph[3].src = 1; 
  //   graph[3].dest = 3; 
  //   graph[3].weight = 2; 
  
  //   // add edge 1-4 (or A-E in above figure) 
  //   graph[4].src = 1; 
  //   graph[4].dest = 4; 
  //   graph[4].weight = 2; 
  
  //   // add edge 3-2 (or D-C in above figure) 
  //   graph[5].src = 3; 
  //   graph[5].dest = 2; 
  //   graph[5].weight = 5; 
  
  //   // add edge 3-1 (or D-B in above figure) 
  //   graph[6].src = 3; 
  //   graph[6].dest = 1; 
  //   graph[6].weight = 1; 
  
  //   // add edge 4-3 (or E-D in above figure) 
  //   graph[7].src = 4; 
  //   graph[7].dest = 3; 
  //   graph[7].weight = -3;
 
  fprintf(ft,"%d",BellmanFord(0));
    //passing created graph and src vertex to BellmanFord Algorithm function
 
    return 0;
}
