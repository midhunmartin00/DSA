#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100
typedef struct Node * node;
typedef struct HeapNode * h_node;

struct Node{
  int dest;
  int weight;
  node next;
};

struct list { 
    node head; 
};

int v;
struct list * graph;
int G[SIZE][SIZE];

void initialize_graph(){
  graph = (struct list *)malloc(v*sizeof(struct list));
  for(int i=0;i<v;++i)
  {
    graph[i].head=NULL;
  }
}

node newNode(int dest,int weight)
{ 
   node temp = (node)malloc(sizeof(struct Node)); 
   temp->weight = weight;
   temp->dest = dest;
   temp->next = NULL;
   return temp;
}


void addEdge(int src, int dest, int weight) 
{ 
    // // Add an edge from src to dest.  A new node is added to the adjacency 
    // // list of src.  The node is added at the begining 
    // int c=1;
    // while(c--)
    // {
    //   node new1 = newNode(dest,weight);
    //   node temp = graph[src].head;
    //   if (temp==NULL)
    //   {
    //     graph[src].head = new1;
    //     break;
    //   }
    //   while(temp->next!=NULL)
    //     temp=temp->next;
    //   temp->next = new1;
    // }
  
    // // Since graph is undirected, add an edge from dest to src also 
    // node new2 = newNode(src,weight);
    // node temp2 = graph[dest].head;
    // if (temp2==NULL)
    // {
    //   graph[dest].head = new2;
    //   return;
    // }
    // while(temp2->next!=NULL)
    //   temp2=temp2->next;
    // temp2->next = new2;  
    node newhNode = newNode(dest, weight); 
    newhNode->next = graph[src].head; 
    graph[src].head = newhNode; 
  
    // Since graph is undirected, add an edge from dest to src also 
    newhNode = newNode(src, weight); 
    newhNode->next = graph[dest].head; 
    graph[dest].head = newhNode; 
}

struct HeapNode { 
    int v; 
    int key; 
};

int heap_size;
int pos[SIZE];
h_node * arr;

h_node newHeapNode(int v, int key) 
{ 
  h_node temp = (h_node)malloc(sizeof(struct HeapNode)); 
  temp->v = v; 
  temp->key = key; 
  return temp; 
}

void initialize_heap(){
  heap_size = 0;
  arr = (h_node*)malloc(SIZE * sizeof(h_node));
}

void minHeapify(int i)
{ 
    int smallest, left, right; 
    smallest = i; 
    left = 2*i + 1; 
    right = 2*i + 2; 
  
    if (left < heap_size && arr[left]->key < arr[smallest]->key) 
        smallest = left; 
    if (right < heap_size && arr[right]->key < arr[smallest]->key) 
        smallest = right; 
    if (smallest != i) { 
        // The nodes to be swapped in min heap 
        h_node s_node = arr[smallest]; 
        h_node i_node = arr[i]; 
        // Swap positions 
        pos[s_node->v] = i; 
        pos[i_node->v] = smallest;
        // Swap nodes 
        h_node t = arr[smallest];
        arr[smallest] = arr[i]; 
        arr[i] = t;
  
        minHeapify(smallest); 
    } 
}

// A utility function to check if the given minHeap is ampty or not 
int checkEmptyHeap() 
{ 
    if (heap_size == 0)
      return 1;
    return 0; 
} 
  
// Standard function to extract minimum node from heap 
h_node extractMin() 
{ 
    if (checkEmptyHeap()) 
        return NULL; 
    // Store the root node 
    h_node root = arr[0]; 
  
    // Replace root node with last node 
    h_node lastNode = arr[heap_size - 1]; 
    arr[0] = lastNode; 
  
    // Update position of last node 
    pos[root->v] = heap_size - 1; 
    pos[lastNode->v] = 0; 
  
    // Reduce heap size and heapify root 
    --heap_size; 
    minHeapify(0); 
  
    return root; 
} 
  
