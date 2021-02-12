#ifndef Skin_h
#define Skin_h
#include<string>
#include<list>
#include<iostream>

struct Block{
	int x, y;
	std::string Name;
	Block(int _y,std::string s="■") :x(20), y(_y),Name(s){};
};

BOOL inline SetConsoleColor(WORD wAttributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;

	return SetConsoleTextAttribute(hConsole, wAttributes);
}

void inline put(std::string c)
{
	for (int i = 0; i < c.size(); ++i) {
		std::cout << c[i];
		Sleep(10);
	}
	Sleep(500);
}

class SkinRoad {
private:
	std::list<Block>Blocks;

	int location=3;

public:
	int Memory = 0;

	//sign表示y
	void add(int sign,std::string s="■") {
		Block a(sign,s);
		Blocks.push_back(a);
	}

	void popBlock() {
		if (Blocks.empty())return;
		Blocks.pop_front();
	}

	bool Find(int _x, int _y) {
		for (auto i = Blocks.begin(); i!= Blocks.end(); ++i) {
			if (i->x == _x && i->y == _y)
			{
				std::cout << i->Name;
				return true;
			}
		}
		return false;
	}
	bool check(){
		auto i = Blocks.begin();
		for (;i!=Blocks.end(); ++i)--(i->x);
		i = Blocks.begin();
		if (i->x <= 0) {
			if (i->y == location)
			{
				if(i->Name=="■")
				   return false;
				else if(i->Name=="*")
				{
					++Memory;
					if (Memory == 1) {
						SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						put("这似乎是一本书籍，吹开灰尘，似乎是一本叫《历史的尘埃》的书籍\n");
						put("                      扉页\n");
						put("    先帝创业未半而中道崩殂，今天下疲弊，此诚危急存亡之秋也。\n");
						put("故有夕柯，逆渊，末厄，Robert之首也。是以先帝简拔以遗天下\n........\n");
						put("后面的文字似乎都被黑笔给划掉了\n");
						put("这本书似乎用的是古语，但是为什么三超神的名字会出现在这里？？？\n");
						put("“Robert”似乎是曾经适用范围最广的文字之一，后又在一场浩劫中消失殆尽，是什么意思？\n");
						SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN);
					}
					else if (Memory == 2) {
						SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						put("这似乎是一页残破的日记\n");
						put("    维护“桃园”实在是太累了，话说最近似乎爆出郑爽有瓜\n");
						put("低情商：“你是孤儿”，高情商：“你妈是郑爽”\n");
						put("写岔了，虽说“桃园”设置了最终指令“带来快乐”，但总感觉还是有些不妥啊\n");
						put("算了，这些都留给上面的大人物操心去吧\n");
						put("“身是心的囚笼，世界是身的囚笼”...这比喻还真贴切\n");
						put("world war III啊，他娘的，不然我们需要设置这块虚拟空间吗？\n");
						put("听爷爷说，他们那个时代有一种动物绿色皮肤，呱呱叫，是专门吃害虫的，话说害虫也越来越少见了啊\n");
						//put("还经常听他唱“快乐的一只小青蛙，lululululululu\n”");
						put("还听说大海是蓝色的，天空也是蓝色的，真让人神往啊\n");
						SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN);
					}
					else if (Memory == 3) {
						put("绝密 保密程度：III 签署人：黄霄童 \n");
						put("最近的一系列数据显示，虚拟世界“■■”似乎出现异常，决定采取■■■■措施警戒\n");
						put("三大机器人似乎对指令理解出现偏差，但现有证据不足，仍有待观察\n");
						put("据《有关世界的管理办法》■■条规定，务必找出实验记■消除技术的罪魁祸首■■，以及目的\n");
						put("该实验■■■■■■■■\n");
						put("...........\n");
						put(".....................\n");
						put("聪明的读者，你明白了吗>~<\n按任意键继续\n");
						_getch();
					}
				}
				
			}
			popBlock();
		}

		return true;
	}

	bool is_empty() { return Blocks.empty(); }

	int role() { return location; }

	void Draw(double last){
		auto iter=Blocks.begin();
		std::cout << "_____________________\n";
		std::cout <<"time: "<< last<< "s\n";
		std::cout << "_____________________\n";
		for (int j = 5; j > 0; --j) {
			//画出主人公
			if (j == location)std::cout << "@";
			else std::cout <<" ";

			//画出障碍物
			for (int i = 1; i <= 20; ++i){
				if (!Find(i, j))std::cout << " ";
			}
			std::cout << "\n";
		}
		std::cout << "~~~~~~~~~~~~~~~~~~~~~\n";
	}

	void SetLocation(int _y) {
		location = _y;
	}
};
#endif
