//Windows������c++̰ʳ�� 

#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <vector>
#include <ctime>

using namespace std;

void gotoxy(int x,int y){          //����Windows���꺯�� 
 COORD pos = {x,y};	
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);	
 SetConsoleCursorPosition(hOut,pos);
}

enum {                             //ö������������ʾ����(getch()����ֵ) 
 Up = 72,Down = 80,Left = 75,Right = 77,Enter = 13,Esc = 27	
};

class Snake_Body{                   //�ߵ�����ڵ���������  
  public:
   int x;	
   int y;
   char body;	
};

class Player_Data{                  //�����Ϣ�������� 
  public:	
   char grade[10];
   char name[10];  
   int score;	
};

int Snake_Speed = 100;             //ȫ�ֱ����ߵ��ٶ� 
char Snake_HeadShape = '#';        //��ͷͼ�� 
char Snake_BodyShape = '*';        //����ͼ�� 
char Snake_PointShape[3] = "*#";   //�˵�ָ��ͼ�� 

class Game_Map{                  //��Ϸ��ͼ��
  public:
   Game_Map();	
   void Creat_Map();
   void Show_Logo(int );
   void Creat_Food();
   void Creat_Food(Snake_Body *,int );
   int Stop_Menu();
   friend class Snake;
  private:
   int i,Map_Long,Map_Wide;
   char Map_Node; 
   Snake_Body Food;	
};

Game_Map::Game_Map(){              //��ʼ����ͼ��ʳ��
  Map_Long = 60;
  Map_Wide = 24;
  Map_Node = ' ';
  Food.body = '$';
  srand(time(NULL));               //��ʼ����������� 
  Creat_Map();
  Creat_Food();		
}

void Game_Map::Creat_Map(){        //�����ͼ
  int x = 2,y = 0,n = 0;	
  while(n<162)
  {	 
   gotoxy(x,y);
   cout<< Map_Node;  
   if(x<Map_Long&&y==0)
   {
    x++;
    Map_Node = '-';
   }
   if(x==Map_Long&&y<Map_Wide)
   {
   	y++;
   	Map_Node = '|';
   } 
   if(y==Map_Wide&&x>1)
   {
   	x--;
    Map_Node = '-';
   } 
   if(x==1&&y>0)
   {
   	 y--;
   	 Map_Node = '|';
   } 
   Sleep(10);
   n++;	
  }
  for(i = 1;i!=19;i++)
  {
    gotoxy(Map_Long+i,5);
	cout<< "_";	
  }
  gotoxy(65,2);	
  cout<< "�÷�";                  //��ʼ��������ʾ�� 
  gotoxy(66,4);
  cout<< '0';
}

void Game_Map::Show_Logo(int n){   //��Ϸ�ж���(��ʾ)
  int x = Map_Long+3,y = 10;
  if(n==1)
  {	
   gotoxy(x,y);	
   cout<< " *********** ";
   gotoxy(x,y+1);	
   cout<< "*           *";
   gotoxy(x,y+2);
   cout<< "*  !     !  *";
   gotoxy(x,y+3);
   cout<< "*           *";
   gotoxy(x,y+4);
   cout<< "*   !!!!!   *";
   gotoxy(x,y+5);
   cout<< " *********** ";
   gotoxy(x,y+7);
   cout<< " ���С��! "; 
  }
  else if(n==2)
  {
   gotoxy(x,y);	
   cout<< " *********** ";
   gotoxy(x,y+1);	
   cout<< "*           *";
   gotoxy(x,y+2);
   cout<< "*  ?     ?  *";
   gotoxy(x,y+3);
   cout<< "*           *";
   gotoxy(x,y+4);
   cout<< "*   ?????   *";
   gotoxy(x,y+5);
   cout<< " *********** ";	
   gotoxy(x,y+7);
   cout<< " ҪС���ˣ� ";
  }
}

void Game_Map::Creat_Food(){       //��ʼ��ʳ��
   Flag: 
	Food.x = rand()%57+2;
    Food.y = rand()%22+1;
    if(Food.x==7&&Food.y==3)
     goto Flag;
    if(Food.x==8&&Food.y==3)
     goto Flag;
    if(Food.x==9&&Food.y==3)
     goto Flag;
	gotoxy(Food.x,Food.y);
    cout<< Food.body;
}
                                   //�������ʳ���Ҳ��������ͻ 
void Game_Map::Creat_Food(Snake_Body *s,int length){
  flag:
    Food.x = rand()%57+2;
    Food.y = rand()%22+1;
	for(i = 0;i!=length-1;i++)
  {
	if(Food.x==s[i].x&&Food.y==s[i].y)
	goto flag; 	
  } 
   gotoxy(Food.x,Food.y);
   cout<< Food.body;			
}

int Game_Map::Stop_Menu(){           //��ͣ�˵� 
   int x = Map_Long+6,y = 20; 
   gotoxy(Map_Long+1,y-2);
   cout<< "__________________"; 	
   gotoxy(x,y);
   cout<< "! ������Ϸ";
   gotoxy(x,y+1);
   cout<< "! �˳���Ϸ"; 
   gotoxy(x-3,y);
   cout<< Snake_PointShape;
   while(true)
  {
   Flag:switch(getch())
   {
    case Up:
      if(y>20)
      {
	    y--;	
        gotoxy(x-3,y+1);
	    cout<< "  ";
	    gotoxy(x-3,y);
	    cout<< Snake_PointShape;	
      }   
      else goto Flag;
      break;
	case Down:
	  if(y<21)
      {
       y++;	
	   gotoxy(x-3,y-1);
	   cout<< "  ";
	   gotoxy(x-3,y);
	   cout<< Snake_PointShape;
      }
      else goto Flag;
      break;
	case Enter:
	  gotoxy(Map_Long+1,y-2);
      cout<< "                   ";	
	  gotoxy(x-3,y);
      cout<< "              ";
      gotoxy(x-3,y+1);
      cout<< "              ";		
	  switch(y)
	  {
	   case 20:
	   	 return 1;
	   case 21:
		 return 0; 	
	  } break;
    }
  }
}

