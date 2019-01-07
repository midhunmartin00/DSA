#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
struct node* create_tree(struct node*root,char *str)
{
    printf("%s",str);
}
void main()
{
    char str0[]="(6(9(17()(5(2)()))(14))(8()(11)))";
    //printf("%s",str);
    int len=strlen(str0);
    char str[len-2];
    for(int i=1;i<len-1;i++)
    {
        str[i-1]=str0[i];
    }
    struct node *root=NULL;
    root=create_tree(root,str);
    


}