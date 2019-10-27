#include <stdio.h>
#include <stdlib.h>

typedef struct element * node;

struct element{
  int data;
  node parent;
  int rank;
};

node arr_a[10001],arr_b[10001],arr_c[10001],arr_d[10001];
int count_a=0,count_b=0,count_c=0,count_d=0;
void initialize()
{
  for (int i=0;i<10001;++i)
  {  
    arr_a[i] = NULL;
    arr_b[i] = NULL;
    arr_c[i] = NULL;
    arr_d[i] = NULL;
  }
}

node newNode(int k)
{
  node temp = (node)malloc(sizeof(struct element));
  temp->data = k;
  temp->parent = NULL;
  return temp;
}

void makeset(FILE * ft,int k)
{
  if (arr_a[k]!=NULL)
    fprintf(ft,"PRESENT\n");
  else
  {
    fprintf(ft,"%d\n",k);

    node temp = newNode(k);
    temp->parent = temp;
    temp->rank = 0;
    arr_a[k] = temp;

    temp = newNode(k);
    temp->parent = temp;
    temp->rank = 0;
    arr_b[k] = temp;

    temp = newNode(k);
    temp->parent = temp;
    temp->rank = 0;
    arr_c[k] = temp;

    temp = newNode(k);
    temp->parent = temp;
    temp->rank = 0;
    arr_d[k] = temp;
  }
}

node findset_a(int elem)
{ 
  node x = arr_a[elem];
  while(x != x->parent)
  { 
    count_a++;
    x = x->parent;
  }
  count_a++;
  return x;
}

int find_a(int elem)
{
  node x = arr_a[elem];
  if (x==NULL)
  {
    return -1;
  }
  while(x != x->parent)
    x = x->parent;
  return x->data;
}

node findset_b(int elem)
{ 
  node x = arr_b[elem];
  while(x != x->parent)
  { 
    count_b++;
    x = x->parent;
  }
  count_b++;
  return x;
}

int find_b(int elem)
{
  node x = arr_b[elem];
  if (x == NULL)
  {
    return -1;
  }
  while(x != x->parent)
    x = x->parent;
  return x->data;
}


node findset_c(int elem)
{ 
  count_c++;
  node x = arr_c[elem];
  if (x != x->parent)
  {
    x->parent = findset_c(x->parent->data);
  }
  //count_c++;
  return x->parent;
}

int find_c(int elem)
{
  node x = arr_c[elem];
  if (x==NULL)
  {
    return -1;
  }
  while(x != x->parent)
    x = x->parent;
  return x->data;
}


node findset_d(int elem)
{ 
  count_d++;
  node x = arr_d[elem];
  if (x != x->parent)
  {
    x->parent = findset_d(x->parent->data);
  }
  return x->parent;
}

int find_d(int elem)
{
  node x = arr_d[elem];
  if (x==NULL)
  {
    return -1;
  }
  while(x != x->parent)
    x = x->parent;
  return x->data;
}

void link_a(node x, node y)
{
  y->parent = x; 
}

void link_b(node x,node y)
{
  if (y->rank > x->rank)
    x->parent = y;
  else
  {  
    y->parent = x;
    if (y->rank == x->rank)
      x->rank = x->rank + 1;
  }
}

void unify(FILE * ft,int x,int y)
{
  if (find_a(x)==-1 || find_a(y)==-1)
  {
    fprintf(ft,"ERROR\n");
    return;
  }
  else
  {
    link_a( findset_a(x) , findset_a(y) );
    fprintf(ft,"%d ",find_a(x));
    link_b( findset_b(x) , findset_b(y) );
    fprintf(ft,"%d ",find_b(x));
    link_a( findset_c(x) , findset_c(y) );
    fprintf(ft,"%d ",find_c(x));
    link_b( findset_d(x) , findset_d(y) );
    fprintf(ft,"%d\n",find_d(x));
  }
}

int main(void) {
  FILE *fp = fopen("input.txt","r");
  FILE *ft = fopen("output.txt","w");
  // initialize();
  // makeset(1);
  // makeset(2);
  // makeset(3);
  // makeset(4);
  // makeset(5);
  // makeset(6);
  // makeset(7);
  // makeset(8);
  // makeset(9);
  // unify(1,2);
  // unify(3,4);
  // unify(5,6);
  // unify(7,8);
  // unify(9,8);
  // unify(6,8);
  // unify(4,8);
  // unify(2,8);
  // node k = findset_b(9);
  // if (k!=NULL)
  //   fprintf(ft,"%d\n",k->data);
  // else
  //   fprintf(ft,"NOT FOUND\n");
  // makeset(10);
  // unify(10,9);
  // fprintf(ft,"%d %d %d %d\n",count_a,count_b,count_c,count_d);
  char c;
  while(1)
  {
    fscanf(fp,"%c",&c);
    if (c=='m')
    {
      int m;
      fscanf(fp,"%d",&m);
      makeset(ft,m);
    }
    else if (c=='u')
    {
      int m,n;
      fscanf(fp,"%d %d",&m,&n);
      unify(ft,m,n);
    }
    else if (c=='f')
    {
      int f;
      fscanf(fp,"%d",&f);
      fprintf(ft,"%d %d %d %d\n",findset_a(f)->data,findset_b(f)->data,findset_c(f)->data,findset_d(f)->data);
    }
    else if (c=='s')
    {
      fprintf(ft,"%d %d %d %d\n",count_a,count_b,count_c,count_d);
      return 0;
    }
  }
}