class Snake{                       //̰ʳ����
  public:	
    Snake();
    void Console();	
    void Move_Up();
    void Move_Down();
    void Move_Left(); 
    void Move_Right();
    void Add_Body();
    void Snake_Dead();
    int Show_Score();
    friend class Game_Map;
    friend class Snake_Game;
  private:	  
    int Head_X,Head_Y,Length;
	int i,Move_Flag,Dead_Flag; 
	vector<Snake_Body> snake;      //��������������  
	Snake_Body aBody;
    Game_Map map; 	
};

Snake::Snake(){                    //��ʼ����
  int i;	
   Head_X = 6;	
   Head_Y = 3;
   Length = 3;
   Dead_Flag = 1;
   aBody.body = ' '; 
   snake.resize(Length);           //��ʼ����̬����(����)���� 
   snake[0].body = Snake_HeadShape;
   for(i = 1;i<Length-1;i++)
   {	
    snake[i].body = Snake_BodyShape;		
   }
   snake[Length-1].body = ' ';
   snake[0].x = Head_X;                    
   snake[0].y = Head_Y;    
   while(snake[0].x<Head_X+4)
   {
   	for(i = Length-1;i!=0;i--)
    {
     snake[i].x = snake[i-1].x;
     snake[i].y = snake[i-1].y;
    }
    snake[0].x++;
    for(i = 0;i<Length;i++)
    {
	  gotoxy(snake[i].x,snake[i].y);
      cout<< snake[i].body;
    }
   }
}

void Snake::Console(){             //���������ƺ��� 
   while(true)
   {
    Flag:
	switch(getch())
	{
     case Up:if(Move_Flag!=2)Move_Up();
	            else Move_Down();
				if(Dead_Flag==0)
				return;
				goto Flag;break;	
     case Down:if(Move_Flag!=1)Move_Down();
	            else Move_Up();
				if(Dead_Flag==0)
				return;
				goto Flag;break;	
     case Left:if(Move_Flag!=4)Move_Left();
                else Move_Right();
				if(Dead_Flag==0)
				return;
				goto Flag;break;
	 case Right:if(Move_Flag!=3)Move_Right();
	            else Move_Left();
				if(Dead_Flag==0)
				return;
				goto Flag;break;
	 case Esc:Dead_Flag = map.Stop_Menu();
	    if(Dead_Flag==0)
			return;
		else goto Flag;
		    break; 
	 default: switch(Move_Flag)
	 {
	  case 1:Move_Up();break;
	  case 2:Move_Down();break;
	  case 3:Move_Left();break;
	  case 4:Move_Right();break; 
	  default:goto Flag;	
	 }								
    } 
   }	
}
   
void Snake::Move_Up(){             //���������ƶ�
   Move_Flag = 1; 
   while(true)
   {
	if(kbhit()!=0)
   	{
      return ;
	}
    if(snake[0].x==map.Food.x&&snake[0].y==map.Food.y)
	{	                           //�ж��Ƿ�Ե�ʳ�� 
	  Add_Body();                 
	  Show_Score();                //ʵʱ��ʾ���� 
	  Snake_Body s[Length];     
	  for(i = 0;i!=Length;i++)
	  {
	  	s[i] = snake[i];
	  }
	  map.Creat_Food(s,Length);	
	}
	Snake_Dead();                  //�����ж� 
	if(Dead_Flag==0)
	 return;
    for(int i = Length-1;i>0;i--)
    {
  	 snake[i].x = snake[i-1].x;
     snake[i].y = snake[i-1].y;
    }
     snake[0].y--;
     Sleep(Snake_Speed);
    for(int i = 0;i<Length;i++)
    {
     gotoxy(snake[i].x,snake[i].y);
     cout<< snake[i].body;
    }
	if(snake[0].x==2||map.Map_Long-snake[0].x==1)
  	map.Show_Logo(1);
  	else
  	map.Show_Logo(2);    
   }		
}

void Snake::Move_Down(){          //���������ƶ�
  Move_Flag = 2;
  while(true)
   {
	if(kbhit()!=0)
   	{
      return;
	}
	if(snake[0].x==map.Food.x&&snake[0].y==map.Food.y)
	{	                         
	  Add_Body();
	  Show_Score();
	  Snake_Body s[Length];
	  for(i = 0;i!=Length;i++)
	  {
	  	s[i] = snake[i];
	  }
	  map.Creat_Food(s,Length);	
	}
	Snake_Dead();
	if(Dead_Flag==0)
	 return;
    for(int i = Length-1;i>0;i--)
    {
  	 snake[i].x = snake[i-1].x;
     snake[i].y = snake[i-1].y;
    }
     snake[0].y++;
     Sleep(Snake_Speed);
    for(int i = 0;i<Length;i++)
    {
     gotoxy(snake[i].x,snake[i].y);
     cout<< snake[i].body;
    }   
	if(snake[0].x==2||map.Map_Long-snake[0].x==1)
  	map.Show_Logo(1);
  	else
  	map.Show_Logo(2); 
   }
}

