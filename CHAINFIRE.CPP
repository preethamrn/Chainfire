#include <iostream.h>
#include <conio.h>
#include <process.h>
#include <dos.h>

//CONTAINS ALL MAX VALUES FOR ALLOCATION OF ARRAYS
enum { MAX_PLAYERS=15, MAX_BOARD_WIDTH=13, MAX_BOARD_HEIGHT=20 };

//CLASS CONTAINING BOARD, POSITIONS OF ALL ORBS, AND ALL FUNCTIONS
class Reactor
{
	private:
	char BOARD[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT];
	int CRITICAL_ORBS[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT], COLOR_MATRIX[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT], PREVIOUS_MOVE[MAX_BOARD_WIDTH][MAX_BOARD_HEIGHT][2], ELIMINATED[MAX_PLAYERS], P_COLOR[MAX_PLAYERS], PLAYER, TURN_NUMBER, X, Y, X_POSITION, Y_POSITION, UNDONE, PLAYERS, BOARD_WIDTH, BOARD_HEIGHT;
	public:
	Reactor();
	void help();
	void screen();
	void blow(int i, int j);
	int blowable();
	void undo();
	void input();
	int win_check();
	void elimination();
	void react();
};

//CONSTRUCTOR INITIALIZING ALL VARIABLES AND GETTING VALUES OF BOARD SIZE AND NUMBER OF PLAYERS
Reactor::Reactor()
{
	X=0;
	Y=0;
	X_POSITION=4;
	Y_POSITION=1;
	UNDONE=0;
	TURN_NUMBER=1;
	PLAYER=1;
	do //GET NUMBER OF PLAYERS
	{
		cout << "Enter No. of Players: "; cin >> PLAYERS;
	} while(PLAYERS > MAX_PLAYERS || PLAYERS < 2);
	do //GET SIZE OF BOARD
	{
		cout << "Enter Board Size (WIDTH <space> HEIGHT): "; cin >> BOARD_WIDTH >> BOARD_HEIGHT;
	} while(BOARD_WIDTH > MAX_BOARD_WIDTH || BOARD_HEIGHT > MAX_BOARD_HEIGHT || PLAYERS > BOARD_HEIGHT*BOARD_WIDTH);
	//INITIALIZES ALL THE COLORS VALUES OF PLAYERS (DEPENDING ON HOW MANY ARE PLAYING)
	switch(PLAYERS)
	{
		//ADD EXTRA PLAYERS HERE----------------------------------------
		case 15: P_COLOR[14]=15;//WHITE
		case 14: P_COLOR[13]=7; //LIGHT GREY
		case 13: P_COLOR[12]=13;//LIGHT PURPLE
		case 12: P_COLOR[11]=6; //ORANGE
		case 11: P_COLOR[10]=11;//LIGHT BLUE
		case 10: P_COLOR[9]=10; //LIGHT GREEN
		case 9: P_COLOR[8]=9;   //DARK LIGHT BLUE
		case 8: P_COLOR[7]=8;   //GREY
		case 7: P_COLOR[6]=12;  //LIGHT RED
		case 6: P_COLOR[5]=3;   //TURQUOISE
		case 5: P_COLOR[4]=5;   //PURPLE
		case 4: P_COLOR[3]=14;  //YELLOW
		case 3: P_COLOR[2]=2;   //GREEN
		case 2: P_COLOR[1]=1;   //BLUE
		case 1: P_COLOR[0]=4;   //RED
	}
}

