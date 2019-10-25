#include <stdio.h>
#include <stdlib.h>

typedef struct Node * node;
typedef struct Item * item;

struct Item;

struct Node{
  int data;
  node next;
  item ptr;
};

struct Item{
  node head;
  node tail;
};

node arr_a[10001],arr_b[10001];

void initialize()
{
  for (int i=0;i<10001;++i)
  {  
    arr_a[i] = NULL;
    arr_b[i] = NULL;
  }
}

node newNode(int k)
{
  node temp = (node)malloc(sizeof(struct Node));
  temp->data = k;
  temp->next = NULL;
  temp->ptr = NULL;
  return temp;
}

item newItem()
{
  item temp = (item)malloc(sizeof(struct Item));
  return temp;
}

void makeset(FILE * ft,int k)
{
  if (arr_a[k]!=NULL)
  {
    fprintf(ft,"PRESENT");
    return;
  }
  fprintf(ft,"%d\n",k);

  item newset_a = newItem();
  newset_a->head = newNode(k);
  newset_a->tail = newset_a->head;
  arr_a[k] = newset_a->head;
  newset_a->head->ptr = newset_a;

  item newset_b = newItem();
  newset_b->head = newNode(k);
  newset_b->tail = newset_b->head;
  arr_b[k] = newset_b->head;
  newset_b->head->ptr = newset_b;
  
}

item find_a(int k)
{
  node temp = arr_a[k];
  if (temp==NULL)
    return NULL;
  return (temp->ptr);
}


item find_b(int k)
{
  node temp = arr_b[k];
  if (temp==NULL)
    return NULL;
  return (temp->ptr);
}

int unify_a(FILE * ft,item set1,item set2)
{
  if (set1==NULL || set2==NULL)
  {
    fprintf(ft,"ERROR");
    return -1;
  }
  else if (set1 == set2)
  {
    fprintf(ft,"%d ",set1->head->data);
    return 0;
  }
  set1->tail->next = set2->head;
  set1->tail = set2->tail;

  node temp = set2->head; 
  while (temp != NULL) 
  { 
        temp->ptr = set1; 
        temp = temp->next; 
  }
  free(set2);
  fprintf(ft,"%d ",set1->head->data);
  return 0;
}

int unify_b(FILE * ft,item set1, item set2)
{
  if (set1==NULL || set2==NULL)
  {
    fprintf(ft,"ERROR");
    return -1;
  }
  else if (set1 == set2)
  {
    fprintf(ft,"%d ",set1->head->data);
    return 0;
  }

  int l1=1,l2=1;
  node temp = set1->head;
  while (temp != set1->tail)
  {
    l1++;
    temp = temp->next;
  }
  temp = set2->head;
  while (temp != set2->tail)
  {
    l2++;
    temp = temp->next;
  }

  if (l2<l1 || (l2==l1 && set1->head->data < set2->head->data) )
  {
    set1->tail->next = set2->head;
    set1->tail = set2->tail;

    node temp = set2->head; 
    while (temp != NULL) 
    { 
        temp->ptr = set1; 
        temp = temp->next; 
    }
    free(set2);
    fprintf(ft,"%d ",set1->head->data);
  }
  else if (l2>l1 || (l2==l1 && set1->head->data >= set2->head->data))
  {
    set2->tail->next = set1->head;
    set2->tail = set1->tail;

    node temp = set1->head; 
    while (temp != NULL) 
    { 
        temp->ptr = set2; 
        temp = temp->next; 
    }
    free(set1);
    fprintf(ft,"%d ",set2->head->data);
  }
  return 0;
}

void unify(FILE * ft, int m, int n)
{
  if (find_a(m)==NULL || find_a(n) ==NULL)
  {
    fprintf(ft,"ERROR");
    return;
  }
  else
  {  
    unify_b(ft,find_b(m),find_b(n));
    unify_a(ft,find_a(m),find_a(n));
  }
}

int main(void) {
  initialize();
  FILE *fp = fopen("input.txt","r");
  FILE *ft = fopen("output.txt","w");
  // makeset(1);
  // makeset(2);
  // makeset(3);
  // makeset(4);
  // makeset(5);
  // makeset(6);
  // makeset(7);
  // makeset(8);
  // makeset(9);
  
  // unify_b(find_b(1),find_b(2));
  // unify_b(find_b(3),find_b(4));
  // unify_b(find_b(5),find_b(6));
  // unify_b(find_b(7),find_b(8));
  // unify_b(find_b(8),find_b(9));
  // //fprintf(ft,"hh %d hh",find_b(6)->head->data);
  // unify_b(find_b(6),find_b(8));
  // //fprintf(ft,"hh %d hh",find_b(6)->head->data);
  // unify_b(find_b(4),find_b(8));
  // unify_b(find_b(2),find_b(8));
  
  // fprintf(ft,"%d",find_b(6)->head->data);
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
      fprintf(ft,"\n");
    }
    else if (c=='f')
    {
      int f;
      fscanf(fp,"%d",&f);
      if (find_a(f) == NULL)
        fprintf(ft,"NOT FOUND");
      else
        fprintf(ft,"%d %d\n",find_a(f)->head->data,find_b(f)->head->data);
    }
    else if (c=='s')
    {
      return 0;
    }
  }
}