void Snake::Move_Left(){           //���������ƶ�
  Move_Flag = 3;
  while(true)
   {
	if(kbhit()!=0)
   	{
      return;
	}
	if(snake[0].x==map.Food.x&&snake[0].y==map.Food.y)
	{	
	  Add_Body();
	  Show_Score();
	  Snake_Body s[Length];
	  for(i = 0;i!=Length;i++)
	  {
	  	s[i] = snake[i];
	  }
	  map.Creat_Food(s,Length);	
	}
    Snake_Dead();
    if(Dead_Flag==0)
	 return;
    for(int i = Length-1;i>0;i--)
    {
  	 snake[i].x = snake[i-1].x;
     snake[i].y = snake[i-1].y;
    }
     snake[0].x--;
     Sleep(Snake_Speed);
    for(int i = 0;i<Length;i++)
    {
     gotoxy(snake[i].x,snake[i].y);
     cout<< snake[i].body;
    }
	if(snake[0].y==1||map.Map_Wide-snake[0].y==1)    
	map.Show_Logo(1);
	else
	map.Show_Logo(2);
   }
}

void Snake::Move_Right(){          //���������ƶ�    
  Move_Flag = 4;
  while(true)
   {
	if(kbhit()!=0)
   	{
      return ;
	}
	if(snake[0].x==map.Food.x&&snake[0].y==map.Food.y)
	{	
	  Add_Body();
	  Show_Score();
	  Snake_Body s[Length];
	  for(i = 0;i!=Length;i++)
	  {
	  	s[i] = snake[i];
	  }
	  map.Creat_Food(s,Length);	
	}
	Snake_Dead();
	if(Dead_Flag==0)
	 return;
    for(int i = Length-1;i>0;i--)
    {
  	 snake[i].x = snake[i-1].x;
     snake[i].y = snake[i-1].y;
    }
     snake[0].x++;
     Sleep(Snake_Speed);
    for(int i = 0;i<Length;i++)
    {
     gotoxy(snake[i].x,snake[i].y);
     cout<< snake[i].body;
    }  
	if(snake[0].y==1||map.Map_Wide-snake[0].y==1)    
	map.Show_Logo(1);
	else
	map.Show_Logo(2);  
   } 
}	

void Snake::Add_Body(){            //��������
  snake[Length-1].body = Snake_BodyShape; 
  Length++;
  snake.push_back(aBody);		
}

void Snake::Snake_Dead(){
  int i = 1;
  if(snake[0].x==map.Map_Long||snake[0].y==map.Map_Wide||snake[0].x==1||snake[0].y==0)
  {
    Dead_Flag = 0;	
  }
  while(snake[i].body!=' ')
  {
    if(snake[i].x==snake[0].x&&snake[i].y==snake[0].y)	
    Dead_Flag = 0;
  	i++; 
  }		
}

int Snake::Show_Score(){           //��ʾ����
  gotoxy(65,2);	 
  cout<< "�÷�";
  gotoxy(66,4);
  cout<< Length-3;
  return Length-3;	
}

class Snake_Game{                  //̰ʳ����Ϸ�� 
  public:
   Snake_Game();
   void Start_Game();
   void Start_Snake();
   void Game_Menu();
   void Game_Setting();
   void Color_Select();
   void Grade_Select();
   void Snake_Select();
   void SnakeGame_Logo(int );
   void GameOver_Logo();
   void Show_Top();
   void Read_Data();
   void Init_Data();
   void Handle_Data(int &);
   void Game_How(); 
  private:
   int i,Player_Score,Menu_X,Menu_Y,Top[5]; 
   Player_Data *p,player[4];
   fstream DataFile;
};

Snake_Game::Snake_Game(){          //��ʼ����Ϸ
  p = NULL;
  Menu_X = 0;
  Menu_Y = 0;
  Read_Data();
  SnakeGame_Logo(15);
}
 
void Snake_Game::Start_Game(){     //�����߶���ʼ��Ϸ                
	Snake _snake;
    _snake.Console();
    system("cls");
    GameOver_Logo();                  
    Player_Score = _snake.Show_Score();
    Handle_Data(Player_Score);
}
	
void Snake_Game::Start_Snake(){
   system("cls");
   Start_Game();	
}

