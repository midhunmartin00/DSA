#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int data;
	struct binary *left, *right;
};
struct node* binary;

struct node* newnode(int data)
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return (temp);
}

struct node* insert(struct node* tree, int i)
{
	if(tree==NULL)
	{
		tree=newnode(i);
		return tree;
	}
	if(i<tree->data)
	tree->left=insert(tree->left, i);
	else
	tree->right=insert(tree->right, i);
	return tree;
}

struct node* search(struct node* tree, int i)
{
    while(tree!=NULL)
    {
	if(i==tree->data)
		return tree;
	if(i<tree->data)
	tree=tree->left;
	else
	tree=tree->right;
    }
    return NULL;
}

void findMin(node tree, FILE *fp)
{
    if(tree==NULL)
    {
        fprintf(fp, "NIL\n");
        return;
    }

    while(tree!=NULL)
    {
        if(tree->left==NULL)
        {
            fprintf(fp, "%d\n", tree->data);
            return;
        }
        tree=tree->left;
    }
}

void findMax(node tree, FILE *fp)
{
    if(tree==NULL)
    {
        fprintf(fp, "NIL\n");
        return;
    }

    while(tree!=NULL)
    {
        if(tree->right==NULL)
        {
            fprintf(fp, "%d\n", tree->data);
            return;
        }
        tree=tree->right;
    }
}

struct node* getMin(struct node* tree)
{
    if(tree==NULL)
        return NULL;

    while(tree!=NULL)
    {
        if(tree->left==NULL)
            return tree;
        tree=tree->left;
    }
}


struct node* getMax(struct node* tree)
{
    if(tree==NULL)
        return NULL;

    while(tree!=NULL)
    {
        if(tree->right==NULL)
            return tree;
        tree=tree->right;
    }
}

struct node*  predecessor(struct node* tree, struct node* pos)
{
	if(pos->left!=NULL)
		return getMax(pos->left);

	struct node* pred=NULL;
	while(tree!=NULL && tree!=pos)
	{
		if(pos->data<tree->data)
		tree= tree->left;
		else
		{
			pred= tree;
			tree= tree->right;
		}
	}
	return pred;
}

struct node* successor(struct node* tree, struct node* pos)
{
	if(pos->left!=NULL)
		return getMin(pos->left);

	struct node* succ=NULL;
	while(tree!=NULL && tree!=pos)
	{
		if(pos->data<tree->data)
		tree= tree->left;
		else
		{
			succ= tree;
			tree= tree->right;
		}
	}
	return succ;
}

void preOrder(struct node* tree, FILE *fp)
{
	if (tree!=NULL)
	{
		fprintf(fp, "%d ",tree->data);
		preOrder(tree->left, fp);
		preOrder(tree->right, fp);
	}
}

void inOrder(struct node* tree, FILE *fp)
{
	if (tree!=NULL)
	{
		inOrder(tree->left, fp);
		fprintf(fp, "%d ",tree->data);
		inOrder(tree->right, fp);
	}
}

void postOrder(struct node* tree, FILE *fp)
{
	if (tree!=NULL)
	{
		postOrder(tree->left, fp);
		postOrder(tree->right, fp);
		fprintf(fp, "%d ",tree->data);
	}
}

struct node* delete(struct node* tree,int key)
{
    int m;
   if(tree==NULL)
     return NULL;
   else if(key>tree->data)
      tree->right=delete(tree->right,key);
   else if(key<tree->data)
      tree->left=delete(tree->left,key);
   else
       {
         if(tree->right==NULL)
            {struct node* temp=tree->left;
            free(tree);
            return temp;
            }
         else if(tree->left==NULL)
            {
              struct node* temp=tree->right;
              free(tree);
              return temp;

            }
          m=getMin(tree->right)->data;
          tree->data=m;
          tree->right=delete(tree->right,m);
       }

   return tree;
}

int choice(char *s)
{
    if(strcmp(s, "insr")==0)
    return 1;
    if(strcmp(s, "srch")==0)
    return 2;
    if(strcmp(s, "minm")==0)
    return 3;
    if(strcmp(s, "maxm")==0)
    return 4;
    if(strcmp(s, "pred")==0)
    return 5;
    if(strcmp(s, "succ")==0)
    return 6;
    if(strcmp(s, "inor")==0)
    return 7;
    if(strcmp(s, "prer")==0)
    return 8;
    if(strcmp(s, "post")==0)
    return 9;
    if(strcmp(s, "delt")==0)
    return 10;
    return -1;
}

int main(int argc, char *argv[])
{
    FILE *fs, *ft;
    fs=fopen(argv[1], "r");
    ft=fopen(argv[2], "a");
	if(fs==NULL || ft==NULL)
	    exit(0);

	struct node* tree= NULL;
    struct node* pos;
	char str[4]; int n,t,i=-9999999;

	while(fscanf(fs, "%s %d", str,&n)!=EOF)
	{
	    t=choice(str);
	    switch (t)
	    {
	        case 1:
	        tree=insert(tree,n);
	        break;

	        case 2:
	        if(search(tree, n)!=NULL)
                fprintf(ft, "FOUND\n");
            else
                fprintf(ft, "NOT FOUND\n");
	        break;

	        case 3:
	        findMin(tree, ft);
	        break;

	        case 4:
	        findMax(tree, ft);
	        break;

	        case 5:
					pos=search(tree, n);
					if(pos==NULL)
						fprintf(ft, "NOT FOUND\n");
					else
					{
						pos=predecessor(tree, pos);
	        	if(pos==NULL)
	        	fprintf(ft, "NIL\n");
						else
						fprintf(ft, "%d\n", pos->data);
					}
	        break;

	        case 6:
					pos=search(tree, n);
					if(pos==NULL)
						fprintf(ft, "NOT FOUND\n");
					else
					{
						pos=successor(tree, pos);
	        	if(pos==NULL)
	        	fprintf(ft, "NIL\n");
						else
						fprintf(ft, "%d\n", pos->data);
					}
	        break;

	        case 7:
	        inOrder(tree, ft);
	        fprintf(ft, "\n");
	        break;

	        case 8:
	        preOrder(tree, ft);
	        fprintf(ft, "\n");
	        break;

	        case 9:
	        postOrder(tree, ft);
	        fprintf(ft, "\n");
	        break;

	        case 10:
	        tree=delete(tree, n);
	        break;

	        default:
	        exit(0);
	    }
	}
}