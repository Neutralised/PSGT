#include "Md5.hpp"
#include "constool.h"
using namespace std;
typedef long long ll;

unsigned char sta[10][114],stb[10][114];
string dea[10],deb[10];
unsigned char decrypta[10][16],decryptb[10][16];
int choicemem,mem;
int rd[10];
//int tatem,tbtem;
string mst[12]={"AK-47","AWP","P90","Desert Eagle","M4A4","AUG","SG-553","内格夫","截短霰弹枪","加利尔AR","宙斯电击枪","格洛克17"};
int sh[3][13]={{20,90,11,38,15,17,16,6,8,14,300,3},{38,210,30,70,33,31,35,100,110,34,400,18}};
int bjl[13]={3,8,8,3,5,5,4,4,2,6,114,514};
string skl[11]={"","lbw番茄连招","啸着玩","*打鸣*","跑 打","队友鲨手","甩狙","rushhhhhh","细节扔枪","A1高闪","自 鲨"};

struct chara
{
	int acc;//精准度 
	int hp;//血量
	int skill;//技能,最多有1个 
	int mas;//专精 
	int pos;//当前所在位置(空地1,箱子2,楼上3) 
	int weapon=11;//当前武器 
	bool shm;//是否失明 
	int kill;//击杀数 
}teama[10],teamb[10];

void md5ed()
{
	MD5_CTX md5;
    
    for(int i=1;i<=mem;i++) 
    {
	    MD5Init(&md5);
	    MD5Update(&md5, sta[i], (int)strlen((char *)sta[i]));//step of midst
	    MD5Final(&md5, decrypta[i]);	
	}
    for(int i=1;i<=mem;i++)
    {
	    MD5Init(&md5);
	    MD5Update(&md5, stb[i], (int)strlen((char *)stb[i]));//step of midst
	    MD5Final(&md5, decryptb[i]);//32 bits	
	}
}

void file_trans()
{
	int i;
	freopen("temp.txt","w",stdout);
	for(int j=1;j<=mem;j++)
	{
	for (i = 4; i<12; i++)
		{
        	printf("%02x", decrypta[j][i]);
    	}	
    cout<<"\n";	
	}
	for(int j=1;j<=mem;j++)
	{
	for (i = 4; i<12; i++)
		{
        	printf("%02x", decryptb[j][i]);
    	}	
    cout<<"\n";	
	}
	freopen("CON","w",stdout);
	freopen("temp.txt","r",stdin);
	for(int j=1;j<=mem;j++)
	cin>>dea[j];
	for(int j=1;j<=mem;j++)
	cin>>deb[j];
	freopen("CON","r",stdin);
//	cout<<dea[1]<<endl;
//	cout<<deb[1];
}//这个没写锅 

void attribute()
{
	file_trans();
	for(int i=1;i<=mem;i++) 
    {
		//Team A 进行md5分配属性 
		//仅使用8位,每4位一个属性 
		for(int j=1;j<=2;j++)
		{
		rd[i]=(1+rand())%300;
		//cout<<rd[i]<<" ";	
		}
		//cout<<endl;
		teama[i].acc=abs((dea[i][4]-'0'+48)*rd[1]-(dea[i][5]-'0'+48)/2*rd[2])%100;
	//	cout<<teama[i].acc<<endl;
		teama[i].hp=200;
		//cout<<teama[i].hp<<endl;
		teama[i].mas=(rand())%11;
		//cout<<mst[teama[i].mas]<<endl;
//		cout<<tatem<<endl; 
		teama[i].skill=rand()%10+1;
			//cout<<teama[i].skill[j]<<endl;
	}
    for(int i=1;i<=mem;i++)
    {
		//Team B 进行md5分配属性 
		for(int j=1;j<=2;j++)
		{
			rd[i]=(1+rand())%300;
		//	cout<<rd[i]<<" ";
		}
		teamb[i].acc=abs((deb[i][4]-'0'+48)*rd[1]-(deb[i][5]-'0'+48)/2*rd[2])%100;
		//cout<<teamb[i].acc<<endl;
		teamb[i].hp=200;
		//cout<<teamb[i].hp<<endl;
		teamb[i].mas=(rand())%11;
		//cout<<mst[teamb[i].mas]<<endl;
//		cout<<tbtem<<endl; 
		teamb[i].skill=rand()%10+1;
		//cout<<teamb[i].skill[j]<<endl;	
	}
}