void Snake_Game::SnakeGame_Logo(int speed){         //��ʼ���������˵�                     
  i = 0,Menu_X = 1,Menu_Y = 0;
 while(i<197)
 {	 
   if(Menu_X<77&&Menu_Y==0)
   { 
     Menu_X++;
	 gotoxy(Menu_X,Menu_Y);
     cout<< '~';	 
   }
   if(Menu_X==77&&Menu_Y<24)
   {
    	
   	gotoxy(Menu_X,Menu_Y);
    cout<< '|';	Menu_Y++;
  } 
   if(Menu_Y==24&&Menu_X>1)
   { 	
   	gotoxy(Menu_X,Menu_Y);
    cout<< '~';
	Menu_X--;	
   } 
   if(Menu_X==1&&Menu_Y>0)
   { 
     Menu_Y--;
   	 gotoxy(Menu_X,Menu_Y);
     cout<< '|'; 
   } 
   Sleep(speed);
   	i++;
 }
   Menu_X = 60,Menu_Y = 2; 
   while(Menu_X>4)
  {
   gotoxy(Menu_X,Menu_Y);
   cout<< "*********** \n";  
   gotoxy(Menu_X,Menu_Y+1);
   cout<< "*********** \n";	 
   gotoxy(Menu_X,Menu_Y+2);
   cout<< "** \n";	 
   gotoxy(Menu_X,Menu_Y+3);
   cout<< "** \n";	 
   gotoxy(Menu_X,Menu_Y+4);
   cout<< "*********** \n";
   gotoxy(Menu_X,Menu_Y+5);
   cout<< "*********** \n";
   gotoxy(Menu_X,Menu_Y+6);
   cout<< "         ** \n";
   gotoxy(Menu_X,Menu_Y+7);
   cout<< "         ** \n";
   gotoxy(Menu_X,Menu_Y+8);
   cout<< "*********** \n";
   gotoxy(Menu_X,Menu_Y+9);
   cout<< "*********** \n";
   Sleep(speed);
   Menu_X--;	
  }
  Menu_X = 18,Menu_Y = 2;
  while(Menu_X<61)
  {
   gotoxy(Menu_X,Menu_Y);
   cout<< " ***********\n";  
   gotoxy(Menu_X,Menu_Y+1);
   cout<< " ***********\n";	 
   gotoxy(Menu_X,Menu_Y+2);
   cout<< " **\n";	 
   gotoxy(Menu_X,Menu_Y+3);
   cout<< " **\n";	 
   gotoxy(Menu_X,Menu_Y+4);
   cout<< " ***********\n";
   gotoxy(Menu_X,Menu_Y+5);
   cout<< " ***********\n";
   gotoxy(Menu_X,Menu_Y+6);
   cout<< " **\n";
   gotoxy(Menu_X,Menu_Y+7);
   cout<< " **\n";
   gotoxy(Menu_X,Menu_Y+8);
   cout<< " ***********\n";
   gotoxy(Menu_X,Menu_Y+9);
   cout<< " ***********\n";
   Sleep(speed);
   Menu_X++;	
  } 
  Menu_X = 48,Menu_Y = 2; 
   while(Menu_X>18)
  {
   gotoxy(Menu_X,Menu_Y);
   cout<< "**       ** \n";  
   gotoxy(Menu_X,Menu_Y+1);
   cout<< "***      ** \n";	 
   gotoxy(Menu_X,Menu_Y+2);
   cout<< "****     ** \n";	 
   gotoxy(Menu_X,Menu_Y+3);
   cout<< "** **    ** \n";	 
   gotoxy(Menu_X,Menu_Y+4);
   cout<< "**  **   ** \n";
   gotoxy(Menu_X,Menu_Y+5);
   cout<< "**   **  ** \n";
   gotoxy(Menu_X,Menu_Y+6);
   cout<< "**    ** ** \n";
   gotoxy(Menu_X,Menu_Y+7);
   cout<< "**     **** \n";
   gotoxy(Menu_X,Menu_Y+8);
   cout<< "**      *** \n";
   gotoxy(Menu_X,Menu_Y+9);
   cout<< "**       ** \n";
   Sleep(speed);
   Menu_X--;	
  }
  Menu_X = 32 ,Menu_Y = 2; 
   while(Menu_X<47)
  {
   gotoxy(Menu_X,Menu_Y);
   cout<< " ** \n";  
   gotoxy(Menu_X,Menu_Y+1);
   cout<< " **      **\n";	 
   gotoxy(Menu_X,Menu_Y+2);
   cout<< " **    **\n";	 
   gotoxy(Menu_X,Menu_Y+3);
   cout<< " **  **\n";	 
   gotoxy(Menu_X,Menu_Y+4);
   cout<< " ****\n";
   gotoxy(Menu_X,Menu_Y+5);
   cout<< " ***\n";
   gotoxy(Menu_X,Menu_Y+6);
   cout<< " ** **\n";
   gotoxy(Menu_X,Menu_Y+7);
   cout<< " **   **\n";
   gotoxy(Menu_X,Menu_Y+8);
   cout<< " **     **\n";
   gotoxy(Menu_X,Menu_Y+9);
   cout<< " **       **\n";
   Sleep(speed);
   Menu_X++;	
  }   
  Menu_X = 33,Menu_Y = 13;    
  while(Menu_Y>1)
  {
   gotoxy(Menu_X,Menu_Y);
   cout<< "     * \n";  
   gotoxy(Menu_X,Menu_Y+1);
   cout<< "    *** \n";	 
   gotoxy(Menu_X,Menu_Y+2);
   cout<< "   ** ** \n";	 
   gotoxy(Menu_X,Menu_Y+3);
   cout<< "  **   ** \n";	 
   gotoxy(Menu_X,Menu_Y+4);
   cout<< "  **   ** \n";
   gotoxy(Menu_X,Menu_Y+5);
   cout<< " ********* \n";
   gotoxy(Menu_X,Menu_Y+6);
   cout<< " **     ** \n";
   gotoxy(Menu_X,Menu_Y+7);
   cout<< "**       ** \n";
   gotoxy(Menu_X,Menu_Y+8);
   cout<< "**       ** \n";
   gotoxy(Menu_X,Menu_Y+9);
   cout<< "**       ** \n";
   gotoxy(Menu_X,Menu_Y+10);
   cout<< "            \n";
   Sleep(speed*2);
   Menu_Y--;	
  }	
 Menu_X = 3,Menu_Y = 12; 
 while(Menu_X<77)
 {
  gotoxy(Menu_X,Menu_Y);
  cout<< "_";	
  Menu_X++;	
 }
  
 Menu_X = 45,Menu_Y = 14; 
 while(Menu_X>4) 
 {
  gotoxy(Menu_X,Menu_Y);
   cout<< " * ** * \n";  
   gotoxy(Menu_X,Menu_Y+1);
   cout<< "* .  . * \n";	 
   gotoxy(Menu_X,Menu_Y+2);
   cout<< "*      * \n";	 
   gotoxy(Menu_X,Menu_Y+3);
   cout<< "*  -   * \n";	 
   gotoxy(Menu_X,Menu_Y+4);
   cout<< " *    *      * * \n";
   gotoxy(Menu_X,Menu_Y+5);
   cout<< "   *  *    * * * *         * \n";
   gotoxy(Menu_X,Menu_Y+6);
   cout<< "    *  * * *    * * *  * ** \n";
   gotoxy(Menu_X,Menu_Y+7);
   cout<< "     * * *       * * * * * \n";
   Sleep(speed*2+10);	
  Menu_X--;	
 } 	
   Menu_X = 41,Menu_Y = 15; 
   Sleep(200);
   gotoxy(Menu_X+4,Menu_Y);
   cout<< "! ��ʼ��Ϸ";
   Sleep(200);
   gotoxy(Menu_X+7,Menu_Y+2);
   cout<< "! ��Ϸѡ��";
   Sleep(200);
   gotoxy(Menu_X+10,Menu_Y+4);
   cout<< "! �˳���Ϸ";
   Sleep(200);
   gotoxy(Menu_X+13,Menu_Y+6);
   cout<< "! ������Ϸ";
   gotoxy(Menu_X,Menu_Y);
   cout<< Snake_PointShape;
  while(true)
  { 
   switch(getch())
   {
   	case Up: 
	   if(Menu_Y>15)
      {
	   Menu_X = Menu_X-3;
	   Menu_Y = Menu_Y-2;
	   gotoxy(Menu_X+3,Menu_Y+2);
	   cout<< "  ";
	   gotoxy(Menu_X,Menu_Y);
       cout<< Snake_PointShape;
      }
	   break;
   	case Down:
	   if(Menu_Y<21)
      { 
        Menu_X = Menu_X+3; 
	    Menu_Y = Menu_Y+2;
	    gotoxy(Menu_X-3,Menu_Y-2);
	    cout<< "  ";
	    gotoxy(Menu_X,Menu_Y);
        cout<< Snake_PointShape;
      }
	   break;
   	case Enter:
   	   switch(Menu_Y)
	  {
	   case 15:system("cls");
	           Start_Game();break;	  	
	   case 17:system("cls");
	           Game_Setting();break;  
	   case 19:exit(0);
	   case 21:Game_How();break;
	  } 		
      break;
   }
  }
}

