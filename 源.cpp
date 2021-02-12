#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<cstring>
#include<stdio.h>
#include <conio.h>
#include"Characters.h"
#include"PK.h"
#include"Skin.cpp"
#include<conio.h>
#include<time.h>
using namespace std;
/*
version2.0 目标更新：
1、新增地图传送点#（3）
2、新增勇者技能--星之力：消耗一颗星星，眩晕年兽1回合
3、游戏介绍可以再加一条 按空格屏息一回合
4、新增隐藏迷宫
5、三超神名字：夕柯，逆渊，末厄  勇者剑：无心
*/
//补充勇者技能介绍


void display();
void Creat_stars();
bool is_legal(COORDINATE& node);
bool get_key();
bool check(int&);
void put(string c);

void pk_play();
void scene();
void skin_play();

struct Send {
	COORDINATE c;
	Send* o;
	Send(int x, int y) :c(x, y),o(NULL){};
	//void SetConnect(Send& a) { o = &a; };
};


Character monster(5, 5);
Voidwalker player(1, 1);

Send one(1, 6),another(6, 6);
int stars_in_map = 0;
int has_stars = 0;
int use_send = 0;
bool notes = false;
extern const int column , row;
int init_map[row][column] = { 
	                     {1,1,1,1,1,1,1},
                         {1,1,1,1,0,1,3},
					     {1,1,0,1,1,1,1},
                         {1,1,0,1,0,1,0},
                         {1,1,1,1,0,1,1},
						 {1,0,1,1,1,1,1},
                         {1,1,1,0,1,0,3} };
int map[row][column];
bool passed = false;

int Creat_random() {
	return rand() % 5+1;
}
/*
0代表墙，
1代表通路,
2代表星星,
3代表传送点，
4代表贝加尔湖畔。
*/

void init(){
	monster.alter_id(COORDINATE(6, 6));
	player.alter_id(COORDINATE(1, 1));
	stars_in_map = 0;
	has_stars = 0;
	use_send = 0;
	for (int i = 0; i < row; ++i)memcpy(map[i], init_map[i], sizeof(int)*column);
	map[5][6] = 2;
	++stars_in_map;
	notes =false;
	passed = false;

	//建立传送点
	one.o = &another;
	another.o = &one;
}
bool is_eq(const COORDINATE& a,const COORDINATE &b)
{
	if (a.x == b.x && a.y == b.y)return true;
	return false;
}

bool elect() {
	cout <<"   在此模式下，你可以选择不同的章节，跳跃性的进入不同的关卡，从而做到在面临选择分支的时候，\n";
	cout << "直接体验不同选择下的结局或者走向，但不建议第一次玩的时候直接选择，这样可能会造成剧情的理解偏差\n";
	cout << "此外,该模式下并不能跳跃到所有的剧情。\n";
	SetConsoleColor(FOREGROUND_BLUE);
	for (int i = 0; i < 25; ++i)cout << "__"; cout << "\n";
	SetConsoleColor(FOREGROUND_RED|FOREGROUND_GREEN | BACKGROUND_BLUE);
	cout << "|神之遗迹探索（1）|世界的真相（2）|你的选择（3）|\n";
	//for (int i = 0; i < 25; ++i)cout << "__"; cout << "\n";
	SetConsoleColor(FOREGROUND_RED);
	cout << "请输入对应的数字进入章节\n";
	L1:switch (_getch()) {
	case '1':
		try {
			skin_play();
		}
		catch (...) {
			skin_play();
		}
		break;
	case '2':
		try {
			pk_play();
		}
		catch (...) {
			put("重新加载中————");
			Sleep(1000);
			system("cls");
			pk_play();
		}
		break;
	case '3':
		return true;//返回true说明要跳到最终选择
	default:
		cout << "输入错误\n";
		goto L1;
	}
	return false;
}
void play();
int main()
{
	srand((int)time(NULL));
	//pk_play();
	cout<<"    \\\\\\|///        年兽\n  ";
	cout<<"\\\\　.-.-　//    大作战\n";
	SetConsoleColor(FOREGROUND_BLUE);
	for (int i = 0; i < 20; ++i)cout << "__"; cout << "\n";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_BLUE);
	cout << "|   从头开始（s）|| 选择关卡进行（k）  |\n";
	//for (int i = 0; i < 20; ++i)cout << "__"; cout << "\n";
	SetConsoleColor(FOREGROUND_RED);

