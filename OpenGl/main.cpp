#include<math.h>
#include<iostream>
#include<windows.h>
#include<stdio.h>
//#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
//#include<conio.h>
//#include <stdlib.h>
using namespace std;
struct sphere
{
    float xvel;
    float yvel;
    float x;
    float y;
    int count;
    int r;
}s[50]={5,7,0.0,0.0,0,0};


int n=0,temp,i,a[50],b;
float f=0.0005,rs = 0.15;
float cx=-1.3,cy=-1.3,k=0;
int score=0,l=2;
int gameover = 1;
int gamebeg = 0;
int p = 0;

int pause = 0;







static void Timer(int value)
{
       if ((!gameover)&&(gamebeg)&&(!pause))
       {
        score++;
        cout<<score;
        cout<<"\n";
    glutPostRedisplay();
    glutTimerFunc(1000,Timer,0);

}}

void Write(char *string){//Write string on the screen
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}




void init(void)
{
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position[] = { 1.0,1.0,2.5, 0.0 };
GLfloat white_light[] = { 0.4, 0.3, 0.8, 0.1 };
GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
glClearColor(1.0, 1.0, 1.0, 1.0);
glShadeModel(GL_SMOOTH);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
glEnable(GL_LIGHTING);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHT0);
glEnable(GL_DEPTH_TEST);

}



void reshape(int w, int h)
{
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
if (w <= h)
glOrtho(-1.8, 1.8, -1.8,1.8, -10.0, 10.0);
else
glOrtho(-1.8,1.8, -1.8, 1.8, -10.0, 10.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}


void HelpScreen(){
char tmp_str[40];
glColor3f(0, 0, 0);
    glRasterPos2f(-1.4, 1.0);
    Write("Controls");
    glColor3f(1,0,0);
    glRasterPos2f(-1.5,0.90);
    Write("W to move the ball up");
    glRasterPos2f(-1.5,0.80);
    Write("A to move the ball left");
    glRasterPos2f(-1.5,0.70);
    Write("S to move the ball down");
    glRasterPos2f(-1.5,0.60);
    Write("D to move the ball right");
    glColor3f(1,0,0);
    glRasterPos2f(-1.5,0.4);
    Write("You are in control of the big ball. ");
    glColor3f(1,0,1);
    glRasterPos2f(-1.5,0.3);
    Write("The objective of the game is to avoid the smaller balls.");
    glRasterPos2f(-1.5,0.2);
    Write("The game ends when the big ball collides with the small balls");
    glRasterPos2f(-1,0.0);
    Write("Esc key  to exit the game at any point");
    glRasterPos2f(-1,-0.2);
    Write("Enter 1-9 to choose your level and start the game");
}




void WelcomeScreen(){
    char tmp_str[40];

    glColor3f(0.4,0.4 ,0.7 );
    glRasterPos2f(-0.3, 1.4);
    Write("GRAPHICS PROJECT");

    glColor3f(1, 0, 0);
    glRasterPos2f(-1, 1.25);
    Write("By Shreyas G - 11CO88 and Shyam Gopal - 11CO89");



}


void keyboard(unsigned char key,int m,int n1)
{
     /*if(pause)
     {
              if(key=='p')
              {
                     pause = 0;
                     }
                     glFlush();
                     glutPostRedisplay();
                     }*/
  // if(!pause)
   {
    switch(key)
    {
               case '1':
               case '2':
               case '3':
               case '4':
               case '5':
               case '6':
               case '7':
               case '8':
               case '9':
                    if(!gamebeg)
                    l=key-48;
                    gameover = 0;
                   gamebeg = 1;
                     init();
                    Timer(0);
                   glutPostRedisplay();
                            break;

        case 'w':   if((cy<1.3)&&(!pause))
                    cy+=0.1;
                    break;
         case 's':   if((cy>-1.2)&&(!pause))
                    cy-=0.1;
                    break;
         case 'd':   if((cx<1.3)&&(!pause))
                    cx+=0.1;
                    break;
         case 'a':   if((cx>-1.2)&&(!pause))
                    cx-=0.1;
                    break;
         /*case 'n': gameover = 0;
                   gamebeg = 1;
                     init();
                    Timer(0);
                   glutPostRedisplay();
                            break;*/
        case 'k' : f+=0.0005;
                     break;
           case 'l': f-=0.0005;
                       break;
           case 'p':pause = 1-pause;
                if(!pause)
                       Timer(0);

                          break;
           case 'r':if(gameover)
             { glFlush();
                score = 0;
           gamebeg = 0;
           gameover = 1;
           f=0.0005;
           p=0;
           for(int i = 0; i<n;i++)
           {
                   s[i].x = 0;
                   s[i].y = 0;
                   s[i].r = 0;
                   s[i].xvel = 5.0;
                   s[i].yvel = 7.0;

                   }
           n=0;
           cx = -1.3;
           cy = -1.3;
           s[0].x = 0.0;
           s[0].y = 1.4;

           } //glutPostRedisplay();
            break;
        case 27:exit(0);
        default:break;
    }}
}


void disp1()
{
    // glFlush();
    int m,i,j;
    float x1,x2,y1,y2,dist=0.16,dist2;
    char tmp_str[50];
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//dinit();
glDisable(GL_LIGHTING);
glColor3f(1.0,0.0,0.0);
glRasterPos2f(-0.1,1.6);
sprintf(tmp_str,"LEVEL : %d  SCORE : %d",l,score);
Write(tmp_str);
glColor3f(0.75,0.45,0.10);
glBegin(GL_LINE_LOOP);
	glVertex3f(-1.51,-1.51,0);
	glVertex3f(-1.51,1.51,0);
	glVertex3f(1.51,1.51,0);
	glVertex3f(1.51,-1.51,0);
glEnd();
glColor3f(0.1,0.2,0.5);
glBegin(GL_POLYGON);
	glVertex3f(-1.5,-1.5,0);
	glVertex3f(-1.5,1.5,0);
	glVertex3f(1.5,1.5,0);
	glVertex3f(1.5,-1.5,0);
glEnd();
glEnable(GL_LIGHTING);
//init();
for(m=0;m<=n;m++)
{
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    glTranslatef(s[m].x,s[m].y,0.0);
    glutSolidSphere(0.075, 20, 16);
    glPopMatrix();
}

for(m=0;m<=n;m++)
{
    if(s[m].x<=-1.4)
    {

        if((s[m].r==0)&&(n<l))
        {

            n=n+1;
            s[n].x=0.0;
            s[n].y=1.4;
            s[n].yvel=n%10;
            s[n].xvel=10-n%10;
            s[m].r=1;
        }
        s[m].xvel=-s[m].xvel;
    }
    if(s[m].x>=1.4)
    {
        s[m].xvel=-s[m].xvel;
    }
    if(s[m].y<=-1.4)
    {
        s[m].yvel=-s[m].yvel;
    }
    if(s[m].y>=1.4)
    {
        s[m].yvel=-s[m].yvel;
    }
    s[m].x+=(f*s[m].xvel*(1-pause));
    s[m].y+=(f*s[m].yvel*(1-pause));
}
glPushMatrix();
glTranslatef(cx,cy,0.0);
glColor3f(0.0,1.0,0.0);
if(!gameover)
{
glutSolidSphere(rs,40,16);}
if(gameover)
{
            if(rs>0.0)
            {
            glutSolidSphere(rs,40,16);
            rs = rs- 0.0005;
            }
            if(rs<=0.0)
            {

                     p=1;
                     rs = 0.15;
                     }
                     }
glPopMatrix();
for(i=0;i<=n;i++)
{
    dist2=sqrt((cx-s[i].x)*(cx-s[i].x)+(cy-s[i].y)*(cy-s[i].y));
    if((0.15+0.075)>dist2)
    { glutKeyboardFunc(NULL);
                          for(m=0;m<=n;m++)
                          {
                                          s[m].xvel = s[m].yvel = 0;
                                          }
                         gameover = 1;

         if(p==1)
        {
        cout<<"Game over\n";
        cout<<"Your Score is:"<<score;

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);


        glColor3f(1.0,0.0,0.0);
        glRasterPos2f(cx,cy);
        Write("GAME OVER");

         glClearColor(0.0,0.0,0.0,0.0);
        }


    }

    for(j=0;j<=n;j++)
    {
        if(i!=j)
        {
         x1=s[i].x;
         x2=s[j].x;
         y1=s[i].y;
         y2=s[j].y;
         dist2=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
         if(dist>dist2)
         {
             s[i].xvel=-s[i].xvel;
             s[i].yvel = -s[i].yvel;

         }
        }

    }
}

glFlush();
glutPostRedisplay();

}

