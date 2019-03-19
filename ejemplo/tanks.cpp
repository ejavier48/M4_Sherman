#include <ctime> 
#include <vector>
#include <cstdlib>
#include <iostream>
#ifdef __linux__
	#include <unistd.h>
#elif TARGET_OS_MAC
	#include <unistd.h>
#elif _WIN32 || _WIN64
	#include <Windows.h>
#endif
#include <curses.h>
#include <cstdio>
using namespace std;
int const Fieldx = 31;
int const Fieldy = 21;
struct Position
{
    int x;
    int y;
};
struct Tank
{
    Position pos;
    int direction;
    bool life;
    int shoot;
    Position spos;
    int sdir;
    int sshoot;
};
struct Bullet
{
    Position pos;
    int direction;
    bool enemyshoot;
    bool exist;
    Bullet()
    {
        pos.x = -1;
        pos.y = -1;
        direction = 0;
        enemyshoot = true;
        exist = false;
    }
};
char part = 'O';
int playerposx;
int playerposy;
int enemyposx[4];
int enemyposy[4];
bool quit = false;
Tank player;
Tank enemy[4];
vector<Bullet> bomb;
Bullet bullet;
char field[Fieldy][Fieldx];
void out();
void init();
int f = -1;
int prevpoints = 0;
int kills;
void rendertank(Tank);
void bulletmove(Bullet&);
void playershoot();
void enemyshoot(Tank);
void bulletimpact();
void playermove();
void enemymove(Tank&);
void resetpos(Tank&);
void renderbullet(Bullet);
void respawn(Tank&);
void tanksgame();
int points = 0;
int lvl;
int lifes = 3;
double time_counter1 = 0;
double time_counter2 = 0;
clock_t this_time;
 
int main() 
{
	#ifdef __linux__
		system("clear");
	#elif TARGET_OS_MAC
		system("clear");
	#elif _WIN32 || _WIN64
		system("cls");
	#endif
	cout << "Movement: 'ARROW KEYS'" << endl;
	cout << "Shooting: 'SPACE KEY'" << endl;
	cout << "Getting extra life (costs 20 points): 'T'" << endl;
	cout << "Quit: 'Q'" << endl;
	cout << "There are 10 levels. To win you need:" << endl;
	cout << "Level 1:  10  kills" << endl; 
	cout << "Level 2:  20  kills" << endl; 
	cout << "Level 3:  30  kills" << endl; 
	cout << "Level 4:  40  kills" << endl; 
	cout << "Level 5:  50  kills" << endl; 
	cout << "Level 6:  60  kills" << endl; 
	cout << "Level 7:  70  kills" << endl; 
	cout << "Level 8:  80  kills" << endl; 
	cout << "Level 9:  90  kills" << endl; 
	cout << "Level 10: 100 kills" << endl; 
	cout << "1 kill = 1 point" << endl;
	cout << "Press any 'ENTER' to start" << endl;
	cout << "Good Luck =)" << endl;
	while (true)
	{
		if ('\n' == getchar())
		{
			break;
		}
		else
			#ifdef __linux__
				sleep(1);
			#elif TARGET_OS_MAC
				sleep(1);
			#elif _WIN32 || _WIN64
				Sleep(1000);
			#endif
	}
	
	for (lvl = 1; lvl <= 10; lvl++)
	{
		bomb.clear();
		f = -1;
		initscr(); noecho(); curs_set(0); keypad(stdscr, 1); nodelay(stdscr, 1);
		init();
		player.life = true;
		for (int i = 0; i<4; i++) {
			enemy[i].life = true;
		}
		tanksgame();
		nodelay(stdscr, 0);
		endwin();
		if (player.life == false)
		{
			cout << "\nSorry, you lose!" << endl;
			cout << "Your Points: " << kills << endl;
			break;
		}
		if ((points >= 10*lvl+prevpoints)&&(lvl<=10))
		{
			prevpoints = points;
			if (lvl<10)
			{
				cout << "\nCongratulations, you won!" << endl;
				cout << "Your Points: " << kills << endl;
				cout << "Starting Level " << lvl+1 << endl;
			}
			else
			{
				cout << "\nCongratulations, you have completed the game!" << endl;
				cout << "Your Points: " << kills << endl;
			}
				
			#ifdef __linux__
				sleep(3);
			#elif TARGET_OS_MAC
				sleep(3);
			#elif _WIN32 || _WIN64
				Sleep(3000);
			#endif
		}
	}
	#ifdef _WIN32
		system("pause");
	#elif _WIN64
		system("pause");
	#endif
    return 0;
    
}
 
