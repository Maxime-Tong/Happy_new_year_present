#include "Characters.h"
#include<vector>
#include<queue>
#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

void Put(string c)
{
	for (int i = 0; i < c.size(); ++i) {
		cout << c[i];
		Sleep(10);
	}
	Sleep(500);
}

bool is_legal(int map[row][column],COORDINATE& node)
{
	if (node.x >=column || node.x < 1 || node.y>=row || node.y < 1)return false;//超出地图范围
	if (map[node.x][node.y] == 0)return false;//位置在墙上
	return true;
}

Character::Character(int _x, int _y):id(_x, _y), cd(0){}

bool Character::is_coordinate(int _x, int _y) {
	if (_x == id.x && _y == id.y)return true;
	return false;
}
void Character::bfs(int map[row][column],const COORDINATE& target)
{
	if (target.x == id.x && target.y == id.y)return;
	struct Situation
	{
		vector<COORDINATE>trace;
		Situation() {};
		Situation(vector<COORDINATE> _t) :trace(_t) {};
		void add_Node(COORDINATE n) { trace.push_back(n); }
	};//trace存储bfs出的路线
	Situation road_map[row][column];
	queue<COORDINATE>q;
	bool visited[row][column] = { 0 };
	int direction[4][2] = { {1,0} ,{-1,0},{0,1},{0,-1} };

	Situation start;
	q.push(id);
	visited[id.x][id.y] = true;
	road_map[id.x][id.y] = start;
	//目标点

	while (!q.empty())
	{
		COORDINATE n1 = q.front();

		for (int i = 0; i < 4; ++i)
		{
			COORDINATE new_node;
			new_node.x = n1.x + direction[i][0];
			new_node.y = n1.y + direction[i][1];
			if (!is_legal(map,new_node))continue;//illegal
			Situation _l(road_map[n1.x][n1.y]);
			_l.add_Node(new_node);

			if (!visited[new_node.x][new_node.y])
			{
				road_map[new_node.x][new_node.y] = _l;
				q.push(new_node);
				visited[new_node.x][new_node.y] = true;
			}
			//when  we find a better solution
			else if (road_map[new_node.x][new_node.y].trace.size() > _l.trace.size())
			{
				road_map[new_node.x][new_node.y] = _l;
				q.push(new_node);
			}

		}
		q.pop();
	}

	//monster launched to march !
	Situation solution = road_map[target.x][target.y];
	if (cd == 0 && solution.trace.size() >= 2)
	{
		id = solution.trace[1];//two steps
		//Put("<<<<吼>>>> ……年兽巨大的喘息声从远处传来，这就是.....年兽的力量......（年兽冲刺了）\n");
		cd = 5;
	}
	else
	{
		id = solution.trace[0];//one step
		--cd;
	}
}

const COORDINATE Character::get_coordinate() { return id; }

void Character::March(int map[row][column],int x_offset, int y_offset)
{
	COORDINATE tmp = id;
	tmp.x += x_offset; tmp.y += y_offset;
	if (is_legal(map,tmp))id = tmp;
	else cout << "这是虚空....还是小心为妙\n";
}

void Character::alter_id(const COORDINATE& target) {
	id =target;
}


void Voidwalker::cross_wall(int map[row][column], int x_offset, int y_offset)
{
	alter_cd(5);
	COORDINATE tmp = get_coordinate();
	tmp.x += x_offset; tmp.y += y_offset;
	if (map[tmp.x][tmp.y] == 0)
	{
		tmp.x += x_offset; tmp.y += y_offset;
		if (map[tmp.x][tmp.y] == 0) {
			cout << "这是虚空....还是小心为妙\n";
			return;
		}
		alter_id(tmp);
		return;
	}
	if (is_legal(map, tmp))alter_id(tmp);
	else cout << "这是虚空....还是小心为妙\n";
}

bool Voidwalker::swimmy(int& stars) {
	if (stars == 0)
	{
		Put("啊...没有星星之力了");
		return false;
	}
	--stars;
	return true;
}