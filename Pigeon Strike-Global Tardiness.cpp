#include "Md5.hpp"
#include "constool.h"
using namespace std;
typedef long long ll;

unsigned char sta[15][114],stb[15][114];
string dea[15],deb[15];
string naa[15],nab[15];
int lena[15],lenb[15];
unsigned char decrypta[15][16],decryptb[15][16];
int choicemem,mem;
int rd[15];
int gamod;
int roundcntr;
int maxlen;
int maxkill;
string maxkill_weapon;
//int tatem,tbtem;
string mst[12]={"AK-47","AWP","P90","Desert Eagle","M4A4","AUG","SG-553","内格夫","截短霰弹枪","加利尔AR","宙斯电击枪","格洛克17"};
int sh[3][13]={{20,90,11,38,15,17,16,6,8,14,300,5},{38,210,30,70,33,31,35,100,110,34,400,18}};
int bjl[13]={3,8,8,3,5,5,4,4,2,6,114,514};
string skl[11]={"","lbw番茄连招","啸着玩","*打鸣*","跑 打","队友鲨手","甩狙","rushhhhhh","细节扔枪","A1高闪","自 鲨"};
map<string,int> ranklst;//用来存储一个人在每轮游戏结束后总共鲨掉的人数 
map<string,int> deadlst;//用来存储在每轮游戏结束后死亡次数 
map<string,int> killlst;//用来存储每轮结束后每种武器鲨掉的个数 

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
	int extra;//额外伤害
	string rank;//结算时显示的称号 
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

void file_trans_for_md5()
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

void file_trans_for_name()
{
	freopen("temp2.txt","w",stdout);
	for(int j=1;j<=mem;j++)
	printf("%s\n",sta[j]);
	for(int j=1;j<=mem;j++)
	printf("%s\n",stb[j]);
	freopen("CON","w",stdout);
	freopen("temp2.txt","r",stdin);
	for(int j=1;j<=mem;j++)
	{
		cin>>naa[j];
		lena[j]=naa[j].length();
		if(lena[j]>maxlen)
		maxlen=lena[j];	
	}
	for(int j=1;j<=mem;j++)
	{
		cin>>nab[j];	
		lenb[j]=nab[j].length();
		if(lenb[j]>maxlen)
		maxlen=lenb[j];	
	}
	freopen("CON","r",stdin);
//	cout<<naa[1]<<endl;
//	cout<<nab[1]<<endl;
}