void Reactor::help()
{
    clrscr();
    for(int i=0; i<PLAYERS; i++)
    {
        textcolor(P_COLOR[i]);
        cprintf("PLAYER %d: 0    ", i+1);
        if((i+1)%4==0) cout << endl;
    }
	cout << "\n\n\nThis is a game called Chain Reaction. The goal of the game is to make reactions that will eliminate the other players and give you control of the board. \nReactions: \nAt the corners: Critical Mass = 1 \nAt the edges: Critical Mass = 2 \nAnywhere else: Critical Mass = 3 \n\nControls: \nMoving: WASD (up, left, down, right) \nUndo: <BACKSPACE> \nSelect: Enter \nExit: 0 \nEaster Egg: Creator\'s Name...";
	//EASTER EGG :3
	if(getch()=='P')
	{
		textcolor(WHITE);
		clrscr();
		cout << "It's the year of 1987. Terror is within the hearts of the Reactorian kingdom. \nPeople must be sacrificed and reacted to regain control of the throne. But how \ndid this all happen?... Press <a specific key that I'm not telling you> to \ncontinue....";
		if(getch()=='R')
		{
			cout << "\n\nThe kingdom\'s era began 200 years ago in 1790. The king, BOB, had recently \naquired a large amount of land in the Tokian Outing. The area was full of \nradiation and over the years the people of the kingdom evolved to gained \nresistance to this radiation and came to be known as Reactorians... \nPress <a specific key that I'm not telling you> to continue";
			if(getch()=='E')
			{
				cout << "\n\nIn the late 1850\'s the Reactorians and their king BOB started realizing the power of the radiation in this reagion. One group wanted to harness this power to increase the area of the kingdom but the other side, leaded by Lord Slimy, knew that this was a bad idea. The civil war between BOB and Lord Slimy started and came to be known as the Great Civil War of 1850. Many people sacrificed themselves for their cause and in the end they came to a concensus and Lord Slimy became the new king. They decided to never partake in the horrendous act of a war ever again. Little did they know, they would have no choice... Press <a specific key that I'm not telling you> to continue";
				if(getch()=='E')
				{
					cout << "\n\nTowards the end of the 19th century, the Reactorian kingdom started being threatened by the original owners of the Tokian Outing... Press <a specific key that I'm not telling you> to continue";
					if(getch()=='T')
					{
						cout << "\n\nThe Tokians were asking for many things that Lord Slimy couldn't provide. As the Tokians lived in the Tokian Outing before the Reactorian Kingdom, they had the power of Reactivity as well. Slowly and steadily they began coming closer and closer to starting a war with the Reactorian kingdom... Press <a specific key that I'm not telling you> to continue";
						if(getch()=='H')
						{
							cout << "\n\nLord Slimy stalled the fight as much as he could but as 1987 approached he knew that there was nothing he could do... Press <a specific key that I'm not telling you> to continue";
							if(getch()=='A')
							{
								cout << "\n\nHe led his units to a battlefield that, fortunately for him, had an adjustable board size coded in. As he units took the positions that he placed them in, the began to react according to a certain set of rules and mechanics that were created by the creator of this program. Many other kingdoms joined this war as well since the programmer also coded in extensive multiplayer capabilities. The war was long and hard but at the end the better kingdom won. That kingdom was... Press <a specific key that I'm not telling you> to continue";
								if(getch()=='M')
								{
									cout << "\n\nWait... Why are you even reading this. Don\'t you have better stuff to do? Go do that stuff. So you want the story to end? Ok then... Press any key to continue";
									getch();
									cout << "\n\nTHE END! Happy now?";
									getch();
								}
							}
						}
					}
				}
			}
		}
	}
	screen();
}

void Reactor::screen()
{
	clrscr();
	if(PLAYER) textcolor(P_COLOR[PLAYER-1]);    //SETS TEXTCOLOR TO COLOR OF PLAYER
	else textcolor(WHITE);
	//PRINTS BORDER
	for(int j=0;j<=BOARD_HEIGHT;j++)
	{
		gotoxy(1,j);
		cprintf("|-");
		for(int i=0;i<BOARD_WIDTH;i++)
		{
			if(i==BOARD_WIDTH-1) cprintf("   -|");
			else cprintf("   -|-");
		}
	}
	//PRINTS ALL THE DIFFERENT ORBS DEPENDING ON THE COLOR AND HOW MANY ARE PRESENT IN ONE POSITION
	for(j=0;j<BOARD_HEIGHT;j++)
	{
		textcolor(WHITE);
		for(int i=0;i<BOARD_WIDTH;i++)
		{
			gotoxy(6*i+3,j+1);
			if(BOARD[i][j]==0) COLOR_MATRIX[i][j]=0;
			if (COLOR_MATRIX[i][j]) textcolor(P_COLOR[COLOR_MATRIX[i][j]-1]);
			else textcolor(WHITE);
			//PRINTS THE NUMBER OF ORBS IN A POSITION
			switch(BOARD[i][j])
			{
				case 0: cprintf("   "); break;
				case 1: cprintf(" 0 "); break;
				case 2: cprintf("0 0"); break;
				case 3: cprintf("000"); break;
				default:cprintf("000"); break;
			}
		}
		cout << endl;
	}
	textcolor(WHITE);
	cout <<"\nPLAYER " << PLAYER << endl << endl;
}