void Snake_Game::GameOver_Logo(){       //�������� 
 int n = 0;
  Menu_X = 1,Menu_Y = 0;
  while(n<197)
 {	 
   if(Menu_X<77&&Menu_Y==0)
   { 
     Menu_X++;
	 gotoxy(Menu_X,Menu_Y);
     cout<< '~';	 
   }
   if(Menu_X==77&&Menu_Y<24)
   {
    	
   	gotoxy(Menu_X,Menu_Y);
    cout<< '|';	Menu_Y++;
  } 
   if(Menu_Y==24&&Menu_X>1)
   { 	
   	gotoxy(Menu_X,Menu_Y);
    cout<< '~';
	Menu_X--;	
   } 
   if(Menu_X==1&&Menu_Y>0)
   { 
     Menu_Y--;
   	 gotoxy(Menu_X,Menu_Y);
     cout<< '|'; 
   }  
   	n++;
 }	
 Menu_X = 25,Menu_Y = 2;
 gotoxy(Menu_X,Menu_Y); 
 cout<< "*****    *     *   *   *****";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+1); 
 cout<< "*       * *    ** **   *    ";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+2); 
 cout<< "*  **   ***    * * *   *****";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+3); 
 cout<< "*   *  *   *   *   *   *    ";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+4); 
 cout<< "*****  *   *   *   *   *****";
 
 Menu_X = 35,Menu_Y = 2;
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+6); 
 cout<< " ***    *   *  *****   **** ";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+7); 
 cout<< "*   *   *   *  *       *   *";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+8); 
 cout<< "*   *   *   *  *****   **** ";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+9); 
 cout<< "*   *    * *   *       *  * ";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+10); 
 cout<< " ***      *    *****   *   *";
 
 Menu_X = 6,Menu_Y = 12;
 Sleep(100);
 gotoxy(Menu_X,Menu_Y); 
 cout<< "  * ** * ";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+1); 
 cout<< " * > <  *";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+2); 
 cout<< " *      *";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+3); 
 cout<< " *  ^   *";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+4); 
 cout<< "  *    *      * *";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+5); 
 cout<< "    *  *    * * * *         *";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+6); 
 cout<< "     *  * * *    * * *  * ** ";
 Sleep(100);
 gotoxy(Menu_X,Menu_Y+7); 
 cout<< "      * * *       * * * * *  ";	
}

