#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
int gd=DETECT,gm;
main()
{
int n,a[10],i,j=0,y,ch,t;
initgraph(&gd,&gm,"C:\\TC\\BGI");
printf("enter the size the code: ");
scanf("%d",&n);
printf("\nenter the code to send: ");
 for(i=0;i<n;i++)
  scanf("%d",&a[i]);

printf("\n1) NRZ-L\n2) NRZ-I\n3) Manchester coding\n4)Differential Manchester coding");
printf("\nenter the choice to select type of line coding");
 scanf("%d",&ch);

 setcolor(BLUE);
 j=20;
 for(i=0;i<n;i++)
  {
  line(j,240,j,440);
  j+=20;
  }

  setcolor(RED);
  switch(ch)
  { case 1: line(0,340,340,340);
	    line(0,240,0,440);		//drawing the axis
	     j=0;
      for(i=0;i<n;i++)
       {

	 if(a[i]==1)
	  {   if(a[i-1]!=1&&i!=0)             // 0 is treated +ve 1 as -ve
	    {   line(0+j,320,0+j,360);       // since y as opp choose -ve logic

	      }
		 line(0+j,360,20+j,360);
	    if(a[i+1]!=1&&i!=n-1)
	     { line(20+j,360,20+j,320);    }
	   }
	else if(a[i]==0)
	  { if(a[i-1]!=0 && i!=0)
	     {  line(0+j,360,0+j,320); }
		line(0+j,320,20+j,320);
	    if(a[i+1]!=0 && i!=n-1)
	    {  line(20+j,320,20+j,360);}
	   }
       //	setcolor(RED);
       //	line(0+j,120,0+j,380);
	// printf("|");
	 j=j+20;
	printf("%d ",a[i]);
	}
	 break;

 case 2: line(0,340,340,340);
	 line(0,240,0,440);
	 t=0;
	 j=0;
	 if(a[0]==0)
	  y=320;
	 else
	  y=360;
	 for(i=0;i<n;i++)
	  {
	    if(a[i]==1)
	     { if(t%2==0)
		{  y=360;
		  line(j,320,j,360);
		}
	       else
		 {
		  y=320;
		  line(j,360,j,320);
		  }
		t++;
	      }
	   line(j,y,20+j,y);
	   j=j+20;
	   printf("%d ",a[i]);
	  }
      break;
   case 3: line(0,340,340,340);
	   line(0,240,0,440);
	   j=0;
      for(i=0;i<n;i++)        // 0 as +ve 1 as -ve
       {

	 if(a[i]==1)
	  {
	      line(0+j,360,10+j,360);
	      line(10+j,320,20+j,320);
	      line(10+j,360,10+j,320);
	    if(a[i+1]==1&&i!=n-1)
	     { line(20+j,360,20+j,320);    }
	   }
	else if(a[i]==0)
	  {
		line(0+j,320,10+j,320);
		line(10+j,360,20+j,360);
		line(10+j,320,10+j,360);
	      if(a[i+1]==0 && i!=n-1)
	      {  line(20+j,320,20+j,360);}
	   }

	 j=j+20;
	printf("%d ",a[i]);
	}
	 break;
  case 4: line(0,340,340,340);
	  line(0,240,0,440);
	  t=0;
	  j=0;
	  y=320;
	  line(j,320,j,360);
	 for(i=0;i<n;i++)
	  {
	    if(a[i]==0)
	     { if(y==320)
		y=360;
		else
		 y=320;
	       line(j,320,j,360);

	      }
	   if(y==360)
	   {
	   line(j,y,10+j,y);
	   line(10+j,320,20+j,320);
	   line(10+j,320,10+j,360);
	   y=320;
	   }
	  else
	  {
	    line(j,y,10+j,y);
	    line(10+j,360,20+j,360);
	    line(10+j,320,10+j,360);
	   y=360;
	  }
	   j=j+20;
	   printf("%d  ",a[i]);
	  }
      break;



}
 getch();
  closegraph();
   return 0; }