//EXPLODES THE POINTS THAT HAVE BEEN SET TO CRITICAL (BY blowable()) CAUSING ADJACENT POINTS TO INCREMENT
void Reactor::blow(int i, int j)
{
	if(BOARD[i][j] > 3 && i > 0 && i < BOARD_WIDTH-1 && j > 0 && j < BOARD_HEIGHT-1) {
		BOARD[i][j] -=4;
		BOARD[i+1][j] += 1;
		COLOR_MATRIX[i+1][j] = PLAYER;
		BOARD[i-1][j] += 1;
		COLOR_MATRIX[i-1][j] = PLAYER;
		BOARD[i][j-1] += 1;
		COLOR_MATRIX[i][j-1] = PLAYER;
		BOARD[i][j+1] += 1;
		COLOR_MATRIX[i][j+1] = PLAYER;
	} else if(BOARD[i][j] > 2 && i == 0 && j != 0 && j != BOARD_HEIGHT-1) {
		BOARD[i][j] -=3;
		BOARD[i+1][j] += 1;
		COLOR_MATRIX[i+1][j] = PLAYER;
		BOARD[i][j-1] += 1;
		COLOR_MATRIX[i][j-1] = PLAYER;
		BOARD[i][j+1] += 1;
		COLOR_MATRIX[i][j+1] = PLAYER;
	} else if(BOARD[i][j] > 2 && j == 0 && i != 0 && i != BOARD_WIDTH-1) {
		BOARD[i][j] -=3;
		BOARD[i+1][j] += 1;
		COLOR_MATRIX[i+1][j] = PLAYER;
		BOARD[i][j+1] += 1;
		COLOR_MATRIX[i][j+1] = PLAYER;
		BOARD[i-1][j] += 1;
		COLOR_MATRIX[i-1][j] = PLAYER;
	} else if(BOARD[i][j] > 2 && i == BOARD_WIDTH-1 && j != 0 && j != BOARD_HEIGHT-1) {
		BOARD[i][j] -=3;
		BOARD[i-1][j] += 1;
		COLOR_MATRIX[i-1][j] = PLAYER;
		BOARD[i][j+1] += 1;
		COLOR_MATRIX[i][j+1] = PLAYER;
		BOARD[i][j-1] += 1;
		COLOR_MATRIX[i][j-1] = PLAYER;
	} else if(BOARD[i][j] > 2 && j == BOARD_HEIGHT-1 && i != 0 && i != BOARD_WIDTH-1) {
		BOARD[i][j] -=3;
		BOARD[i+1][j] += 1;
		COLOR_MATRIX[i+1][j] = PLAYER;
		BOARD[i][j-1] += 1;
		COLOR_MATRIX[i][j-1] = PLAYER;
		BOARD[i-1][j] += 1;
		COLOR_MATRIX[i-1][j] = PLAYER;
	} else if(BOARD[i][j] > 1 && i == 0 && j == 0) {
		BOARD[i][j] -=2;
		BOARD[i+1][j] += 1;
		COLOR_MATRIX[i+1][j] = PLAYER;
		BOARD[i][j+1] += 1;
		COLOR_MATRIX[i][j+1] = PLAYER;
	} else if(BOARD[i][j] > 1 && i == 0 && j == BOARD_HEIGHT-1) {
		BOARD[i][j] -=2;
		BOARD[i+1][j] += 1;
		COLOR_MATRIX[i+1][j] = PLAYER;
		BOARD[i][j-1] += 1;
		COLOR_MATRIX[i][j-1] = PLAYER;
	} else if(BOARD[i][j] > 1 && i == BOARD_WIDTH-1 && j == 0) {
		BOARD[i][j] -=2;
		BOARD[i-1][j] += 1;
		COLOR_MATRIX[i-1][j] = PLAYER;
		BOARD[i][j+1] += 1;
		COLOR_MATRIX[i][j+1] = PLAYER;
	} else if(BOARD[i][j] > 1 && i == BOARD_WIDTH-1 && j == BOARD_HEIGHT-1) {
		BOARD[i][j] -=2;
		BOARD[i-1][j] += 1;
		COLOR_MATRIX[i-1][j] = PLAYER;
		BOARD[i][j-1] += 1;
		COLOR_MATRIX[i][j-1] = PLAYER;
	}
	screen();
}