void attribute()
{
	file_trans_for_md5();
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
	setcolor(2);
    for(int j=1;j<=mem;j++)
    {
   		printf("-----------------------\n第%d个成员\n名称:%s\n精准:%d\nhp:%d\n专精:%s\n",j,sta[j],teama[j].acc,teama[j].hp,mst[teama[j].mas].data());
   		printf("技能:");
   		printf("%s ",skl[teama[j].skill].data());
   		printf("\n-----------------------\n");
	}
	setcolor(8);
	cout<<"Team B:\n";
	setcolor(2);
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
	file_trans_for_name();
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

void deadout(chara a,int count,bool team)
{
	switch(a.kill)
	{
		case 2:
			setcolor(2);
			printf("%s已经带走了2人!\n",team?stb[count]:sta[count]);
			setcolor(5);
			break;
		case 3:
			setcolor(1);
			printf("%s鲨疯了!淦翻了3个人!\n",team?stb[count]:sta[count]);
			setcolor(5);
			break;
		case 4:
			setcolor(4);
			printf("%s如同天上降魔猪,真是人间野猪神!4个人已经倒在他脚下!\n",team?stb[count]:sta[count]);
			setcolor(5);
			break;
		case 5:
			setcolor(6);
			printf("王牌!%s鲨掉了5人!\n",team?stb[count]:sta[count]);
			setcolor(5);
			break;
		case 6:
			setcolor(6);
			printf("%s还在鲨戮!6人已死!\n",team?stb[count]:sta[count]);
			setcolor(5);
			break;
		case 7:
			setcolor(6);
			printf("这不可能...%s是吃了炫迈吗根本停不下来...\n7个人头入账!",team?stb[count]:sta[count]);
			setcolor(5);
			break;
		case 8:
			setcolor(6);
			printf("第8个......怎么还是%s?!这b开挂了吧......\n",team?stb[count]:sta[count]);
			setcolor(5);
			break;
		case 9:
			setcolor(1);
			printf("%s消灭了整支敌方队伍......\n",team?stb[count]:sta[count]);
			setcolor(5);
			break;
		}
}

void use_skill(chara &a,bool team,int count)//count:第几个成员 team:属于哪个队伍 
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
	if(team==1)//B队 
		printf("%s使用技能",stb[count]);
	else
		printf("%s使用技能",sta[count]);	
	setcolor(8);
	printf("%s",skl[a.skill].data());
	setcolor(5);
	printf(",");
	int rdmst=rand()%mem+1;
	if(team)
	{
		if(a.skill==5)
		{
			while(teamb[rdmst].hp==0)
			rdmst=rand()%mem+1;	
		}
		else
		{
			while(teama[rdmst].hp==0)
			rdmst=rand()%mem+1;	
		}	
	}
	else
	{
		if(a.skill==5)
		{
			while(teama[rdmst].hp==0)
			rdmst=rand()%mem+1;
		}
		else
		{
			while(teamb[rdmst].hp==0)
			rdmst=rand()%mem+1;		
		}
	}
	int rdmsh=rand()%sh[1][a.weapon]+sh[0][a.weapon];
	if(rdmsh%bjl[a.weapon]==0||(a.pos==3&&a.acc%bjl[a.weapon]==0))//2楼射击可加大爆的几率 
		rdmsh*=2;
	if(a.weapon==a.mas)
	    rdmsh=rdmsh*2;
	if(a.skill==4)
		rdmsh/=3;
	if(a.skill==6)
		rdmsh*=2;
	if(a.skill==2||a.skill==4||a.skill==5||a.skill==6||a.skill==7)
	{
		rdmsh+=a.extra;
		a.extra=0;
		if(team)
		{
			if(a.skill==5)
			{
				teamb[rdmst].hp-=rdmsh;
				if(teamb[rdmst].hp<=0)
				teamb[rdmst].hp=0;
			}
			else
			{
				teama[rdmst].hp-=rdmsh;
				if(teama[rdmst].hp<=0)
				teama[rdmst].hp=0;	
			}
		}
		else
		{
			if(a.skill==5)
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
	}
	chara target;
	if(a.skill!=5)
	target=team?teama[rdmst]:teamb[rdmst];
	else
	target=team?teamb[rdmst]:teama[rdmst];
//	int tempw=a.weapon;
	switch(a.skill)
	{
		case 1:
			rdmsh*=2;
			setcolor(1); 
			printf("大喊一声'番茄鼻s番茄炒b',下回合伤害+%d!\n",rdmsh);
			setcolor(5);
			a.extra=rdmsh;
			break;
		case 2:
			setcolor(2);
			printf("一边嚎叫一边用%s淦飞了%s,造成了%d点伤害,%s当前血量%d\n",mst[a.weapon].data(),team?sta[rdmst]:stb[rdmst],rdmsh,team?sta[rdmst]:stb[rdmst],target.hp);
			setcolor(5);
			break;
		case 3:
			printf("旁若无人地打起了鸣,诉说着被刀的血的教训......所以跳过本回合\n");
			break;
		case 4:
			printf("学习CF玩家好榜样,用%s边跑边射%s,只打中了1/3的子弹,造成了%d点伤害,%s当前血量%d\n",mst[a.weapon].data(),team?sta[rdmst]:stb[rdmst],rdmsh,team?sta[rdmst]:stb[rdmst],target.hp);
			break;
		case 5:
			printf("瞎稽疤乱射,手中的%s不受控制地射向了队友%s,造成了%d点伤害,%s当前血量%d\n",mst[a.weapon].data(),team?stb[rdmst]:sta[rdmst],rdmsh,team?stb[rdmst]:sta[rdmst],target.hp);
			break;
		case 6:
			printf("抬起手中的%s信手一枪,甩到了%s脸上,让对方血条掉落%d,%s仅剩%d血量!\n",mst[a.weapon].data(),team?sta[rdmst]:stb[rdmst],rdmsh,team?sta[rdmst]:stb[rdmst],target.hp);
			break;
		case 7:
			printf("仰天长啸'勇敢牛牛,不怕困难',rush了%s,对方血量减少%d,%s血量还剩%d\n",team?sta[rdmst]:stb[rdmst],rdmsh,team?sta[rdmst]:stb[rdmst],target.hp);
			break;
		case 8:
			a.weapon=11;
			printf("扔下了手中的%s,武器变回格洛克17,并双手过头行法国军礼\n",mst[a.weapon].data());
			break;
		case 9:
			if(team)
				for(register int i=1;i<=mem;i++)
				teama[i].shm=1;
			else
				for(register int i=1;i<=mem;i++)
				teamb[i].shm=1;
			printf("甩出一枚睾级Flash Bomb,闪瞎了对面所有人!\n");
			break;
		case 10:
			printf("以迅雷不及掩耳盗铃儿响叮当仁不让世界充满爱在西元前仆后继无人间失格物致知之为知之不知为不知是智障也的势头掏出一把小刀割开了自己的喉咙!\n");
			setcolor(1);
			printf("%s杀死了自己!\n",team?stb[count]:sta[count]);
			setcolor(5);
			a.hp=0; 
			a.kill--;
			break;
	}
	if(a.skill!=10)
	{
		if(team)
		{
			if(a.skill!=5)
			{
				if(teama[rdmst].hp==0)
				{
					killlst[mst[a.weapon]]++;
					a.kill++;
					setcolor(4);
					printf("-------------------------\n%s被%s使用%s杀死了.\n",team?sta[rdmst]:stb[rdmst],team?stb[count]:sta[count],mst[a.weapon].data());
					setcolor(5);
					deadout(a,count,team);
				}	
			}
			else
			{
				if(teamb[rdmst].hp==0)
				{
					killlst[mst[a.weapon]]++;
					a.kill++;
					setcolor(4);
					printf("-------------------------\n%s被%s使用%s杀死了.\n",team?stb[rdmst]:sta[rdmst],team?stb[count]:sta[count],mst[a.weapon].data());
					setcolor(5);
					deadout(a,count,team);
				}	
			}	
		}
		else
		{
			if(a.skill!=5)
			{
				if(teamb[rdmst].hp==0)
				{
					killlst[mst[a.weapon]]++;
					a.kill++;
					setcolor(4);
					printf("-------------------------\n%s被%s使用%s杀死了.\n",team?sta[rdmst]:stb[rdmst],team?stb[count]:sta[count],mst[a.weapon].data());
					setcolor(5);
					deadout(a,count,team);
				}	
			}
			else
			{
				if(teama[rdmst].hp==0)
				{
					killlst[mst[a.weapon]]++;
					a.kill++;
					setcolor(4);
					printf("-------------------------\n%s被%s使用%s杀死了.\n",team?stb[rdmst]:sta[rdmst],team?stb[count]:sta[count],mst[a.weapon].data());
					setcolor(5);
					deadout(a,count,team);
				}	
			}	
		}	
	}
}
//肝! 
//string skl[11]={"","lbw番茄连招","啸着玩","*打鸣*","跑 打","队友鲨手","甩狙","rushhhhhh","细节扔枪","A1高闪","自 鲨"};
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
		rdmsh+=a.extra;
		a.extra=0;
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
			a.weapon=rand()%11;
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
			killlst[mst[a.weapon]]++;
			a.kill++;
			setcolor(4);
			printf("-------------------------\n%s被%s使用%s杀死了.\n",team?sta[rdmst]:stb[rdmst],team?stb[count]:sta[count],mst[a.weapon].data());
			setcolor(5);
		}
		deadout(a,count,team);
	}
	else
	{
		if(teamb[rdmst].hp==0)
		{
			killlst[mst[a.weapon]]++;
			a.kill++;
			setcolor(4);
			printf("-------------------------\n%s被%s使用%s杀死了.\n",team?sta[rdmst]:stb[rdmst],team?stb[count]:sta[count],mst[a.weapon].data());
			setcolor(5);
			deadout(a,count,team);
		}	
	}
}

