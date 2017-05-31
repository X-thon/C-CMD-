#ifndef POINT_H
#define POINT_H
/*
 class_name:                 point
 class_data_member:          sign;     根据judge而产生的该点的图标，断路为 * 号，通路为 空格符 ;
                             judge;    标志该点的通断性，false为断路，true为通路，默认为false ;
 class_function:             change;   产生迷宫时调用，改变该点的通断性 ;
 */
class point{
public:
	char sign;
	bool judge;
	point()
	{
		judge = false;
		sign = '#';
	}
	void change()
	{
		judge = true;
		sign = ' ';
	}
};
#endif