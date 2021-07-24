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
string mst[12]={"AK-47","AWP","P90","Desert Eagle","M4A4","AUG","SG-553","�ڸ��","�ض�����ǹ","������AR","��˹���ǹ","�����17"};
int sh[3][13]={{20,90,11,38,15,17,16,6,8,14,300,3},{38,210,30,70,33,31,35,100,110,34,400,18}};
int bjl[13]={3,8,8,3,5,5,4,4,2,6,114,514};
string skl[11]={"","lbw��������","Х����","*����*","�� ��","��������","˦��","rushhhhhh","ϸ����ǹ","A1����","�� ��"};
//string plc[7]={"","A��ͨ��","��·��","�˼��ſ�","B�㹰��","A��ƽ̨","��·¥��"};
//string act[21]={"","�ܵ������Ӻ���","͵͵����¥","��Ϣ����,��׼��",};

struct chara
{
	int acc;//��׼�� 
	int hp;//Ѫ��
	int skill;//����,�����1�� 
	int mas;//ר�� 
	int pos;//��ǰ����λ��(�յ�1,����2,¥��3) 
	int weapon=11;//��ǰ���� 
	bool shm;//�Ƿ�ʧ�� 
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
}//���ûд�� 

void attribute()
{
	file_trans();
	for(int i=1;i<=mem;i++) 
    {
		//Team A ����md5�������� 
		//��ʹ��8λ,ÿ4λһ������ 
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
		//Team B ����md5�������� 
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
   		printf("��%d����Ա:����ǰ:%s\n���ܺ�16λ:",j,sta[j]);
    	for (i = 4; i<12; i++)
		{
        	printf("%02x", decrypta[j][i]);
    	}	
    	cout<<"\n";	
    	printf("����ǰ:%s\n���ܺ�32λ:",sta[j]);
    	for (i = 0; i<16; i++)
		{
        	printf("%02x", decrypta[j][i]);
    	}
		cout<<"\n";	
	}
	cout<<"Team B:\n";
    for(int j=1;j<=mem;j++)
    {
		printf("��%d����Ա:����ǰ:%s\n���ܺ�16λ:",j,stb[j]);
    	for (i = 4; i<12; i++)
		{
        	printf("%02x", decryptb[j][i]);
    	}	
    	cout<<"\n";	
		printf("����ǰ:%s\n���ܺ�32λ:",stb[j]);
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
   		printf("-----------------------\n��%d����Ա\n����:%s\n��׼:%d\nhp:%d\nר��:%s\n",j,sta[j],teama[j].acc,teama[j].hp,mst[teama[j].mas].data());
   		printf("����:");
   		printf("%s ",skl[teama[j].skill].data());
   		printf("\n-----------------------\n");
	}
	setcolor(8);
	cout<<"Team B:\n";
	setcolor(3);
    for(int j=1;j<=mem;j++)
    {
   		printf("-----------------------\n��%d����Ա\n����:%s\n��׼:%d\nhp:%d\nר��:%s\n",j,stb[j],teamb[j].acc,teama[j].hp,mst[teamb[j].mas].data());
   		printf("����:");
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
	cout<<"��������Ϸģʽ:\n";
	setcolor(4);
	cout<<"1:1v1 ���ŶԾѳ�\n2:3v3 ���ٶ�ս��\n3:5v5 ��׼��\n";
	setcolor(5);
	cin>>choicemem;
	mem=choicemem*2-1;
	cout<<"������A������(�ÿո���и���):\n";
	for(int i=1;i<=mem;i++)
	cin>>sta[i];
	cout<<"������B������(�ÿո���и���):\n";
	for(int i=1;i<=mem;i++)
	cin>>stb[i];
	const int NUM=mem*2;//����������� Ȼ������ʾ������֮ǰ��Ū����((( 
	md5ed();
	for (int i=0;i<=NUM;i++)
	{
		if(i*100.0/NUM<=50)
		setcolor(3);
		else
		setcolor(7);
		printf("����ת��ΪMD5:%.2lf%%\r",i*100.0/NUM);
		Sleep(150);
	}
	printf("\nTransformation Completed.\n");
	setcolor(5);
	printf("Game starting...\n");
}

//void use_skill(chara a,bool team,int count)//count:�ڼ�����Ա team:�����ĸ����� 
//{
//	if(team==1)//B�� 
//	{
//	printf("%sʹ��",stb[count]);
//	setcolor(8);
//	printf("%s",skl[a.skill].data());
//	setcolor(5);	
//	}
//	int rdplc=rand()%5+1;
//	//����ϫ���� 
//}
//�������� ����ֱ����ͨ�ж� 

void actt(chara &a,bool team,int count,int rdmac)
{
	if(a.shm==1)
	{
		printf("-------------------------\n%s��Ϊ����ʧ��,���������˴˻غ�\n",team?stb[count]:sta[count]);
		a.shm=0;
		return;
	}
	rdmac%=5;
	rdmac+=1;
	int rdmst=rand()%mem+1;
	int rdmsh=rand()%sh[1][a.weapon]+sh[0][a.weapon];
	if(rdmsh%bjl[a.weapon]==0||(a.pos==3&&a.acc%bjl[a.weapon]==0))//2¥����ɼӴ󱬵ļ��� 
		rdmsh*=2;
	if(rdmac==3||rdmac==4)
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
			printf("-------------------------\n%s���˸���,%s����Ϲ��\n",team?stb[count]:sta[count],team?sta[rdmst]:stb[rdmst]);
			if(team) teama[rdmst].shm=1;
			else
			teamb[rdmst].shm=1;
			break;
		case 2:
			if(a.pos==3)
			{
			setcolor(3);
			printf("-------------------------\n%sʹ��%s�����%s,���%d���˺�,%s��ǰѪ��%d\n",team?stb[count]:sta[count],mst[a.weapon].data(),team?sta[rdmst]:stb[rdmst],rdmsh,team?sta[rdmst]:stb[rdmst],target.hp);
			setcolor(5);
			}
			else
			{
			a.pos=3;
			setcolor(3);
			printf("-------------------------\n%sƭ���ϵ�,�ﵽ��2¥\n",team?stb[count]:sta[count]);
			setcolor(5);	
			}
			break;
		case 3:
			setcolor(1);
			printf("-------------------------\n%s��Ϣ����,��׼��%s\n",team?stb[count]:sta[count],team?sta[rdmst]:stb[rdmst]);
			printf("%sʹ��%s��׼�����%s,���%d���˺�,%s��ǰѪ��%d\n",team?stb[count]:sta[count],mst[a.weapon].data(),team?sta[rdmst]:stb[rdmst],rdmsh,team?sta[rdmst]:stb[rdmst],target.hp);
			setcolor(5);
			break;
		case 4:
			setcolor(3);
			printf("-------------------------\n%sʹ��%s�����%s,���%d���˺�,%s��ǰѪ��%d\n",team?stb[count]:sta[count],mst[a.weapon].data(),team?sta[rdmst]:stb[rdmst],rdmsh,team?sta[rdmst]:stb[rdmst],target.hp);
			setcolor(5);
			break;
		case 5:
			while(tempw==a.weapon)
			a.weapon=rand()%12;
			setcolor(4);
			printf("-------------------------\n%s���˰�%s,�ӵ������е�%s\n",team?stb[count]:sta[count],mst[a.weapon].data(),mst[tempw].data());
			setcolor(5);
			break;
		default :
			printf("-------------------------\n%s����һ�غϴ�,��Ϊ����˼��Ϊʲô�����������������������%d\n",team?stb[count]:sta[count],rdmac);
			break;
	} 
	if(team)
	{
	if(teama[rdmst].hp==0)
	{
		setcolor(4);
		printf("-------------------------\n%s��%sʹ��%sɱ����.\n",team?sta[rdmst]:stb[rdmst],team?stb[count]:sta[count],mst[a.weapon].data());
		setcolor(5);
	}	
	}
	else
	{
	if(teamb[rdmst].hp==0)
	{
		setcolor(4);
		printf("-------------------------\n%s��%sʹ��%sɱ����.\n",team?sta[rdmst]:stb[rdmst],team?stb[count]:sta[count],mst[a.weapon].data());
		setcolor(5);
	}	
	}
}

bool winner;

void game()
{
	cls();
	setcolor(4);
	printf("��Ϸ��ʼ\n");
	setcolor(5);
	bool flag=true;//ʤ������:��һ��ȫ���� 
	int count=0;
	int round=2;
	while(flag)
	{
		round++;
		int count=rand()%mem+1;
		if(round%2==0)//ż�� team B 
		{
			if(teamb[count].hp==0)
			continue;
			setcolor(8);
			printf("�ֵ�Team B�ж�:\n");
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
			printf("�ֵ�Team A�ж�:\n");
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
		flag=(teama[i].hp)?1:0;
		if(!flag)
		{
			winner=1;
			printf("\nTeam B Wins!\n");
			Sleep(3000);
			system("pause");
			return;
		}//Team B Wins
		else
		{
			for(register int i=1;i<=mem;i++)
			flag=(teamb[i].hp)?1:0;
			if(!flag)
			{
				winner=1;
				printf("\nTeam A Wins!\n");
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
    //debug_1();//���md5�� 
    attribute();
    debug_2();
    printf("(��������Ĳ���,��Ϻ�����yes.)\n");
    string fuck="";
    cin>>fuck;
    game();
    return 0;
}
