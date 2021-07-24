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
string mst[11]={"AK-47","AWP","P90","Desert Eagle","M4A4","AUG","SG-553","内格夫","截短霰弹枪","加利尔AR","宙斯电击枪"};
string skl[11]={"","lbw番茄连招","啸着玩","*打鸣*","跑 打","队友鲨手","甩狙","rushhhhhh","细节扔枪","A1高闪","自 鲨"};
string plc[7]={"","A点通道","中路门","匪家门口","B点拱门","A点平台","中路楼梯"};
string act[21]={"","蹲在中路箱子背后",""};

struct chara
{
	int acc;//精准度 
	int hp;//血量
	int skill;//技能,最多有1个 
	int mas;//专精 
	int pos;//当前所在位置 
	int weapon;//当前武器 
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

void use_skill(chara a,bool team,int count)//count:第几个成员 team:属于哪个队伍 
{
	if(team==1)//B队 
	{
	printf("%s使用",stb[count]);
	setcolor(8);
	printf("%s",skl[a.skill].data());
	setcolor(5);	
	}
	int rdplc=rand()%5+1;
	switch(a.skill)
	{
		case 1:
			printf(",大喊'番茄bs番茄炒B'冲向了%s\n",plc[rdplc].data());
			break;
		case 2:
			printf(",\n",plc[rdplc].data());
			break;
	}	
}

void actt(chara a,bool team,int count,int rdmac)
{
	//
}

void game()
{
	cls();
	setcolor(4);
	printf("游戏开始.\n");
	setcolor(5);
	bool flag=true;
	int count=0;
	while(flag)
	{
		count++;
		int rdmc=rand()%mem+1;
		if(count%2==0)//偶数 team B 
		{
			switch(teamb[count].pos)
			{
				case 1:
					int rdmac=rand()%32+1;
					if(rdmac==31)
					use_skill(teamb[count],1,count);
					else
					actt(teamb[count],1,count,rdmac);
					break;
			}	
		}
	} 
}

int main()
{
	srand(time(NULL));
    strout();
    //debug_1();//输出md5码 
    attribute();
    debug_2();
    game();
    return 0;
}
