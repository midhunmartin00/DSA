#include <stdio.h>
#include <math.h>
#include <string.h>

void search(char text[], char pattern[] ,int q, FILE * ft)
{

  int n = strlen(text)-2;
  int m = strlen(pattern)-2;
  int d = 256;
  int h = pow(d,m-1);
    h = h%q;
  int p=0,t=0;

  for(int i=0;i<m;++i)
  {
    p = (d*p + pattern[i])%q;
    t = (d*t + text[i])%q;
  }

  for(int i = 0 ; i<=n-m;++i)
  {
    if (p == t)
    {
      int j=0;
      while(j<m)
      {
        if (pattern[j] != text[i+j])
          break;
        j++;
      }

      if (j==m)
        fprintf(ft,"%d ",i);
    }

    if (i< n-m)
    {
      t = (d*(t - text[i]*h) + text[i+m])%q;

      if (t<0)
        t = (t + q);
    }
  }
}

int main(void) {
  char text[100],pattern[100];
  int q = 163; // A prime number
  FILE * fp = fopen("input.txt","r");
  FILE * ft = fopen("output.txt","w");
  while(1)
  {
      char ch;
      fscanf(fp,"%c",&ch);
      if (ch == 't')
      {
        char ch1,temp;
        fscanf(fp,"%c%c",&ch1,&temp);
        fgets(text,100,fp);
        
      }
      else if (ch == 'p')
      {
        char ch1;
        fscanf(fp,"%c",&ch1);
        if (ch1=='r')
        {
          search(text,pattern,q,ft);
          fprintf(ft,"\n");
        }
        else if (ch1 == ' ')
        {
          char temp;
          fscanf(fp,"%c",&temp);
          fgets(pattern,100,fp);
        }
      }
      else if (ch == 'e')
        break;
  }
  fclose(fp);
  fclose(ft);
}