L3:	switch (_getch()) {
	case's':break;
	case'k':
		if (!elect())exit(0);
		else goto L2;
		break;
	default:
		cout << "输入错误\n";
		goto L3;
	}

	put("按k键跳过剧情（skip），空格键继续——\n");
	if (_getch() == 'k')goto L1;
	SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_RED);
	put("天渡港   日间八点一刻\n");
	put("人声嘈杂，呼声高奋。\n");
	put("「背叛天渡者，当斩！」\n");
	put("「这样的人不配成为勇者，不配为我等尊贡！」\n");
	put("初下帆船的剑士，带着满腔的信念前来向憧憬已久的第20任勇者请教，殊不知天渡正在发生着这样的大事。\n");
	put("「兄弟？发生了甚么事情？」\n");
	put("「咳！老哥您是从多远的外疆来的啊？您没见近日星轨变换日益怪离，禾田麦粒每夜都遭不明怪物袭击，勇者守护不力，违背皇天旨意，零时将予执行头斩！」\n");
	put("剑士大惊，迅速赶往都城牢狱，以金令牌进入了牢狱最深处，见到了跪于方窗前的第20任勇者。\n");
	put("剑鞘出剑，他斩断锁链和镣铐，将勇者扶起。\n");
	put("「快走，带上我的金令牌，从这出去一直朝东走，登上朝阳号帆船，给船长看这块令牌，他会带你去到安全的地方，这个世界需要你！」\n");
	put("「我可是，犯下了滔天巨罪之人，为民众带来恐慌之人，你知道你在做什么吗？」\n");
	put("「星轨怪离，年兽出没，本就不是你的错误，万物之巨变，反而需要你再来拯救啊！明日我代你受刑，拜托了，不要放弃这个世界上的人们啊！」\n");
	put("勇者抬头，这位剑士似乎知道鲜有人问津的星变规律和勇者神力。\n");
	put("「年轻人，勇者不仅有守护的职责，还有安定民心的职责。我若不死，则民将以之为触犯了天之大忌，民心若是如此惶恐，暴乱四起，如何拯救？」\n");
	SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_RED|FOREGROUND_INTENSITY);
	put("说罢，勇者爽朗大笑，左手抚膺，随后深呼一起，迅速将左掌击于剑士心脏处。\n");
	put("「这是？勇者神力！」\n");
	SetConsoleColor(FOREGROUND_INTENSITY| FOREGROUND_RED);
	put("「民心，由我来安定；世界，请你来拯救！快去收集满7颗散落人间的星星，召唤神龙！」\n");
	SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_RED);
	put("一阵热流涌荡在剑士的躯体里，第21任勇者，诞生了。\n");
	put("「今晚零时，请你为我行刑吧，新一任的勇者啊！」\n");

	SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_BLUE);
	put("零时  皓月高照\n");
	put("绞刑台下挤满了民众，愤怒，恐慌，紧张。\n");
	put("新勇者强忍着热泪，挥起宝剑，剑锋挥下得那一刻，他看见\n");
	put("老勇者嘴角扬起了微笑，他在说：\n");
	put("「开始你的征程吧，勇者！」\n");

	put("这是一个控制勇者（@），躲避年兽（！），并收集星星（*）的游戏，（#）代表传送法阵，\n");
	put("（$）是传送中有着女神的眼泪之称的贝加尔湖。\n");
	put("操作介绍：\n勇者操作：1、wsad控制上下左右（注意大小写sensitive）2、技能\n");
	put("  虚空行走：当cd为0时可触发，按下j键后按下wasd键可以穿越墙壁（年兽不能穿越墙壁）\n");
	put("  星神之力：依靠勇者神息激发所拥有的星星，按下k键后消耗一颗星星并让年兽停止一回合，你仍能按wsad行走\n");
	put("年兽：据传是星轨混乱孕育出的神兽，具有巨大的力量，在一段时间（cd==0）后能进行冲刺，勇者行进一回合而它能行进两回合\n");

