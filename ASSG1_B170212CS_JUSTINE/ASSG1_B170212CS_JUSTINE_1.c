#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
FILE *fp;
FILE *fs;
struct node
{
    int data;
    struct node* next;
};
struct node* head=NULL;
void print(FILE* fs)
{
    
    struct node* temp=head;
    while(temp!=NULL)
    {
        printf("%d ",temp->data);
        fprintf(fs,"%d ",temp->data);
        temp=temp->next;
        
    }
}
void add_node(int val)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    struct node* temp2=head;
    temp->data=val;
    temp->next=NULL;
    if(head==NULL)
    {
        head=temp;
    }
    else
    {
    while(temp2->next!=NULL)
    {
        temp2=temp2->next;
    }
    temp2->next=temp;  
    }
   
}
void create(int val)
{
    int num;
    for(int i=0;i<val;i++)
    {
        fscanf(fp,"%d",&num);
        add_node(num);
    }
}
int h_occur()
{
    struct node* temp=head;
    struct node*temp2=head;
    int max=0,val,count=0,num1,num2;
    while(temp!=NULL)
    {
        while(temp2->next!=NULL)
        {
            val=temp->data;
            if(val==temp2->next->data)
            {
                count=count+1;
                num1=val;
            }
            temp2=temp2->next;
        }
        if(count>max)
        {
            max=count;
            num2=num1;
        }
        temp=temp->next;
        temp2=temp;

    }
    if(max==0)
        return head->data;
    else
        return num2;
}
void main(int argc, char const *argv[])
{
 char element;
 int num;
 fp=fopen(argv[1],"r");
 fs = fopen(argv[2],"w");
 if(fp == NULL)
    {
        printf("FILE EMPTY\n");
        
    }

    while(!feof(fp))
    {
        fscanf(fp,"%c", &element);
        switch(element)
        {
            case 'c' :
                        fscanf(fp,"%d",&num);
                        create(num);
                        break; 
            case 'p' :
                        print(fs);
                        fprintf(fs,"\n");
                        break;
            case 'h' :
                        h_occur;
                        fprintf(fs,"\n");
                        break;
            case 'a' :
                        fscanf(fp,"%d",&num);
                        add_node(num);
                        break;
            case 's' :  
                        exit(0);
                        break;
        }       
    }
}