#include "Maze.h"
/*
p_x and p_y initialization is in order to select a start point randomly.
maze_wide and maze_high , which in order to log the wide and height of the maze.
map is the maze's instance. Initalize it all into '*'.
*/
maze::maze()
{
	srand((unsigned)time(NULL));
	maze_wide = MAX_LEN;
	maze_high = MAX_LEN;
	p_x = 0;    //为什么设置为1就无法走通
	p_y = (rand() % (MAX_LEN - 2) + 1);
	map = new point*[MAX_LEN];
	for (int i = 0; i < MAX_LEN; ++i)
	{
		map[i] = new point[MAX_LEN];
	}
	map[p_x][p_y].change();
	//标明结束点
	end.x = p_x;
	end.y = p_y;
	//设置当前点
	p1.x = p_x;
	p1.y = p_y;
	//固定一开始只有一个邻接点，先将它打通
	step(p1);
	search();
	player.x = start.x; player.y = start.y;
	map[player.x][player.y].sign = 'O';
}

/*
  Destructor.
*/
maze::~maze()
{
	delete[]map;
}

/*
  Maze output.
*/
void maze::show()
{
	for (int i = 0; i < maze_high; ++i)
	{
		for (int j = 0, count = 0; j < maze_wide; ++j, ++count)
		{
			printf("%c", map[i][j]);
			if (count == maze_wide - 1)
			{
				printf("\n");
			}
		}
	}
	printf("\n");
}

/*
  Randomly select a direction, change the coordinates, and set the point to the point.
*/
special_point maze::select_next_adiacent_points(special_point p_now)    //接收“当前点”，返回选定的下一个点
{
	special_point p;
	int choice;
	int x2 = p_now.x, y2 = p_now.y;    //保存副本
	do{
		p_now.x = x2; p_now.y = y2;    //刷新数据
		choice = rand() % 4;
		switch (choice)
		{
		case 0:
			p_now.x += 2;
			break;
		case 1:
			p_now.x += -2;
			break;
		case 2:
			p_now.y += 2;
			break;
		case 3:
			p_now.y += -2;
			break;
		}
	} while (!inside_point(p_now));    //如果坐标在图内，则该点可作为邻接点
	map[p_now.x][p_now.y].change();
	//将下一个邻接点的坐标赋值给p;
	p.x = p_now.x;
	p.y = p_now.y;
	//将找到的下一个邻接点返回
	return p;
}

bool maze::inside_point(special_point p)
{
	if (p.x > 0 && p.x < MAX_LEN - 1 && p.y > 0 && p.y < MAX_LEN - 1)
		return true;
	else
		return false;
}

//返回打通后的下一点
special_point maze::through_path(special_point p_1, special_point p_2)     //p_1表示当前点，p_2表示选定的下一点
{
	special_point p;
	if (p_1.x < p_2.x)
	{
		p.x = p_1.x + 1;
		p.y = p_1.y;
		map[p.x][p.y].change();
	}
	else if (p_1.x > p_2.x)
	{
		p.x = p_1.x - 1;
		p.y = p_1.y;
		map[p.x][p.y].change();
	}
	else if (p_1.y < p_2.y)
	{
		p.x = p_1.x;
		p.y = p_1.y + 1;
		map[p.x][p.y].change();
	}
	else if (p_1.y > p_2.y)
	{
		p.x = p_1.x;
		p.y = p_1.y - 1;
		map[p.x][p.y].change();
	}
	//打通道路后，将当前点跳跃至下一邻接点
	p_1.x = p_2.x;p_1.y = p_2.y;
	p.x = p_1.x; p.y = p_1.y; 
	//返回当前点
	return p;
}

bool maze::judge_is_pass_way(int x, int y)
{
	if (map[x][y].judge == true)
		return true;
	else
		return false;
}

bool maze::judge_no_end_point(int x, int y)
{
	bool flag = false;
	if (x - 2 > 0)    //如果 x - 2 在图内，则可以判断通断性
	{
		if (!map[x - 2][y].judge)    //如果不是通的，则代表并非结束点，还存在邻接点
			return flag = true;
	}
	if (x + 2 < MAX_LEN - 1)
	{
		if (!map[x + 2][y].judge)
			return flag = true;
	}
	if (y - 2 > 0)
	{
		if (!map[x][y - 2].judge)
			return flag = true;
	}
	if (y + 2 < MAX_LEN - 1)
	{
		if (!map[x][y + 2].judge)
			return flag = true;
	}
	return flag;    //如果四个方向上的邻接点都为通路，则该点为结束点
}

//将寻找下一点、连接两点结合为一步；返回当前点
special_point maze::step(special_point p_now)
{
	special_point p;
	p = select_next_adiacent_points(p_now);
	p_now = through_path(p_now, p);
	return p_now;
}

void maze::search()
{
	search_path(p1);
	start = create_start_point(start);
}

special_point maze::search_path(special_point p_now)
{
	//不断判断是否将要结束，如果还不是结束点，将其打通
	while (judge_no_end_point(p_now.x, p_now.y))
	{
		p_now = step(p_now);
		search_path(p_now);
	}
	return p_now;
}

special_point maze::create_start_point(special_point p_start)
{
	int x, y;
	x = MAX_LEN - 2;
	do{
		y = (rand() % (MAX_LEN - 2)) + 1;
	} while (map[x][y].judge == false);    //只要该点不为通路，就一直找
	p_start.x = x;
	p_start.y = y;
	//map[x][y].sign = 'O';    为了测试而加上的语句
	return p_start;
}

void maze::move()
{
	ch = _getch();
	switch (ch)
	{
	case 'w':m_up(); break;
	case 's':m_down(); break;
	case 'a':m_left(); break;
	case 'd':m_right(); break;
	}
}

void maze::m_up()
{
	if (ch == 'w')
	{
		if (map[player.x - 1][player.y].sign != '#')
		{
			map[player.x][player.y].sign = ' ';
			//player.x = player.x - 1;
			player.x--;
			map[player.x][player.y].sign = 'O';
		}
	}
}

void maze::m_down()
{
	if (ch == 's')
	{
		if (map[player.x + 1][player.y].sign != '#')
		{
			map[player.x][player.y].sign = ' ';
			//player.x = player.x + 1;
			player.x++;
			map[player.x][player.y].sign = 'O';
		}
	}
}

void maze::m_left()
{
	if (ch == 'a')
	{
		if (map[player.x][player.y - 1].sign != '#')
		{
			map[player.x][player.y].sign = ' ';
			//player.y = player.y - 1;
			player.y--;
			map[player.x][player.y].sign = 'O';
		}
	}
}

void maze::m_right()
{
	if (ch == 'd')
	{
		if (map[player.x][player.y + 1].sign != '#')
		{
			map[player.x][player.y].sign = ' ';
			//player.y = player.y + 1;
			player.y++;
			map[player.x][player.y].sign = 'O';
		}
	}
}