void out()
{
    for (int i = 0; i < Fieldy; i++)
    {
        move(i, 0);
        for (int j = 0; j < Fieldx; j++)
        {
            addch(field[i][j]);
        }
    }
    move(Fieldy, 0);
    printw("Level ");
    printw("%d", lvl);
    move(Fieldy + 1, 0);
    printw("%d", kills);
    printw(" points   ");
    move(Fieldy + 2, 0);
    printw("%d", lifes);
    printw(" lifes    ");
    move(Fieldy + 3, 0);
    printw("Kills left to complete level: ");
    printw("%d/%d     ", (points-prevpoints), (lvl*10));
}
 
void init()
{
    for (int i = 0; i < Fieldy; i++)
    {
        for (int j = 0; j < Fieldx; j++)
        {
            if (i == 0)
            {
                field[i][j] = '#';
            }
            else if (j == 0)
            {
                field[i][j] = '#';
            }
            else if (i == (Fieldy-1))
            {
                field[i][j] = '#';
            }
            else if (j == (Fieldx-1))
            {
                field[i][j] = '#';
            }
            else
            {
                field[i][j] = ' ';
            }
        }
    }
    player.pos.y = (Fieldy/2)-1;
    player.pos.x = (Fieldx/2)-1;
    player.direction = 1;
    enemy[0].pos.y = 2;
    enemy[0].pos.x = 2;
    enemy[0].direction = 2;
    enemy[0].shoot = 0;
    enemy[0].spos.y = 2;
    enemy[0].spos.x = 2;
    enemy[0].sdir = 2;
    enemy[0].sshoot = 0;
    enemy[1].pos.y = (Fieldy-5);
    enemy[1].pos.x = 2;
    enemy[1].direction = 1;
    enemy[1].shoot = 0;
    enemy[1].spos.y = (Fieldy-5);
    enemy[1].spos.x = 2;
    enemy[1].sdir = 1;
    enemy[1].sshoot = 0;
    enemy[2].pos.y = 2;
    enemy[2].pos.x = (Fieldx-5);
    enemy[2].direction = 2;
    enemy[2].shoot = 0;
    enemy[2].spos.y = 2;
    enemy[2].spos.x = (Fieldx-5);
    enemy[2].sdir = 2;
    enemy[2].sshoot = 0;
    enemy[3].pos.y = (Fieldy-5);
    enemy[3].pos.x = (Fieldx-5);
    enemy[3].direction = 1;
    enemy[3].shoot = 0;
    enemy[3].spos.y = (Fieldy-5);
    enemy[3].spos.x = (Fieldx-5);
    enemy[3].sdir = 1;
    enemy[3].sshoot = 0;
    time_counter1 = time_counter2 = clock();
}
 
void rendertank(Tank t)
{
    if (t.life == true)
    {
        if (t.direction == 1)
        {
            field[t.pos.y][t.pos.x] = part;
            field[t.pos.y-1][t.pos.x] = part;
            field[t.pos.y][t.pos.x-1] = part;
            field[t.pos.y][t.pos.x+1] = part;
            field[t.pos.y+1][t.pos.x-1] = part;
            field[t.pos.y+1][t.pos.x+1] = part;
        }
        else if (t.direction == 2)
        {
            field[t.pos.y][t.pos.x] = part;
            field[t.pos.y+1][t.pos.x] = part;
            field[t.pos.y][t.pos.x-1] = part;
            field[t.pos.y][t.pos.x+1] = part;
            field[t.pos.y-1][t.pos.x-1] = part;
            field[t.pos.y-1][t.pos.x+1] = part;
        }
        else if (t.direction == 3)
        {
            field[t.pos.y][t.pos.x] = part;
            field[t.pos.y][t.pos.x+1] = part;
            field[t.pos.y-1][t.pos.x] = part;
            field[t.pos.y+1][t.pos.x] = part;
            field[t.pos.y-1][t.pos.x-1] = part;
            field[t.pos.y+1][t.pos.x-1] = part;
        }
        else if (t.direction == 4)
        {
            field[t.pos.y][t.pos.x] = part;
            field[t.pos.y][t.pos.x-1] = part;
            field[t.pos.y-1][t.pos.x] = part;
            field[t.pos.y+1][t.pos.x] = part;
            field[t.pos.y-1][t.pos.x+1] = part;
            field[t.pos.y+1][t.pos.x+1] = part;
        }
    }
    
}
 
void renderbullet(Bullet b)
{
    if (b.exist == true)
    {
        field[b.pos.y][b.pos.x] = '*';
    }
    
}
 
