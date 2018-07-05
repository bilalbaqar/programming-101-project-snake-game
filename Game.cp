//Header Files
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

//srand funtion
void srand( unsigned seed );

//Staring Functions
void Welcome_screen(void);
void Main_menu(void);
void Credits(void);
void Title(void);
void Enter_username(int player_number);
void Username(char name_input[15]);
void Instructions(void);
int File_players(void);


//Main functions
void Snakegame(int player_number);
void Draw_snake_game (char grid[100][100], int player_number, int life);
void Scoring(int player_number,int life);
void Level_change(int level);
void Snake_hit(int life);

//Bonus
void draw_bonus( char grid[][100]);
void bonus_level(int level,int player_number);
void bonus_level_change(int level);

//Ending Functions
void Highscores(int player_number,int &exit);
void Game_end(int player_number,int &exit);
void Save_player_score(int player_number);


//Global Variables
struct players //Structure
{
	char name[15];
	int score;
};
struct players p[100]; //Structure Array
int speed;








int main()
{
	Welcome_screen();//only loading + enter 

	Main_menu();//*CREDITS & *PLAY GAME

	int no_of_players=File_players();//checks the file for saved players and stores them in the structure player


	for(int player_number=no_of_players; player_number<99 ; player_number++ )//Loop of 'number of player'
	{
		
		Enter_username(player_number);//Entering username
		Instructions();//Instructions on how to play

		Snakegame(player_number);

		int exit=0;//when 1 breaks the loop, it becomes 1 when E is pressed in the Game_end function. 
		Save_player_score(player_number);//function called to store the players score and name to file 
		
		Game_end(player_number,exit);//provides the option of *HIGHSCORES(after which function is called) *PLAY AGAIN(function ends) *EXIT (function ends with exit=1)
		if (exit==1)
		{
			break;
		}
	}
	return 0;
}

