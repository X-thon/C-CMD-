#ifndef MAZE_H
#define MAZE_H
#include "Point.h"
#include "Special_point.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include<conio.h>
using namespace std;
const int MAX_LEN = 30;
class maze{
private:
	special_point p1;    //当前点
	special_point p2;    //下一邻接点
	char ch;
	int p_x;    //存放迷宫中某一点的坐标
	int p_y;
	int maze_wide;    //存放迷宫的宽与高
	int maze_high;
	point **map;    //存放迷宫
	vector<point> v1;
public:
	special_point start;    //特殊点类存放起始点与结束点
	special_point end;
	special_point player;    //表示当前玩家位置
	maze();    //构造函数
	~maze();    //析构函数
	void search();
	special_point search_path(special_point p_now);    
	special_point select_next_adiacent_points(special_point p_now);    //将当前所在坐标传入，寻找下一邻接点
	void show();    //输出迷宫
	bool inside_point(special_point p);    //判断该点是否为边界点
	special_point through_path(special_point p_1, special_point p_2);
	bool judge_is_pass_way(int x, int y);    //判断该点是否为通路
	bool judge_no_end_point(int x, int y);    //判断是否还有路走
	special_point step(special_point p_now);    //一步
	special_point create_start_point(special_point p_start);    //生成起始点
	void move();
	void m_down();
	void m_up();
	void m_left();
	void m_right();
};
#endif