void Snake_Game::Game_Setting(){        //��Ϸ�����˵� 
  Menu_X = 4;
  Menu_Y = 4;
  gotoxy(8,4);	
  cout<< "! ��ɫѡ��";	
  gotoxy(8,6);
  cout<< "! �ȼ�ѡ��";
  gotoxy(8,8);
  cout<< "! ����ѡ��";
  gotoxy(8,10);
  cout<< "! Ӣ�۰�";
  gotoxy(4,4);
  cout<< Snake_PointShape;
  gotoxy(3,22);
  cout<< "���� [Up] �� [Down] ��ѡ��,�� [Enter]ȷ��,�� [Esc] ����";
  for(i = 0;i<20;i++)
  {
   gotoxy(30,i);
   cout<< "|";	
 }
 gotoxy(0,20);
 for(i = 0;i<80;i++)
 {
  cout<< "_";	
 }
 while(true)
 {
  Flag:switch(getch())
  {	
   case Up:
    if(Menu_Y>4)
    {
	 Menu_Y = Menu_Y-2;
	 gotoxy(Menu_X,Menu_Y+2);
	 cout<< "  ";
	 gotoxy(Menu_X,Menu_Y);
     cout<< Snake_PointShape;
    }
	else 
	goto Flag;
	break;
   case Down: 
    if(Menu_Y<10)
    {
	 Menu_Y = Menu_Y+2;
	 gotoxy(Menu_X,Menu_Y-2);
	 cout<< "  ";
	 gotoxy(Menu_X,Menu_Y);
     cout<< Snake_PointShape;
    }
	else 
	goto Flag;
	break;
   case Esc:
   	 system("cls");
     SnakeGame_Logo(0);break; 		
   case Enter:
   	switch(Menu_Y)
   {
    case 4:
     gotoxy(Menu_X,Menu_Y);	
     cout<< "  ";	
	 Color_Select();break;
	case 6: 
	 gotoxy(Menu_X,Menu_Y);	
     cout<< "  ";
	 Grade_Select();break;
	case 8: 
	 gotoxy(Menu_X,Menu_Y);	
     cout<< "  ";
	 Snake_Select();break;
	case 10: 
	 gotoxy(Menu_X,Menu_Y);	
     cout<< "  ";
     Show_Top();break;
   }  
  }	
 }	
}

void Snake_Game::Color_Select(){        //ɫ��ѡ��˵
   Menu_X = 45;
   Menu_Y = 4;
   gotoxy(Menu_X,Menu_Y);
   cout<< "! ��ɫ";
   gotoxy(Menu_X,6);
   cout<< "! ��ɫ  ";
   gotoxy(Menu_X,8);
   cout<< "! ��ɫ ";
   gotoxy(Menu_X,10);
   cout<< "! ��ɫ";
   gotoxy(Menu_X,12);
   cout<< "! ��ɫ";
   gotoxy(Menu_X,14);
   cout<< "! ��ɫ";
   gotoxy(Menu_X-4,Menu_Y);
   cout<< Snake_PointShape;
  while(true)
 {
  Flag:switch(getch())
  {
   case Esc:
   	gotoxy(Menu_X-4,Menu_Y);
   	cout<< "  ";
    Game_Setting();	 
   case Up:
    if(Menu_Y>4)
    {
	 Menu_Y = Menu_Y-2;
	 gotoxy(Menu_X-4,Menu_Y+2);
	 cout<< "  ";
	 gotoxy(Menu_X-4,Menu_Y);
     cout<< Snake_PointShape;
    }
	else 
	goto Flag;
	break;
   case Down: 
    if(Menu_Y<14)
    {
	 Menu_Y = Menu_Y+2;
	 gotoxy(Menu_X-4,Menu_Y-2);
	 cout<< "  ";
	 gotoxy(Menu_X-4,Menu_Y);
     cout<< Snake_PointShape;
    }
	else 
	goto Flag;
	break;	
   case Enter:
   	switch(Menu_Y)
   {
    case 4:     		
	 system("color 1");break;
	case 6: 
     system("color 4");break;
	case 8: 
     system("color 2");break;
    case 10:
     system("color 5");break;	
    case 12:
	 system("color 6");break;
	case 14:
	 system("color 7");break;	
   }  
  }	
 }	
}

void Snake_Game::Grade_Select(){        //��Ϸ�ȼ�ѡ��˵
   Menu_X = 45;
   Menu_Y = 4;
   gotoxy(Menu_X,Menu_Y);
   cout<< "! ��ϰ";
   gotoxy(Menu_X,6);
   cout<< "! ��   ";
   gotoxy(Menu_X,8);
   cout<< "! ��ͨ ";
   gotoxy(Menu_X,10);
   cout<< "! ����   ";
   gotoxy(Menu_X,12);
   cout<< "! ����    ";
   gotoxy(Menu_X,14);
   cout<< "        ";
   gotoxy(Menu_X-4,Menu_Y);
   cout<< Snake_PointShape;
   while(true)
  {
   Flag:switch(getch())
   {
    case Esc:
     gotoxy(Menu_X-4,Menu_Y);
     cout<< "  ";
     Game_Setting();	
    case Up:
     if(Menu_Y>4)
     {
	  Menu_Y = Menu_Y-2;
	  gotoxy(Menu_X-4,Menu_Y+2);
	  cout<< "  ";
	  gotoxy(Menu_X-4,Menu_Y);
      cout<< Snake_PointShape;
     }
	 else 
	 goto Flag;
 	 break;
    case Down: 
     if(Menu_Y<12)
     {
 	  Menu_Y = Menu_Y+2; 
	  gotoxy(Menu_X-4,Menu_Y-2);
	  cout<< "  ";
	  gotoxy(Menu_X-4,Menu_Y);
      cout<< Snake_PointShape;
     }
	 else 
	 goto Flag;
	 break;	
    case Enter:
    switch(Menu_Y)
    {
     case 4:Snake_Speed = 400;
 	  gotoxy(Menu_X-4,4);
   	  cout<< "  ";  	
	  Game_Setting();	  		
	  break;
	 case 6:Snake_Speed = 200; 
	  gotoxy(Menu_X-4,6);
   	  cout<< "  ";  	
	  Game_Setting();
      break;
	 case 8:Snake_Speed = 100;
	  gotoxy(Menu_X-4,8);
   	  cout<< "  ";  	
	  Game_Setting();
      break;
     case 10:Snake_Speed = 50;
      gotoxy(Menu_X-4,10);
   	  cout<< "  ";  	
	  Game_Setting();
      break;	
     case 12:Snake_Speed = 20;
	  gotoxy(Menu_X-4,Menu_Y);
   	  cout<< "  ";  	
	  Game_Setting();	
	  break;	
    }  
   }	
 }	
}

