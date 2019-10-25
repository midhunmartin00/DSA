#include <stdio.h>
#include <stdlib.h>

int m = 1023;
int hashTable[1023];


//Linear Probing
void store(int key,int value)
{
  int i=1;
  int index = key%m;
  while(hashTable[index] != 0 && hashTable[index] != -1)
  {
    index = (++index)%m;
    ++i;
  }
  hashTable[index]=value;
}

int search_linear(int key,int value)
{ 
  int i=1;
  int index = key%m;
  while(i<m)
  {
    if(hashTable[index] == 0)
      return 0;
    else if(hashTable[index] == value)
      return 1;
    else 
    {
      index = (++index)%m;
      ++i;
    }
  }
  return 0;
}

void print(int arr[][2],int n,FILE * ft)
{
  for (int i=0;i<n;++i)
  {
    int first = arr[i][0];
    int sec = arr[i][1];
    if (search_linear(sec,first))
      fprintf(ft,"(%d,%d)\n",sec,first);
    else
      store(first,sec);
  }
}

int main()
{
  FILE * fp = fopen("input.txt","r");
  FILE * ft = fopen("output.txt","w");
  int arr[1000][2];
  int n=0;
  while (1)
  {
    char c;
    fscanf(fp,"%c",&c);
    if (c=='s')
    {
      int first,sec;
      fscanf(fp," (%d, %d)",&first,&sec);
      arr[n][0] = first;
      arr[n][1] = sec;
      ++n;
    } 
    else if (c=='p')
    {
      print(arr,n,ft);
    }
    else if(c=='e')
    {
      return 0;
    }
  }
}