//SETS ALL THE PLACES WHERE AN EXPLOSION IS POSSIBLE SO THAT THEY CAN BE EXPLODED IN THE NEXT CALL OF blow() DURING EXECUTION
int Reactor::blowable()
{
    int Reaction_Over=0;
    for(int X=0; X<BOARD_WIDTH; X++)
    {
	for(int Y=0; Y<BOARD_HEIGHT; Y++)
        {
	    if(BOARD[X][Y] > 3 && X > 0 && X < BOARD_WIDTH-1 && Y > 0 && Y < BOARD_HEIGHT-1) {
                CRITICAL_ORBS[X][Y]=1;
                Reaction_Over=1;
            } else if(BOARD[X][Y] > 2 && X == 0 && Y != 0 && Y != BOARD_HEIGHT-1) {
                CRITICAL_ORBS[X][Y]=1;
                Reaction_Over=1;
            } else if(BOARD[X][Y] > 2 && Y == 0 && X != 0 && X != BOARD_WIDTH-1) {
                CRITICAL_ORBS[X][Y]=1;
                Reaction_Over=1;
            } else if(BOARD[X][Y] > 2 && X == BOARD_WIDTH-1 && Y != 0 && Y != BOARD_HEIGHT-1) {
                CRITICAL_ORBS[X][Y]=1;
                Reaction_Over=1;
            } else if(BOARD[X][Y] > 2 && Y == BOARD_HEIGHT-1 && X != 0 && X != BOARD_WIDTH-1) {
                CRITICAL_ORBS[X][Y]=1;
                Reaction_Over=1;
            } else if(BOARD[X][Y] > 1 && X == 0 && Y == 0) {
                CRITICAL_ORBS[X][Y]=1;
                Reaction_Over=1;
            } else if(BOARD[X][Y] > 1 && X == 0 && Y == BOARD_HEIGHT-1) {
                CRITICAL_ORBS[X][Y]=1;
                Reaction_Over=1;
            } else if(BOARD[X][Y] > 1 && X == BOARD_WIDTH-1 && Y == 0) {
                CRITICAL_ORBS[X][Y]=1;
                Reaction_Over=1;
            } else if(BOARD[X][Y] > 1 && X == BOARD_WIDTH-1 && Y == BOARD_HEIGHT-1) {
                CRITICAL_ORBS[X][Y]=1;
                Reaction_Over=1;
            }
	}
    }
    return Reaction_Over;
}

//RESETS BOARD TO THE PREVIOUS MOVE STATE AND GOES BACK TO PREVIOUS PLAYER SO (S)HE CAN MOVE AGAIN
void Reactor::undo()
{
	for(int i=0;i < BOARD_WIDTH; i++)
	{
        for(int j=0; j < BOARD_HEIGHT; j++)
	{
			BOARD[i][j]=PREVIOUS_MOVE[i][j][0];
			COLOR_MATRIX[i][j]=PREVIOUS_MOVE[i][j][1];
		}
    }
	do {
		if(PLAYER==1)
		{
			PLAYER=PLAYERS;
			TURN_NUMBER--;
		}
		else PLAYER--;
	} while(ELIMINATED[PLAYER-1]);
}

//GETS INPUT AND KEEPS MOVING USING WASD INPUT UNTIL ENTER KEY IS PRESSED. WHEN PRESSED IT WILL EXIT WITH THE CURRENT VALUES OF X/Y_POSITION
void Reactor::input()
{
	int inputgiven=0;
	while(!inputgiven)
	{
		screen();
		gotoxy(X_POSITION,Y_POSITION);
		switch(getch())
		{
			case 'w': Y_POSITION-=1; break;
			case 's': Y_POSITION+=1; break;
			case 'a': X_POSITION-=6; break;
			case 'd': X_POSITION+=6; break;
			case 'h': help(); break;
			case  13: if(COLOR_MATRIX[X_POSITION/6][Y_POSITION-1]==PLAYER || COLOR_MATRIX[X_POSITION/6][Y_POSITION-1]==0) inputgiven = 1; break;
			case   8: if(!UNDONE) {
							undo(); UNDONE=1;
						} break;
			case  48 : exit(0);
		}
		if(X_POSITION < 4) X_POSITION+=6;
		else if(X_POSITION > BOARD_WIDTH*6) X_POSITION-=6;
		else if(Y_POSITION < 1) Y_POSITION+=1;
		else if(Y_POSITION > BOARD_HEIGHT) Y_POSITION-=1;
	}
}

//CHECKS WHETHER ANY PLACE HAS WON
int Reactor::win_check()
{
	for(int i=0; i<BOARD_WIDTH; i++)
    {
        for(int j=0; j<BOARD_HEIGHT; j++)
        {
			if(COLOR_MATRIX[i][j]!=PLAYER && COLOR_MATRIX[i][j]!=0) return 0;
		}
    }
    return 1;
}