bool winner;

//void mapinit()
//{
//	freopen("mapdata.txt","r",stdin);
//	string nameee;
//	int killl;
//	while(scanf("%s%d",&nameee,&killl)!=EOF)
//		ranklst[nameee]=killl;
//	freopen("CON","r",stdin);
//	printf("%s %d\n",nameee.data(),ranklst[nameee]);
//}

//void mapsave()
//{
//	freopen("mapdata.txt","w",stdout);
//	for(register int i=1;i<=mem;i++)
//	cout<<sta[i]<<" "<<ranklst[naa[i]]<<endl;
//	for(register int i=1;i<=mem;i++)
//	cout<<stb[i]<<" "<<ranklst[nab[i]]<<endl;
//	freopen("CON","w",stdout);
//}

//写锅了 别问 问就是我太拉了 

void weaponkill()
{
	for(register int i=1;i<=11;i++)
	{
		if(killlst[mst[i]]>maxkill)
		{
			maxkill=killlst[mst[i]];
			maxkill_weapon=mst[i];
		}	
	}
}

void print_data()
{
	double kd;
	setcolor(1);
	printf("----------\nTeam A战绩:\n----------\n");
	setcolor(7);
	printf("After %d rounds.\n",roundcntr);
	setcolor(5);
	for(register int i=1;i<=mem;i++)
	{
		if(teama[i].hp==0)
		deadlst[naa[i]]++;
		ranklst[naa[i]]+=teama[i].kill;
		kd=(double)(ranklst[naa[i]]-deadlst[naa[i]])/roundcntr;
		teama[i].rank="重在参与";
		if(kd>=1.5)
		teama[i].rank="K/D 爆表"; 
		if(ranklst[naa[i]]>=15||teama[i].kill>=4)
		teama[i].rank="鲨人狂魔"; 
		if(teama[i].kill==0)
		teama[i].rank="摸鱼带师";
		if(deadlst[naa[i]]>=10)
		teama[i].rank="提 款 姬";
		if(deadlst[naa[i]]>=20)
		teama[i].rank="敌方卧底";
		if(teama[i].kill==mem)
		teama[i].rank="灭队大佬";
		if(teama[i].rank=="灭队大佬"||teama[i].rank=="K/D 爆表"||teama[i].rank=="鲨人狂魔")
		setcolor(6);
		else if(teama[i].rank=="提 款 姬"||teama[i].rank=="敌方卧底") 
		setcolor(7);
		else if(teama[i].rank=="摸鱼带师")
		setcolor(2);
		printf("%s",teama[i].rank.data());
		setcolor(4);
		printf("  ");
		int nope=(maxlen-lena[i])/2;
		for(register int j=1;j<=nope;j++)
		printf(" ");
		printf("%s",sta[i]);
		for(register int j=1;j<=(maxlen-lena[i]-nope);j++)
		printf(" ");
		setcolor(5);
		printf(" [k]:%d,[Tk]: %d ,[Td]: %d ,[Ave(K/D)]: %.02lf\n",teama[i].kill,ranklst[naa[i]],deadlst[naa[i]],kd);	
	}
	setcolor(2);
	printf("----------\nTeam B战绩:\n----------\n");
	setcolor(7);
	printf("After %d rounds.\n",roundcntr);
	setcolor(5);
	for(register int i=1;i<=mem;i++)
	{
		if(teamb[i].hp==0)
		deadlst[nab[i]]++;
		ranklst[nab[i]]+=teamb[i].kill;
		kd=(double)(ranklst[nab[i]]-deadlst[nab[i]])/roundcntr;
		teamb[i].rank="重在参与";
		if(kd>=1.5)
		teamb[i].rank="K/D 爆表";
		if(ranklst[nab[i]]>=15||teamb[i].kill>=4)
		teamb[i].rank="鲨人狂魔"; 
		if(teamb[i].kill==0)
		teamb[i].rank="摸鱼带师";
		if(deadlst[nab[i]]>=10)
		teamb[i].rank="提 款 姬";
		if(deadlst[nab[i]]>=20)
		teamb[i].rank="敌方卧底";
		if(teamb[i].kill==mem)
		teamb[i].rank="灭队大佬";
		if(teamb[i].rank=="灭队大佬"||teamb[i].rank=="K/D 爆表"||teamb[i].rank=="鲨人狂魔")
		setcolor(8);
		else if(teamb[i].rank=="提 款 姬"||teamb[i].rank=="敌方卧底") 
		setcolor(7);
		else if(teamb[i].rank=="摸鱼带师")
		setcolor(2);
		printf("%s",teamb[i].rank.data());
		setcolor(4);
		printf("  ");
		int nope=(maxlen-lenb[i])/2;
		for(register int j=1;j<=nope;j++)
		printf(" ");
		printf("%s",stb[i]);
		for(register int j=1;j<=(maxlen-lenb[i]-nope);j++)
		printf(" ");
		setcolor(5);
		printf(" [k]:%d,[Tk]: %d ,[Td]: %d ,[Ave(K/D)]: %.02lf\n",teamb[i].kill,ranklst[nab[i]],deadlst[nab[i]],kd);
	}
	weaponkill();
	setcolor(4);
	printf("目前击杀数最多武器:%s,击杀个数:%d\n",maxkill_weapon.data(),maxkill);
	setcolor(5);
}

