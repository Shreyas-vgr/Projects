/*  Two's complement multiplication of 8 bit binary numbers using roberston algorithm 
    NAME   : SHREYAS G
    REG NO : 11CO88
 */


#include<stdio.h>
#include<math.h>
#include<conio.h>
main()
{
     int flag=0,x,y,a[8]={0},q[8]={0},m[8]={0},f=0,i=0,j=0,temp,carry=0,correct=0,f1=0,final[16],sum=0,neg=0;
     printf(" MULTPLICATION ALGORITHM(ROBERSTON)\n");
     printf("Enter the value of the multiplier X(Q) : ");
      scanf("%d",&x);
     printf("\nEnter the value of the multiplicand Y(M) : ");
      scanf("%d",&y);

    if(x<0||y<0)                                                               //if neg=1 product is negative
       neg=1;
    if(x<0&&y<0)
       neg=0;
    if(x<0)                                                                     // X is negative
      {
        flag=1;
        correct=1;
        x=-1*x;
      }
     i=7;
    while(x!=0)
    {
        q[i--]=x%2;                                                             //conversion to binary
        x/=2;
    }
    if(flag)                                                                    // One's complement of X
    {
     for(i=0;i<8;i++)
      {
          if(q[i]==0)
           q[i]=1;
          else
           q[i]=0;
      }

                                                                                // Two's complement of X
      if(q[7]==0)
       q[7]=1;
      else
      {
        q[7]=0;
        for(i=6;i>=0;i--)
        {
          if(q[i]==1)
           q[i]=0;
          else
          {
              q[i]=1;
              break;
          }
        }
      }

    }
//------------------------------------------------------------------------------------------------------------------------------------------//
    flag=0;
    i=7;
    if(y<0)                                                                     // Y is negative
     {
      f1=1;
      flag=1;
      y=-1*y;
     }
    while(y!=0)
    {
        m[i--]=y%2;
        y/=2;
    }

    if(flag)                                                                     //Finding One's complement of Y
    {
     for(i=0;i<8;i++)
      {
          if(m[i]==0)
           m[i]=1;
          else
           m[i]=0;
      }
                                                                                 //Finding Two's complement of Y
      if(m[7]==0)
       m[7]=1;
      else
      {
        m[7]=0;
        for(i=6;i>=0;i--)
        {
          if(m[i]==1)
           m[i]=0;
          else
          {
              m[i]=1;
              break;
          }
        }
      }

    }
 //---------------------------------------------------------------------------------------------------------------------------//   
    printf("\nValue of Q : ");
    for(i=0;i<8;i++)
     printf("%d ",q[i]);
    printf("\nValue of M : ");
    for(i=0;i<8;i++)
     printf("%d ",m[i]);

 //-------------Starting the algorithm--------------------
printf("\n     Flip-Flop\t  Accumulator-A\t\t\tRegister-Q");
printf("\n\n\t%d",f);
printf("       ");
for(j=0;j<8;j++)
 printf(" %d",a[j]);
printf("\t\t");
for(j=0;j<8;j++)
 printf("%d ",q[j]);
 for(i=0;i<8;i++)
 {
     if(i==7&&correct==1)                                                      //correction step if x<0
     {

     for(i=0;i<8;i++)
      {
          if(m[i]==0)
           m[i]=1;
          else
           m[i]=0;
      }
                                                                               //Finding Two's complement of Y
      if(m[7]==0)                                                                //to subtract the from partial product
       m[7]=1;
      else
      {
        m[7]=0;
        for(i=6;i>=0;i--)
        {
          if(m[i]==1)
           m[i]=0;
          else
          {
              m[i]=1;
              break;
          }
        }
      }
       carry=0;
        for(j=7;j>=0;j--)                                                        //Adding M to A
          {                                                                      //A:=A+M;
             a[j]+=m[j]+carry;
             if(a[j]==1)
             {
                 carry=0;
             }
             else if(a[j]==2)
             {
                a[j]=0;
                carry=1;
             }
             else if(a[j]==3)
             {
                 a[j]=1;
                 carry=1;
             }
          }
           if(f1==1)
            f=0;
          goto start;

     }                                                                            //end of correction
     if(q[7]==1)
      {   carry=0;
          for(j=7;j>=0;j--)                                                       //Adding M to A
          {
             a[j]=a[j]+m[j]+carry;
             if(a[j]==1)
             {
                 carry=0;
             }
             else if(a[j]==2)
             {
                a[j]=0;
                carry=1;
             }
             else if(a[j]==3)
             {
                 a[j]=1;
                 carry=1;
             }
          }

      }
      start:
      if(f==0)
       {
           if(m[0]==1&&q[7]==1)
            f=1;
       }

       //Shift FAQ
          for(j=6;j>=0;j--)
           q[j+1]=q[j];
          q[0]=a[7];
          for(j=6;j>=0;j--)
           a[j+1]=a[j];
          a[0]=f;

 printf("\n\n\t%d",f);
printf("       ");
for(j=0;j<8;j++)
printf(" %d",a[j]);
printf("\t\t");
for(j=0;j<8;j++)
 printf("%d ",q[j]);

 }
j=0;
flag=0;
printf("\n\n");
for(i=0;i<8;i++)
 {
  printf("%d ",a[i]);
  final[j++]=a[i];
 }
for(i=0;i<8;i++)
 {
  printf("%d ",q[i]);
  final[j++]=q[i];
 }
 if(neg==1)                                                                  //Find two's complement
 {
     flag=1;
     for(i=0;i<16;i++)
      {
          if(final[i]==0)
           final[i]=1;
          else
           final[i]=0;
      }

      if(final[15]==0)
       final[15]=1;
      else
      {
        final[15]=0;
        for(i=14;i>=0;i--)
        {
          if(final[i]==1)
           final[i]=0;
          else
          {
              final[i]=1;
              break;
          }
        }
      }
 }
 //Converting the binary array to a decimal number
 for(i=15;i>=0;i--)
 {
     sum+=pow(2,15-i)*final[i];
 }
 if(flag)
  sum*=-1;
 printf("\nThe product is : %d",sum);

getch();
}//end of main
