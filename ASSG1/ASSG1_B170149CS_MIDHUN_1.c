#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct linkedList
{
  int data;
  struct linkedList *next;
};
typedef struct linkedList *node;
node q=NULL,head=NULL;
node createNode(int a)
{
  node p=(node)malloc(sizeof(struct linkedList));
  p->data=a;
  p->next=NULL;
  return p;  
}
node create(FILE *fp,int n)
{
  int i,a;
  node p;
  for(i=0;i<n;i++)
  {
    fscanf(fp,"%d",&a);
    p=createNode(a);
    if(i==0)
    head=p;
    else
    q->next=p;
    q=p;
  }
}
void add_node(int a)
{
  node p=createNode(a);
  if(head==NULL)
  head=p;
  else
  q->next=p;
  q=p;
}
void h_occur(FILE *f)
{
  int max_elem, max_freq;
  max_freq = 0;
  node i,j;
  int count,check;
  for(i=head;i!=NULL;i=i->next)
  {
    count = 0;
    check=i->data;
    for(j=head;j!=NULL;j=j->next)
    {
      if (j->data == check)
        count++;
    }
    if (count>max_freq)
    {
      max_freq = count;
      max_elem = check;
    }
  }
  fprintf(f,"%d\n",max_elem);
}
void print(FILE *f)
{
  node p;
  for(p=head;p!=NULL;p=p->next)
  fprintf(f,"%d ",p->data);
  fprintf(f,"\n");
}
int main()
{
  FILE *fp,*f;
  int i,n;
  char c;
  fp=fopen("input.txt","r");
  f=fopen("output.txt","w");
  while ( fscanf(fp,"%c",&c)!=EOF )
  {
    //printf("%c",c);
    if (c=='c')
    {
      int n,p;
      fscanf(fp,"%d",&n);
      create(fp,n);
    }
    else if (c=='p')
    {
      print(f);
    }
    else if (c=='h')
    {
      h_occur(f);
    }
    else if (c=='a')
    {
      fscanf(fp,"%d",&n);
      add_node(n);
    }
    else if (c=='s')
      return 0;
  }
  fclose(fp);
  fclose(f);
}
