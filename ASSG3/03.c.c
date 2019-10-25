#include <stdio.h>
#include <stdlib.h>

typedef struct Node * node; 


struct Node{
  int data;
  int deg;
  node parent,child,sibling;
};

node root=NULL;

node newNode(int key){
  node temp = (node)malloc(sizeof(struct Node));
  temp->child = temp->parent = temp->sibling = NULL;
  temp->deg = 0;
  temp->data = key;
  return temp;
}

void link(node y, node z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->deg = z->deg + 1;
}

node unify(node heap, node h)
{

  node heap1 = heap;
  node heap2 = h;
  node new_heap;
  node final_heap;
 
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
    if (heap1==NULL)
      new_heap = heap2;
    else
      new_heap = heap1;
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
  //node H = new_heap;
  //Code for arranging after merged
  node prev_x,next_x,x;
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

node insert(node heap,int key){
  node h = newNode(key);
  if (heap==NULL)
    return h;
  heap = unify(heap,h);
  return heap;
}

void revertList(node h) 
{ 
    if (h->sibling != NULL) 
    { 
        revertList(h->sibling); 
        (h->sibling)->sibling = h; 
    } 
    else
        root = h; 
}

node extractMin(node heap_root) 
{ 
    node h = heap_root;
    if (h == NULL) 
       return NULL; 
  
    node min_node_prev = NULL; 
    node min_node = h; 
  
    // Find minimum value 
    int min = h->data; 
    node curr = h; 

    while (curr->sibling != NULL) 
    { 
        if ((curr->sibling)->data < min) 
        { 
            min = (curr->sibling)->data; 
            min_node_prev = curr; 
            min_node = curr->sibling; 
        } 
        curr = curr->sibling; 
    } 
  
    // If there is a single Node 
    if (min_node_prev == NULL && min_node->sibling == NULL)
        h = NULL; 
    else if (min_node_prev == NULL) 
        h = min_node->sibling; 
    // Remove min node from list 
    else
        min_node_prev->sibling = min_node->sibling; 
  
    // Set root (which is global) as children 
    // list of min node 
    if (min_node->child != NULL) 
    { 
        revertList(min_node->child); 
        (min_node->child)->sibling = NULL; 
    } 
  
     
    return unify(root,h); 
}

int getmaxdegree(node h){
  node temp = h;
  while(temp->sibling)
  {
    temp=temp->sibling;
  }
  return temp->deg;
}

void display_siblings(FILE * ft,node h) 
{ 
  if (h==NULL)
    return;
//Print present level
  node temp = h;
  while(temp)
  {
        fprintf(ft,"%d ",temp->data);
        temp = temp->sibling;
  }
}

void display(FILE * ft,node h)
{
  if (h==NULL)
    return;
  node temp = h;
  while(temp)
  {
    display_siblings(ft,temp->child);
    temp = temp->sibling;
  }

  temp = h;
  while(temp)
  {
    display(ft,temp->child);
    temp = temp->sibling;
  } 
}
 
node minimum(node h){
  int min = h->data; 
  node curr = h; 
  node min_node;
    while (curr->sibling != NULL) 
    { 
        if ((curr->sibling)->data < min) 
        { 
            min = (curr->sibling)->data;  
            min_node = curr->sibling; 
        } 
        curr = curr->sibling; 
    }
  return min_node; 
}


node find(node heap,int key)
{
  if (heap==NULL)
    return NULL;
  
  if (heap->data == key)
    return heap;

  node found=find(heap->child,key);
  if (found!=NULL)
    return found;
  
  return find(heap->sibling,key);
}


void decrease(node root, int key, int new_value){
  node h = find(root,key);
  if (h==NULL)
    return;
  
  h->data = new_value;
  node parent = h->parent;

  while(parent!=NULL && h->data < parent->data)
  {
    int temp = parent->data;
    parent->data = h->data;
    h->data = temp;
    h = parent;
    parent = parent->parent;
  }

}

node delete(node root,int key)
{
  node temp = find(root,key);

  if (temp==NULL)
    return root;

  decrease(root,key,-32000);

  return extractMin(root);
}


int main(void) {
  // fprintf(ft,"Hello World\n");

  // root = insert(root,10);
  // root = insert(root,20);
  // root = insert(root,30);
  // root = insert(root,40);
  // root = insert(root,50);
  // root = insert(root,7);
  // root = insert(root,8);
  // root = insert(root,9);
  // root = insert(root,10);
  // root = insert(root,11);
  // root = insert(root,12);
  // root = extractMin(root);
  // display_siblings(root);
  // display(root);
  //fprintf(ft,"%d \n",getmaxdegree(root));
  //fprintf(ft,"%d",root->sibling->child->child->child->data);
  FILE * ft = fopen("output.txt","w");
  FILE * fp = fopen("input.txt","r");
  char c;
  while(1)
  {
    fscanf(fp,"%c",&c);
    if (c=='i')
    {
      int num;
      fscanf(fp,"%d",&num);
      root=insert(root, num);
    }
    else if (c=='d')
    {
      int num;
      fscanf(fp,"%d",&num);
      root=delete(root, num);
    }
    else if (c=='m')
    {
      node min=minimum(root);
      fprintf(ft,"%d\n",min->data);
    }
    else if (c=='p')
    {
      display_siblings(ft,root);
      display(ft,root);
      fprintf(ft,"\n");
    }
    else if (c=='x')
    {
      root = extractMin(root);
    }
    else if (c=='s')
    {
      return 0;
    }
  }
  return 0;
}
