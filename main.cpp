#include"Maze.h"
#include<Windows.h>
int main()
{
	maze m;
	//m.search();
	
	while (m.player.x != m.end.x || m.player.y != m.end.y)
	{
		m.show();
		cout << m.player.x << " " << m.player.y << endl;
		m.move();
		system("cls");
	}
	cout << "Beat the game!" << endl;
	system("pause");
	return 0;
}