//ELIMINATES PLAYERS
void Reactor::elimination()
{
	for(int i=0; i<PLAYERS; i++)
	{
		int PlayerEliminatedFlag=1;
		for(int j=0; j<BOARD_WIDTH; j++)
		{
			for(int k=0; k<BOARD_HEIGHT; k++)
			{
				if(COLOR_MATRIX[j][k]==i+1)
				{
					ELIMINATED[i]=0;
					PlayerEliminatedFlag=0;
					break;
				}
			}
			if(PlayerEliminatedFlag==0) break;
		}
		if(PlayerEliminatedFlag==1)
        {
            ELIMINATED[i]=1;    //IF PLAYER IS ELIMINATED THEN IT STORES A VALUE IN AN ARRAY AND SKIPS THAT PLAYER'S TURN FOR THE REST OF THE GAME
        }
	}
}

void Reactor::react()
{
	//INITIALIZES ALL DATA TO 0
	for(int i=0; i<BOARD_WIDTH; i++)
	{
		for(int j=0; j<BOARD_HEIGHT; j++)
		{
			BOARD[i][j] = 0;
			CRITICAL_ORBS[i][j] = 0;
			COLOR_MATRIX[i][j] = 0;
			PREVIOUS_MOVE[i][j][0]=0;
			PREVIOUS_MOVE[i][j][1]=0;
		}
	}
	for(i=0; i<PLAYERS; i++) ELIMINATED[i]=0;
	do
	{
		input();    //GET INPUT AND EXIT WITH MODIFIED X/Y_POSITION VALUES
		//STORES THE CURRENT UNMODIFIED ARRAYS INCASE UNDO IS PRESSED NEXT TURN
		for(int i = 0;i < BOARD_WIDTH; i++)
		{
			for(int j = 0; j < BOARD_HEIGHT; j++)
			{
				PREVIOUS_MOVE[i][j][0]=BOARD[i][j];
				PREVIOUS_MOVE[i][j][1]=COLOR_MATRIX[i][j];
			}
		}
		//GETS X AND Y VALUES FROM MODIFIED X/Y_POSITION FROM input()
		X = X_POSITION/6;
		Y = Y_POSITION-1;
		COLOR_MATRIX[X][Y]=PLAYER;  //STORES THE VALUES OF PLAYER IN THAT POSITION
		BOARD[X][Y] += 1;           //INCREMENTS THE BOARD IN THAT POSITION
		while(blowable())           //WHILE THERE ARE SOME CRITICAL ORBS PRESENT
		{
			for(int i=0; i<BOARD_WIDTH; i++)
			{
				for(int j=0; j<BOARD_HEIGHT; j++)
				{
					if(CRITICAL_ORBS[i][j]==1) //IF THE POSITION IS IN AN EXPLODABLE STATE
					{
						blow(i,j); //THEN EXPLODE IT
						CRITICAL_ORBS[i][j]=0;  //AND RESET ITS VALUE
					}
				}
			}
			sound(300); delay(200); nosound(); delay(200); //PLAYS A SOUND EVERY ITERATION OF EXPLOSIONS
			if(win_check())
            		{
                		screen();
				gotoxy(9, BOARD_HEIGHT+2);
				cout << " WON!";
                		switch(getch())
                		{
                    			case  8  : undo(); break;
                    			default  : exit(0);
                		}
			}
		}
		if(TURN_NUMBER!=1) elimination(); //ELIMINATE PLAYERS AFTER EVERYONE HAS GOTTEN AT LEAST ONE CHANCE TO PUT AN ORB ON THE BOARD
		//GO TO THE NEXT PLAYER
		do {
			if(PLAYER==PLAYERS) //IF IT'S THE LAST PLAYER THEN GO BACK TO PLAYER 1
			{
				PLAYER=1;
				TURN_NUMBER++;
			}
			else PLAYER++;
		} while(ELIMINATED[PLAYER-1]);
		UNDONE=0;
	} while(1);

}

void main()
{
	textcolor(WHITE);
	textbackground(BLACK);
	clrscr();
	cout << "CHAIN REACTION!"; delay(1000); //ASCII ART (APPARENTLY...)
	clrscr();
	Reactor reaction;   //CREATES AN OBJECT OF THE CLASS CALLED REACTOR
	reaction.react();   //CAUSES THE REACTOR TO REACT, ie, THE GAME HAS BEGUN
}
