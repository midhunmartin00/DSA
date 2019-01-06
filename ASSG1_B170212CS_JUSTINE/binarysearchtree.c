#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node* left;
    struct node* right;
   
};
struct node* newnode(int data)
{
    struct node *newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
    
}

struct node* insert(struct node* root,int data)
{
    if(root==NULL)
    {
        root=newnode(data);
    }
    else if(data<=root->data)
    {
       root->left= insert(root->left,data);   
    }
    else if(data>=root->data)
    {
        root->right= insert(root->right,data); 
    }
    return root;
}
int search(struct node* root,int data)
{
    if(root==NULL)
    {
        return -1;       
    }
    else if(data==root->data)
    {
        return 1;
    }
    else if(data<=root->data)
    {
       search(root->left,data);   
    }
    else
    {
        search(root->right,data); 
    }
    
}
void main()
{
    int num;
    struct node* root=NULL;
    root=insert(root,15);
    root=insert(root,12);
    root=insert(root,135);
    root=insert(root,175);
    printf("enter the number to be searched ::");
    scanf("%d",&num);
    int result=search(root,num);
    if(result==1)
    {
        printf("element found");
    }
    else{
        printf("not found");
    }


}

