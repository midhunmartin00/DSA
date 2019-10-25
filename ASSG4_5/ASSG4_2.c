#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define SIZE 100

int n_vertices;
int G[SIZE][SIZE];

void initialize()
{
   for(int i=0;i<SIZE;i++)
    for(int j=0;j<SIZE;j++)
      G[i][j]=0;
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

int dijkstra(int start, int end)
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
        { // Update distance[v] only if is not in check_set, there is an edge from u to v, and total weight of path from src to  v through u issmaller than current value of distance[v] 
       	if (!check_set[v] && G[u][v] && distance[u] != INT_MAX && distance[u]+G[u][v] < distance[v])
            distance[v] = distance[u] + G[u][v];
        }
     }

    //printf("%d\n",distance[end]);
    return distance[end];
}

int main(void) {
  FILE * fp = fopen("input.txt","r");

  FILE * ft = fopen("output.txt","w");
  initialize();
  char waste;
  fscanf(fp,"%d%c",&n_vertices,&waste);
  char c;
  for (int i=0;i<n_vertices;++i)
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
        G[i][data] = 1;        
        if (ch=='\n')
          break;
      }
    }    
  }
  for (int i=0;i<n_vertices;++i)
  {
    fscanf(fp,"%c",&c);
    if (c!='\n')
    {
      int counter=0;
      fseek(fp,-1,SEEK_CUR);
      while(1)
      {
        char ch;
        int data;
        fscanf(fp,"%d%c",&data,&ch);
        while(counter<n_vertices)
        {
          if (G[i][counter]==1)
          { 
            G[i][counter] = data;
            counter++;
            break;
          }
          counter++;
        }       
        if (ch=='\n')
          break;
      }
    }
  }
  //for(int i=0;i<n_vertices;++i)
	//{for(int j=0;j<n_vertices;++j)
	//	printf("%d ",G[i][j]);
	//printf("\n");}
  while(1)
  {
    char che[4];
    int start,end;
    char ch = fscanf(fp,"%s",che);
    if (ch==EOF)
      break;
    if (che[0] == 'a')
    {
      int src;
      fscanf(fp,"%d",&src);
      for(int i=0;i<n_vertices;++i)
      {  
        int ans = dijkstra(src,i);
        if (ans==INT_MAX)
          fprintf(ft,"INF ");
        else fprintf(ft,"%d ",ans);
      }
      fprintf(ft,"\n");
    }
    else if (che[1]=='s')
    {
      int st,end;
      fscanf(fp,"%d%d",&st,&end);
      int ans = dijkstra(st,end);
      if (ans==INT_MAX)
        fprintf(ft,"UNREACHABLE\n");
      else
        fprintf(ft,"%d\n",ans);
    }
    else if (che[1]=='t')
      break;
  }
  // // Print adjacency matrix
  // for(int i=0;i<n_vertices;i++)
  //      {
  //        for(int j=0;j<n_vertices;j++)
  //        printf("%d ",G[i][j]);
  //         printf("\n");
  //      }
  // dijkstra(0,6);
  // dijkstra(0,7);
  // dijkstra(5,6);
  // dijkstra(8,7);
  fclose(fp);
  fclose(ft);
  return 0;
}
