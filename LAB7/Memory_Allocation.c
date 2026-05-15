#include<stdio.h>

void firstFit(int b[],int m,int p[],int n)
{
    int u[10]={0},a[10];

    for(int i=0;i<n;i++)
    {
        a[i]=-1;

        for(int j=0;j<m;j++)
        {
            if(!u[j] && b[j]>=p[i])
            {
                a[i]=j;
                u[j]=1;
                break;
            }
        }
    }

    printf("\nFirst Fit\nPNo\tPSize\tBlock\n");

    for(int i=0;i<n;i++)
        if(a[i]!=-1)
            printf("%d\t%d\t%d\n",i+1,p[i],a[i]+1);
        else
            printf("%d\t%d\tNot Allocated\n",i+1,p[i]);
}

void bestFit(int b[],int m,int p[],int n)
{
    int u[10]={0},a[10],best;

    for(int i=0;i<n;i++)
    {
        a[i]=-1;
        best=-1;

        for(int j=0;j<m;j++)
        {
            if(!u[j] && b[j]>=p[i])
            {
                if(best==-1 || b[j]<b[best])
                    best=j;
            }
        }

        if(best!=-1)
        {
            a[i]=best;
            u[best]=1;
        }
    }

    printf("\nBest Fit\nPNo\tPSize\tBlock\n");

    for(int i=0;i<n;i++)
        if(a[i]!=-1)
            printf("%d\t%d\t%d\n",i+1,p[i],a[i]+1);
        else
            printf("%d\t%d\tNot Allocated\n",i+1,p[i]);
}

void worstFit(int b[],int m,int p[],int n)
{
    int u[10]={0},a[10],worst;

    for(int i=0;i<n;i++)
    {
        a[i]=-1;
        worst=-1;

        for(int j=0;j<m;j++)
        {
            if(!u[j] && b[j]>=p[i])
            {
                if(worst==-1 || b[j]>b[worst])
                    worst=j;
            }
        }

        if(worst!=-1)
        {
            a[i]=worst;
            u[worst]=1;
        }
    }

    printf("\nWorst Fit\nPNo\tPSize\tBlock\n");

    for(int i=0;i<n;i++)
        if(a[i]!=-1)
            printf("%d\t%d\t%d\n",i+1,p[i],a[i]+1);
        else
            printf("%d\t%d\tNot Allocated\n",i+1,p[i]);
}

int main()
{
    int m,n,b[10],p[10];

    printf("Enter no. of blocks: ");
    scanf("%d",&m);

    printf("Enter block sizes:\n");
    for(int i=0;i<m;i++)
        scanf("%d",&b[i]);

    printf("Enter no. of processes: ");
    scanf("%d",&n);

    printf("Enter process sizes:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);

    firstFit(b,m,p,n);
    bestFit(b,m,p,n);
    worstFit(b,m,p,n);

    return 0;
}
