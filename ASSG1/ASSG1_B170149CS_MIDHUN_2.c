#include <stdio.h>
#include <ctype.h>
char stack[100];
int top=-1;
void push(char c)
{
  stack[++top]=c;
}
char pop()
{
  if(top==-1)
  return -1;
  else
  return stack[top--];
}
int check(char c)
{
  if(c=='(')
  return 0;
  else if(c=='+' || c=='-')
  return 1;
  else if(c=='*' || c=='/')
  return 2;
  else 
  return 3;
}
void infixToPostfix(char str[])
{
  int i;
  char x;
  top=-1;
  FILE *f;
  f=fopen("output.txt","a");
  for(i=0;str[i]!='\0';i++)
  {
    if(isalpha(str[i]))
    fprintf(f,"%c",str[i]);
    else if(str[i]=='(')
    push(str[i]);
    else if(str[i]==')')
    {
      while((x=pop())!='(')
      fprintf(f,"%c",x);
    }
    else
    {
      if(top==-1)
      push(str[i]);
      else
      {
      while(top!=-1 && check(stack[top]) >= check(str[i]))
      fprintf(f,"%c",pop());
      push(str[i]);
      }
    }    
  }
  while(top!=-1)
  fprintf(f,"%c",pop());
  fprintf(f,"\n");
  fclose(f);  
}
void print()
{
  FILE *f;
  char str[100];
  f=fopen("output.txt","r");
  while(fscanf(f,"%s",str) != EOF)
  printf("%s\n",str);
  fclose(f);
}
int main() 
{
  //infixToPostfix("a+b");
  FILE*fp;
  char str[100];
  fp=fopen("input.txt","r");
  while(fscanf(fp,"%s",str) != EOF)
  {
    //printf("%s",str);
    infixToPostfix(str); 
  }
  print();
  return 0;
}