void slinit()
{
	for(register int i=1;i<=mem;i++)
	{
		teamb[i].hp=teama[i].hp=200;
		teama[i].kill=teamb[i].kill=0;
		teama[i].weapon=teamb[i].weapon=11;	
		teama[i].shm=teamb[i].shm=0;
	}
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
			while(teamb[count].hp==0)
			{
				count++;	
				if(count>mem)
				count=1;
			}
			setcolor(8);
			printf("轮到Team B行动:\n");
			setcolor(5);
			printf("==============\n");
			if(!gamod)
			Sleep(1000);
			int rdmac=rand()%31+1;
			if(rdmac==31||rdmac==30||rdmac==29)
			use_skill(teamb[count],1,count);
			else
			actt(teamb[count],1,count,rdmac);	
		}
		else
		{
			while(teama[count].hp==0)
			{
				count++;	
				if(count>mem)
				count=1;
			}
			setcolor(8);
			printf("轮到Team A行动:\n");
			setcolor(5);
			printf("==============\n");
			if(!gamod)
			Sleep(1000);
			int rdmac=rand()%31+1;
			if(rdmac==31||rdmac==30||rdmac==29)
			use_skill(teama[count],0,count);
			else
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
			Sleep(1000);
			print_data();
			Sleep(1000);
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
				Sleep(1000);
				print_data();
				Sleep(1000);
				return;
			}
		}//Team A wins
		if(!gamod)
		Sleep(1500);
	} 
}