void debug_1()
{
	int i;
	cout<<"Team A:\n";
    for(int j=1;j<=mem;j++)
    {
   		printf("第%d个成员:加密前:%s\n加密后16位:",j,sta[j]);
    	for (i = 4; i<12; i++)
		{
        	printf("%02x", decrypta[j][i]);
    	}	
    	cout<<"\n";	
    	printf("加密前:%s\n加密后32位:",sta[j]);
    	for (i = 0; i<16; i++)
		{
        	printf("%02x", decrypta[j][i]);
    	}
		cout<<"\n";	
	}
	cout<<"Team B:\n";
    for(int j=1;j<=mem;j++)
    {
		printf("第%d个成员:加密前:%s\n加密后16位:",j,stb[j]);
    	for (i = 4; i<12; i++)
		{
        	printf("%02x", decryptb[j][i]);
    	}	
    	cout<<"\n";	
		printf("加密前:%s\n加密后32位:",stb[j]);
    	for (i = 0; i<16; i++)
		{
        	printf("%02x", decryptb[j][i]);
    	}
		cout<<"\n";	
	}
}

void debug_2()
{
	setcolor(8);
	cout<<"Team A:\n";
	setcolor(3);
    for(int j=1;j<=mem;j++)
    {
   		printf("-----------------------\n第%d个成员\n名称:%s\n精准:%d\nhp:%d\n专精:%s\n",j,sta[j],teama[j].acc,teama[j].hp,mst[teama[j].mas].data());
   		printf("技能:");
   		printf("%s ",skl[teama[j].skill].data());
   		printf("\n-----------------------\n");
	}
	setcolor(8);
	cout<<"Team B:\n";
	setcolor(3);
    for(int j=1;j<=mem;j++)
    {
   		printf("-----------------------\n第%d个成员\n名称:%s\n精准:%d\nhp:%d\n专精:%s\n",j,stb[j],teamb[j].acc,teama[j].hp,mst[teamb[j].mas].data());
   		printf("技能:");
   		printf("%s ",skl[teamb[j].skill].data());
   		printf("\n-----------------------\n");
	}
	setcolor(5);
}

void strout()
{
	setcolor(8);
	cout<<"Welcome To <Pigeon Strike:Global Tardinness>.\n";
	setcolor(5);
	cout<<"请输入游戏模式:\n";
	setcolor(4);
	cout<<"1:1v1 中门对狙场\n2:3v3 快速对战场\n3:5v5 标准场\n";
	setcolor(5);
	cin>>choicemem;
	mem=choicemem*2-1;
	cout<<"请输入A队名称(用空格或换行隔开):\n";
	for(int i=1;i<=mem;i++)
	cin>>sta[i];
	cout<<"请输入B队名称(用空格或换行隔开):\n";
	for(int i=1;i<=mem;i++)
	cin>>stb[i];
	const int NUM=mem*2;//任务完成总量 然而我显示加载条之前就弄完了((( 
	md5ed();
	for (int i=0;i<=NUM;i++)
	{
		if(i*100.0/NUM<=50)
		setcolor(3);
		else
		setcolor(7);
		printf("正在转换为MD5:%.2lf%%\r",i*100.0/NUM);
		Sleep(150);
	}
	printf("\nTransformation Completed.\n");
	setcolor(5);
	printf("Game starting...\n");
}