void Snake_Game::Snake_Select(){        //����״ѡ��˵� 
   Menu_X = 45;
   Menu_Y = 4;
   gotoxy(Menu_X,Menu_Y);
   cout<< "! **#     ";
   gotoxy(Menu_X,6);
   cout<< "! -->    ";
   gotoxy(Menu_X,8);
   cout<< "! ~~@    ";
   gotoxy(Menu_X,10);
   cout<< "         ";
   gotoxy(Menu_X,12);
   cout<< "         ";
   gotoxy(Menu_X,14);
   cout<< "         ";
   gotoxy(Menu_X-4,Menu_Y);
   cout<< Snake_PointShape;
  while(true)
 {
  Flag:switch(getch())
  {
   case Esc:
   	gotoxy(Menu_X-4,Menu_Y);
   	cout<< "  ";
    Game_Setting();
   case Up:
    if(Menu_Y>4)
    {
	 Menu_Y = Menu_Y-2;
	 gotoxy(Menu_X-4,Menu_Y+2);
	 cout<< "  ";
	 gotoxy(Menu_X-4,Menu_Y);
     cout<< Snake_PointShape;
    }
	else 
	goto Flag;
	break;
   case Down: 
    if(Menu_Y<8)
    {
	 Menu_Y = Menu_Y+2;
	 gotoxy(Menu_X-4,Menu_Y-2);
	 cout<< "  ";
	 gotoxy(Menu_X-4,Menu_Y);
     cout<< Snake_PointShape;
    }
	else 
	goto Flag;
	break;	
   case Enter:
   	switch(Menu_Y)
   {
    case 4:     		
	 strcpy(Snake_PointShape,"*#");
	 Snake_HeadShape = '#';
	 Snake_BodyShape = '*';
	 gotoxy(Menu_X-4,4);
	 cout<< "  ";  	
	 Game_Setting();
	 break;
	case 6: 
     strcpy(Snake_PointShape,"->");
	 Snake_HeadShape = '>';
	 Snake_BodyShape = '-';
	 gotoxy(Menu_X-4,6);
	 cout<< "  ";  	
	 Game_Setting();
	 break;
	case 8:
	 strcpy(Snake_PointShape,"~@");
	 Snake_HeadShape = '@';
	 Snake_BodyShape = '~'; 
	 gotoxy(Menu_X-4,8);
	 cout<< "  ";  	
	 Game_Setting();
     break;	
   }  
  }	
 } 	
}

void Snake_Game::Read_Data(){           //��ȡ������� 
  DataFile.open("Data.dat",ios::in|ios::binary);
  if(!DataFile)
 {
  cerr << "open error"<< endl;
  return ;	
 } 
  for(i = 0;i!=4;i++)
  {	
    p = new Player_Data;
  	DataFile.read((char *)p,sizeof(Player_Data));
	player[i] = *p;
	delete p;
  }
  DataFile.close(); 
  strcpy(player[0].grade,"��");
  strcpy(player[1].grade,"��ͨ");
  strcpy(player[2].grade,"����");
  strcpy(player[3].grade,"����");
}

void Snake_Game::Init_Data(){           //��ʼ��������� 
  DataFile.open("Data.dat",ios::out|ios::binary);
  if(!DataFile)
  {
   cerr << "open error"<< endl;
   return;	
  }
  for(i = 0;i!=4;i++)
  {
   strcpy(player[i].name,"NULL");	
   player[i].score = 0;	
  }
  strcpy(player[0].grade,"��");
  strcpy(player[1].grade,"��ͨ");
  strcpy(player[2].grade,"����");
  strcpy(player[3].grade,"����");
  for(i = 0;i!=4;i++)
  {
    p = &player[i];	
  	DataFile.write((char *)p,sizeof(Player_Data));
  }	
  DataFile.close();		
}

void Snake_Game::Show_Top(){            //��ʾӢ�۰� 
   Menu_X = 45;
   Menu_Y = 4;
  while(Menu_Y<15) 
  {
   gotoxy(Menu_X,Menu_Y);
   cout<< "          ";
   Menu_Y = Menu_Y+2;
  }
   Menu_X = 40;
   Menu_Y = 4;
   gotoxy(Menu_X,Menu_Y);
   cout<< "| �ȼ� |---";
   gotoxy(Menu_X+12,Menu_Y); 
   cout<< "| �ǳ� |----";
   gotoxy(Menu_X+24,Menu_Y);
   cout<< "| ���� |";
   gotoxy(Menu_X+1,Menu_Y+2);
   cout<< '['<< player[0].grade<< ']';
   gotoxy(Menu_X+1,Menu_Y+4);
   cout<< '['<< player[1].grade<< ']';
   gotoxy(Menu_X+1,Menu_Y+6);
   cout<< '['<< player[2].grade<< ']';
   gotoxy(Menu_X+1,Menu_Y+8);
   cout<< '['<< player[3].grade<< ']';
   
   gotoxy(Menu_X+13,Menu_Y+2);
   cout<< '['<< player[0].name<< ']';
   gotoxy(Menu_X+13,Menu_Y+4);
   cout<< '['<< player[1].name<< ']';
   gotoxy(Menu_X+13,Menu_Y+6);
   cout<< '['<< player[2].name<< ']';
   gotoxy(Menu_X+13,Menu_Y+8);
   cout<< '['<< player[3].name<< ']';   
   
   gotoxy(Menu_X+25,Menu_Y+2);
   cout<< '['<< player[0].score<< ']';
   gotoxy(Menu_X+25,Menu_Y+4);
   cout<< '['<< player[1].score<< ']';
   gotoxy(Menu_X+25,Menu_Y+6);
   cout<< '['<< player[2].score<< ']';
   gotoxy(Menu_X+25,Menu_Y+8);
   cout<< '['<< player[3].score<< ']';
   
   gotoxy(Menu_X+2,Menu_Y+14);
   cout<< "�� [R] ����������!";
   if(getch()=='r')
   {
   	gotoxy(Menu_X+2,Menu_Y+15);
   	cout<< "��/��?(Y/N)";
   	if(getch()=='y')
   	{
   	 Init_Data();	
   	}
   	else;
   }
    system("cls");
    Game_Setting();
}