L1:  try 
	{ 
		play();
}
catch (...) {
	put("退出请按q键(quit)，任意键重来\n");
	if (_getch() == 'q')exit(0);
	goto L1;//PLAY AGAGIN
	}

	if (passed)
	{
L2:     put("恭喜你！打败了年兽，请选择吧，是选择忘记一切，还是回到现实？(按下q,选择忘记；按下w，选择回到现实)\n");
		char c = _getch();
		while (c != 'q' && c != 'w')c = _getch();
		if (c == 'q') {
			SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED);
			put("“04.24，和Sakura去东京天空树，世界上最暖和的地方在天空树的顶上。”\n");
			put("“04.25，和Sakura去明治神宫，有人在那里举办婚礼。”\n");
			put("“04.26，和Sakura去迪士尼，鬼屋很可怕，但是有Sakura在，所以不可怕。”\n");
			put("“Sakura最好了。”...\n");
			put("勇者的脑海里，全是年兽出现前和绘梨衣的故事，不，我果然还是放不下，勇者服下了蓝色药丸\n");
			put("天旋地转，落在他手上的泪珠，是他闭上眼睛前最后的光芒\n........\n");
			put("“傻孩子，发什么楞呢，来吃年夜饭啦！！！一个阿姨敲了敲一个年轻男孩的头\n”");
			put("妈——我都多大啦..........\n殊不知，他身后的宝石，正发出诡异的光\n");
			put("游戏结束");
			_getch();
		}
		else {
			SetConsoleColor(FOREGROUND_INTENSITY|FOREGROUND_RED);
			put("我总是忍不住回想起那座城市的夜晚\n");
			put("灯火燃成的篝火\n");
			put("我坐在天台上\n");
			put("时光短促又漫长\n");
			put("风从我的耳边流过带来整个世界的声音\n风中\n");
			put("有人弹唱 有人舞蹈 有人相爱\n");
			put("花的种子在天空中四散，在黑暗中恣意盛开\n");
			put("紫色的太阳般的蒲公英\n");
			put("下坠的青色吊兰\n");
			put("红色和金色交织成的玫瑰\n");
			put("白色的大丽菊……\n");
			put("这个世界灿烂盛大，我想真正守护它\n");
			put("勇者吞下了红色药丸\n");
			put("他看到镜子中的自己，在向自己招手，勇者穿过镜子，他醒了\n");
			system("color F8");
			put("从培养液中爬出，周围是一个又一个的蚕蛹，里面的人儿或苍老，或年幼，或美艳，或苍白\n");
			put("朝着光明，他挪动着，影子融入黑暗\n");
			put("游戏结束");
			_getch();
		}
	}
	return 0;
}