//void use_skill(chara a,bool team,int count)//count:第几个成员 team:属于哪个队伍 
//{
//	if(team==1)//B队 
//	{
//	printf("%s使用",stb[count]);
//	setcolor(8);
//	printf("%s",skl[a.skill].data());
//	setcolor(5);	
//	}
//	int rdplc=rand()%5+1;
//	//夏凌汐负责处 
//}
//明天再做 今晚直接普通行动 

void actt(chara &a,bool team,int count,int rdmac)
{
	if(a.shm==1)
	{
		a.shm=0;
		int rdmlkq=rand()%20+1; 
		if(rdmlkq!=20)
		{
		printf("-------------------------\n%s因为正在失明,所以跳过了此回合\n",team?stb[count]:sta[count]);
		return;	
		}
		else
		printf("-------------------------\n%s虽然刚才被闪了,但是用他老狗的意识继续操作!\n",team?stb[count]:sta[count]);
	}
	rdmac%=5;
	rdmac+=1;
	int rdmst=rand()%mem+1;
	if(team)
	{
		while(teama[rdmst].hp==0)
		rdmst=rand()%mem+1;	
	}
	else
	{
		while(teamb[rdmst].hp==0)
		rdmst=rand()%mem+1;	
	}
	int rdmsh=rand()%sh[1][a.weapon]+sh[0][a.weapon];
	if(rdmsh%bjl[a.weapon]==0||(a.pos==3&&a.acc%bjl[a.weapon]==0))//2楼射击可加大爆的几率 
		rdmsh*=2;
	if(a.weapon==a.mas)
	    rdmsh=rdmsh*2;
	if(rdmac==3||rdmac==4||(rdmac==2&&a.pos==3))
	{
		if(team)
		{
			teama[rdmst].hp-=rdmsh;
			if(teama[rdmst].hp<=0)
			teama[rdmst].hp=0;
		}
		else
		{
			teamb[rdmst].hp-=rdmsh;
			if(teamb[rdmst].hp<=0)
			teamb[rdmst].hp=0;
		}	
	}
	chara target=team?teama[rdmst]:teamb[rdmst];
	int tempw=a.weapon;
	switch(rdmac)
	{
		case 1:
			printf("-------------------------\n%s扔了个闪,%s被闪瞎了\n",team?stb[count]:sta[count],team?sta[rdmst]:stb[rdmst]);
			if(team) teama[rdmst].shm=1;
			else
			teamb[rdmst].shm=1;
			break;
		case 2:
			if(a.pos==3)
			{
				setcolor(3);
				printf("-------------------------\n%s使用%s射击了%s,造成%d点伤害,%s当前血量%d\n",team?stb[count]:sta[count],mst[a.weapon].data(),team?sta[rdmst]:stb[rdmst],rdmsh,team?sta[rdmst]:stb[rdmst],target.hp);
				setcolor(5);
			}
			else
			{
				a.pos=3;
				setcolor(3);
				printf("-------------------------\n%s骗过上帝,溜到了2楼\n",team?stb[count]:sta[count]);
				setcolor(5);	
			}
			break;
		case 3:
			setcolor(1);
			printf("-------------------------\n%s屏息凝神,瞄准了%s\n",team?stb[count]:sta[count],team?sta[rdmst]:stb[rdmst]);
			printf("%s使用%s精准射击了%s,造成%d点伤害,%s当前血量%d\n",team?stb[count]:sta[count],mst[a.weapon].data(),team?sta[rdmst]:stb[rdmst],rdmsh,team?sta[rdmst]:stb[rdmst],target.hp);
			setcolor(5);
			break;
		case 4:
			setcolor(3);
			printf("-------------------------\n%s使用%s射击了%s,造成%d点伤害,%s当前血量%d\n",team?stb[count]:sta[count],mst[a.weapon].data(),team?sta[rdmst]:stb[rdmst],rdmsh,team?sta[rdmst]:stb[rdmst],target.hp);
			setcolor(5);
			break;
		case 5:
			while(tempw==a.weapon)
			a.weapon=rand()%12;
			setcolor(4);
			printf("-------------------------\n%s起了把%s,扔掉了手中的%s\n",team?stb[count]:sta[count],mst[a.weapon].data(),mst[tempw].data());
			setcolor(5);
			break;
		default :
			printf("-------------------------\n%s发了一回合呆,因为他在思考为什么程序会随机到不该随机的数字%d\n",team?stb[count]:sta[count],rdmac);
			break;
	} 
	if(team)
	{
	if(teama[rdmst].hp==0)
	{
		a.kill++;
		setcolor(4);
		printf("-------------------------\n%s被%s使用%s杀死了.\n",team?sta[rdmst]:stb[rdmst],team?stb[count]:sta[count],mst[a.weapon].data());
		setcolor(5);
	}	
	}
	else
	{
	if(teamb[rdmst].hp==0)
	{
		a.kill++;
		setcolor(4);
		printf("-------------------------\n%s被%s使用%s杀死了.\n",team?sta[rdmst]:stb[rdmst],team?stb[count]:sta[count],mst[a.weapon].data());
		setcolor(5);
	}	
	}
}

