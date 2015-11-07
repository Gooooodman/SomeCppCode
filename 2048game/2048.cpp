#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

void gotoxy(int x, int y)
{
 COORD pos = {x,y};
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleCursorPosition(hOut, pos);
}

enum{
 Up = 72,Down = 80,Left = 75,Right = 77	
};

class Game{
  public: 	
   Game();
   void Draw_Map();	
   void Init_Array(); 
   void Produce();
   void Console();
   void Up_Do();
   void Down_Do();
   void Left_Do();
   void Right_Do();	
   void Dead();
   void Show_Score();
  private:
   int i,j,x,y,b,a[4][4],f,g;
   int score;
};

Game::Game(){
 score = 0;
 srand(time(NULL));	
 f = 0;
 for(i = 0;i!=4;i++)
 {
  for(j = 0;j!=4;j++)	
  {
   a[i][j] = 0;		 
  }	
 }
  Draw_Map();
  Produce();
  Produce();
  Init_Array();		
}

void Game::Show_Score(){
    gotoxy(17,12);
  	cout<< "Score : ";
  	cout<< score;		
}

void Game::Dead(){
  int c = 0,b = 0,d = 0;
  for(int i = 0;i!=4;i++)
  for(int j = 0;j!=4;j++)
  {
   	if(a[i][j]==0)
   	d = 1;
  }	
  if(d==0)
  {
   for(int i = 0;i!=4;i++)
   {
   for(int j =0;j!=3;j++)
    {
     if(a[i][j]==a[i][j+1])
     c = 1;
   }	
   }
   for(int j = 0;j!=4;j++)
   {
    for(int i =0;i!=3;i++)
    {
      if(a[i][j]==a[i+1][j])
       b = 1;
    }	
   }
    if(c==0&&b==0)
   {
  	gotoxy(5,12);
  	cout<< "GameOver";
  	cout<< "     Score : ";
  	cout<< score;
  	getch();
   }
  }
}

void Game::Draw_Map(){
  x = 4,y = 2;
  gotoxy(x,y);
  cout<< "+------+------+------+------+";
  gotoxy(x,y+1);
  cout<< "|      |      |      |      |";
  gotoxy(x,y+2);
  cout<< "|------+------+------+------|";
  gotoxy(x,y+3);
  cout<< "|      |      |      |      |";
  gotoxy(x,y+4);
  cout<< "|------+------+------+------|";
  gotoxy(x,y+5);
  cout<< "|      |      |      |      |";
  gotoxy(x,y+6); 
  cout<< "|------+------+------+------|";
  gotoxy(x,y+7);
  cout<< "|      |      |      |      |";
  gotoxy(x,y+8);
  cout<< "+------+------+------+------+";	
}

void Game::Init_Array(){
Show_Score();	
 y = 3;
 for(i = 0;i!=4;i++)
 { 
  x = 6;
  for(j = 0;j!=4;j++)	
  {
    gotoxy(x,y);
	if(a[i][j]==0)
	cout<< "    ";
	else 
	{	
	  cout<< "    ";
	  gotoxy(x,y);
   	  cout<< a[i][j];
    }
   	x = x+7;
  }		
  y = y+2;
 }	
  Dead();	
}

void Game::Produce(){
  if((rand()%100)%5==0)
   b = 4;
  else b = 2;
   Flag:
    i = rand()%4;
    j = rand()%4;
   if(a[i][j]==0)
    a[i][j] = b;
   else goto Flag;	
   f = 0;
}

void Game::Console(){
  while(true)
  { 
   Flag:
   switch(getch())
   { 	
   	case Up:Up_Do();goto Flag;break;
   	case Down:Down_Do();goto Flag;break;
	case Left:Left_Do();goto Flag;break;
	case Right:Right_Do();goto Flag;break; 
   }	
  }
}