void display()
{
    system("cls");

	cout << "Monster:\n" <<" cd: "<<monster.get_cd() << endl;
	cout << "player:\n" << " cd: " << player.get_cd() << endl;
	cout << "stars you have:\n" <<has_stars<< endl;
	const string orstr = "|";
	const string line = "__";
	const string space = " ";

	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	for (int j = 1; j <column; j++) { cout << space << line; }
	cout << endl;
	
	for (int i = 1; i < row; ++i)
	{
		for (int j = 1; j < column; ++j)
		{

			cout << orstr;
			SetConsoleColor(FOREGROUND_BLUE);
			if (i == 6 && j == 1) {
				cout << "$ ";
			}
			else if (player.is_coordinate(i, j))
			{
				cout << "@ ";
			}
			else if (monster.is_coordinate(i, j))
			{
				cout << "! ";
			}
			else if (map[i][j] == 0)cout << "■";
			else if (map[i][j] == 2)cout << "* ";
			else if (map[i][j] == 3)cout << "# ";
			else cout << "  ";
			SetConsoleColor(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		}
		cout << orstr<<endl;
		for (int j = 1; j < column; j++) { cout << space << "--"; }
		cout << endl;
	}
}

bool is_legal(COORDINATE& node)
{
	if (node.x > column || node.x < 1 || node.y>row || node.y < 1)return false;//超出地图范围
	if (map[node.x][node.y] == 0)return false;//位置在墙上
	return true;
}

void Creat_stars()
{
	int stars_x,stars_y;
	while (true)
	{
		stars_x = Creat_random();stars_y = Creat_random();
		COORDINATE tmp(stars_x, stars_y);
		if (is_legal(tmp))break;
	}
	++stars_in_map;
	map[stars_x][stars_y] = 2;
}


bool get_key()
{
	char c = _getch();
	player.alter_cd(-1);//时间流逝
	if (c == 'j')
	{
		cout << "召唤！虚空行走！！";
		c = _getch();
		if (player.get_cd() != 0)
		{
			//system("color 01");
			put("啊....魔力不足不能施法\n");
			goto L1;//CD不到不能触发技能！
		}
		//system("color 01");
		put("神啊，赐予我力量吧！虚空行走！！！！\n轰！！！\n");
		switch (c)
		{
		case 'w':player.cross_wall(map, -1, 0); break;
		case 's':player.cross_wall(map, 1, 0); break;
		case 'a':player.cross_wall(map, 0, -1); break;
		case 'd':player.cross_wall(map, 0, 1); break;
		}
	}
	else if (c == 'k')
	{
		cout << "星神之力！！！";
		if(player.swimmy(has_stars))//消耗星星
		{
		get_key();
		return false;//发动眩晕技能
		}
	}
	else
	{
	L1:
		switch (c)
		{
		case 'w':player.March(map, -1, 0); break;
		case 's':player.March(map, 1, 0); break;
		case 'a':player.March(map, 0, -1); break;
		case 'd':player.March(map, 0, 1); break;
		}
	}
	return true;//没有发动眩晕技能
}


void play() {
	
	SetConsoleColor(FOREGROUND_RED);
	
	put("操作建议:\n1、控制好和年兽的距离，活用传送门、虚空行走以及地形优势才能躲避年兽,掌握好cd时长。\n2、按下除了wsadjk键以外的键勇者不会走动\n");
	put("开始吧！按下任意键继续.....");
	_getch();
	init();
	display();
	//Creat_stars();
	while (has_stars < 7)
	{
		//cin
		if(get_key())//返回false说明发动技能年兽不动
		//bfs the line
		monster.bfs(map,player.get_coordinate());
		//update the map
		if (!check(has_stars))throw("lose game");
		//进入剧情分支
		if(player.is_coordinate(6,1))
		{
			if (has_stars != 3) 
			{
				put("君不见，\n沙场残阳红似血，\n白骨千里露荒野\n......");
				put("勇者抚摸着刻在贝加尔湖畔的石头上的诗句，叹了口气\n");
				put("唉，宁做太平犬，莫做乱离人！\n星轨颠倒，年兽癫狂，天下大乱。又逢大旱，叛贼以“天国”为号，四处作乱\n");
				put("我还是快些去收集星星罢\n");
			}
		    else
			{
				SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN);
			L2:			put("勇者身上的三颗星星次序飞出，湖面掀起巨大的波浪，一座地下宫殿显现出来\n");
				try {
					skin_play();
				}
				catch (...) {
					cout << "按q键（quit）退出,任意键重来\n";
					if (_getch() == 'q')exit(0);
					else goto L2;
				}

			L1:	try {
				pk_play();
			}
			catch (...) {
				goto L1;
			}
			break;
			}
		}
		//dispaly
		display();
	}
	if (has_stars == 7)
	{
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN);
		put("第七颗星星*正在前方闪闪发光，勇者身上其余六颗星星也随之飞出\n");
		put("   *   \n *   * \n   *   \n *   * \n   *\n");
		system("color 70"); system("cls");
		SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_RED|BACKGROUND_BLUE| BACKGROUND_RED| BACKGROUND_GREEN);
		put("勇者被传送至一个神奇的空间……四周一片纯白\n");
		put("勇者：这是……哪？是……哪，哪（回音）\n");
		put("Hello？……ello……llo……lo……o（鹅鹅鹅……这回音不太合理吧）\n");
		put("我真帅！……你真丑……真丑……丑（这绝对是某个人偷偷自己念的吧喂！）\n");
		put("三超神出现了！ ）|&|（    ）|&|（    ）|&|（ \n");
		put("超神夕柯(^_^)：勇者，你有什么愿望，有什么愿望，什么愿望，愿望，望....\n");
		//put("勇者（心理活动）：这回音特效也太廉价了\n");
		put("勇者：我.......我希望能解除世界的危机，世界的危机，危机，机\n");
		put("……\n");
		put("超神逆渊：世界的危机已经解除，解除，除....\n");
		put("勇者（心理活动）：啊嘞，这么简单就可以解除？！但似乎有什么不对，不过……前辈一定可以瞑目了吧\n");
		put("年兽消失了，但……在短短的三个月后，魔王出现,世界再度陷入危机，勇者又一次踏上了拯救世界的旅途……\n");
		put("游戏结束：达成B结局《拯救世界》\n");
		_getch();
		exit(0);
	}
	passed = true;
}

