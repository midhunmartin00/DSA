#include <stdio.h>
#include <stdlib.h>

//Linear Probing
void insert_linear(int key,int hashTable[],int m)
{
  int i=1;
  int index = key%m;
  while(hashTable[index] != 0 && hashTable[index] != -1)
  {
    index = (++index)%m;
    ++i;
  }
  hashTable[index]=key;
}

void delete_linear(int key,int hashTable[],int m)
{
  int i=1;
  int index = key%m;
  while(hashTable[index] != key)
  {
    index = (++index)%m;
    ++i;
  }
  hashTable[index]=-1;
}

int search_linear(int key,int hashTable[],int m)
{ 
  int i=1;
  int index = key%m;
  while(i<m)
  {
    if(hashTable[index] == 0)
      return -1;
    else if(hashTable[index] == key)
      return 1;
    else 
    {
      index = (++index)%m;
      ++i;
    }
  }
  return -1;
}

//Quadratic Probing

void insert_quad(int key,int hashTable[],int m,int c1,int c2)
{
  int i=1;
  int index = key%m;
  int org = index;
  while(hashTable[index] != 0 && hashTable[index] != -1)
  {
    index = (org + c1*i + c2*i*i)%m;
    ++i;
  }
  hashTable[index]=key;
}

void delete_quad(int key,int hashTable[],int m,int c1,int c2)
{
  int i=1;
  int index = key%m;
  int org = index;
  while(hashTable[index] != key)
  {
    index = (org + c1*i + c2*i*i)%m;
    ++i;
  }
  hashTable[index]=-1;
}

int search_quad(int key,int hashTable[],int m,int c1,int c2)
{ 
  int i=1;
  int index = key%m;
  int org = index;
  while(i<m)
  {
    if(hashTable[index] == 0)
      return -1;
    else if(hashTable[index] == key)
      return 1;
    else 
    {
      index = (org + c1*i + c2*i*i)%m;
      ++i;
    }
  }
  return -1;
}

//Double hashing
int primeNumber(int m)
{
  for(int i=m-1;i>1;--i)
  {
    int flag = 0;
    for (int j=2;j<(i/2);++j)
    {
      if (i%j==0)
        flag++;
    }
    if (flag==0)
      return i;
  }
}

void insert_double(int key,int hashTable[],int m,int r)
{
  int i=1;
  int index = key%m;
  int org = index;
  while(hashTable[index] != 0 && hashTable[index] != -1)
  {
    index = (org + r*i)%m;
    ++i;
  }
  hashTable[index]=key;
}

void delete_double(int key,int hashTable[],int m,int r)
{
  int i=1;
  int index = key%m;
  int org = index;
  while(hashTable[index] != key)
  {
    index = (org + r*i)%m;
    ++i;
  }
  hashTable[index]=-1;
}

int search_double(int key,int hashTable[],int m,int r)
{ 
  int i=1;
  int index = key%m;
  int org = index;
  while(i<m)
  {
    if(hashTable[index] == 0)
      return -1;
    else if(hashTable[index] == key)
      return 1;
    else 
    {
      index = (org + r*i)%m;
      ++i;
    }
  }
  return -1;
}

// Print function for Linear,Probing,Quadratic probing , double hashing

void print(int hashTable[],int m,FILE *ft)
{
  for (int i=0;i<m;++i)
  {
    if (hashTable[i] == 0 || hashTable[i] == -1)
      fprintf(ft,"%d()\n",i);
    else
      fprintf(ft,"%d(%d)\n",i,hashTable[i]);
  }
}

//Chaining

typedef struct linkedlist * node;

struct linkedlist{
  int data;
  node next;
};

node newNode(){
  node temp = (node)malloc(sizeof(struct linkedlist));
  temp->data=0;
  temp->next=NULL;
  return temp;
}

void insert_chain(node hashTable[] , int key, int m)
{
  int index = key%m;
    node temp = hashTable[index];
    if( temp->data == 0)
    {
      temp->data = key;
    }
    else
    {
      node new_data = newNode();
      new_data->data = key;

      node temp = hashTable[index];
      while (temp->next!=NULL)
      {
        temp = temp->next;
      }
      temp->next = new_data;
    }
}

void print_chain(node hashTable[],int m,FILE *ft)
{
  for (int i=0;i<m;++i)
  {  
    node temp = hashTable[i];
    fprintf(ft,"%d(",i);
    if (temp->data!=0 && temp!=NULL)
    {
      fprintf(ft,"%d",temp->data);
      temp=temp->next;
    }
    while(temp!=NULL && temp->data!=0)
    {
      fprintf(ft," %d",temp->data);
      temp = temp->next;
    }
    fprintf(ft,")\n");
  }
}