void Game::Up_Do(){	 
int d = 0;
 for(int n = 0;n!=4;n++)
  for(i = 1;i!=4;i++)
  {
   for(j = 0;j!=4;j++)
   {
	if(a[i][j]!=0&&a[i-1][j]==0&&(n==0||n==2||n==3))
  	{ 	
  	  f = 1;	
	  a[i-1][j] = a[i][j]; 
	  a[i][j] = 0;	
  	}
  	if(a[i][j]!=0&&a[i][j]==a[i-1][j]&&n==1)
  	{		
  	  f = 1;	
	  d++;		
   	  a[i][j] = 0;
	  a[i-1][j]*=2;		
	  score+=a[i-1][j];
  	}
   }
  }
  for(j = 0;j!=4;j++)
  {
    if(a[1][j]!=0&&a[1][j]==a[0][j]&&d==0) 
    {
	 f = 1;		
   	 a[1][j] = 0;
	 a[0][j]*=2;
	 score+=a[0][j];
    }
  }
  if(f>0) 		
   Produce();   
  Init_Array();	
}

void Game::Down_Do(){
 int d = 0;
 for(int n = 0;n!=4;n++)
  for(i = 2;i>=0;i--)
   for(j = 0;j!=4;j++)
   {
  	if(a[i][j]!=0&&a[i+1][j]==0&&(n==0||n==2||n==3))
  	{
  	  f = 2;	
	  a[i+1][j] = a[i][j]; 
	  a[i][j] = 0;	
  	}
	else if(a[i][j]!=0&&a[i][j]==a[i+1][j]&&n==1)
  	{
  	  f = 1;	
	  d++;	
	  a[i][j] = 0;
	  a[i+1][j]*=2;	
	  score+=a[i+1][j];	
  	}
   }
   for(j = 0;j!=4;j++)
  {
    if(a[2][j]!=0&&a[2][j]==a[3][j]&&d==0)
	{ 
	 f = 1;		
   	 a[2][j] = 0;
	 a[3][j]*=2;
	 score+=a[3][j];	
    }
  }
  if(f>0) 		
   Produce();   
  Init_Array();	
}

void Game::Left_Do(){
  int d;
 for(int n = 0;n!=4;n++)
  for(j = 1;j!=4;j++)
   for(i = 0;i!=4;i++)
   {
  	if(a[i][j]!=0&&a[i][j-1]==0&&(n==0||n==2||n==3))
  	{ 	
  	  f = 1;	
	  a[i][j-1] = a[i][j]; 
	  a[i][j] = 0;	
  	}
    else if(a[i][j]!=0&&a[i][j]==a[i][j-1]&&n==1)
  	{
  	  f = 1;	
	  d++;		
   	  a[i][j] = 0;
	  a[i][j-1]*=2;
	  score+=a[i][j-1];		
  	}
   }
   for(i = 0;i!=4;i++)
  {
    if(a[i][1]!=0&&a[i][1]==a[i][0]&&d==0) 
 	{
	 f = 1;		
   	 a[i][1] = 0;
	 a[i][0]*=2;	
    }
  }
  if(f>0)  
  Produce();
  Init_Array();		
}                           

void Game::Right_Do() {
 int d = 0;
 for(int n = 0;n!=4;n++)
  for(j = 2;j>=0;j--)
  {
   for(i = 0;i!=4;i++)
   {
  	if(a[i][j]!=0&&a[i][j+1]==0&&(n==0||n==2||n==3))
  	{ 	
  	  f = 1;	
	  a[i][j+1] = a[i][j]; 
	  a[i][j] = 0;	
  	}
    else if(a[i][j]!=0&&a[i][j]==a[i][j+1]&&n==1)
  	{
  	  f = 1;	
	  d++;	
   	  a[i][j] = 0;
	  a[i][j+1]*=2;	
	  score+=a[i][j+1];	
  	}
   }
  }
   for(i = 0;i!=4;i++)
  {
    if(a[i][2]!=0&&a[i][2]==a[i][3]&&d==0) 
	{
	 f = 1;		
   	 a[i][2] = 0;
	 a[i][3]*=2;
	 score+=a[i][3];	
    }
  }
  if(f>0)  
  Produce();
  Init_Array();	
}

int main()
{ 
 system("title 2048");	
 system("mode con cols=38 lines=15");	
 Game game;	
 game.Console();
 getch();	
 return 0;	
}