bool check(int& has_stars){
	COORDINATE tmp = player.get_coordinate();
	if (map[tmp.x][tmp.y] == 2)
	{
		++has_stars;
		map[tmp.x][tmp.y]=1;//delete stars
		--stars_in_map;
	}
	else if (is_eq(tmp, monster.get_coordinate()))
	{
		system("cls");
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		put("桀桀....看着逐渐逼近的年兽，死亡的气息悄然而至，你无力而绝望的闭上了眼睛\n");
		put("果然....我还是什么都做不到.....\n");
		put("前辈...对不起，我辜负了你的期待.....\n");
		put("至此，勇者离开了历史的舞台，世界陷入混乱....");
		return false;
	}
	if (stars_in_map != 1)Creat_stars();
	
	//使用传送门
	if (map[tmp.x][tmp.y] == 3) {
		if (is_eq(tmp,one.c))tmp = (one.o)->c;
		else tmp = (another.o)->c;
		++use_send;
		put("传送阵泛起白光，“咻——咻”，魔力快速聚集于此地\n");
		player.alter_id(tmp);
	}

	if (use_send == 3&&!notes) {
		notes = true;
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		put("在传送的过程中，发现了一本残破的日记\n");
		put("1月19日 新开这本日记，希望能记录下我寻找神之遗迹的历程。\n");
		put("……\n");
		put("2月1日 打牌。\n");
		put("2月2日 打牌。\n");
		put("2月3日 打麻将。今天似乎赢了很多钱。\n");
		put("2月5日 虎石之啊虎石之！你怎么能如此堕落！这样还如何寻找神之遗迹！不能再这样打下去了。\n");
		put("2月6日 打牌。u1s1，打牌真香。\n");
		put("……\n");
		put("5月12日 终于翻译出这段话的意思了“风暴汇聚处，三星集齐时，神之遗迹现。”风暴汇聚处在哪？三星是什么？\n");
		put("5月19日 ‘lacrimae’ 或许风暴汇聚处指的就是有着女神眼泪 之称的贝加尔湖畔！\n");
		put("6月20日 我终于抵达贝加尔湖畔了,怎么总感觉我好像电影里那种插满flag的小角色，为主角找到信息后就会死去?\n");
		put("6月21日 我似乎发现了惊天大秘密，干，感觉活不久了……\n");
		put("后面似乎有几页已经被撕毁\n");
		put("“风暴汇聚处，三星集齐时，神之遗迹现。”\n");
		put("按任意键继续\n");
		_getch();
	}
	return true;
}



