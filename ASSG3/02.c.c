#include <stdio.h>
#include <stdlib.h>

typedef struct Node * node;

struct Node{
  int key;
  node left;
  node right;
  int height;
};

int height(node n)
{
  if (n==NULL)
    return 0;
  else
    return n->height;
}

int max(int a, int b)
{
  if (a>b)
    return a;
  else
    return b;
}

node newNode(int data)
{
  node temp = (node)malloc(sizeof(struct Node)); 
  temp->key   = data; 
  temp->left   = NULL; 
  temp->right  = NULL; 
  temp->height = 1; 
  return temp;
}

int getBalance(node n)
{
  if(n==NULL)
    return 0;
  return ( height(n->left) - height(n->right) );
}

node leftrotate(node x)
{
  node y = x->right;
  node t2 = y->left;

  //Rotating
  y->left = x;
  x->right = t2;

  x->height = max( height(x->left) , height(x->right) ) + 1 ;
  y->height = max( height(y->left) , height(y->right) ) + 1 ;

  return y;
}

node rightrotate(node y)
{
  node x = y->left;
  node t2 = x->right;

  //Rotating
  x->right = y;
  y->left = t2;

  y->height = max( height(y->left) , height(y->right) ) + 1;
  x->height = max( height(x->left) , height(x->right) ) + 1;

  return x;
}

node insert(node root,int key)
{
  if (root == NULL)
    return (newNode(key));
  
  if (key < root->key)
    root->left = insert(root->left,key);
  else if (key > root->key)
    root->right = insert(root->right,key);
  else
    return root;

  root->height = 1 + max( height(root->left) , height(root->right) );

  int balance = getBalance(root);

  if (balance>1 && key < root->left->key)
    return rightrotate(root);

  if (balance<-1 && key > root->right->key)
    return leftrotate(root);

  if (balance > 1 && key > root->left->key)
  {
    root->left = leftrotate(root->left);
    return rightrotate(root);
  }

  if (balance < -1 && key < root->right->key)
  {
    root->right = rightrotate(root->right);
    return leftrotate(root);
  }

  return root;
}

int findMin(node root)
{
  if (root == NULL)
    return -1;
  else if(root->left == NULL)
    return (root->key);
  else
    return (findMin(root->left));
}


node deleteNode(node root,int key)
{
  if (root==NULL)
    return root;
  if (key > root->key)
    root->right = deleteNode(root->right,key);
  else if (key < root->key)
    root->left = deleteNode(root->left,key);
  else
  { 
    if (root->left == NULL) 
    { 
      node temp = root->right; 
      root = temp;
    } 
    else if (root->right == NULL) 
    { 
      node temp = root->left; 
      root = temp; 
    }
    else
    {
      int min = findMin(root->right); 
      root->key = min; 
      root->right = deleteNode(root->right, min);
    }
  } 

  if (root==NULL)
    return root;
  
  root->height = 1 + max( height(root->left), height(root->right) );

  int balance = getBalance(root); 

  if (balance > 1 && getBalance(root->left) >= 0) 
      return rightrotate(root); 
  if (balance > 1 && getBalance(root->left) < 0) 
  { 
     root->left =  leftrotate(root->left); 
     return rightrotate(root); 
  } 
  if (balance < -1 && getBalance(root->right) <= 0) 
      return leftrotate(root); 
  if (balance < -1 && getBalance(root->right) > 0) 
  { 
    root->right = rightrotate(root->right); 
    return leftrotate(root); 
  }
  
  return root; 
}

void preOrder(FILE * ft,node root) 
{ 
  fprintf(ft,"(");
  if(root != NULL) 
  { 
    fprintf(ft,"%d", root->key);
    if (root->left!=NULL || root->right!=NULL)
    {
      preOrder(ft,root->left);
      preOrder(ft,root->right);
    } 
  } 
  fprintf(ft,")");
} 

int isAVL(node root)
{
  if (root==NULL)
    return 1;
  int bal = getBalance(root);
  if (bal>=-1 && bal<=1)
     return (isAVL(root->left) && isAVL(root->right));
  else
    return 0;
}

node search(node root,int key)
{
  node p = (node)malloc(sizeof(struct Node));
  if(root->key == key)
  {
    //fprintf(ft,"FOUND");
    //return root;
    p = root;
  }
  else if(key > root->key)
  {
    if (root->right == NULL)
    {  
      //fprintf(ft,"NOT FOUND");
      p = NULL;
      //return p;
    }
    else
      p = search(root->right,key);
  }
  else if(key < root->key)
  {
    if(root->left == NULL)
    { 
      //fprintf(ft,"NOT FOUND");
      p = NULL;
      //return p;
    }
    else
      p = search(root->left,key);
  }
  return p;
}



int main(void) {
  node root = NULL; 
  // root = insert(root, 10); 
  // root = insert(root, 20); 
  // root = insert(root, 30); 
  // root = insert(root, 40); 
  // root = insert(root, 50); 
  // root = insert(root, 25); 
  // root = insert(root, 9); 
  // root = insert(root, 5); 
  // root = insert(root, 10); 
  // root = insert(root, 0); 
  // root = insert(root, 6); 
  // root = insert(root, 11); 
  // root = insert(root, -1); 
  // root = insert(root, 1); 
  // root = insert(root, 2); 
  // preOrder(root); 
  // root = deleteNode(root,5);
  // root = leftrotate(root);
  // root = rightrotate(root);
  // fprintf(ft,"\n%d\n",isAVL(root));
  // preOrder(root);
  FILE * fp = fopen("input.txt","r");
  FILE * ft = fopen("output.txt","w");
  int k;
  while(1)
  {
    fscanf(fp,"%d",&k);
    if (k==1)
    {
      int m;
      fscanf(fp,"%d", &m);
      root = insert(root,m);
    }
    else if (k==2)
    {
      int m;
      fscanf(fp,"%d", &m);
      root = deleteNode(root,m);
    }
    else if (k==3)
    {
      int m;
      fscanf(fp,"%d", &m);
      node p = search(root,m);
      p = leftrotate(root);
    }
    else if (k==4)
    {
      int m;
      fscanf(fp,"%d", &m);
      node p = search(root,m);
      p = rightrotate(root);
    }
    else if (k==5)
    {
      int m;
      fscanf(fp,"%d", &m);
      node p = search(root,m);
      fprintf(ft,"%d\n",getBalance(p));
    }
    else if (k==6)
    {
      preOrder(ft,root);
      fprintf(ft,"\n");
    }
    else if (k==7)
    {
      int k = isAVL(root);
      if (k==1)
        fprintf(ft,"TRUE\n");
      else
        fprintf(ft,"FALSE\n");
    }
    else if (k==8)
    {
      int m;
      fscanf(fp,"%d", &m);
      node k = search(root,m);
      if (k==NULL)
        fprintf(ft,"FALSE\n");
      else
        fprintf(ft,"TRUE\n");
    }
    else if (k==9)
    {
      return 0;
    }
  }
}