void delete_chain(node hashTable[],int key,int m)
{
  int index = key%m;
  node temp = hashTable[index];
  if (temp->data == key)
  {
    if (temp->next == NULL)
      temp->data = 0;
    else
    {
      hashTable[index] = temp->next;
      free(temp);
    }
  }
  else
  {
    while(temp->next->data != key)
    {
      temp = temp->next;
    }
    node temp2 = temp->next;
    temp->next = temp2->next;
    free(temp2);
  }
}


int search_chain(node hashTable[],int key,int m)
{
  int index = key%m;
  node temp = hashTable[index];
  while(temp != NULL)
  {
    if (temp->data == key)
      return 1;
    temp = temp->next;
  }
  return -1;
}

int main(void) {
  FILE *fp = fopen("input.txt","r");
  FILE *ft = fopen("output.txt","w");
  char c;
  fscanf(fp,"%c",&c);
  int m;
  fscanf(fp,"%d",&m);
  if (c=='a')
  {
    int hashTable[m];
    for (int i=0;i<m;++i)
      hashTable[i] = 0;
    while(1)
    {
      char ch;
      fscanf(fp,"%c",&ch);
      if (ch == 'i')
      {
        int key;
        fscanf(fp,"%d",&key);
        insert_linear(key,hashTable,m);
      }
      else if (ch == 's')
      {
        int key;
        fscanf(fp,"%d",&key);
        int k= search_linear(key,hashTable,m);
        fprintf(ft,"%d\n",k);
      }
      else if (ch == 'd')
      {
        int key;
        fscanf(fp,"%d",&key);
        delete_linear(key,hashTable,m);
      }
      else if (ch == 'p')
        print(hashTable,m,ft);
      else if (ch == 't')
        break;
    }
  }
  else if (c=='b')
  {
    int hashTable[m];
    for (int i=0;i<m;++i)
      hashTable[i] = 0;
    while(1)
    {
      int c1,c2;
      fscanf(fp,"%d%d",&c1,&c2);
      char ch;
      fscanf(fp,"%c",&ch);
      if (ch == 'i')
      {
        int key;
        fscanf(fp,"%d",&key);
        insert_quad(key,hashTable,m,c1,c2);
      }
      else if (ch == 's')
      {
        int key;
        fscanf(fp,"%d",&key);
        int k= search_quad(key,hashTable,m,c1,c2);
        fprintf(ft,"%d\n",k);
      }
      else if (ch == 'd')
      {
        int key;
        fscanf(fp,"%d",&key);
        delete_quad(key,hashTable,m,c1,c2);
      }
      else if (ch == 'p')
        print(hashTable,m,ft);
      else if (ch == 't')
        break;
    }
  }
  else if (c=='c')
  {
    
    int hashTable[m];
    for (int i=0;i<m;++i)
      hashTable[i] = 0;
    while(1)
    {
      int p;
      p = primeNumber(m);
      char ch;
      fscanf(fp,"%c",&ch);
      if (ch == 'i')
      {
        int key;
        fscanf(fp,"%d",&key);
        int r = p - (key%p);
        insert_double(key,hashTable,m,r);
      }
      else if (ch == 's')
      {
        int key;
        fscanf(fp,"%d",&key);
        int r = p - (key%p);
        int k= search_double(key,hashTable,m,r);
        fprintf(ft,"%d\n",k);
      }
      else if (ch == 'd')
      {
        int key;
        fscanf(fp,"%d",&key);
        int r = p - (key%p);
        delete_double(key,hashTable,m,r);
      }
      else if (ch == 'p')
        print(hashTable,m,ft);
      else if (ch == 't')
        break;
    }
  }
  else if (c=='d')
  {
    node hashTable[m];
    for (int i=0;i<m;++i)
    {  
      node data = newNode();
      hashTable[i] = data;
    }
    while(1)
    {
      char ch;
      fscanf(fp,"%c",&ch);
      if (ch == 'i')
      {
        int key;
        fscanf(fp,"%d",&key);
        insert_chain(hashTable,key,m);
      }
      else if (ch == 's')
      {
        int key;
        fscanf(fp,"%d",&key);
        int k= search_chain(hashTable,key,m);
        fprintf(ft,"%d\n",k);
      }
      else if (ch == 'd')
      {
        int key;
        fscanf(fp,"%d",&key);
        delete_chain(hashTable,key,m);
      }
      else if (ch == 'p')
        print_chain(hashTable,m,ft);
      else if (ch == 't')
        break;
    }
  } 
  
}