void EndScreen(void)
{

  glutKeyboardFunc(keyboard);
    char tmp_str[40];

    // Print the status of the game on the screen
    glColor3f(1, 0, 0);
    glRasterPos2f(-1.0, 1.00);

    sprintf(tmp_str, "YOUR FINAL SCORE IS: %d", score);
    Write(tmp_str);

    glRasterPos2f(-1.0,0.75);
    Write("THANK YOU FOR PLAYING");

    glRasterPos2f(-1.0,0.0);
    Write("PRESS R TO RESTART THE GAME AND ESC TO EXIT");
    }




void display(void)
{if(p==0)
         {
          if(gamebeg)
          {
                   disp1();
               }
    else
      {
          char tmp_str[50];
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glClearColor(1.0,1.0,1.0,1.0);
          WelcomeScreen();
           //sprintf(tmp_str, "Level: %d Points: %d", lvl, score);
       // Write(tmp_str);
          HelpScreen();
          glFlush();
          glutPostRedisplay();
          }
}
if(p==1)
{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          EndScreen();
        Sleep(1000);
         glFlush();
          glutPostRedisplay();
                 }

}







int main(int argc, char** argv)
{
for(i=0;i<50;i++)
 a[i]=-1;
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(750, 750);
glutInitWindowPosition(100, 25);
init();
glutCreateWindow("Game");
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);


glutMainLoop();
return 0;
}