void playermove()
{
    switch (getch()) {
        case KEY_UP:
            player.direction = 1;
            player.pos.y--;
            break;
        case KEY_DOWN:
            player.direction = 2;
            player.pos.y++;
            break;
        case KEY_RIGHT:
            player.direction = 3;
            player.pos.x++;
            break;
        case KEY_LEFT:
            player.direction = 4;
            player.pos.x--;
            break;
        case 't': case 'T':
			if (kills >= 20)
			{
				kills = kills - 20;
				lifes++;
			}
			break;
        case ' ':
            playershoot();
            break;
        case 'q': case 'Q':
            quit = true;
            break;
    }
}
void resetpos(Tank& t)
{   
    if (t.pos.y < 2)
    {
        t.pos.y++;
    }
    else if (t.pos.y > (Fieldy-4))
    {
        t.pos.y--;
    }
    else if (t.pos.x > (Fieldx-4))
    {
        t.pos.x--;
    } 
    else if (t.pos.x < 2)
    {
        t.pos.x++;
    } 
    
    for (int i = 0; i<4; i++)
    {
        if ((player.pos.x - enemy[i].pos.x < 3)&&(player.pos.y - enemy[i].pos.y < 3)&&(player.pos.x - enemy[i].pos.x > -3)&&(player.pos.y - enemy[i].pos.y > -3)&&(enemy[i].life == true))
        {
            player.pos.x = playerposx;
            player.pos.y = playerposy;
        }
    }
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j<4; j++)
        {
            if(i == j)
            {
                continue;
            }
            else if ((enemy[i].pos.x - enemy[j].pos.x < 3)&&(enemy[i].pos.y - enemy[j].pos.y < 3)&&(enemy[i].pos.x - enemy[j].pos.x > -3)&&(enemy[i].pos.y - enemy[j].pos.y > -3)&&(enemy[j].life == true))
            {
                enemy[i].pos.x = enemyposx[i];
                enemy[i].pos.y = enemyposy[i];
            }
        }
    }
    for (int i = 0; i<4; i++)
    {
        if ((enemy[i].pos.x - player.pos.x < 3)&&(enemy[i].pos.y - player.pos.y < 3)&&(enemy[i].pos.x - player.pos.x > -3)&&(enemy[i].pos.y - player.pos.y > -3)&&(player.life == true))
        {
            enemy[i].pos.x = enemyposx[i];
            enemy[i].pos.y = enemyposy[i];
        }
    }
}
 
void enemymove(Tank& t)
{
    if (t.life == true)
    {
        t.direction = rand() % 4 + 1;
        t.shoot = rand() % 5;
        if (t.direction == 1)
        {
            t.pos.y--;
        }
        else if (t.direction == 2)
        {
            t.pos.y++;
        }
        else if (t.direction == 3)
        {
            t.pos.x++;
        }
        else if (t.direction == 4)
        {
            t.pos.x--;
        }
        if (t.shoot == 1)
        {
            enemyshoot(t);
        }
    }
}
 
void playershoot()
{
    f++;
    bomb.push_back(bullet);
    bomb[f].exist = true;
    bomb[f].direction = player.direction;
    bomb[f].enemyshoot = false;
    if(bomb[f].direction == 1)
    {
        bomb[f].pos.x = player.pos.x;
        bomb[f].pos.y = player.pos.y-2;
    }
    else if(bomb[f].direction == 2)
    {
        bomb[f].pos.x = player.pos.x;
        bomb[f].pos.y = player.pos.y+2;
    }
    else if(bomb[f].direction == 3)
    {
        bomb[f].pos.x = player.pos.x+2;
        bomb[f].pos.y = player.pos.y;
    }
    else if(bomb[f].direction == 4)
    {
        bomb[f].pos.x = player.pos.x-2;
        bomb[f].pos.y = player.pos.y;
    }
}
 
void enemyshoot(Tank e)
{
    f++;
    bomb.push_back(bullet);
    bomb[f].exist = true;
    bomb[f].direction = e.direction;
    bomb[f].enemyshoot = true;
    if(bomb[f].direction == 1)
    {
        bomb[f].pos.x = e.pos.x;
        bomb[f].pos.y = e.pos.y-2;
    }
    else if(bomb[f].direction == 2)
    {
        bomb[f].pos.x = e.pos.x;
        bomb[f].pos.y = e.pos.y+2;
    }
    else if(bomb[f].direction == 3)
    {
        bomb[f].pos.x = e.pos.x+2;
        bomb[f].pos.y = e.pos.y;
    }
    else if(bomb[f].direction == 4)
    {
        bomb[f].pos.x = e.pos.x-2;
        bomb[f].pos.y = e.pos.y;
    }
}
 
