#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct dynamic{
  int * array[SIZE];
}arr;

void initialize(){
  int temp_size=1;

  for (int i=0;i<SIZE;++i)
  {
    arr.array[i]=(int*)malloc(temp_size*sizeof(int));
    arr.array[i][0]=-32000;
    temp_size*=2;
  }
}

int * merge(int a[],int b[],int n){
  int * c=(int*)malloc(2*n*sizeof(int));
  int i = 0;  
  int j = 0;  
  int k = 0;
  while (i < n && j < n) 
  { 
    if (a[i] <= b[j]) 
    { 
      c[k] = a[i]; 
      i++; 
    } 
    else
    { 
      c[k] = b[j]; 
      j++; 
    } 
    k++; 
  } 
  while (i < n) 
  { 
    c[k] = a[i]; 
    i++; 
    k++; 
  } 
  while (j < n) 
  { 
    c[k] = b[j]; 
    j++; 
    k++; 
  } 
  return c;
}

void insert(int num){
  int * new_array = (int*)malloc(sizeof(int));
  new_array[0]=num;
  int present_size=1;
  for (int i=0;i<SIZE;++i)
  {
    if (arr.array[i][0] == -32000)
    {
      arr.array[i] = new_array;
      break;
    }
    else
    {
      new_array = merge(arr.array[i],new_array,present_size);
      arr.array[i][0]=-32000;
      present_size*=2;
    }
  }
}

int binarySearch(int arr[], int l, int r, int key) 
{ 
    while (l <= r) { 
        int m = l + (r - l) / 2; 
        if (arr[m] == key) 
            return m; 
        
        if (arr[m] < key) 
            l = m + 1; 
        else
            r = m - 1; 
    } 
    return -1;
}

void search(FILE * ft,int key)
{
  int cur_size=1;
  int rel_size=1;
  int flag=0;
  for (int i=0;i<SIZE;++i)
  {
    if (arr.array[i][0] != -32000)
    {
      int check = binarySearch(arr.array[i],0,cur_size-1,key);
      if (check!=-1)
      {
        //fprintf(ft,"%d\n",i);

        // int var = cur_size-1 + check;
        // fprintf(ft,"%d\n",var);

        int var1 = rel_size-1 + check;
        fprintf(ft,"%d\n",var1);

        flag=1;
        break;
      }
      rel_size*=2;
    }
    cur_size*=2;
  }
  if (flag==0)
    fprintf(ft,"NIL\n");
}

void print(FILE * ft)
{
  int cur_size=1;
  for (int i=0;i<SIZE;++i)
  {
    if (arr.array[i][0] != -32000)
    {
      for(int j=0;j<cur_size;++j)
        fprintf(ft,"%d ",arr.array[i][j]);
    }
    cur_size*=2;
  }
}



int main(){
  FILE * ft = fopen("output.txt","w");
  FILE * fp =fopen("input.txt","r");
  initialize();
  // for (int i=1;i<18;++i)
  //   insert(i);
  // print();
  // fprintf(ft,"\n");
  // search(13);
  char c;
  while(1)
  {
    fscanf(fp,"%c",&c);
    if (c=='i')
    {
      int n;
      fscanf(fp,"%d",&n);
      insert(n);
    }
    else if(c=='s')
    {
      int n;
      fscanf(fp,"%d",&n);
      search(ft,n);
    }
    else if (c=='p')
    {
      print(ft);
      fprintf(ft,"\n");
    }
    else if(c=='x')
    {
      break;
    }
  }
  return 0;
}