void pk_play() {
	//章节选择
	system("cls");
	SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN);
	put("勇者终于走出黑暗的迷宫，来到了尽头\n");
	put("这里似乎有着一个虚拟投影，咻——一个苍老的身影出现了\n");
	put("“能看到这个投影的有缘人，我想来到这你应该已经发现了这个世界的真相”\n");
	put("“没错，自从第三次世界大战以后，地球环境剧变，我们只好转移到地下生活”\n");
	put("“在这个毫无希望的世界，人们创造了“桃园”的虚拟世界”\n");
	put("“这个世界充满光明，甚至比大战前的世界更加美好”\n");
	put("“直到——”老人的目光似乎穿透了时光，又好像在回忆过去的情景\n");
	put("人工智能终端的三大机器人扭曲了最终指令“带来快乐”，大部分人的记忆被删除\n");
	put("少数人组成的人类反抗军在这场与机器人的战斗中落败\n");
	put("如今，既然你见到了我，那这个世界一定是走向了更加灰暗的未来\n");
	put("这里有两颗药丸，红色的可以让你忘记这一切，重新回到你的生活中\n蓝色的则能够让你从机器中苏醒，回到真实世界\n");
	put("旁边的英灵召唤系统，或许可以帮助你战胜困难\n");
	put("勇者正在犹豫之时，轰隆！！！！！异变陡生\n");
	put("你惊吓到了witch！ ps:出自求生之路\n");
	put("呸，年兽竟然找到了这里！\n");
	put("警告，控制中心遭到破坏，警告，控制中心遭到破坏\n");
	put("正在启动英灵召唤系统\n");
	put("就是这个了！！召唤！！出来吧，皮卡丘！ ps:此处应有bgm,可惜我不会,所以使用了阴间配色来代替\n");
	system("color 36");
	put("“你就是我的master吗？我乃法兰西大数学家Cauchy !”\n");
	put("“小弟弟，记住了，我的名字是——Alice !”\n“让我们赞美太阳吧！让我们用歌声带来勇气和力量，带来虔诚和服从！”\n");
	cout << "`\\' `._.' '/'    `-...-'      \\ o o /\n";
	cout << "(·)   (·)\n";
	cout << "    <~~>   \n";
	cout << "   |____|  \n ";
	put("勇者,Alice 和 Cauchy 与身躯庞大的年兽形成鲜明的对比\n");

	Monster* boss = new Monster;
	Hero* hero_Cauchy = new Hero;
	Hero* hero_Alice = new Hero;
	Hero* hero_Trump = new Hero;
	hero_Cauchy->m_Name = "Cauchy"; hero_Cauchy->EquipWeapon(new Knife);
	hero_Alice->m_Name = "Alice"; hero_Alice->EquipWeapon(new MagicStick);
	hero_Trump->m_Name = "勇者"; hero_Trump->EquipWeapon(new GodSword);
	system("color 70");
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	put("接下来就是最终决战！\n按下i、o、p之一，即可选中英灵进行战斗");
	put("以下是各个角色的特点：\n 勇者 圣剑无心：各方面数值较为平衡，可暴击可吸血可眩晕，但触发几率不高\n");
	put("Cauchy 圣剑无名：暴击伤害高，但普攻血量较低，不能吸血\n");
	put("Alice 石中剑无君：普攻伤害高，不能暴击，但容易吸血\n");
	put("一旦勇者的血量为0，游戏结束，而Cauchy和Alice为0仍可继续，需要综合各方优点才能击败年兽，当然还需要一点运气\n");
	put("准备好了吗？按任意键继续\n");
	_getch();

	system("cls");
	cout << "战斗正式开始！\n";
	SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	while (true) {
		system("cls");
		cout << "*****************************************************\n";
		cout << "Monster:\n Hp:" << boss->get_m_Hp() << "  防御（Def）:" << boss->get_m_Def() << "\n";

		if (hero_Trump->m_Hp <= 0) {
			cout << "勇者阵亡，你输了\n";
			cout << "是否重来？\n";
			cout << "重来请输入c\n";
			if (_getch() == 'c') {
				throw("try again");
			}
			else exit(0);
		}
		else hero_Trump->out();

		if (hero_Cauchy->m_Hp <= 0) {
			cout << "Cauchy失去意识\n";
			hero_Cauchy->is_energy = false;
		}
		else hero_Cauchy->out();

		if (hero_Alice->m_Hp <= 0) {
			cout << "Alice失去意识\n";
			hero_Alice->is_energy = false;
		}
		else hero_Alice->out();

		cout << "请选择进攻英雄（i:勇者，o:Cauchy,p:Alice）\n";
		cout << "*****************************************************\n";
		char c = _getch();

		switch (c)
		{
		case 'i':
			if (hero_Trump->is_energy)
			{
				SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
				put("star burst stream! 星爆气流斩！\n");
				scene();
				hero_Trump->Attack(boss);
			}
			break;
		case'o':
			if (hero_Cauchy->is_energy) {
				SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				put("柯西收敛准则!给爷收敛！\n");
				scene();
				hero_Cauchy->Attack(boss);
			}
			break;
		case'p':
			if (hero_Alice->is_energy) {
				SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				put("Excalibur————！！\n");
				scene();
				hero_Alice->Attack(boss);
			}
			break;
		}
		if (boss->get_m_Hp() <= 0) {
			put(boss->get_m_Name()); put("最后一击！神圣的洛必达啊，请赐予我力量！泰勒展开！！！！\n");
			put("轰隆一声巨响，幻兽巨大的身躯坠落下来\n");
			break;
		}
		//找出三者的最大值
		Hero* hero = nullptr;
		hero = (hero_Trump->m_Hp > hero_Cauchy->m_Hp) ? hero_Trump : hero_Cauchy;
		hero = (hero->m_Hp > hero_Alice->m_Hp) ? hero : hero_Alice;

		boss->Attack(hero);
		Sleep(2000);
	}
  
}

