#include <stdio.h>
#include <stdlib.h>

struct dynamic{
  int * array;
  int cur_size;
  int max_size;
};

typedef struct dynamic * node;

void initialize(node arr)
{
  arr->max_size=1;
  arr->array= (int*)calloc(1,sizeof(int));
  arr->cur_size=0;
}

void append(node arr,int num)
{
  if(arr->cur_size == arr->max_size)
  {
    arr->max_size*=2;
    arr->array = (int*)realloc(arr->array,arr->max_size*sizeof(int));
  }
  arr->array[arr->cur_size]=num;
  arr->cur_size++;
}

void print(FILE * ft,node arr)
{
  fprintf(ft,"(");
  int i;
  for (i=0;i<(arr->cur_size - 1);++i)
  {
    fprintf(ft,"%d ",arr->array[i]);
  }
  fprintf(ft,"%d)",arr->array[i]);
}

int member(node arr,int x)
{
  for (int i=0;i<arr->cur_size;++i)
  {
    if(arr->array[i] == x)
      return 1;
  }
  return 0;
}

int length(node arr)
{
  return arr->cur_size;
}

void slice(FILE * ft,node arr,int a, int b){
  for (int i=a-1;i<b;++i)
  {
    fprintf(ft,"%d ",arr->array[i]);
  }
}

void concatenate(node a, node b)
{
  int size=b->cur_size;
  for(int i=0;i<size;++i)
  {
    append(a,b->array[i]);
  }
}

int main(void) {
  int num;
  char c;
  FILE * fp = fopen("input.txt","r");
  FILE * ft = fopen("output.txt","w");
  // struct dynamic arr1,arr2;
  // initialize(&arr1);
  // initialize(&arr2);
  while(1)
  {
    fscanf(fp,"%c",&c);
    if (c == 'a')
    {
      struct dynamic arr;
      initialize(&arr);
      char cc;
      fscanf(fp," (");
      while(1)
      {
        fscanf(fp,"%d%c",&num,&cc);
        append(&arr,num);
        if (cc == ')')
        {
          break;
        }
      }
      fscanf(fp,"%d\n",&num);
      append(&arr,num);
      print(ft,&arr);
      fprintf(ft,"\n");
    }
    else if(c== 'c')
    {
      struct dynamic arr1,arr2;
      initialize(&arr1);
      initialize(&arr2);
      char cc;
      fscanf(fp," (");
      while(1)
      {
        fscanf(fp,"%d%c",&num,&cc);
        append(&arr1,num);
        if (cc == ')')
        {
          break;
        }
      }

      fscanf(fp," (");
      while(1)
      {
        fscanf(fp,"%d%c",&num,&cc);
        append(&arr2,num);
        if (cc == ')')
        {
          fscanf(fp,"\n");
          break;
        }
      }
      concatenate(&arr1,&arr2);
      print(ft,&arr1);
      fprintf(ft,"\n");
    }
    else if (c=='m')
    {
      struct dynamic arr3;
      initialize(&arr3);
      char cc;
      fscanf(fp," (");
      while(1)
      {
        fscanf(fp,"%d%c",&num,&cc);
        append(&arr3,num);
        if (cc == ')')
        {
          break;
        }
      }
      fscanf(fp,"%d\n",&num);
      fprintf(ft,"%d\n",member(&arr3,num));
    }
    else if (c=='l')
    {
      struct dynamic arr4;
      initialize(&arr4);
      char cc;
      fscanf(fp," (");
      while(1)
      {
        fscanf(fp,"%d%c",&num,&cc);
        append(&arr4,num);
        if (cc == ')')
        {
          fscanf(fp,"\n");
          break;
        }
      }
      fprintf(ft,"%d\n",length(&arr4));
    }
    else if (c=='s')
    {
      struct dynamic arr5;
      initialize(&arr5);
      char cc;
      fscanf(fp," (");
      while(1)
      {
        fscanf(fp,"%d%c",&num,&cc);
        append(&arr5,num);
        if (cc == ')')
        {
          break;
        }
      }
      int a,b;
      fscanf(fp,"%d%d\n",&a,&b);
      slice(ft,&arr5,a,b);
      fprintf(ft,"\n");
    }
    else if(c=='x')
      break;
  }
  return 0;
}
