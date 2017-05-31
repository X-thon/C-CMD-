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
	p_x = 0;    //Ϊʲô����Ϊ1���޷���ͨ
	p_y = (rand() % (MAX_LEN - 2) + 1);
	map = new point*[MAX_LEN];
	for (int i = 0; i < MAX_LEN; ++i)
	{
		map[i] = new point[MAX_LEN];
	}
	map[p_x][p_y].change();
	//����������
	end.x = p_x;
	end.y = p_y;
	//���õ�ǰ��
	p1.x = p_x;
	p1.y = p_y;
	//�̶�һ��ʼֻ��һ���ڽӵ㣬�Ƚ�����ͨ
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
special_point maze::select_next_adiacent_points(special_point p_now)    //���ա���ǰ�㡱������ѡ������һ����
{
	special_point p;
	int choice;
	int x2 = p_now.x, y2 = p_now.y;    //���渱��
	do{
		p_now.x = x2; p_now.y = y2;    //ˢ������
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
	} while (!inside_point(p_now));    //���������ͼ�ڣ���õ����Ϊ�ڽӵ�
	map[p_now.x][p_now.y].change();
	//����һ���ڽӵ�����긳ֵ��p;
	p.x = p_now.x;
	p.y = p_now.y;
	//���ҵ�����һ���ڽӵ㷵��
	return p;
}

bool maze::inside_point(special_point p)
{
	if (p.x > 0 && p.x < MAX_LEN - 1 && p.y > 0 && p.y < MAX_LEN - 1)
		return true;
	else
		return false;
}

//���ش�ͨ�����һ��
special_point maze::through_path(special_point p_1, special_point p_2)     //p_1��ʾ��ǰ�㣬p_2��ʾѡ������һ��
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
	//��ͨ��·�󣬽���ǰ����Ծ����һ�ڽӵ�
	p_1.x = p_2.x;p_1.y = p_2.y;
	p.x = p_1.x; p.y = p_1.y; 
	//���ص�ǰ��
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
	if (x - 2 > 0)    //��� x - 2 ��ͼ�ڣ�������ж�ͨ����
	{
		if (!map[x - 2][y].judge)    //�������ͨ�ģ�������ǽ����㣬�������ڽӵ�
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
	return flag;    //����ĸ������ϵ��ڽӵ㶼Ϊͨ·����õ�Ϊ������
}

//��Ѱ����һ�㡢����������Ϊһ�������ص�ǰ��
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
	//�����ж��Ƿ�Ҫ��������������ǽ����㣬�����ͨ
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
	} while (map[x][y].judge == false);    //ֻҪ�õ㲻Ϊͨ·����һֱ��
	p_start.x = x;
	p_start.y = y;
	//map[x][y].sign = 'O';    Ϊ�˲��Զ����ϵ����
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