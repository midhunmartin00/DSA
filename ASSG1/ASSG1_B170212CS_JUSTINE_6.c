#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct  node *left;
	struct  node *right;
};
struct queue
{
	struct node* data;
	struct queue* next;
};
struct queue *top = NULL;
void push(struct node* val)
{
    struct queue* head=(struct queue*)malloc(sizeof(struct queue));
    struct queue* temp=top;
	head->data=val;
    head->next=NULL;
	if(top==NULL)
	{
		top=head;
	}
	else{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=head;
	}
   
}
void pop()
{
    struct queue* temp=top;
    top=top->next;
    free(temp);
}
struct node* newnode(int val)
{
	struct node *nodes=(struct node*)malloc(sizeof(struct node));
	nodes->data=val;
	nodes->left=NULL;
	nodes->right=NULL;
	return nodes;

}
int max(int v1,int v2)
{
	if(v1>v2)
		return v1;
	else
		return v2;
}
int height(struct node* root)
{
	if(root==NULL)
		return 0;
	return max(height(root->left),height(root->right))+1;
}
int diameter(struct node * root) 
{ 
    if (root == NULL) 
          return 0; 
  int leftheight = height(root->left); 
  int rightheight = height(root->right); 
  int leftdiameter = diameter(root->left); 
  int rightdiameter = diameter(root->right); 
  return max(leftheight + rightheight + 1, max(leftdiameter, rightdiameter)); 
} 
int get_size() 
{
	struct queue *temp=top;
	int count=0;
	if(top==NULL)
	{
		return 0;
	}
	else{
		while(temp!=NULL)
		{
			temp=temp->next;
			count++;
		}
		return count;
	}
}
int maxwidth(struct node* node)
{
	if(node==NULL)
	{
		return 0;
	}

	int result=0;
	push(node);
	while(top!=NULL)
	{
		int count=get_size();
		
		result=max(count,result);
		while(count--)
		{
			struct node* temp=top->data;
			pop();
			if(temp->left!=NULL)
			{
				push(temp->left);
			}
			if(temp->right!=NULL)
			{
				push(temp->right);
			}
			int c=get_size();
			//printf("count is : %d",c);
			
		}
		
	}
	return result;
}

void main()
{
	struct node* root =newnode(5);
	root->left=newnode(15);
	root->right=newnode(25);
    root->left->left=newnode(250);
    root->left->right=newnode(20);
	 root->right->left=newnode(50);
	//root->right->right=newnode(2);

	int height_tree=height(root)-1;
    int dia=diameter(root);
    int width=maxwidth(root);
	printf("height of tree is : %d",height_tree);
    printf("diameter of tree is : %d",dia);
	printf("maxwidth of tree is : %d",width);


}	