#ifndef POINT_H
#define POINT_H
/*
 class_name:                 point
 class_data_member:          sign;     ����judge�������ĸõ��ͼ�꣬��·Ϊ * �ţ�ͨ·Ϊ �ո�� ;
                             judge;    ��־�õ��ͨ���ԣ�falseΪ��·��trueΪͨ·��Ĭ��Ϊfalse ;
 class_function:             change;   �����Թ�ʱ���ã��ı�õ��ͨ���� ;
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