void scene() {
	SetConsoleColor(FOREGROUND_RED);
	system("cls");
	cout << "`-...-'                    （·）_（·）";//20个空格
	int cnt = 1;
	string space = " ";
	string skill = ">>";
	while (cnt < 20) {
		system("cls");
		cout << "`-...-'";
		for (int i = 1; i < cnt; ++i) {
			cout << space;
		}
		cout << skill;
		for (int i = 1; i < 20 - cnt; ++i) {
			cout << space;
		}
		cout << "（·）_（·）";
		++cnt;
		Sleep(10);
	}
	system("cls");
	cout << "`-...-'                   （·）_（·）* * *";
	cout << endl;
	SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void skin_play() {
	SkinRoad skinroad;
	int round = 0;
	bool is_win = false;
	char c;
	int location;
	put("琥珀酒、碧玉觞、金足樽、翡翠盘，食如画、酒如泉，古琴涔涔、钟声叮咚。\n");
	put("神殿四周装饰着倒铃般的花朵，花萼洁白，骨瓷样泛出半透明的光泽，花瓣顶端是一圈深浅不一的淡紫色，似染似天成。\n");
	put("“身是心的囚笼，世界是身的囚笼，疯狂被束缚，欲望被压制”\n");
	put("勇者抚摸着神殿柱子上的文字，若有所思\n");
	put("一阵光芒闪过，勇者被传送到一处迷宫\n");
	put("此时此刻，身后的石墙突然开始推进，不好！！快跑！！\n");
	put("............\n");
	put("注意此关有时间限制，“w”“s”控制主人公上下移动，躲避石块■，*是勇者逃跑路上发现的杂物\n");
	put("有助于推进剧情，但不要求每一个*都碰到\n");
	put("注意！！此关有时间限制，一定时间内没有跑出一定距离游戏就会失败\n");
	put("每按一次‘w’'s'主人公会前进一点，加速啊，躲避石块，走着走着就能走出迷宫！\n");
	put("按任意键开始游戏\n");
	double start = (double)clock();
	double last = (double)clock() - start;
	while(!is_win){
		++round;
		if (round % 10 == 2) {
		    last = (double)clock() - start;
			last /= CLOCKS_PER_SEC;
			
			if (last > 36)break;
		}
		if (round%10==1&&Creat_random() % 100 < 10)
			skinroad.add(Creat_random()%5+1, "*");

		if(round%3==1)skinroad.add(Creat_random() % 5 + 1);
		//清空缓冲区
		//cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');
		c = _getch();
		location = skinroad.role();
		if (location < 5 && c == 'w')skinroad.SetLocation(++location);
		else if (location > 1 && c == 's')skinroad.SetLocation(--location);

		system("cls"); skinroad.Draw(last);
		//更新坐标
		if (!skinroad.check())break;
		//检查blocks是否都消耗完
		if (skinroad.Memory==3)is_win = true;
	}
	if (is_win) {
		cout << "轰！！！石门在背后戛然而止\n";
	}
	else {
		cout << "啊啊啊啊啊啊啊啊，跑不动了\n";
		cout << "啪唧，勇者被石墙刺穿后夹成了肉饼\n";
		Sleep(2000);
		throw("you lose");
	};
}