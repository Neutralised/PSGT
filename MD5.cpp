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
string mst[11]={"AK-47","AWP","P90","Desert Eagle","M4A4","AUG","SG-553","�ڸ��","�ض�����ǹ","ذ��","��˹���ǹ"};
string skl[11]={"","lbw��������","Х����","*����*","�� ��","��������","˦��","rushhhhhh","ϸ����ǹ","A1����","�� ��"};
string act[]


struct chara
{
	int acc;//��׼�� 
	int hp;//Ѫ��
	string skill;//����,�����1�� 
	int mas;//ר�� 
	int pos;//��ǰ����λ�� 
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
		teama[i].skill=skl[rand()%10+1];
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
		teamb[i].skill=skl[rand()%10+1];
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
   		printf("%s ",teama[j].skill.data());
   		printf("\n-----------------------\n");
	}
	setcolor(8);
	cout<<"Team B:\n";
	setcolor(3);
    for(int j=1;j<=mem;j++)
    {
   		printf("-----------------------\n��%d����Ա\n����:%s\n��׼:%d\nhp:%d\nר��:%s\n",j,stb[j],teamb[j].acc,teama[j].hp,mst[teamb[j].mas].data());
   		printf("����:");
   		printf("%s ",teamb[j].skill.data());
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

void game()
{
	cls();
	setcolor(4);
	printf("��Ϸ��ʼ.\n");
	setcolor(5);
	bool flag=true;
	int count=0;
	while(flag)
	{
		count++;
		int rdmc=rand()%mem+1;
		int rdmac=rand()%
	} 
}

int main()
{
	srand(time(NULL));
    strout();
    //debug_1();//���md5�� 
    attribute();
    debug_2();
    game();
    return 0;
}
