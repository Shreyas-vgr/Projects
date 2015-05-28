#include<stdio.h>
#include<string.h>
main()
{   
  int b,c,a[16],i,j,k, x[8],y[8];
 printf("enter the two numbers");
 scanf("%d %d",&b,&c);
x=bin(b);
y=bin(c);
printf( " %s | %s ",x,y);
for(i=0;i<8;i++)
 a[i]=0;
for(i=8;i<16;i++)
 a[i]=x[8-i];
for(i=7;i>0;i--)
{
  if(x[0]==0&&y[0]==0)
    {
 				    //both x and y are positive
      if(x[i]==1)
        {  for(j=0;j<16;j++)
              a[j]=a[j]+y[j];
        }
       for(k=16;k>0;k--)
          a[k]=a[k-1];
           a[0]=0;
        //dis(a);
 }
}

dis(a);
}
int bin(int q[],int v)
{
 int r,p=1,s=0,k=0;
 while(v>0)
 {
   r=v%2;
   s=s+r*p;
   q[k++]=s;
   v/=2;
  p*=10;
 }
q[k]='\0';
return q;
}
void dis(int d[20])
{ int s;
 for(s=0;s<16;s++)
   printf("%d",d[s]);
}