void bulletmove(Bullet& b)
{
    if ((b.direction == 1)&&(b.exist == true))
    {
        b.pos.y--;
    }
    else if ((b.direction == 2)&&(b.exist == true))
    {
        b.pos.y++;
    }
    else if ((b.direction == 3)&&(b.exist == true))
    {
        b.pos.x++;
    }
    else if ((b.direction == 4)&&(b.exist == true))
    {
        b.pos.x--;
    }
    if (b.pos.y < 1)
    {
        b.pos.y++;
        b.exist = false;
    }
    else if (b.pos.y > (Fieldy-3))
    {
        b.pos.y--;
        b.exist = false;
    }
    else if (b.pos.x > (Fieldx-3))
    {
        b.pos.x--;
        b.exist = false;
    } 
    else if (b.pos.x < 1)
    {
        b.pos.x++;
        b.exist = false;
    } 
    for (int j = 0; j < 4; j++)
    { 
        if ((b.pos.x - enemy[j].pos.x < 2)&&(b.pos.y - enemy[j].pos.y < 2)&&(b.pos.x - enemy[j].pos.x > -2)&&(b.pos.y - enemy[j].pos.y > -2)&&(b.enemyshoot == false)&&(b.exist == true)&&(enemy[j].life == true))
        {
            enemy[j].life = false;
            b.exist = false;
            points++;
            kills++;
        }
        else if ((b.pos.x - enemy[j].pos.x < 2)&&(b.pos.y - enemy[j].pos.y < 2)&&(b.pos.x - enemy[j].pos.x > -2)&&(b.pos.y - enemy[j].pos.y > -2)&&(b.enemyshoot == true)&&(b.exist == true)&&(enemy[j].life == true))
        {
            b.exist = false;
        }
        else if ((b.pos.x - player.pos.x < 2)&&(b.pos.y - player.pos.y < 2)&&(b.pos.x - player.pos.x > -2)&&(b.pos.y - player.pos.y > -2)&&(b.enemyshoot == true)&&(b.exist == true)&&(player.life == true))
        {
			lifes--;
			if (lifes == 0)
			{
				player.life = false;
			}
            b.exist = false;
        }
    
    }
    for (int i = 0; i<bomb.size(); i++)
    {
        for (int j = 0; j<bomb.size(); j++)
        {
            if(i == j)
            {
                continue;
            }
            else if ((bomb[i].pos.x - bomb[j].pos.x < 1)&&(bomb[i].pos.y - bomb[j].pos.y < 1)&&(bomb[i].pos.x - bomb[j].pos.x > -1)&&(bomb[i].pos.y - bomb[j].pos.y > -1)&&(bomb[i].exist == true)&&(bomb[j].exist == true))
            {
                bomb[i].exist = false;
                bomb[j].exist = false;
            }
        }
    }
}
void respawn(Tank& t)
{
	if (t.life == false)
	{
		t.life = true;
		t.pos.y = t.spos.y;
		t.pos.x = t.spos.x;
		t.direction = t.sdir;
		t.shoot = t.sshoot;
	}
}
void tanksgame()
{
    while(quit != true)
    { 
        for (int i = 0; i < Fieldy; i++)
        {
            for (int j = 0; j < Fieldx; j++)
            {
                if (i == 0)
                {
                    field[i][j] = '#';
                }
                else if (j == 0)
                {
                    field[i][j] = '#';
                }
                else if (i == (Fieldy-1))
                {
                    field[i][j] = '#';
                }
                else if (j == (Fieldx-1))
                {
                    field[i][j] = '#';
                }
                else
                {
                    field[i][j] = ' ';
                }
            }
        }
        rendertank(player);
        for (int i = 0; i<4; i++)
        {
            rendertank(enemy[i]);
        }
        playerposx = player.pos.x;
        playerposy = player.pos.y;
        for (int i = 0; i<4; i++)
        {
            enemyposx[i] = enemy[i].pos.x;
            enemyposy[i] = enemy[i].pos.y;
        }
        for (int i = 0; i<bomb.size(); i++)
        {
            renderbullet(bomb[i]);
        }
        playermove();
        this_time = clock();
        if (this_time - time_counter1 >= CLOCKS_PER_SEC / 3.0)
        {
            time_counter1 += CLOCKS_PER_SEC / 3.0;
            for (int i = 0; i<4; i++)
            {
				respawn(enemy[i]);
                enemymove(enemy[i]);
            }
        }
        if (this_time - time_counter2 >= CLOCKS_PER_SEC / 10.0)
        {
            time_counter2 += CLOCKS_PER_SEC / 10.0;
            for (int i = 0; i<bomb.size(); i++)
            {
                 bulletmove(bomb[i]);
            }
        }
        resetpos(player);
        for (int i = 0; i<4; i++)
        {
            resetpos(enemy[i]);
        }
        for (int i = 0; i < bomb.size(); i++)
        {
			if (bomb[i].exist == false)
			{
				bomb.erase(bomb.begin()+i);
				f--;
			}
		}
        out();
        if ((points >= 10*lvl+prevpoints)||(player.life == false))
        {
            break;
        }
		#ifdef __linux__
				usleep(10);
		#elif TARGET_OS_MAC
			usleep(10);
		#elif _WIN32 || _WIN64
				Sleep(10);
		#endif
    }
}

