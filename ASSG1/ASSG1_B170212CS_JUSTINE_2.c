#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
FILE *fs;
FILE *fp;
struct node
{
    char data;
    struct node *next;
};
struct node* top=NULL;
void push(char val)
{
    struct node* head=(struct node*)malloc(sizeof(struct node));
    head->data=val;
    head->next=top;
    top=head;
}
void pop()
{
    struct node* temp=top;
    top=top->next;
    free(temp);
}
int weight(char operator)
{
    int mass=0;
    if(operator=='*'||operator=='/')
        mass= 2;
    if(operator=='+'||operator=='-')
        mass=1;
    if(operator=='^')
        mass=3;
    return mass;
}
int priority(char p,char q)
{
    int weight1=weight(p);
    int weight2=weight(q);
    if(weight1>weight2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void infixToPostfix(char *str,FILE *fs)
{
    //create a stack-- done
    
    int len=strlen(str);
    int j=0;
    char final[len];//empty string
    //loop
    for(int i=0;i<len-1;i++)
    {
        //if str[i] is operand ie; a,b,c etc..
        //put it to final string
        if(str[i]==' ' || str[i]=='\n')
        {
            continue;
        }
        else if(str[i]=='(')
        {
             push(str[i]);
        }
        else if(str[i]=='*'||str[i]=='+'||str[i]=='/'||str[i]=='-'||str[i]=='^')
        {
            while(top!=NULL && top->data!='('&& priority(top->data,str[i]))
             {
                  final[j]=top->data;
                  pop(top->data);
                  j++;
                  
             }
                  
            push(str[i]);
        }
        else if(str[i]==')')
         {
            while(top!=NULL && top->data !=  '(') 
            {
				final[j]=top->data;
				pop();
                j++;
                
			}
            pop(); 
         }
        else
        {
            final[j]=str[i];
            j++;
        }
        
    }
    while(top!=NULL)
    {
        final[j]=top->data;
        pop();
        j++;
    }
    final[j]='\0';
    printf("%s \n",final);
    fprintf(fs,"%s",final);
    fprintf(fs,"\n");
}
void main(int argc,char* argv[])
{
    char *str=NULL;
    size_t len=0;
    size_t strlength;
    fp=fopen(argv[1],"r");
    fs=fopen(argv[2],"a");
    //printf("%s",argv[1]);
    while(!feof(fp))
    {
        
    strlength=getline(&str,&len,fp);
    // printf("%s ",str);
    infixToPostfix(str,fs);
       

    }

}
