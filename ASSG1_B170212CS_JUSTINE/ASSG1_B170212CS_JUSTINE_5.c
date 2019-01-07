#include<stdio.h>
#include<stdlib.h>
FILE *fp;

struct node
{
	int data;
	struct  node *left;
	struct  node *right;
};

struct node* newnode(int val)
{
	struct node *nodes=(struct node*)malloc(sizeof(struct node));
	nodes->data=val;
	nodes->left=NULL;
	nodes->right=NULL;
	return nodes;

}
struct node* insert(struct node* root,int val)
{
    if(root==NULL)
    {
        root=newnode(val);
        return root;
    }
    if(val<root->data)
    {
        root->left=insert(root->left,val);
        return root;
    }
    else
    {
        root->right=insert(root->right,val);
        return root;
    }
}
void preorder(struct node* root,FILE *fp)
{
    
    
    if(root!=NULL)
    {
        printf("(");
        fprintf(fp,"("); 
        printf("%d",root->data);
        fprintf(fp,"%d",root->data); 
        preorder(root->left,fp);
        preorder(root->right,fp);
        //printf("%d",root->data);
        printf(")");
    }
    else
    {
      fprintf(fp,"()");  
    }

    

}
void main(int argc,char *argv[])
{
    int n,val;
    struct node* root=NULL;
    FILE *fs;
    fs=fopen(argv[1],"r");
    fp=fopen(argv[2],"a");
    
    while(!feof(fs))
    {
        fscanf(fs,"%d",&n);
        printf("%d\n",n);
        for(int i=0;i<n;i++)
        {
             fscanf(fs,"%d",&val);
             root=insert(root,val);
             printf("%d ",val);
        }
    }
    preorder(root,fp);
    
}