bool winner;

void print_data()
{
	setcolor(1);
	printf("----------\nTeam A战绩:\n----------\n");
	setcolor(5);
	for(register int i=1;i<=mem;i++)
	printf("%s killed:%d\n",sta[i],teama[i].kill);
	setcolor(2);
	printf("----------\nTeam B战绩:\n----------\n");
	setcolor(5);
	for(register int i=1;i<=mem;i++)
	printf("%s killed:%d\n",stb[i],teamb[i].kill);
}

void game()
{
	cls();
	setcolor(4);
	printf("游戏开始\n");
	setcolor(5);
	bool flag1=false;//胜利条件:有一方全挂了 
	bool flag[10]={1,1,1,1,1,1,1,1,1,1};
	int count=0;
	int round=2;
	while(!flag1)
	{
		round++;
		int count=rand()%mem+1;
		if(round%2==0)//偶数 team B 
		{
			if(teamb[count].hp==0)
			continue;
			setcolor(8);
			printf("轮到Team B行动:\n");
			setcolor(5);
			printf("==============\n");
			Sleep(1000);
			int rdmac=rand()%31+1;
//			if(rdmac==31)
//			use_skill(teamb[count],1,count);
//			else
			actt(teamb[count],1,count,rdmac);	
		}
		else
		{
			if(teama[count].hp==0)
			continue;
			setcolor(8);
			printf("轮到Team A行动:\n");
			setcolor(5);
			printf("==============\n");
			Sleep(1000);
			int rdmac=rand()%31+1;
//			if(rdmac==31)
//			use_skill(teama[count],0,count);
//			else
			actt(teama[count],0,count,rdmac);	
		}
		for(register int i=1;i<=mem;i++)
		flag[i]=(teama[i].hp)?1:0;
		flag1=true;
		for(register int i=1;i<=mem;i++)
			if(flag[i]) flag1=false;
		if(flag1)
		{
			winner=1;
			printf("\nTeam B Wins!\n");
			Sleep(3000);
			print_data();
			Sleep(3000);
			system("pause");
			return;
		}//Team B Wins
		else
		{
			for(register int i=1;i<=mem;i++)
			flag[i]=(teamb[i].hp)?1:0;
			flag1=true;
			for(register int i=1;i<=mem;i++)
			if(flag[i]) flag1=false;
			if(flag1)
			{
				winner=1;
				printf("\nTeam A Wins!\n");
				Sleep(3000);
				print_data();
				Sleep(3000);
				system("pause");
				return;
			}
		}//Team A wins
		Sleep(1500);
	} 
}

int main()
{
	srand(time(NULL));
    strout();
    //debug_1();//输出md5码 
    attribute();
    debug_2();
    printf("(请检阅您的部队,完毕后输入yes.)\n");
    string fuck="";
    cin>>fuck;
    game();
    return 0;
}