int main()
{
	srand(time(NULL));
    strout();
    //debug_1();//输出md5码 
    attribute();
    setcolor(4);
    printf("\n您是否想要检阅部队?(Y/N)\n");
    setcolor(5);
    string chooo;
    cin>>chooo;
    if(chooo=="y"||chooo=="Y"||chooo=="fuck")
    {
	    debug_2();
	    printf("(请检阅您的部队,完毕后输入yes.)\n");
	    string fuck="";
	    cin>>fuck;	
	}
    setcolor(4);
    printf("您是否想打开快速战斗模式?(Y/N)\n");
    setcolor(5);
    string cccc;
    cin>>cccc;
    if(cccc=="Y"||cccc=="y"||cccc=="fuck")
    gamod=1;
    else
    gamod=0;
    cccc="Y";
    while(cccc=="Y"||cccc=="y"||cccc=="fuck")
    {
    	roundcntr++;
    	slinit();
    	//mapinit();
	    game();
	    //mapsave();
	    printf("\n是否再来一局?(Y/N) \n");
	    cin>>cccc;	
	    if(cccc!="Y"&&cccc!="y"&&cccc!="fuck")
	    break;
	    setcolor(4);
	    printf("您是否想打开快速战斗模式?(Y/N)\n");
	    setcolor(5);
	    string fuccccc;
	    cin>>fuccccc;
	    if(fuccccc=="Y"||fuccccc=="y"||fuccccc=="fuck")
	    gamod=1;
	    else
	    gamod=0;
	}
    return 0;
}
