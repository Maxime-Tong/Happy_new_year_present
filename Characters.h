#ifndef _Characters_h
#define _Characters_h
const int column=7, row=7;

struct COORDINATE {
	unsigned int x, y;
	COORDINATE(int _x, int _y) :x(_x), y(_y) {}
	COORDINATE(){};
};

class Character{
private:
	COORDINATE id;
	int cd;

public:
	Character(int _x, int _y);

	bool is_coordinate(int _x, int _y);

	void bfs(int map[row][column],const COORDINATE& target);

	const COORDINATE get_coordinate();

	void March(int map[row][column], int x_offset, int y_offset);

	void alter_id(const COORDINATE& target);

	int const get_cd()const { return cd; }

	void alter_cd(int offset) {
		if(cd>0||offset==5)cd += offset; }//需要给出修改的差值

};

class Voidwalker :public Character
{
	
public:
	
	Voidwalker(int _x, int _y) :Character(_x, _y) {};

	void cross_wall(int map[row][column], int x_offset, int y_offset);

	bool swimmy(int& stars);
};


#endif