void Snake_Game::Handle_Data(int &score){           //�������
  switch(Snake_Speed)
  {
   case 20:
   	 if(Player_Score>player[3].score)
   	 {
	  player[3].score = score;
	  gotoxy(50,16);	
   	  cout<< "������!";
	  gotoxy(50,17); 	
   	  cout<< "������Ӣ���ǳ� :";
   	  gotoxy(50,18);	 	
   	  cin>> player[3].name;	 	
   	 }
   	 else
   	 {
   	  gotoxy(40,17);
	  cout<< "�����Ŭ���� !";
	  gotoxy(40,18);
	  cout<< "����������� !";	 
     }
	 break;	
   case 50:
     if(Player_Score>player[2].score)
   	 {
	  player[2].score = score;
	  gotoxy(50,16);	
   	  cout<< "������!";
	  gotoxy(50,17); 	
   	  cout<< "������Ӣ���ǳ� :";
   	  gotoxy(50,18);	 	
   	  cin>> player[2].name;	 	
   	 }
   	 else
   	 {
   	  gotoxy(40,17);
	  cout<< "�����Ŭ���� !";
	  gotoxy(40,18);
	  cout<< "�����������";
     }
	 break;
   case 100:
     if(Player_Score>player[1].score)
   	 {
	  player[1].score = score;
	  gotoxy(50,16);	
   	  cout<< "������!";
	  gotoxy(50,17); 	
   	  cout<< "������Ӣ���ǳ� :";
   	  gotoxy(50,18);	 	
   	  cin>> player[1].name;	 	
   	 }
   	 else
   	 {
   	  gotoxy(40,17);
	  cout<< "�����Ŭ���� !";
	  gotoxy(40,18);
	  cout<< "�����������";
     } 
	 break;
   case 200:
     if(Player_Score>player[0].score)
   	 {
   	  player[0].score = score;
	  gotoxy(50,16);	
   	  cout<< "������!";
	  gotoxy(50,17); 	
   	  cout<< "������Ӣ���ǳ� :";
   	  gotoxy(50,18);	  	 	
   	  cin>> player[0].name;	 	
   	 }
   	 else
   	 {
   	  gotoxy(40,17);
	  cout<< "�����Ŭ���� !";
	  gotoxy(40,18);
	  cout<< "�����������";
     }
	 break;	
	case 400:break; 
  }	
  DataFile.open("Data.dat",ios::out|ios::binary);
  if(!DataFile)
  {
   cerr << "open error"<< endl;
   return ;	
  }
  for(i = 0;i!=4;i++)
  {
    p = &player[i];	
  	DataFile.write((char *)p,sizeof(Player_Data));
  }	
  DataFile.close();
  getch();
  system("cls");
  SnakeGame_Logo(15);
}

void Snake_Game::Game_How(){            //��Ϸ˵�� 
  system("cls");	
   i = 0,Menu_X = 20,Menu_Y = 5;
  while(i!=110)
 {
  gotoxy(Menu_X,Menu_Y);
  cout<< '*';
  if(Menu_X!=60&&Menu_Y==5)	
  {
  	Menu_X++;
  }	
  if(Menu_X==60&&Menu_Y!=20)
  {
  	Menu_Y++;
  }
  if(Menu_X!=20&&Menu_Y==20)
  {
  	Menu_X--;
  }
  if(Menu_X==20&&Menu_Y!=5)
  {
  	Menu_Y--;
  }
  i++;
 }
 Menu_X = 25,Menu_Y = 8;
 gotoxy(Menu_X,Menu_Y);
 cout<< "ͨ����[Up]����[Down]����[left] ";
 gotoxy(Menu_X,Menu_Y+2);
 cout<< "����[Right]���������ߵ��ƶ����� ";
 gotoxy(Menu_X,Menu_Y+4); 
 cout<< "����Ե�ʳ���������ײ��ǽ ";
 gotoxy(Menu_X,Menu_Y+6);
 cout<< "���Լ�����ô��Ϸ���� .��һ����";
 gotoxy(Menu_X,Menu_Y+8);
 cout<< "Ϸ��������ݣ�ģʽ������Ӣ�۰�";	
 getch();
 system("cls");
 SnakeGame_Logo(0);		
}

int main()
{	
 system("title Snake");                  //���ñ��� 
 system("mode con cols=80 lines=25");	 //������ʾ��С 
 system("color 2");                      //���ó�ʼ��ɫ 
 Snake_Game snakegame;                   //������Ϸ����� 
 getch();	
 return 0;	
}
