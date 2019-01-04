#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
FILE* fp;
FILE* fs;
struct node
{
    int data;
    struct node *next;
};
struct node* top=NULL;
void push(int val)
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
int isOperand(char op)
{
    if(op=='+'||op=='-'||op=='*'||op=='/'||op=='^')
    {
        return 1;
    }
    else 
        return 0;


}
void evaluatePostfix(char *str,FILE *fp)
{
    int len=strlen(str);
    int data1,data2,new;
    int k=0;
    for(int i=0;i<len-1;i++)
    {
        //printf("%c ..",str[i]);
        if(str[i]==' ')
        {
            printf("%d is k...",k);
            push(k);
            k=0;
            continue;
        }
        else if(isOperand(str[i]))
        {
            
            switch (str[i])
            {
                case '+':
                    data1=top->data;
                    pop();
                    data2=top->data;
                    pop();
                    new=data1+data2;
                    push(new);
                    break;
                case '-':
                    data1=top->data;
                    pop();
                    data2=top->data;
                    pop();
                    new=data2-data1;
                    push(new);
                    break;
                case '*':
                    data1=top->data;
                    pop();
                    data2=top->data;
                    pop();
                    new=data1*data2;
                    push(new);
                    break;
                case '/':
                    data1=top->data;
                    pop();
                    data2=top->data;
                    pop();
                    new=data2/data1;
                    push(new);
                    break;
                case '^':
                    data1=top->data;
                    pop();
                    data2=top->data;
                    pop();
                    new=pow(data2,data1);
                    push(new);
                    break;
                default:
                    break;
            }
            i++;
        }
        else if(str[i]>0)
        {
           // printf("before type casting ..%c \n",str[i]);
            int data=(int)str[i]-48;
            k=k*10+data;
            //printf("the push is after--  %d --\n",data);
        }
    }
    int output=top->data;
    printf("output is : %d",output);
    fprintf(fp,"%d",output);
    
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
    //printf("%s is string ...",str);
    evaluatePostfix(str,fs);    
    }

}
