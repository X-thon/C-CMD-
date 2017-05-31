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
	special_point p1;    //��ǰ��
	special_point p2;    //��һ�ڽӵ�
	char ch;
	int p_x;    //����Թ���ĳһ�������
	int p_y;
	int maze_wide;    //����Թ��Ŀ����
	int maze_high;
	point **map;    //����Թ�
	vector<point> v1;
public:
	special_point start;    //�����������ʼ���������
	special_point end;
	special_point player;    //��ʾ��ǰ���λ��
	maze();    //���캯��
	~maze();    //��������
	void search();
	special_point search_path(special_point p_now);    
	special_point select_next_adiacent_points(special_point p_now);    //����ǰ�������괫�룬Ѱ����һ�ڽӵ�
	void show();    //����Թ�
	bool inside_point(special_point p);    //�жϸõ��Ƿ�Ϊ�߽��
	special_point through_path(special_point p_1, special_point p_2);
	bool judge_is_pass_way(int x, int y);    //�жϸõ��Ƿ�Ϊͨ·
	bool judge_no_end_point(int x, int y);    //�ж��Ƿ���·��
	special_point step(special_point p_now);    //һ��
	special_point create_start_point(special_point p_start);    //������ʼ��
	void move();
	void m_down();
	void m_up();
	void m_left();
	void m_right();
};
#endif