// uses pos[] of min heap to get the current index of node in min heap 
void decreaseKey(int v, int key) 
{ 
    // Get the index of v in  heap array 
    int i = pos[v];
  
    // Get the node and update its key value 
    arr[i]->key = key; 
  
    // Travel up while the complete tree is not hepified. 
    // This is a O(Logn) loop 
    while (i && arr[i]->key < arr[(i - 1) / 2]->key) { 
        // Swap this node with its parent 
        pos[arr[i]->v] = (i - 1) / 2; 
        pos[arr[(i - 1) / 2]->v] = i; 
        //Swapping
        h_node t = arr[i];
        arr[i] = arr[(i - 1) / 2];
        arr[(i - 1) / 2] = t;
        // move to parent index 
        i = (i - 1) / 2; 
    } 
} 

int isInMinHeap(int v) 
{ 
    return (pos[v] < heap_size);
}


void printArr(FILE * ft,int arr[]) 
{ 
    int sum=0;
    for (int i = 1; i < v; ++i) 
        sum+=G[arr[i]][i];//printf("%d - %d\n", arr[i], i); 
    fprintf(ft,"%d",sum);
}

void PrimMST(FILE * ft)
{ 
     
    int parent[v]; // Array to store constructed MST 
    int key[v]; // Key values used to pick minimum weight edge in cut 
  
    // minHeap represents set E 
    initialize_heap();
  
    // Initialize min heap with all vertices. Key value of 
    // all vertices (except 0th vertex) is initially infinite 
    for (int i = 1; i < v; ++i) { 
        parent[i] = -1; 
        key[i] = INT_MAX; 
        arr[i] = newHeapNode(i, key[i]); 
        pos[i] = i;
    }
  
    // Make key value of 0th vertex as 0 so that it 
    // is extracted first
    key[0] = 0; 
    arr[0] = newHeapNode(0, key[0]); 
    pos[0] = 0; 
  
    // Initially size of min heap is equal to V 
    heap_size = v; 
  
    // In the followin loop, min heap contains all nodes 
    // not yet added to MST. 
    while (!checkEmptyHeap()) { 
        // Extract the vertex with minimum key value 
        h_node min = extractMin(); 
        int u = min->v; // Store the extracted vertex number 

        // Traverse through all adjacent vertices of u (the extracted 
        // vertex) and update their key values 
        node temp = graph[u].head;
        while (temp != NULL) { 
            int d = temp->dest; 
            // If v is not yet included in MST and weight of u-v is 
            // less than key value of v, then update key value and 
            // parent of v 
            if (isInMinHeap(d) && temp->weight < key[d]){ 
                key[d] = temp->weight; 
                parent[d] = u; 
                decreaseKey(d, key[d]); 
            }
            temp = temp->next;
        }
    }

    printArr(ft,parent); 
} 

int G[SIZE][SIZE];

int main(void) {
  FILE * fp = fopen("input.txt","r");
  FILE * ft = fopen("output.txt","w");
  char waste;
  fscanf(fp,"%d%c",&v,&waste);
  char c;
  for (int i=0;i<v;++i)
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
  for (int i=0;i<v;++i)
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
        while(count<v)
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
  // scanf("%d",&v);
  // v = 9;
  initialize_graph();

  for (int i=0;i<v;++i)
    for (int j=0;j<v;++j)
      if (G[i][j]!=0)
        addEdge(i,j,G[i][j]);
  // addEdge(0, 1, 4); 
  // addEdge(0, 7, 8);
  // addEdge(1, 2, 8);
  // addEdge(1, 7, 11); 
  // addEdge(2, 3, 7); 
  // addEdge(2, 8, 2); 
  // addEdge(2, 5, 4); 
  // addEdge(3, 4, 9); 
  // addEdge(3, 5, 14); 
  // addEdge(4, 5, 10); 
  // addEdge(5, 6, 2); 
  // addEdge(6, 7, 1); 
  // addEdge(6, 8, 6); 
  // addEdge(7, 8, 7); 
  PrimMST(ft);
  return 0;
}