int File_players(void)
{
	FILE *p1,*p2;//pointers declared to save adress of files 
	do {
		p1=fopen("playernames.txt","a+"); //files with the names of the players is opened
	}while(p1==NULL);//keeps trying to open if the file isnt opening

	int no_of_players=0,i=0,j=0;//number of players already in the file
	char one_character;
	while((one_character=getc(p1)) != EOF) 	//character by character is stored in one_character variable.
	{
		if(one_character=='\n')//when a line break arises
		{
			p[j].name[i]='\0';//string closes
			i=0;//new string starts
			j++;//new strings starts
			no_of_players++;//no of players in the file already++
		}	
		else 
		{
			
			p[j].name[i]=one_character;//character stored in the index positions of the string 
			i++;
		}
		
	}
	fclose(p1);
	do{
	p2=fopen("playerscores.txt","a+");//files with the scores of the players is opened
	}while(p1==NULL);//keeps trying to open if the file isnt opening

	for (int index=0;index<no_of_players;index++)//loop to store score in different array positions
	{
		fscanf(p2,"%d\n", &p[index].score);
	}
	fclose(p2);


	return no_of_players;//returns the number of players in the file

}
void Title(void)
{
	
	printf("\n");
	printf("        ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
	printf("         þþþþ  þþ  þ   þþþ   þ  þþ þþþþþ    þþþþ   þþþ    þþ  þþþ  þþþþþ\n");
	printf("        þ      þþ  þ   þ þ   þ þþ  þ       þ       þ þ    þþ  þþþ  þ    \n");
	printf("        þþ     þþþ þ   þ þ   þ þ   þ      þ        þ þ    þþ  þþþ  þ    \n");
	printf("         þþþ   þ þ þ  þþ þþ  þþþ   þþþþ   þ    þ  þþ þþ  þþþþ þþþ  þþþþ \n");
	printf("            þ  þ þþþ  þþþþþ  þ þþ  þ      þ    þ  þþþþþ  þ  þþ þþ  þ    \n");
	printf("            þ  þ  þþ  þ   þþ þ þþ  þ       þ   þ  þ   þþ þ  þþ þþ  þ    \n");
	printf("        þþþþ   þ   þ þþ   þþ þ  þþ þþþþþ    þþþþ þþ   þþ þ  þþ þþ  þþþþþ\n");
	printf("        ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ\n");
	printf("        \n");
	printf("        \n");
	}


void Welcome_screen(void)//Title+Loading+Press enter
{

	Title();

	printf("\n\n\n\n\n\n\n");
	printf("        ################################################################\n");
	printf("        #                                                              #\n");
	printf("        #        ***  *   **     **                                    #\n");
	printf("        #         *   **   *      *                                    #\n");
	printf("        #         *   **  *       *                                    #\n");
	printf("        #          * * *  *  ***  *  ***  ***  ***** ***  ***          #\n");
	printf("        #          * * *  * *   * * *  * *   *  *  **  * *   *         #\n");
	printf("        #          * *  **  ***** * *    *   *  *  *   * *****         #\n");
	printf("        #           *   **  *     * *    *   *  *  *   * *             #\n");
	printf("        #           *   *    *** *** ***  ***  ****** *** ***          #\n");
	printf("        #                                                              #\n");
	printf("        ################################################################\n");
	printf("\n\n\n\n\n");
	printf("                                   Loading                              \n");


	printf("                            ");

	for (int timer=0; timer<20;timer++)//printing dots for loading effect
	{
		printf(".");
		Sleep(200);
	}
	system("cls");

	
	Title();

	printf("\n\n\n\n\n\n\n");
	printf("        ################################################################\n");
	printf("        #                                                              #\n");
	printf("        #        ***  *   **     **                                    #\n");
	printf("        #         *   **   *      *                                    #\n");
	printf("        #         *   **  *       *                                    #\n");
	printf("        #          * * *  *  ***  *  ***  ***  ***** ***  ***          #\n");
	printf("        #          * * *  * *   * * *  * *   *  *  **  * *   *         #\n");
	printf("        #          * *  **  ***** * *    *   *  *  *   * *****         #\n");
	printf("        #           *   **  *     * *    *   *  *  *   * *             #\n");
	printf("        #           *   *    *** *** ***  ***  ****** *** ***          #\n");
	printf("        #                                                              #\n");
	printf("        ################################################################\n");
	printf("\n\n\n\n\n\n");
	printf("                                 Press Enter                            \n");

	getchar();

	system("cls");
}

void Main_menu(void)//PLay game+Credits
{
	char menu;

	Title();
	printf("\n\n\n\n\n\n");
	printf("             ***     **      *          ***     **                      \n");
	printf("              **    **                   **    **                       \n");
	printf("              **    **                   **    **                       \n");
	printf("              * *  * *  *** ** *****     * *  * *  *** ***** ** **      \n");
	printf("              * *  * *    *  *  *  *     * *  * * *   * *  *  *  *      \n");
	printf("              *  **  *  ***  *  *  *     *  **  * ***** *  *  *  *      \n");
	printf("              *  **  * *  *  *  *  *     *  **  * *     *  *  *  *      \n");
	printf("              **    *****************    **    *** *** ****** *****     \n");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("                              Enter to PLAY GAME                       \n\n\n\n");
	printf("                             Press C for CREDITS                        \n");
	
	cscanf("%c", &menu);

	if (menu=='c'||menu=='C')
	{
		system("cls");
		Credits();
	}


	system("cls");

	
}


void Credits(void)//Credits+Back to Main menu
{
	Title();
	printf("\n\n\n");
	printf("                               +--------------+                         \n");
	printf("                               |   Made by    |                         \n");
	printf("                               | ÄÄÄÄÄÄÄÄÄÄÄÄ |                         \n");
	printf("                               | BILAL  BAQAR |                         \n");
	printf("                               |              |                         \n");
	printf("                               | MARIAM AAMIR |                         \n");
	printf("                               +--------------+                         \n\n\n\n\n");
	printf("                               +--------------+                         \n");
	printf("                               |              |                         \n");
	printf("                               |C Programming |                         \n");
	printf("                               |              |                         \n");
	printf("                               |   Project    |                         \n");
	printf("                               |              |                         \n");
	printf("                               |   BICSE-8    |                         \n");
	printf("                               |              |                         \n");
	printf("                               |    NUST      |                         \n");
	printf("                               |              |                         \n");
	printf("                               |    SEECS     |                         \n");
	printf("                               +--------------+                         \n\n\n\n");
	printf("                                 Press Enter         \n");

	getchar();
	system("cls");
	Main_menu();

}

void Username(char name_input[15])
{
	Title();
	printf("\n\n\n\n\n                              +--------------------+                    \n"); 
	printf("                              |                    |                    \n"); 
	printf("                              |   ENTER USERNAME   |                    \n"); 
	printf("                              |                    |                    \n"); 
	printf("                              +--------------------+                    \n"); 
	printf("                                                                        \n"); 
	printf("                                 +--------------+                       \n"); 
	printf("                                 |%-14s|                       \n",name_input); 
	printf("                                 +--------------+                       \n"); 
}
void Enter_username(int player_number)
{
	system("cls");
	char name_input[15]="             ";
	Username(name_input); 
	char one_letter;
	for (int index_position=0;index_position<14;index_position++)//To take input one letter at time in one_letter and then store it in name_input
	{
		cscanf("%c", &one_letter);
		if (one_letter==char(13))//checks if the key is not the enter key (13 is the ascii value for enter)
		{
			break;
		
		}
		else if(one_letter==char(8))//Checks for back space, if backspace is hit it erases the last value(8 is the ascii value for back space)
		{
			name_input[index_position-1]=' ';
			index_position=index_position-2;
			system("cls");
			Username(name_input);
		}
		else//At enter key the input of the user name ends
		{
			name_input[index_position]=one_letter;
			system("cls");
			Username(name_input);
		}
	}

	strcpy(p[player_number].name,name_input);//Coping the name from name_input to player name in structure 

}

void Instructions(void) //Instructions .. enter to continue
{

	system("cls");
	Title();
	printf("\n\n                               +----------------+                       \n");     
	printf("                               |+--------------+|                       \n");     
	printf("                               ||              ||                       \n");     
	printf("                               || INSTRUCTIONS ||                       \n");     
	printf("                               ||              ||                       \n");     
	printf("                               |+--------------+|                       \n");     
	printf("                               +----------------+                            \n\n\n");
	printf("     1.Aim of the game is to eat as many bugs as you can with your snake,    \n");
	printf("       without hiting the walls or your snake's body.                        \n");
	printf("     2.Eating makes your snake grow, a little at a time.                       \n");
	printf("     3.The longer your snake, the more score you will get for eating each bug.\n");
	printf("     4.Try to use the bonus levels to increase your scores.                  \n");
	printf("     5.Level will increase as your score increases.                          \n");
	printf("                                                                             \n");
	printf("                +----+                                      +-------+        \n");
	printf("                |Up=W|                                      |Ï Í BUG|        \n");
	printf("                +----+                                      +-------+        \n");
	printf("         +------+   +-------+  +-----------------------+                     \n");
	printf("         |Left=A|   |Right=D|  |N Í SPEED UP/SPEED DOWN|                     \n");
	printf("         +------+   +-------+  +-----------------------+                     \n");
	printf("               +------+                                 +---------------+    \n");     
	printf("               |Down=S|                                 | Í EXTRA LIFE |   \n");      
	printf("               +------+                                 +---------------+    \n\n\n"); 
	printf("                                   Press Enter                               \n");     
	getchar();//asks for enter key

}
void Draw_snake_game (char grid[100][100], int player_number,int life)
{
	Title();
	for (int i=0;i<24;i++)//printing the grid
	{
		printf("        ");
		for (int j=0;j<70;j++)
		{
			printf("%c", grid[i][j]);
		}
		printf("\n");
	}
	Scoring(player_number,life);//scoring system
	Sleep(speed);//time delay that controls the speed of the snake
}

void Scoring(int player_number,int life)
{
	p[99].score=0;//need to explain this 
	int hiscore[100];//array to store the index positions of the scores in decending order
	for (int k=player_number+1;k<100;k++)
	{
		hiscore[k]=99;
	}
	for (int i=0;i<=player_number;i++)
	{
		int x=player_number;
		for (int j=0;j<=player_number;j++)
		{
			if (p[i].score>p[j].score)
			{
				x--;
			}
		}
		hiscore[x]=i;
	}
	printf("                             ³                   ³          \n"    );                                                   
	printf("              +-------+      ³   %-16s³     High Scores \n"   , p[player_number].name);                                 
	printf("              |P=Pause|      ³                   ³            \n"  );                                                   
	printf("              +-------+      ³       SCORE       ³   %-16s%d\n" ,p[hiscore[0]].name,p[hiscore[0]].score);               
	printf("                             ³                  ³   %-16s%d\n" ,p[hiscore[1]].name,p[hiscore[1]].score);               
	printf("          +--------------+   ³+-----------------+³   %-16s%d\n" ,p[hiscore[2]].name,p[hiscore[2]].score);               
	printf("          |M=Instructions|   ³|%-17d|³   %-16s%d\n", p[player_number].score,p[hiscore[3]].name,p[hiscore[3]].score);    
	printf("          +--------------+   ³+-----------------+³   %-16s%d\n"  ,p[hiscore[4]].name,p[hiscore[4]].score);              
	printf("                             ³     LIVES LEFT    ³   %-16s%d\n"  ,p[hiscore[5]].name,p[hiscore[5]].score);              
	printf("              +------+       ³                  ³   %-16s%d\n"       ,p[hiscore[6]].name,p[hiscore[6]].score);         
	printf("              |O=Exit|       ³         %-2d        ³   %-16s%d\n"  ,life,p[hiscore[7]].name,p[hiscore[7]].score);       
	printf("              +------+       ³                   ³   %-16s%d\n"   ,p[hiscore[8]].name,p[hiscore[8]].score);             
                                                                                                                                
                                                                                                                                
                                                                                                                                
                                                                                                                                
       
                                                                                                                                    

}


void Snakegame(int player_number)
{
	/*
	level changing at
	level 1 ....score>0          speed=50 millisec delay
	level 2 ... score>3000       speed=40 millisec delay
	level 3 ... score>5000       speed=30 millisec delay
	level 4 ... score>8000       speed=20 millisec delay
	level 5 ... score>10000      speed=10 millisec delay
	*/






	//srand is used because normal rand generates the same numbers once the program is run again .. 
	srand( time(NULL) );

	
	

	//declarations for the bonus stuff
	//for heart printing
	int heart_print=0, lx, ly, t_s, t_f, heart_score=1000;
	
	
	
	//sx = x co-ordinate of the snake's head
	//sy = y co-ordinate of the snake's head
	//int speed is inversely proportional to the actual speed. it is the time in milisecs in Sleep(speed) function.
	//snake_safe is the condition for the inner loops. turns to 0 when a hit happens

	system("cls");
	int level=1,life=10,direction,snakelength=2,hit/*when hit happens then becomes 1*/;//so that the loops breaks and the snake starts from the origin
	int rx,ry;//the co ordinates of the bugs to eat
	speed=50;

	//level 1
	Level_change(1);


	/*map=level 1
	map1=level 2
	map2=level 3
	map3=level 4
	map4=level 5*/


	

	char map[100][100]={    "################################################################",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"#                                                              #",
							"################################################################"};
				
	
	


	//printing snake 
	int sx=3;
	int sy=1;
	int snake_x[5000]={sx,2,1};//array to store the locations of the index postitions of the snake .. 0 being the head and so on 
	int snake_y[5000]={sy,1,1};//array to store the locations of the index postitions of the snake .. 0 being the head and so on
	for (int index_position=1 ; index_position <= snakelength ; index_position++ )
	{
		map[snake_y[index_position]][snake_x[index_position]]='#';//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
	}
	map[sy][sx]=char(1);//printing the head in the map





	//randomly generating co ordinates for the bug
	//rx is the x co-ordinate of the bug
	//ry is the y co-ordinate of the bug
	
	do {
		rx=1+rand()%62;
		ry=1+rand()%23;
	}while(map[ry][rx]=='#');
	map[ry][rx]='Ï';



	//printing the grid on the output screen
	Draw_snake_game(map,player_number,life);


	//character variable to store the direction keys hit
	char move;
	
	
	//to make the snakelength back to 2
	snakelength=2;
	
	
	while (p[player_number].score<=3000&&life>=0)//loop only run for the first interation after key is hit
	{
		move=getch();

		if (move=='d'||move=='D')//right move
		{
			direction=1;
		}
		else if (move=='a'||move=='A')//left move
		{
			direction=0;
		}
		else if (move=='w'||move=='W')//up move
		{
			direction=2;
		}
		else if (move=='s'||move=='S')//down move
		{
			direction=3;
		}
		else if (move=='p'||move=='P')//pause
		{
			getchar();
		}
		else if (move=='m'||move=='M')//Instructions
		{
			Instructions();
		}
		else if (move=='n'||move=='N')//speed up/slow down
		{
			if(speed!=0)//speed increases
			{
				speed=0;
			}
			else//speed decreases
			{
				speed=50;
			}
		}
		else if(move=='o'||move=='O')
		{
			life=-1;
			break;
		}
		else if(move==':')//this is the shortcut to move to the next level(cheat)
		{
			p[player_number].score=3100;
		}
		

		while(p[player_number].score<=3000&&life>=0)//loop runs untill key is hit or wall is hit 
		{
			system("cls");
			if(direction==1)
			{
				sx=sx+1;
			}	
			else if(direction==0)
			{
				sx=sx-1;
			}
			else if(direction==2)
			{
				sy=sy-1;	
			}
			else if(direction==3)
			{
				sy=sy+1;
			}

			for (int index_position=snakelength ; index_position>0 ; index_position--)//snake index positions take the value of the preceding one
			{
				snake_x[index_position]=snake_x[index_position-1];
				snake_y[index_position]=snake_y[index_position-1];
			}

			//the new co-ordinates of the head of the snake are store in the index position 0 of the arrays
			snake_x[0]=sx;
			snake_y[0]=sy;


			char map[100][100]={    "################################################################",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"################################################################"};
			
			for (int index_position=1 ; index_position <= snakelength ; index_position++ )
			{
				map[snake_y[index_position]][snake_x[index_position]]='#';//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
			}
			
			if(map[sy][sx]=='#'||map[sy][sx]=='.')//if a hit happens
			{
				snakelength=2;
				sx=3;
				sy=1;
				printf("\a");//Beep Sound
				


				//array to store the locations of the index postitions of the snake .. 0 being the head and so on 
				snake_x[0]=sx;
				snake_y[0]=sy;
				snake_x[1]=2;
				snake_x[2]=1;
				snake_y[1]=1;
				snake_y[2]=1;
				speed=50;
				hit=1;//so that he loops break
				life--;
				Snake_hit(life);//prints that u hav hit
			}

			////printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
			for (int index_position=1 ; index_position <= snakelength ; index_position++ )
			{
				map[snake_y[index_position]][snake_x[index_position]]='#';
			}
			
			//when snake eats the bug
			if(sx==rx&&sy==ry)
			{
				
				p[player_number].score+=snakelength*10*level;//score increasing
				snakelength++;
				do{
				rx=rand()%63;
				ry=rand()%23;
				}
				while (map[ry][rx]!=' ');
			}


			//-------------------------------bonus starts----------------------------------
		
			

			if (p[player_number].score>heart_score)
			{
				do{
				lx=rand()%63;
				ly=rand()%23;
				}
				while (map[ly][lx]=='#');//the co ordinates of heart are randomly generated
				int time_start=GetTickCount();
				t_s=time_start;
				heart_print=1;//activates the printing of the heart
				
				heart_score+=1000;//this ensures this activation does not happen again unless the score is valid
			}
			
			


			if (heart_print==1)//prints the heart
			{

				int time_finish=GetTickCount();
				t_f=time_finish;
				if ((t_f-t_s)/1000<10)//print the heart for 10 secs only
				{
					map[ly][lx]=char(3);
				}
			}

			
			if(sx==lx&&sy==ly)//if the snake gets the heart
			{
				life++;
				heart_print=0;//turns of the printing of the heart
				map[ly][lx]=' ';
			}
			
			






			//-------------------------------bonus end----------------------------------

			map[sy][sx]=char(1);//printing the head in the map

			map[ry][rx]='Ï';//printing the bug on the map

			Draw_snake_game(map,player_number,life);
			
			//this function looks for a key board hit
			if (kbhit())
			{
				break;
			}

			//if the snake hits the wall or itself the snake will become and small and start from the origin
			else if(hit==1)
			{
				hit=0;
				break;
				
			}
		}
	}

//-----------------------------------------------------------------------------------------------------------------------------
//level 2

	//declarations for the heart
	heart_score=4000;
	heart_print=0;

	
	if(life>=0)//so that if the person has pressed the exit button or has lost all his lives the next level does not start
	{

		//bonus level

		bonus_level(1,player_number);//bonus level function called ... takes u to the bonus level

		Level_change(2);

		system("cls");
		char map1[100][100]={    "################################################################",
								"#                                                              #",
								"#                                                              #",
								"#                                                              #",
								"#                                                              #",
								"#                                                              #",
								"#            ###################                               #",
								"#            ###################                               #",
								"#            ###################                               #",
								"#            ###################                               #",
								"#            ####################################              #",
								"#            ####################################              #",
								"#            ####################################              #",
								"#            ####################################              #",
								"#                             ###################              #",
								"#                             ###################              #",
								"#                             ###################              #",
								"#                             ###################              #",
								"#                                                              #",
								"#                                                              #",
								"#                                                              #",
								"#                                                              #",
								"#                                                              #",
								"################################################################"};
				

		//level up
		level=2;

		//speed faster
		speed=40;

		//to make the snakelength back to 2
		snakelength=2;

		//printing snake 
		sx=3;
		sy=1;
		//array to store the locations of the index postitions of the snake .. 0 being the head and so on
		snake_x[0]=sx;
		snake_y[0]=sy;
		snake_x[1]=2;
		snake_x[2]=1;
		snake_y[1]=1;
		snake_y[2]=1;
		for (int index_position=1 ; index_position <= snakelength ; index_position++ )
		{
			map1[snake_y[index_position]][snake_x[index_position]]='#';//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
		}
		map1[sy][sx]=char(1);//printing the head in the map





		//randomly generating co ordinates for the bug
		//rx is the x co-ordinate of the bug
		//ry is the y co-ordinate of the bug
		do{
		rx=rand()%63;
		ry=rand()%23;
		}
		while (map1[ry][rx]!=' ');
		map1[ry][rx]='Ï';



		//printing the grid on the output screen
		Draw_snake_game(map1,player_number,life);



		while (p[player_number].score<=5000&&life>=0)//loop only run for the first interation after key is hit
		{
			move=getch();

			if (move=='d'||move=='D')//right move
			{
				direction=1;
			}
			else if (move=='a'||move=='A')//left move
			{
				direction=0;
			}
			else if (move=='w'||move=='W')//up move
			{
				direction=2;
			}
			else if (move=='s'||move=='S')//down move
			{
				direction=3;
			}
			else if (move=='p'||move=='P')//pause
			{
				getchar();
			}
			else if (move=='m'||move=='M')//Instructions
			{
				Instructions();
			}
			else if (move=='n'||move=='N')//speed up/slow down
			{
				if(speed!=0)//speed increases
				{
					speed=0;
				}
				else//speed decreases
				{
					speed=40;
				}
			}
			else if(move=='o'||move=='O')
			{
				life=-1;
				break;
			}
			else if(move==':')
			{
				p[player_number].score=5100;//this is the shortcut to move to the next level(cheat)
			}
			

			while(p[player_number].score<=5000&&life>=0)//loop runs untill key is hit or wall is hit 
			{
				system("cls");
				if(direction==1)
				{
					sx=sx+1;
				}	
				else if(direction==0)
				{
					sx=sx-1;
				}
				else if(direction==2)
				{
					sy=sy-1;	
				}
				else if(direction==3)
				{
					sy=sy+1;
				}
				for (int index_position=snakelength ; index_position>0 ; index_position--)//snake index positions take the value of the preceding one
				{
					snake_x[index_position]=snake_x[index_position-1];
					snake_y[index_position]=snake_y[index_position-1];
				}

				//the new co-ordinates of the head of the snake are store in the index position 0 of the arrays
				snake_x[0]=sx;
				snake_y[0]=sy;


				char map1[100][100]={    "################################################################",
										"#                                                              #",
										"#                                                              #",
										"#                                                              #",
										"#                                                              #",
										"#                                                              #",
										"#            ###################                               #",
										"#            ###################                               #",
										"#            ###################                               #",
										"#            ###################                               #",
										"#            ####################################              #",
										"#            ####################################              #",
										"#            ####################################              #",
										"#            ####################################              #",
										"#                             ###################              #",
										"#                             ###################              #",
										"#                             ###################              #",
										"#                             ###################              #",
										"#                                                              #",
										"#                                                              #",
										"#                                                              #",
										"#                                                              #",
										"#                                                              #",
										"################################################################"};
				
				for (int index_position=1 ; index_position <= snakelength ; index_position++ )
				{
					map1[snake_y[index_position]][snake_x[index_position]]='#';//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
				}
				
				if(map1[sy][sx]=='#'||map1[sy][sx]=='.')//if a hit happens
				{
					snakelength=2;
					sx=3;
					sy=1;
					printf("\a");//Beep Sound

					//array to store the locations of the index postitions of the snake .. 0 being the head and so on 
					snake_x[0]=sx;
					snake_y[0]=sy;
					snake_x[1]=2;
					snake_x[2]=1;
					snake_y[1]=1;
					snake_y[2]=1;
					speed=40;
					hit=1;
					life--;
					Snake_hit(life);
				}

				//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
				for (int index_position=1 ; index_position <= snakelength ; index_position++ )
				{
					map1[snake_y[index_position]][snake_x[index_position]]='#';
				}
				
				//when snake eats the bug
				if(sx==rx&&sy==ry)
				{
					p[player_number].score+=snakelength*10*level;
					snakelength++;
					do{
					rx=rand()%63;
					ry=rand()%23;
					}
					while (map1[ry][rx]!=' ');
				}


				//---------------------------------bonus starts--------------------------------
		
			
				
				if (p[player_number].score>heart_score)
				{
					do{
					lx=rand()%63;
					ly=rand()%23;
					}
					while (map1[ly][lx]=='#');
					int time_start=GetTickCount();
					t_s=time_start;
					heart_print=1;//activates the printing of the heart
					heart_score+=1000;
				}
				
				


				if (heart_print==1)//prints the heart
				{

					int time_finish=GetTickCount();
					t_f=time_finish;
					if ((t_f-t_s)/1000<10)//print the heart for 10 secs only

					{
						map1[ly][lx]=char(3);
					}
				}

				
				if(sx==lx&&sy==ly)//if the snake gets the heart
				{
					life++;
					heart_print=0;//turns of the printing of the heart
					map1[ly][lx]=' ';
				}
				
				//-------------------------------bonus end----------------------------------


				map1[sy][sx]=char(1);//printing the head in the map

				map1[ry][rx]='Ï';//printing the bug on the map

				Draw_snake_game(map1,player_number,life);
				
				//this function looks for a key board hit
				if (kbhit())
				{
					break;
				}

				//if the snake hits the wall or itself the snake will become and small and start from the origin
				else if(hit==1)
				{
					hit=0;
					break;
					
				}
			}
		}
	}

//-----------------------------------------------------------------------------------------------------------------------------
//level 3

	
	//declarations for the heart
	heart_score=6000;
	heart_print=0;

	if (life>=0)
	{
		bonus_level(2,player_number);
		Level_change(3);
		system("cls");
		char map2[100][100]={		"################################################################",
									"#                                                              #",
									"#  ##################################################          #",
									"#  ##################################################          #",
									"#                                          ##########          #",
									"#                                          ##########          #",
									"#                                          ##########          #",
									"#                                          ##########          #",
									"#      #########################           ##########          #",
									"#      ######            #######           ##########          #",
									"#      ######            #######           ##########          #",
									"#      ######            #######           ##########          #",
									"#                                          ##########          #",
									"#                                          ##########          #",
									"#                                                              #",
									"#    ########                                                  #",
									"#    ########                                                  #",
									"#    ########                                                  #",
									"#    ########                                                  #",
									"#    #################     ################################    #",
									"#    #################     ################################    #",
									"#                          ################################    #",
									"#                                                              #",
									"################################################################"};
				

		//level up
		level=3;

		//speed faster
		speed=30;

		//to make the snakelength back to 2
		snakelength=2;

		//printing snake 
		sx=3;
		sy=1;
		//array to store the locations of the index postitions of the snake .. 0 being the head and so on
		snake_x[0]=sx;
		snake_y[0]=sy;
		snake_x[1]=2;
		snake_x[2]=1;
		snake_y[1]=1;
		snake_y[2]=1;
		for (int index_position=1 ; index_position <= snakelength ; index_position++ )
		{
			map2[snake_y[index_position]][snake_x[index_position]]='#';//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
		}
		map2[sy][sx]=char(1);//printing the head in the map





		//randomly generating co ordinates for the bug
		//rx is the x co-ordinate of the bug
		//ry is the y co-ordinate of the bug
		do{
		rx=rand()%63;
		ry=rand()%23;
		}
		while (map2[ry][rx]!=' ');
		map2[ry][rx]='Ï';


		//printing the grid on the output screen
		Draw_snake_game(map2,player_number,life);



		while (p[player_number].score<=8000&&life>=0)//loop only run for the first interation after key is hit
		{
			move=getch();

			if (move=='d'||move=='D')//right move
			{
				direction=1;
			}
			else if (move=='a'||move=='A')//left move
			{
				direction=0;
			}
			else if (move=='w'||move=='W')//up move
			{
				direction=2;
			}
			else if (move=='s'||move=='S')//down move
			{
				direction=3;
			}
			else if (move=='p'||move=='P')//pause
			{
				getchar();
			}
			else if (move=='m'||move=='M')//Instructions
			{
				Instructions();
			}
			else if (move=='n'||move=='N')//speed up/slow down
			{
				if(speed!=0)//speed increases
				{
					speed=0;
				}
				else//speed decreases
				{
					speed=30;
				}
			}
			else if(move=='o'||move=='O')
			{
				life=-1;
				break;
			}
			else if(move==':')//this is the shortcut to move to the next level(cheat)
			{
				p[player_number].score=8100;
			}

			while(p[player_number].score<=8000&&life>=0)//loop runs untill key is hit or wall is hit 
			{
				system("cls");
				if(direction==1)
				{
					sx=sx+1;
				}	
				else if(direction==0)
				{
					sx=sx-1;
				}
				else if(direction==2)
				{
					sy=sy-1;	
				}
				else if(direction==3)
				{
					sy=sy+1;
				}
				for (int index_position=snakelength ; index_position>0 ; index_position--)//snake index positions take the value of the preceding one
				{
					snake_x[index_position]=snake_x[index_position-1];
					snake_y[index_position]=snake_y[index_position-1];
				}

				//the new co-ordinates of the head of the snake are store in the index position 0 of the arrays
				snake_x[0]=sx;
				snake_y[0]=sy;


				char map2[100][100]={		"################################################################",
											"#                                                              #",
											"#  ##################################################          #",
											"#  ##################################################          #",
											"#                                          ##########          #",
											"#                                          ##########          #",
											"#                                          ##########          #",
											"#                                          ##########          #",
											"#      #########################           ##########          #",
											"#      ######            #######           ##########          #",
											"#      ######            #######           ##########          #",
											"#      ######            #######           ##########          #",
											"#                                          ##########          #",
											"#                                          ##########          #",
											"#                                                              #",
											"#    ########                                                  #",
											"#    ########                                                  #",
											"#    ########                                                  #",
											"#    ########                                                  #",
											"#    #################     ################################    #",
											"#    #################     ################################    #",
											"#                          ################################    #",
											"#                                                              #",
											"################################################################"}; 

				
				for (int index_position=1 ; index_position <= snakelength ; index_position++ )
				{
					map2[snake_y[index_position]][snake_x[index_position]]='#';//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
				}
				
				if(map2[sy][sx]=='#'||map2[sy][sx]=='.')//if a hit happens
				{
					snakelength=2;
					sx=3;
					sy=1;
					printf("\a");//Beep Sound


					//array to store the locations of the index postitions of the snake .. 0 being the head and so on 
					snake_x[0]=sx;
					snake_y[0]=sy;
					snake_x[1]=2;
					snake_x[2]=1;
					snake_y[1]=1;
					snake_y[2]=1;
					speed=30;
					hit=1;
					life--;
					Snake_hit(life);
				}

				//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
				for (int index_position=1 ; index_position <= snakelength ; index_position++ )
				{
					map2[snake_y[index_position]][snake_x[index_position]]='#';
				}
				
				//when snake eats the bug
				if(sx==rx&&sy==ry)
				{
					p[player_number].score+=snakelength*10*level;
					snakelength++;
					do{
					rx=rand()%63;
					ry=rand()%23;
					}
					while (map2[ry][rx]!=' ');
				}
				//-----------------------------------------------------------------bonus starts
		
			/*declarations for the heart
	heart_score=4000;
	heart_print=0;*/

			if (p[player_number].score>heart_score)
			{
				do{
				lx=rand()%63;
				ly=rand()%23;
				}
				while (map2[ly][lx]=='#');
				int time_start=GetTickCount();
				t_s=time_start;
				heart_print=1;//activates the printing of the heart
				//heart_activate_1=0;//this ensures this activation does not happen again
				heart_score+=1000;
			}
			
			


			if (heart_print==1)//prints the heart
			{

				int time_finish=GetTickCount();
				t_f=time_finish;
				if ((t_f-t_s)/1000<10)//print the heart for 10 secs only
				{
					map2[ly][lx]=char(3);
				}
			}

			
			if(sx==lx&&sy==ly)//if the snake gets the heart
			{
				life++;
				heart_print=0;//turns of the printing of the heart
				map2[ly][lx]=' ';
			}
			







			//-----------------------------------------------------------------bonus end





				map2[sy][sx]=char(1);//printing the head in the map

				map2[ry][rx]='Ï';//printing the bug on the map

				Draw_snake_game(map2,player_number,life);
				
				//this function looks for a key board hit
				if (kbhit())
				{
					break;
				}

				//if the snake hits the wall or itself the snake will become and small and start from the origin
				else if(hit==1)
				{
					hit=0;
					break;
					
				}
			}
		}
	}

//-----------------------------------------------------------------------------------------------------------------------------
//level 4

	//declarations for the heart
	heart_score=9000;
	heart_print=0;
	
	if (life>=0)
	{
		bonus_level(3,player_number);

		Level_change(4);
		system("cls");
		char map3[100][100]={		"################################################################",
									"#                                                              #",
									"#                                                              #",
									"#    #####################################################     #",
									"#    #                                                         #",
									"#    #                                                         #",
									"#    #                                                         #",
									"#    #     ###############################################     #",
									"#    #     #                                                   #",
									"#    #     #                                                   #",
									"#    #     #    ##########################################     #",
									"#    #     #    #                                              #",
									"#    #     #    #                                              #",
									"#    #     #    ##########################################     #",
									"#    #     #                                                   #",
									"#    #     #                                                   #",
									"#    #     ###############################################     #",
									"#    #                                                         #",
									"#    #                                                         #",
									"#    #                                                         #",
									"#    #####################################################     #",
									"#                                                              #",
									"#                                                              #",
									"################################################################"};
				

		//level up
		level=4;

		//speed faster
		speed=20;

		//to make the snakelength back to 2
		snakelength=2;

		//printing snake 
		sx=3;
		sy=1;
		//array to store the locations of the index postitions of the snake .. 0 being the head and so on
		snake_x[0]=sx;
		snake_y[0]=sy;
		snake_x[1]=2;
		snake_x[2]=1;
		snake_y[1]=1;
		snake_y[2]=1;
		for (int index_position=1 ; index_position <= snakelength ; index_position++ )
		{
			map3[snake_y[index_position]][snake_x[index_position]]='#';//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
		}
		map3[sy][sx]=char(1);//printing the head in the map





		//randomly generating co ordinates for the bug
		//rx is the x co-ordinate of the bug
		//ry is the y co-ordinate of the bug
		do{
		rx=rand()%63;
		ry=rand()%23;
		}
		while (map3[ry][rx]!=' ');
		map3[ry][rx]='Ï';


		//printing the grid on the output screen
		Draw_snake_game(map3,player_number,life);



		while (p[player_number].score<=10000&&life>=0)//loop only run for the first interation after key is hit
		{
			move=getch();

			if (move=='d'||move=='D')//right move
			{
				direction=1;
			}
			else if (move=='a'||move=='A')//left move
			{
				direction=0;
			}
			else if (move=='w'||move=='W')//up move
			{
				direction=2;
			}
			else if (move=='s'||move=='S')//down move
			{
				direction=3;
			}
			else if (move=='p'||move=='P')//pause
			{
				getchar();
			}
			else if (move=='m'||move=='M')//Instructions
			{
				Instructions();
			}
			else if (move=='n'||move=='N')//speed up/slow down
			{
				if(speed!=0)//speed increases
				{
					speed=0;
				}
				else//speed decreases
				{
					speed=20;
				}
			}
			else if(move=='o'||move=='O')
			{
				life=-1;
				break;
			}
			else if(move==':')//this is the shortcut to move to the next level(cheat)
			{
				p[player_number].score=10100;
			}

			while(p[player_number].score<=10000&&life>=0)//loop runs untill key is hit or wall is hit 
			{
				system("cls");
				if(direction==1)
				{
					sx=sx+1;
				}	
				else if(direction==0)
				{
					sx=sx-1;
				}
				else if(direction==2)
				{
					sy=sy-1;	
				}
				else if(direction==3)
				{
					sy=sy+1;
				}
				for (int index_position=snakelength ; index_position>0 ; index_position--)//snake index positions take the value of the preceding one
				{
					snake_x[index_position]=snake_x[index_position-1];
					snake_y[index_position]=snake_y[index_position-1];
				}

				//the new co-ordinates of the head of the snake are store in the index position 0 of the arrays
				snake_x[0]=sx;
				snake_y[0]=sy;


				char map3[100][100]={		"################################################################",
											"#                                                              #",
											"#                                                              #",
											"#    #####################################################     #",
											"#    #                                                         #",
											"#    #                                                         #",
											"#    #                                                         #",
											"#    #     ###############################################     #",
											"#    #     #                                                   #",
											"#    #     #                                                   #",
											"#    #     #    ##########################################     #",
											"#    #     #    #                                              #",
											"#    #     #    #                                              #",
											"#    #     #    ##########################################     #",
											"#    #     #                                                   #",
											"#    #     #                                                   #",
											"#    #     ###############################################     #",
											"#    #                                                         #",
											"#    #                                                         #",
											"#    #                                                         #",
											"#    #####################################################     #",
											"#                                                              #",
											"#                                                              #",
											"################################################################"}; 

				
				for (int index_position=1 ; index_position <= snakelength ; index_position++ )
				{
					map3[snake_y[index_position]][snake_x[index_position]]='#';//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
				}
				
				if(map3[sy][sx]=='#'||map3[sy][sx]=='.')//if a hit happens
				{
					snakelength=2;
					sx=3;
					sy=1;
					printf("\a");//Beep Sound


					//array to store the locations of the index postitions of the snake .. 0 being the head and so on 
					snake_x[0]=sx;
					snake_y[0]=sy;
					snake_x[1]=2;
					snake_x[2]=1;
					snake_y[1]=1;
					snake_y[2]=1;
					speed=20;
					hit=1;
					life--;
					Snake_hit(life);
				}

				//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
				for (int index_position=1 ; index_position <= snakelength ; index_position++ )
				{
					map3[snake_y[index_position]][snake_x[index_position]]='#';
				}
				
				//when snake eats the bug
				if(sx==rx&&sy==ry)
				{
					p[player_number].score+=snakelength*10*level;
					snakelength++;
					do{
					rx=rand()%63;
					ry=rand()%23;
					}
					while (map3[ry][rx]!=' ');
				}

				//-----------------------------------------------------------------bonus starts
		
			

			if (p[player_number].score>heart_score)
			{
				do{
				lx=rand()%63;
				ly=rand()%23;
				}
				while (map3[ly][lx]=='#');
				int time_start=GetTickCount();
				t_s=time_start;
				heart_print=1;//activates the printing of the heart
				//heart_activate_1=0;//this ensures this activation does not happen again
				heart_score+=1000;
			}
			
			


			if (heart_print==1)//prints the heart
			{

				int time_finish=GetTickCount();
				t_f=time_finish;
				if ((t_f-t_s)/1000<10)//print the heart for 10 secs only
				{
					map3[ly][lx]=char(3);
				}
			}

			
			if(sx==lx&&sy==ly)//if the snake gets the heart
			{
				life++;
				heart_print=0;//turns of the printing of the heart
				map3[ly][lx]=' ';
			}
			







			//-----------------------------------------------------------------bonus end





				map3[sy][sx]=char(1);//printing the head in the map

				map3[ry][rx]='Ï';//printing the bug on the map

				Draw_snake_game(map3,player_number,life);
				
				//this function looks for a key board hit
				if (kbhit())
				{
					break;
				}

				//if the snake hits the wall or itself the snake will become and small and start from the origin
				else if(hit==1)
				{
					hit=0;
					break;
					
				}
			}
		}
	}

//-----------------------------------------------------------------------------------------------------------------------------
//level 5

	//declarations for the heart
	heart_score=11000;
	heart_print=0;
	
	if (life>=0)
	{
		bonus_level(4,player_number);//bonus level
		Level_change(5);
		system("cls");
		char map4[100][100]={		"################################################################",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#    ..####...#...#.....#.....#...#...#####.                   #",
									"#    .#.......##..#....#.#....#..#....#.....                   #",
									"#    .##......#.#.#....#.#....#.#.....#.....                   #",
									"#    ..###....#.#.#...#...#...###.....####..                   #",
									"#    .....#...#..##...#####...#.##....#.....                   #",
									"#    .....#...#..##...#...#...#..##...#.....                   #",
									"#    .####....#...#..#.....#..#...##..#####.                   #",
									"#                                                              #",
									"#                                                              #",
									"#                                                              #",
									"#                         ...###.....#......#...##..#####.     #",
									"#                         ..#.......#.#.....#...##..#.....     #",
									"#                         .#........#.#....#.#.#.#..#.....     #",
									"#                         .#.......#...#...#.#.#.#..####..     #",
									"#                         .#...#...#####...#.#.#.#..#.....     #",
									"#                         .##..#...#...#...#.##..#..#.....     #",
									"#                         ..####..#.....#..#..#..#..#####.     #",
									"#                                                              #",
									"#                                                              #",
									"################################################################"};
				

		//level up
		level=5;

		//speed faster
		speed=10;

		//to make the snakelength back to 2
		snakelength=2;

		//printing snake 
		sx=3;
		sy=1;
		//array to store the locations of the index postitions of the snake .. 0 being the head and so on
		snake_x[0]=sx;
		snake_y[0]=sy;
		snake_x[1]=2;
		snake_x[2]=1;
		snake_y[1]=1;
		snake_y[2]=1;
		for (int index_position=1 ; index_position <= snakelength ; index_position++ )
		{
			map4[snake_y[index_position]][snake_x[index_position]]='#';//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
		}
		map4[sy][sx]=char(1);//printing the head in the map





		//randomly generating co ordinates for the bug
		//rx is the x co-ordinate of the bug
		//ry is the y co-ordinate of the bug
		do{
		rx=rand()%63;
		ry=rand()%23;
		}
		while (map4[ry][rx]!=' ');
		map4[ry][rx]='Ï';


		//printing the grid on the output screen
		Draw_snake_game(map4,player_number,life);



		while (p[player_number].score<=50000000&&life>=0)//loop only run for the first interation after key is hit
		{
			move=getch();

			if (move=='d'||move=='D')//right move
			{
				direction=1;
			}
			else if (move=='a'||move=='A')//left move
			{
				direction=0;
			}
			else if (move=='w'||move=='W')//up move
			{
				direction=2;
			}
			else if (move=='s'||move=='S')//down move
			{
				direction=3;
			}
			else if (move=='p'||move=='P')//pause
			{
				getchar();
			}
			else if (move=='m'||move=='M')//Instructions
			{
				Instructions();
			}
			else if (move=='n'||move=='N')//speed up/slow down
			{
				if(speed!=0)//speed increases
				{
					speed=0;
				}
				else//speed decreases
				{
					speed=10;
				}
			}
			else if(move=='o'||move=='O')
			{
				life=-1;
				break;
			}
			

			while(p[player_number].score<=5000000000&&life>=0)//loop runs untill key is hit or wall is hit 
			{
				system("cls");
				if(direction==1)
				{
					sx=sx+1;
				}	
				else if(direction==0)
				{
					sx=sx-1;
				}
				else if(direction==2)
				{
					sy=sy-1;	
				}
				else if(direction==3)
				{
					sy=sy+1;
				}
				for (int index_position=snakelength ; index_position>0 ; index_position--)//snake index positions take the value of the preceding one
				{
					snake_x[index_position]=snake_x[index_position-1];
					snake_y[index_position]=snake_y[index_position-1];
				}

				//the new co-ordinates of the head of the snake are store in the index position 0 of the arrays
				snake_x[0]=sx;
				snake_y[0]=sy;


				char map4[100][100]={		"################################################################",
											"#                                                              #",
											"#                                                              #",
											"#                                                              #",
											"#    ..####...#...#.....#.....#...#...#####.                   #",
											"#    .#.......##..#....#.#....#..#....#.....                   #",
											"#    .##......#.#.#....#.#....#.#.....#.....                   #",
											"#    ..###....#.#.#...#...#...###.....####..                   #",
											"#    .....#...#..##...#####...#.##....#.....                   #",
											"#    .....#...#..##...#...#...#..##...#.....                   #",
											"#    .####....#...#..#.....#..#...##..#####.                   #",
											"#                                                              #",
											"#                                                              #",
											"#                                                              #",
											"#                         ...###.....#......#...##..#####.     #",
											"#                         ..#.......#.#.....#...##..#.....     #",
											"#                         .#........#.#....#.#.#.#..#.....     #",
											"#                         .#.......#...#...#.#.#.#..####..     #",
											"#                         .#...#...#####...#.#.#.#..#.....     #",
											"#                         .##..#...#...#...#.##..#..#.....     #",
											"#                         ..####..#.....#..#..#..#..#####.     #",
											"#                                                              #",
											"#                                                              #",
											"################################################################"}; 

				
				for (int index_position=1 ; index_position <= snakelength ; index_position++ )
				{
					map4[snake_y[index_position]][snake_x[index_position]]='#';//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
				}
				
				if(map4[sy][sx]=='#'||map4[sy][sx]=='.')//if a hit happens
				{
					snakelength=2;
					sx=3;
					sy=1;
					printf("\a");//Beep Sound


					//array to store the locations of the index postitions of the snake .. 0 being the head and so on 
					snake_x[0]=sx;
					snake_y[0]=sy;
					snake_x[1]=2;
					snake_x[2]=1;
					snake_y[1]=1;
					snake_y[2]=1;
					speed=10;
					hit=1;
					life--;
					Snake_hit(life);
				}

				//printing the body of the snake, on the map, using the array of the coordinates of the index positions of the body
				for (int index_position=1 ; index_position <= snakelength ; index_position++ )
				{
					map4[snake_y[index_position]][snake_x[index_position]]='#';
				}
				
				//when snake eats the bug
				if(sx==rx&&sy==ry)
				{
					p[player_number].score+=snakelength*10*level;
					snakelength++;
					do{
					rx=rand()%63;
					ry=rand()%23;
					}
					while (map4[ry][rx]!=' ');
				}

				//-----------------------------------------------------------------bonus starts
		
			

				if (p[player_number].score>heart_score)
				{
					do{
					lx=rand()%63;
					ly=rand()%23;
					}
					while (map4[ly][lx]=='#'||map4[ly][lx]=='.');
					int time_start=GetTickCount();
					t_s=time_start;
					heart_print=1;//activates the printing of the heart
					//heart_activate_1=0;//this ensures this activation does not happen again
					heart_score+=2500;
				}
				
				


				if (heart_print==1)//prints the heart
				{

					int time_finish=GetTickCount();
					t_f=time_finish;
					if ((t_f-t_s)/1000<10)//print the heart for 10 secs only
					{
						map4[ly][lx]=char(3);
					}
				}

				
				if(sx==lx&&sy==ly)//if the snake gets the heart
				{
					life++;
					heart_print=0;//turns of the printing of the heart
					map4[ly][lx]=' ';
				}
				

				//-----------------------------------------------------------------bonus end




				map4[sy][sx]=char(1);//printing the head in the map

				map4[ry][rx]='Ï';//printing the bug on the map

				Draw_snake_game(map4,player_number,life);
				
				//this function looks for a key board hit
				if (kbhit())
				{
					break;
				}

				//if the snake hits the wall or itself the snake will become and small and start from the origin
				else if(hit==1)
				{
					hit=0;
					break;
					
				}
			}
		}
	}
}






void Game_end(int player_number,int &exit)
{
	
	system("cls");
	Title();
	printf("\n                          +------------------------+  \n");
	printf("                          |                        |  \n");
	printf("                          |  THANKYOU FOR PLAYING  |  \n");
	printf("                          |                        |  \n");
	printf("                          +------------------------+ \n");
	printf("\n\n                    +----------------+\n");
	printf("                    |Your Final Score| = %d\n",p[player_number].score);
	printf("                    +----------------+\n");
	printf("\n\n\n                            Press H for HIGHSCORES");
	printf("\n\n\n                         Press Enter to PLAY AGAIN"); 
	printf("\n\n\n                               Press E to exit\n\n\n\n\n");
	char menu;
	do{
	cscanf("%c", &menu);
	}while(menu!='h'&&menu!='H'&&menu!='e'&&menu!='E'&&menu!=char(13));

	if(menu=='h'||menu=='H')
	{
		Highscores(player_number,exit);
	}
	
	else if(menu=='e'||menu=='E')
	{
		exit=1;
	}
	else
	{
		getchar();
	}
}
void Highscores(int player_number,int &exit)//printing highscores last time
{
	int hiscore[100];//array will store the player number .. from the player with the highest score to the player with the lowest
	for (int k=player_number+1;k<100;k++)//the index postion 99 of p[].score is given as has the value 0 .. 
	{
		hiscore[k]=99;
	}
	
	for (int i=0;i<=player_number;i++)
	{
		int x=player_number;
		for (int j=0;j<=player_number;j++)
		{
			if (p[i].score > p[j].score)//comparing two scores .. all scores are compared .. 
			{
				x--;
			}
		}
		hiscore[x]=i;//index value of the score arrat are stored. largest number in hiscore[0] and so on .. 
	}
	system("cls");
	Title();
	printf("\n                                 +--------+                             \n");                                       
	printf("                                 |HISCORES|                             \n");                                       
	printf("                                 +--------+                             \n");  
	for (int number=0;number<25;number++)
	{
	printf("                      %-2d.  %-18s%d\n",number+1,p[hiscore[number]].name,p[hiscore[number]].score);
	}
	printf("\n                                 Press ENTER\n");
	getchar();
	Game_end(player_number,exit);

}



void Save_player_score(int player_number)
{
	FILE *p1,*p2;
	p1=fopen("playernames.txt","a+");
	p2=fopen("playerscores.txt","a+");
	fprintf(p2,"%d\n", p[player_number].score);
	fprintf(p1,"%s\n", p[player_number].name);
	
	fclose(p2); 
	fclose(p1); 
}
void Level_change(int level)
{
	system("cls");
	Title();
	printf("\n\n\n\n                           +-----------------------+   \n");      
	printf("                           |    +-------------+    |   \n");      
	printf("                           |    |  +-------+  |    |   \n");      
	printf("                           |    |  |       |  |    |   \n");      
	printf("                           |    |  | LEVEL |  |    |   \n");      
	printf("                           |    |  |       |  |    |   \n");      
	printf("                           |    |  +-------+  |    |   \n");      
	printf("                           |    +-------------+    |   \n");      
	printf("                           +-----------------------+   \n");      
	printf("                                       º               \n");      
	printf("                                    +-----+            \n");      
	printf("                                    |     |            \n");      
	printf("                                    |  %d  |            \n",level);//no of level displayed
	printf("                                    |     |            \n");      
	printf("                                    +-----+            \n");      
	printf("                                                       \n\n\n\n");      
	printf("                                  PRESS ENTER          \n");      
	printf("                                                       \n");      
	printf("                                  TO CONTINUE          \n"); 
	getchar();
	system("cls");
}

void Snake_hit(int life)
{
	if (life>=0)
	{

		system("cls");
		Title();
		printf("\n\n\n\n");     
		printf("                  +-----------------------------------------+\n");     
		printf("                  |OOOPS!!   Your Snake Just Got Knocked Out|\n");     
		printf("                  +-----------------------------------------+ \n\n\n");        
		printf("                     +----------+\n");     
		printf("                     |lIVES LEFT| = ");

		for (int heart=0;heart<life;heart++)
		{
			printf("%c ",char(3));
		}
		printf("= %d\n                     +----------+\n\n\n\n\n",life);      
		printf("                                 PRESS ENTER\n\n\n");     
		     
		printf("                                 TO CONTINUE\n");     
		getchar();
		system("cls");
	}
}






void draw_bonus( char grid[][100])
{
	Title();
	printf("\n");
	for (int i=0;i<24;i++)//printing the bonus_levels
	{
		printf("        ");
		for (int j=0;j<70;j++)
		{
			printf("%c", grid[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");                                                         
	printf("                          Get to the finishing point (²)\n");     
	printf("\n");                                                             
	printf("                    as soon as possible to earn extra points.\n");
	printf("\n");                                                             
	printf("                               Or press (o) to exit.\n");         


}

void bonus_level(int level,int player_number)
{
	system("cls");
	
	if (level==1)
	{

		bonus_level_change(1);//prints that this is a bonus level
		
		int time_on=1;//this 
		char bonus_move;// to store the characters to move
		int bonus_level_end=0;
		int bonus_x=16,bonus_y=3,time_2;//time_2 is the final time 
		const char c=char(1);//this is just a smiley face
		int time_1=GetTickCount();//initail time taken 
		char bonus_level[100][100]= {"                        BONUS     LEVEL                         ", 
										"        BONUS                                      BONUS        ", 
										"               ##################################               ", 
										"        LEVEL  #°                               #  LEVEL        ", 
										"               ##############################   #               ", 
										"               ##   #                           #               ", 
										" BONUS         ## # #  ######### ################        BONUS  ", 
										"               #  # #          # #              #               ", 
										" LEVEL         # ## ########## # # ##### # #### #        LEVEL  ", 
										"               #  # #          # #     # # #  # #               ", 
										"               ## # #  ######### # ### # # ## # #               ", 
										"        BONUS  #  # #          # # # # # #    # #  BONUS        ", 
										"               # ## ########## # # # # # ###### #               ", 
										"        LEVEL  #  # #    #   # # # #   #        #  LEVEL        ", 
										"               ## # ## # # # # #   # ### ###### #               ", 
										"               #  #    #   #   #   #     #    # #               ", 
										" BONUS         # #########################  # # #        BONUS  ", 
										"               #                        ##  # # #               ", 
										" LEVEL         ######################## ##  # # #        LEVEL  ", 
										"               #    #   #   #   #   #   ##  ### #               ", 
										"               #² #   #   #   #   #   ####      #               ", 
										"        BONUS  ##################################  BONUS        ", 
										"                                                                ", 
										"        LEVEL           BONUS     LEVEL            LEVEL        "};




		bonus_level[bonus_y][bonus_x]=c;

		draw_bonus(bonus_level);
		
		while (bonus_level_end==0)//will stay 0 unless level crosses or exit pressed
		{
			bonus_level[bonus_y][bonus_x]=' ';
			
			
			cscanf("%c",&bonus_move);
			
			if (bonus_move=='w'||bonus_move=='W')//up
			{
				
				
				if (bonus_level[bonus_y-1][bonus_x]!='#')
				{
					bonus_y=bonus_y-1;
				}

			}

			else if(bonus_move=='s'||bonus_move=='S')//down
			{
				
				if (bonus_level[bonus_y+1][bonus_x]!='#')
				{
					bonus_y=bonus_y+1;
				}
			}

				
			else if(bonus_move=='a'||bonus_move=='A')//left
			{
				
				if (bonus_level[bonus_y][bonus_x-1]!='#')
				{
					bonus_x=bonus_x-1;
				}

			}
			else if(bonus_move=='d'||bonus_move=='D')//right
			{
				
				if (bonus_level[bonus_y][bonus_x+1]!='#')
				{
					bonus_x=bonus_x+1;
				}
			}
			else if(bonus_move == 'o'||bonus_move=='O')//exit
			{
				bonus_level_end=1;
				time_on=0;// this variable is there so that the loops breaks and the score is not added.
				break;
			}

			
			bonus_level[bonus_y][bonus_x]=c;
			
			system("cls");

			draw_bonus(bonus_level);
			

			if(bonus_y==20&&bonus_x==16)
			{
				int u=GetTickCount();//final time taken
				time_2=u;
				bonus_level_end=1;//to break the loop
				
			}
		}



		if(time_on==1)
		{
			p[player_number].score+=10000/((time_2-time_1)/1000);//lesser the time taken more the score
			system("cls");
		}
		else 
		{
			
			system("cls");
		}
	}
	//-----------------------------------------------------------------------------------------------------------------------
	else if (level==2)
	{
		bonus_level_change(2);//prints that this is a bonus level
		int time_on=1;//this 
		char bonus_move;// to store the characters to move
		int bonus_level_end=0;
		int bonus_x=1,bonus_y=3,time_2;//time_2 is the final time 
		const char c=char(1);//this is just a smiley face
		int time_1=GetTickCount();//initail time taken 
		char bonus_level[100][100]= {"                        BONUS     LEVEL                         ", 
									"                                                                ", 
									"################################################################", 
									"#±#                                                            #", 
									"# # ########################################################## #", 
									"# # #                                                        # #", 
									"# # # ###################################################### # #", 
									"# # # #                                                    # # #", 
									"# # # # ################################################## # # #", 
									"# # # # #                                                # # # #", 
									"# # # # # ############################################## # # # #", 
									"# # # # # #   #   #   #   #   #   #   #   #   #   #   ## # # # #", 
									"# # # # #   #   #   #   #   #   #   #   #   #   #   # ²# # # # #", 
									"# # # # ################################################ # # # #", 
									"# # # #                                                  # # # #", 
									"# # # #################################################### # # #", 
									"# # #                                                      # # #", 
									"# # ######################################################## # #", 
									"# #                                                          # #", 
									"# ############################################################ #", 
									"#                                                              #", 
									"################################################################", 
									"                                                                ", 
									"                        BONUS     LEVEL                         "};





		bonus_level[bonus_y][bonus_x]=c;

		draw_bonus(bonus_level);
		
		while (bonus_level_end==0)//will stay 0 unless level crosses or exit pressed
		{
			bonus_level[bonus_y][bonus_x]=' ';
			
			
			cscanf("%c",&bonus_move);
			
			if (bonus_move=='w'||bonus_move=='W')//up
			{
				
				
				if (bonus_level[bonus_y-1][bonus_x]!='#')
				{
					bonus_y=bonus_y-1;
				}

			}

			else if(bonus_move=='s'||bonus_move=='S')//down
			{
				
				if (bonus_level[bonus_y+1][bonus_x]!='#')
				{
					bonus_y=bonus_y+1;
				}
			}

				
			else if(bonus_move=='a'||bonus_move=='A')//left
			{
				
				if (bonus_level[bonus_y][bonus_x-1]!='#')
				{
					bonus_x=bonus_x-1;
				}

			}
			else if(bonus_move=='d'||bonus_move=='D')//right
			{
				
				if (bonus_level[bonus_y][bonus_x+1]!='#')
				{
					bonus_x=bonus_x+1;
				}
			}
			else if(bonus_move == 'o'||bonus_move=='O')//exit
			{
				bonus_level_end=1;
				time_on=0;// this variable is there so that the loops breaks and the score is not added.
				break;
			}

			
			bonus_level[bonus_y][bonus_x]=c;
			
			system("cls");

			draw_bonus(bonus_level);
			

			if(bonus_y==12&&bonus_x==54)
			{
				int u=GetTickCount();//final time taken
				time_2=u;
				bonus_level_end=1;//to break the loop
				
			}
		}



		if(time_on==1)
		{
			p[player_number].score+=10000/((time_2-time_1)/750);//lesser the time taken more the score
			system("cls");
		}
		else 
		{
			
			system("cls");
		}


	}
	//-----------------------------------------------------------------------------------------------------------------------
	else if (level==3)
	{
		bonus_level_change(3);//prints that this is a bonus level
		
		int time_on=1;//this 
		char bonus_move;// to store the characters to move
		int bonus_level_end=0;
		int bonus_x=8,bonus_y=3,time_2;//time_2 is the final time 
		const char c=char(1);//this is just a smiley face
		int time_1=GetTickCount();//initail time taken 
		char bonus_level[100][100]= {"                        BONUS     LEVEL                         ", 
										"                                                                ", 
										"      ####################################################      ", 
										"      #                                 #     #          #      ", 
										"      ####### ##### ##### ##### ##### ##### ##### ###### #      ", 
										"      #²#      #     #      ### #                      # #      ", 
										"BONUS # ######## #   ###### ### # ###################  # # BONUS", 
										"      # # #    #   #   #  # ### #                      # #      ", 
										"LEVEL # #   #    # ### # ## ### ################ ####### # LEVEL", 
										"      # ############ # #  #                    #       # #      ", 
										"      # ##           # ## # ################## ######  # #      ", 
										"      # #  ######### # #  # #                # #    #  # #      ", 
										"      # ##         # # # ## # ############## # #  #    # #      ", 
										"      # #  #####   # # #  # # #            # # #  ###### #      ", 
										"      # ##     #   # # ## # # #            # # #       # #      ", 
										"      # #  ### ##### # #  # # ####### ###### # ####### # #      ", 
										"BONUS # ##   #     # # # ## #       # #      # #       # # BONUS", 
										"      # ###  ####### # #  # ####### # # ###### # ####### #      ", 
										"LEVEL #            #   #  #       # # #        #       # # LEVEL", 
										"      # ########################### # # ################ #      ", 
										"      #                             # #                  #      ", 
										"      ####################################################      ", 
										"                                                                ", 
										"                        BONUS     LEVEL                         "};





		bonus_level[bonus_y][bonus_x]=c;

		draw_bonus(bonus_level);
		
		while (bonus_level_end==0)//will stay 0 unless level crosses or exit pressed
		{
			bonus_level[bonus_y][bonus_x]=' ';
			
			
			cscanf("%c",&bonus_move);
			
			if (bonus_move=='w'||bonus_move=='W')//up
			{
				
				
				if (bonus_level[bonus_y-1][bonus_x]!='#')
				{
					bonus_y=bonus_y-1;
				}

			}

			else if(bonus_move=='s'||bonus_move=='S')//down
			{
				
				if (bonus_level[bonus_y+1][bonus_x]!='#')
				{
					bonus_y=bonus_y+1;
				}
			}

				
			else if(bonus_move=='a'||bonus_move=='A')//left
			{
				
				if (bonus_level[bonus_y][bonus_x-1]!='#')
				{
					bonus_x=bonus_x-1;
				}

			}
			else if(bonus_move=='d'||bonus_move=='D')//right
			{
				
				if (bonus_level[bonus_y][bonus_x+1]!='#')
				{
					bonus_x=bonus_x+1;
				}
			}
			else if(bonus_move == 'o'||bonus_move=='O')//exit
			{
				bonus_level_end=1;
				time_on=0;// this variable is there so that the loops breaks and the score is not added.
				break;
			}
			
			if (bonus_x==10&&bonus_y==16)
			{
				bonus_level[18][8]='#';
			}
			if (bonus_x==46&&bonus_y==18)
			{
				bonus_level[18][40]='#';
			}
			bonus_level[bonus_y][bonus_x]=c;
			
			system("cls");

			draw_bonus(bonus_level);
			

			if(bonus_y==5&&bonus_x==7)
			{
				int u=GetTickCount();//final time taken
				time_2=u;
				bonus_level_end=1;//to break the loop
				
			}
		}



		if(time_on==1)
		{
			p[player_number].score+=10000/((time_2-time_1)/500);//lesser the time taken more the score
			system("cls");
		}
		else 
		{
			
			system("cls");
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------
	else if (level==4)
	{
		bonus_level_change(4);//prints that this is a bonus level
		int time_on=1;//this 
		char bonus_move;// to store the characters to move
		int bonus_level_end=0;
		int bonus_x=1,bonus_y=2,time_2;//time_2 is the final time 
		const char c=char(1);//this is just a smiley face
		int time_1=GetTickCount();//initail time taken 
		char bonus_level[100][100]= {"                        BONUS     LEVEL                         ", 
									"################################################################", 
									"#²# # # # # # # # # # #     # # # # # # # # # # # # # # #   # ##", 
									"# # # # #   # # # # # # ### # # # # # # #     #   # # # # # # ##", 
									"# # #   # # # # # # # # # # # # # # #   # # # # # # # #   # # ##", 
									"# # # #   # # # # # # # # # # # # #   # # ### # # ###   # # # ##", 
									"# #   # # # #   # # # # #     # # # # #   # # # # # # # ###   ##", 
									"# # # ##### # # # # # # ##### # # # ### # # # # # # # # # # # ##", 
									"# # # #   # # # # # # #   # # ### # # ### # # # # # # ### ### ##", 
									"# # # # # # # # ### # # # # # # # # # # ### # # #   # # #   # ##", 
									"# # ### # # # # # # # # ### # #   # #   #     # # # # # # # # ##", 
									"# # # # # # # # # # # # # # # # # # # # # ### # # #   # # # # ##", 
									"# # # # # # # #     # # # # #   # # # # # # ### # ### # # # # ##", 
									"# #   # # #   ### # # #     # # # # # # # #   # # # ### # # # ##", 
									"# # # # # # # # # #   # # # ##### # # #   # # # # # #   # # # ##", 
									"# # ### # # # # # # # # ### # # # # # # ### # # # # # # # # # ##", 
									"# # # # # # # # # ### # # # # #   # # ###   # # #     # # # # ##", 
									"# # # # # # # # # # # # # # #   # # #   # # # # # # # # # # # ##", 
									"# #   # # ### # # # # #   # # # # # ### # # ### # ### # # # # ##", 
									"# # # # # # #   #   # # # # # ##### # # # # #   # # # # # # ####", 
									"# # # # # # # # # # ### ### # #   # # #   # # # # # # #   # # ##", 
									"#   #   #   # # # #     # # #   #   # # # #   # #   # # # #   ²#", 
									"################################################################", 
									"                        BONUS     LEVEL                         "};






		bonus_level[bonus_y][bonus_x]=c;

		draw_bonus(bonus_level);
		
		while (bonus_level_end==0)//will stay 0 unless level crosses or exit pressed
		{
			bonus_level[bonus_y][bonus_x]=' ';
			
			
			cscanf("%c",&bonus_move);
			
			if (bonus_move=='w'||bonus_move=='W')//up
			{
				
				
				if (bonus_level[bonus_y-1][bonus_x]!='#')
				{
					bonus_y=bonus_y-1;
				}

			}

			else if(bonus_move=='s'||bonus_move=='S')//down
			{
				
				if (bonus_level[bonus_y+1][bonus_x]!='#')
				{
					bonus_y=bonus_y+1;
				}
			}

				
			else if(bonus_move=='a'||bonus_move=='A')//left
			{
				
				if (bonus_level[bonus_y][bonus_x-1]!='#')
				{
					bonus_x=bonus_x-1;
				}

			}
			else if(bonus_move=='d'||bonus_move=='D')//right
			{
				
				if (bonus_level[bonus_y][bonus_x+1]!='#')
				{
					bonus_x=bonus_x+1;
				}
			}
			else if(bonus_move == 'o'||bonus_move=='O')//exit
			{
				bonus_level_end=1;
				time_on=0;// this variable is there so that the loops breaks and the score is not added.
				break;
			}

			
			bonus_level[bonus_y][bonus_x]=c;
			
			system("cls");

			draw_bonus(bonus_level);
			

			if(bonus_y==21&&bonus_x==61)
			{
				int u=GetTickCount();//final time taken
				time_2=u;
				bonus_level_end=1;//to break the loop
				
			}
		}



		if(time_on==1)
		{
			p[player_number].score+=10000/((time_2-time_1)/750);//lesser the time taken more the score
			system("cls");
		}
		else 
		{
			
			system("cls");
		}


	}
system("cls");



}
void bonus_level_change(int level)
{
	system("cls");
	Title();
	printf("\n\n\n\n                           +-----------------------+   \n");         
    printf("                           |    +-------------+    |   \n");         
    printf("                           |    |             |    |   \n");         
    printf("                           |    |    BONUS    |    |   \n");         
    printf("                           |    |             |    |   \n");         
    printf("                           |    |    LEVEL    |    |   \n");         
    printf("                           |    |             |    |   \n");         
    printf("                           |    +-------------+    |   \n");         
    printf("                           +-----------------------+   \n");         
    printf("                                       º               \n");         
    printf("                                    +-----+            \n");         
    printf("                                    |     |            \n");         
    printf("                                    |  %d  |            \n",level); // printing the level change 
    printf("                                    |     |            \n");         
    printf("                                    +-----+            \n");         
    printf("                                                       \n\n\n\n");   
    printf("                                  PRESS ENTER          \n");         
    printf("                                                       \n");         
    printf("                                  TO CONTINUE          \n"); 
	getchar();
	system("cls");
}


