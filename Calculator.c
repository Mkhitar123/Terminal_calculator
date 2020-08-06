#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define size 15

// the program purpose calculate matematics expressions.
// for example 1+2*3 or 2*4-(3+1)

// this function find and calculate depended on privilege level.
int Calculate(int a[],char b[], int len_a);


// this function for delete n elements from array
void delete(char a[],int i, int n);
void delete_int(int a[],int position, int len);

//this function does "simb"  operation between x and y.
int X_operat_Y(int x, int y,char simb);


int main(int argc, char*argv[])
{   
    

    int **Num_Arr;
    char **Simb_Arr;
    Num_Arr=calloc(size,sizeof(int));
    Simb_Arr=calloc(size,sizeof(char));
    for(int i=0;i<size;++i)
    {
        Num_Arr[i]=calloc(size,sizeof(int));
        Simb_Arr[i]=calloc(size, sizeof(char));
    }
    int arr_j[size];
    //printf("\033[01;33m");
    printf("  Enter mathematical expression!\n ");
    //printf("\033[0m");
    //printf("\033[1;31m");
    printf(" in the end of add '=' simbol.\n  ");
    //printf("\033[0m");
    
    int N_i,N_j;
    int S_i,S_j;
    int cou_sim=0;
    N_i=N_j=S_i=S_j=0;
    first:
    while(N_j<size&&S_j<size&&N_i<size&&S_i<size )
    {   
        if(scanf("%d",&Num_Arr[N_i][N_j])!=0)
        {
            N_j++;
        }
        second:
        if(scanf("%c",&Simb_Arr[S_i][S_j])!=0)
        {   
                // if(Simb_Arr[S_i][S_j]=='/'||Simb_Arr[S_i][S_j]=='*'||Simb_Arr[S_i][S_j]=='+'||Simb_Arr[S_i][S_j]=='-'&&cou_sim<N_j)
                // {
                //     cou_sim++;
                // }
                if(Simb_Arr[S_i][S_j]=='(')
                {
                    arr_j[S_i]=N_j;
                    delete(Simb_Arr[S_i],S_j,1);                 
                    N_i++;
                    S_i++;
                    N_j=0;
                    S_j=0;
                    goto first;
                }
                if(Simb_Arr[S_i][S_j]==')')
                {   
                    Simb_Arr[S_i][S_j]='\0';
                    int n,x;
                    n=sizeof(Num_Arr[N_i])/sizeof(int);
                    x=Calculate(Num_Arr[N_i],Simb_Arr[S_i],n);
                    free(Num_Arr[N_i]);
                    free(Simb_Arr[S_i]);
                    N_i--;
                    S_i--;
                    Num_Arr[N_i][arr_j[S_i]]=x;
                    N_j=arr_j[S_i]+1;
                    S_j=strlen(Simb_Arr[S_i]);
                    goto second;
                }

                if(Simb_Arr[S_i][S_j]=='=')
                {
                    Simb_Arr[S_i][S_j]='\0';
                    break;
                }
                S_j++;
        }

    }
    
    printf("  Result:%d  %s",Calculate(Num_Arr[N_i],Simb_Arr[S_i],N_j),"\n ");
    system("pause");
    return 0;

}

int Calculate(int a[],char b[], int len_a)
{
    int *new_Arr;
    new_Arr=calloc(strlen(b)+1, sizeof(int));
    for(int i=0; i<strlen(b)+1;++i)
    {
        new_Arr[i]=a[i];

    }
    const char Simb[4]="/*-+";
    int start_count=0;
    int i=0;
    START:

    while(b[i]!='\0')
    {
        i++;
        if(b[i-1]==Simb[start_count])
        {
            new_Arr[i-1]=X_operat_Y(new_Arr[i-1],new_Arr[i],Simb[start_count]);
            delete_int(new_Arr,i,strlen(b));
            delete(b,i-1,1);
            i=0;
        }
        
    }

    if(start_count<strlen(Simb))
    {
        start_count++;
        i=0;
        goto START;
    }

    return new_Arr[0];

}


void delete(char a[],int j, int n)
{
    for(int i=j;i<strlen(a);++i)
    {
        a[i]=a[i+n];
    }
    if (j==strlen(a))
    {
        a[j]='\0';
    }
    
}
void delete_int(int a[],int position, int len)
{
      for(int i=position;i<len;++i)
    {
        a[i]=a[i+1];
    }  
    
}

int X_operat_Y(int x, int y,char simb)
{
if(simb=='*')
{x*=y;}
else if(simb=='/')
{x/=y;}
else if(simb=='+')
{x+=y;}
else if(simb=='-')
{x-=y;}
return x;
}