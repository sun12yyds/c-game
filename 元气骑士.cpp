#include<bits/stdc++.h>
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<cmath>
#define KEY_DOWN(VK_NONAME)((GetAsyncKeyState(VK_NONAME)&0x8000)?1:0)
using namespace std;
int m[35][35],n[35][35];
void Color(int a)
{
    if(a==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    if(a==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
    if(a==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
    if(a==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
    if(a==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
    if(a==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
    if(a==6) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
    if(a==7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN);//木 
    if(a==8) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//铁 
    if(a==9) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
    if(a==10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|BACKGROUND_GREEN);
    if(a==11) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|BACKGROUND_GREEN);
    if(a==12) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|BACKGROUND_GREEN);
    if(a==13) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|BACKGROUND_INTENSITY|BACKGROUND_BLUE);
}
void SetPos(int x,int y)
{
    COORD pos;
    pos.X=y*2,pos.Y=x+3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
int X,Y,gx,gy,gunT,gunZ,T,G[10],F[30];
int Win,Lev,Blood,Dun,Bmax,Dmax,WuDi,Gguai,Bo,Boo,sy,bu;
int Bx,By,Bblood,Bsi,Bjiao,Bdu,Bfang,Bxz,Byz;
void Map(int x);
void Jian(int x)
{
    if(WuDi>0) return;
    if(Dun>x) Dun-=x; else if(Dun<=0) Blood-=x;
    else if(Dun>0&&Dun<=x)
    {
        if(F[13]==0) Blood-=x-Dun;
        if(F[13]==1) WuDi=20;
        if(F[17]==1) Boo=3;
        Dun=-1;
    }
}
bool CanGo(int x,int y,int q) //0为自己 1其他 2激光怪 3激光枪 4子弹怪 5爆毒 6子弹 7 BOSS
{
    if(abs(Bx-x)<=1&&abs(By-y)<=1&&q==1) return 0;
    if(m[x][y]==2||m[x][y]==3) return 0;
    if((q==0||q==1)&&n[x][y]==1) return 0;
    if(m[x][y]==0) return 1;
    if(m[x][y]>=4&&m[x][y]<=8) return 1;
    if(m[x][y]>=84&&m[x][y]<=88) return 1;
    if(m[x][y]>=9&&m[x][y]<=31) return 1;
    if(m[x][y]>=59&&m[x][y]<=81) return 1;
    if((q==2||q==3||q==5)&&m[x][y]==1) return 1;
    if((q==2||q==3)&&m[x][y]>=100&&m[x][y]<250) return 1;
    if((q==0||q==3||q==5)&&m[x][y]>=50&&m[x][y]<55) return 1;
    if((q==4||q==7)&&m[x][y]/100==1) return 1;
    return 0;
}
void CoutMe()
{
    if(gx<0&&CanGo(X-1,Y,0)) X--;if(gx>0&&CanGo(X+1,Y,0)) X++;if(gy<0&&CanGo(X,Y-1,0)) Y--;if(gy>0&&CanGo(X,Y+1,0)) Y++;
    int r;Color(0);if(WuDi>0) r=rand()%5+1,Color(r);
    if(gunT!=1) SetPos(X-1,Y),cout<<"︹";if(gunT!=5) SetPos(X+1,Y),cout<<"︺";if(gunT!=7) SetPos(X,Y-1),cout<<"﹝";if(gunT!=3) SetPos(X,Y+1),cout<<"﹞";
    if(gunT==1) SetPos(X-1,Y),cout<<"↑";if(gunT==2) SetPos(X-1,Y+1),cout<<"↗";if(gunT==3) SetPos(X,Y+1),  cout<<"→";if(gunT==4) SetPos(X+1,Y+1),cout<<"↘";
    if(gunT==5) SetPos(X+1,Y),cout<<"↓";if(gunT==6) SetPos(X+1,Y-1),cout<<"↙";if(gunT==7) SetPos(X,Y-1),  cout<<"←";if(gunT==8) SetPos(X-1,Y-1),cout<<"↖";
    SetPos(X,Y),cout<<"●";Color(0);
    if(WuDi>0) Map(4);
    if(m[X][Y]>=50&&m[X][Y]<55) Jian(5),system("color 4F"),Sleep(30),system("color 0F"),Map(4);
    if(m[X][Y]>=4&&m[X][Y]<=7&&F[12]==0) Jian(3),system("color 4F"),Sleep(30),system("color 0F"),Map(4);
    if(m[X][Y]>=4&&m[X][Y]<=7&&F[12]==1) Jian(1),system("color 4F"),Sleep(30),system("color 0F"),Map(4);
    if(m[X][Y]>=59&&m[X][Y]<=80&&F[4]==0) Jian(1),system("color 4F"),Sleep(30),system("color 0F"),Map(4);
    if(m[X][Y]==2&&F[4]==0) Jian(3),system("color 4F"),Sleep(30),system("color 0F"),Map(4);
    m[X][Y]=0,gx=gy=0;
}
int Cout(int x,int i,int j)
{
        int Guai=0;
        if(m[i][j]==0&&x==2) SetPos(i,j),cout<<"  ";
        if(m[i][j]==1) SetPos(i,j),Color(7),cout<<"■",Color(0);//木
        if(n[i][j]==0&&m[i][j]==2) SetPos(i,j),Color(8),cout<<"■",Color(0);//铁
        if(n[i][j]==10&&m[i][j]==0) SetPos(i,j),cout<<"  ",Color(0);
        if(n[i][j]==31&&m[i][j]==0) SetPos(i,j),cout<<"  ",Color(0);
        if(m[i][j]==32) m[i][j]=0;//怪子弹灰 
        if(n[i][j]>=20&&n[i][j]<22&&m[i][j]==1) SetPos(i,j),Color(7),cout<<"▁",Color(0);//木
        if(n[i][j]>=22&&n[i][j]<24&&m[i][j]==1) SetPos(i,j),Color(7),cout<<"▂",Color(0);//木
        if(n[i][j]>=24&&n[i][j]<26&&m[i][j]==1) SetPos(i,j),Color(7),cout<<"▄",Color(0);//木
        if(n[i][j]>=26&&n[i][j]<28&&m[i][j]==1) SetPos(i,j),Color(7),cout<<"▆",Color(0);//木
        if(n[i][j]>=28&&n[i][j]<30&&m[i][j]==1) SetPos(i,j),Color(7),cout<<"▆",Color(0);//木
        if(n[i][j]>45&&n[i][j]<=50&&m[i][j]==2) SetPos(i,j),Color(4),cout<<"▲",Color(0);//刺
        if(m[i][j]==3) SetPos(i,j),Color(5),cout<<"〓",Color(0);//箱 
        if(m[i][j]>=4&&m[i][j]<=7) SetPos(i,j),Color(5),cout<<"█",Color(0),m[i][j]++;//烟 
        if(m[i][j]==8) SetPos(i,j),cout<<"  ",m[i][j]=0;//烟尘
        if(m[i][j]>=84&&m[i][j]<=87) SetPos(i,j),Color(5),cout<<"█",Color(0),m[i][j]++;//烟 
        if(m[i][j]==88) SetPos(i,j),cout<<"  ",m[i][j]=0;//烟尘
        if(m[i][j]>=10&&m[i][j]<=30) SetPos(i,j),Color(10),cout<<"@ ",Color(0),m[i][j]++;//毒 
        if(m[i][j]>=60&&m[i][j]<=80) SetPos(i,j),Color(11),cout<<"@ ",Color(0),m[i][j]++;//怪毒 
        if(m[i][j]==9||m[i][j]==59) SetPos(i,j),Color(12),cout<<"@ ",Color(0),m[i][j]++;//金毒 
        if(m[i][j]==31||m[i][j]==81) SetPos(i,j),cout<<"  ",m[i][j]=0;//毒尘
        if(n[i][j]==1) SetPos(i,j),Color(13),cout<<"~ ",Color(0);//水
        if(m[i][j]==50) SetPos(i,j),Color(1),cout<<"●",Color(0),Guai++;//怪 
        if(m[i][j]==51) SetPos(i,j),Color(10),cout<<"●",Color(0),Guai++;//怪 
        if(m[i][j]==52) SetPos(i,j),Color(3),cout<<"●",Color(0),Guai++;//怪 
        if(m[i][j]==53) SetPos(i,j),Color(4),cout<<"●",Color(0),Guai++;//怪 
        if(m[i][j]==54) SetPos(i,j),Color(5),cout<<"●",Color(0),Guai++;//怪
        if(m[i][j]/100==1)
        {
            if((m[i][j]%100)/10<=1) SetPos(i,j),cout<<"☉";
            if((m[i][j]%100)/10==2) SetPos(i,j),Color(4),cout<<"◎",Color(0);
            if((m[i][j]%100)/10==3) SetPos(i,j),Color(1),cout<<"◎",Color(0);
            if((m[i][j]%100)/10==4) m[i][j]=4;
            if((m[i][j]%100)/10==5) SetPos(i,j),Color(3),cout<<"◎",Color(0);
            if((m[i][j]%100)/10==6) SetPos(i,j),Color(2),cout<<"¤",Color(0);
            if((m[i][j]%100)/10>=7&&(m[i][j]%100)/10<=9) SetPos(i,j),Color(2),cout<<"◎",Color(0);
        }
        if(m[i][j]/100==2) if((m[i][j]%100)/10==1) SetPos(i,j),Color(3),cout<<"☉",Color(0);
        return Guai;
}
void Boss()
{
    SetPos(Bx-1,By-1),cout<<"      ";SetPos(Bx,By-1),cout<<"      ";SetPos(Bx+1,By-1),cout<<"      ";
    int mov=rand()%30+1,R=rand()%300,ms;
    if(mov==1&&CanGo(Bx-1,By-2,1)&&CanGo(Bx,By-2,1)&&CanGo(Bx+1,By-2,1)) By--;
    if(mov==2&&CanGo(Bx-1,By+2,1)&&CanGo(Bx,By+2,1)&&CanGo(Bx+1,By+2,1)) By++;
    if(mov==3&&CanGo(Bx-2,By-1,1)&&CanGo(Bx-2,By,1)&&CanGo(Bx-2,By+1,1)) Bx--;
    if(mov==4&&CanGo(Bx+2,By-1,1)&&CanGo(Bx+2,By,1)&&CanGo(Bx+2,By+1,1)) Bx++;
    if(mov==5&&Bsi==0) Bsi+=rand()%3+1; if(mov==6&&Bjiao==0) Bjiao+=rand()%3+1;if(mov==7&&Bdu==0) Bdu+=5;
    if(mov==8&&Bxz==0) Bxz+=rand()%20-10;if(mov==9&&Byz==0) Byz+=rand()%20-10;
    if(Byz<0) {Byz++; if(By-2>1) By--;}if(Byz>0) {Byz--; if(By+2<28) By++;}if(Bxz<0) {Bxz++; if(Bx-2>1) Bx--;}if(Bxz>0) {Bxz--; if(Bx+2<28) Bx++;}
    if(R<15&Gguai<=5) Bfang++;
    else if(R<5&&Gguai<=10) Bfang++;
    else if(R==0) Bfang++;
    SetPos(Bx-1,By-1),Color(0),cout<<" ●● ";
    SetPos(Bx,By-1)  ,Color(4),cout<<")██(";
    SetPos(Bx+1,By-1),Color(4),cout<<" …… ";Color(0);
    if(abs(Bx-X)<=1&&abs(By-Y)<=1) Jian(50);int I,J;
    if(Bsi>0) {Bsi--;I=Bx-2,J=By+rand()%3-1;if(CanGo(I,J,7)) m[I][J]=211;I=Bx+rand()%3-1,J=By+2;if(CanGo(I,J,7)) m[I][J]=213;I=Bx+2,J=By+rand()%3-1;if(CanGo(I,J,7)) m[I][J]=215;I=Bx+rand()%3-1,J=By-2;if(CanGo(I,J,7)) m[I][J]=217;}
    if(Bjiao>0) {Bjiao--;I=Bx-2,J=By+2;if(CanGo(I,J,7)) m[I][J]=212;I=Bx+2,J=By+2;if(CanGo(I,J,7)) m[I][J]=214;I=Bx+2,J=By-2;if(CanGo(I,J,7)) m[I][J]=216;I=Bx-2,J=By-2;if(CanGo(I,J,7)) m[I][J]=218;}
    if(Bdu>0) {if(Bdu>0) Bdu--;for(int i=Bx-4;i<=Bx+4;i++) for(int j=By-4;j<=By+4;j++) if(CanGo(i,j,2)&&abs(Bx-X)>1&&abs(By-Y)>1&&i>0&&j>0) m[i][j]=59;}
    if(Bfang>0) {Bfang--;I=Bx+rand()%5-2,J=By+rand()%5-2;int rr=rand()%6-1;if(rr==-1) rr=0; if(((rr<3&&Lev<5)||(Lev>5))&&(CanGo(I,J,7))) m[I][J]=50+rr;}
    if(Lev==4) ms=3;if(Lev==9) ms=5;if(Lev==14) ms=10;if(Lev==19) ms=15;if(Lev==24) ms=20;
    if(T%50==0&&Bblood<ms*12) Bblood++,Map(3);
    for(int i=Bx-1;i<=Bx+1;i++)
    for(int j=By-1;j<=By+1;j++)
    {
        int du=0;
        if(m[i][j]/100==1) Bblood-=1,Bsi+=rand()%3+1,Map(3);
        if(m[i][j]/10==15) Bblood-=2,Map(3);
        if(m[i][j]<50||m[i][j]>55) m[i][j]=0;
        if(m[i][j]>=84&&m[i][j]<=87) Bblood-=1,Bsi+=rand()%3+1,Map(3);
        if(du==0&&m[i][j]>=9&&m[i][j]<=30) Bblood-=1,du++,Bdu++,Map(3);
        if(Bblood<=0) {Bblood=0;SetPos(Bx-1,By-1),cout<<"      ";SetPos(Bx,By-1),cout<<"      ";SetPos(Bx+1,By-1),cout<<"      ";}
    }
}
void Map(int x)//x=0只输中间 1输全屏 2输身周 2输上方 4 CoutMe中用 5 GuaiQuan中用
{
    if(x!=4) CoutMe();
    int f1,f2,f3,f4,Guai=0;
    if(x==0) f1=f3=2,f2=f4=28;
    if(x==1||x==5) f1=f3=1,f2=f4=29;
    if(x==2) f1=X-1,f2=X+1,f3=Y-1,f4=Y+1;
    if((x==4||x==3||x==1)&&Win>=0)
    {
        SetPos(-3,2),cout<<Lev/5+1<<'-'<<Lev%5+1;
        SetPos(-2,2),cout<<"枪：";
        if(gunZ==1) cout<<"爆炸枪";if(gunZ==2) cout<<"穿甲枪";if(gunZ==3) cout<<"穿甲枪";
        if(gunZ==4) cout<<"激光枪";if(gunZ==5) cout<<"爆炸枪";if(gunZ==6) cout<<"毒气枪";if(gunZ==7) cout<<"弹跳枪";
        cout<<"        子弹数：";if(gunZ==1) cout<<"∞";else cout<<G[gunZ]<<" ";
        SetPos(-1,2),cout<<"血量：";Color(4);int r;
        if(WuDi>0) r=rand()%5+1,Color(r); for(int i=1;i<=13;i++) cout<<"█";Color(0);for(int i=Blood;i<Bmax;i++) cout<<"█";
        Color(0);SetPos(-1,18),cout<<"                    ";
        SetPos(0,2),cout<<"盾牌：";Color(9);
        if(Dun!=0) for(int i=1;i<=26;i++) cout<<"█";Color(0);for(int i=max(1,Dun);i<Dmax;i++) cout<<"█";
        if(Bblood>0)
        {
            int ms;
            if(Lev==4) ms=5; if(Lev==9) ms=10; if(Lev==14) ms=14; if(Lev==19) ms=17; if(Lev==24) ms=20; 
            SetPos(-1,15),cout<<"                                ";
            SetPos(-1,15),cout<<"Boss：";Color(4);for(int i=1;i<=(Bblood-1)%12+1;i++) cout<<"█";
            SetPos(-1,24),Color(3);cout<<(Bblood-1)/12+1;
        }
    }
    if(x==5)
    {
        Color(0);
        SetPos(-3,2),cout<<"  ↑           W 开箱（当有箱子在旁时）    开局无敌3秒";
        SetPos(-2,2),cout<<"←  →移动     A/D 顺/逆时针转枪     空格 暂停";
        SetPos(-1,2),cout<<"  ↓           S 发射子弹 清除所有怪进下一关    盾会恢复";
        SetPos(0,2), cout<<" 每五关可获得一个天赋   完成 5-5 通关   ",Color(3),cout<<"按 y 进第一关";
        for(int i=f1;i<=f2;i++)
        for(int j=f3;j<=f4;j++) Cout(x,i,j);
    }
    if(x!=3&&x!=4)
    {
        for(int i=f1;i<=f2;i++)
        for(int j=f3;j<=f4;j++) Guai+=Cout(x,i,j);
        if(x!=2)
        {
            int Rr=rand()%3;
            if(Guai<Gguai&&Guai!=0&&F[15]==1&&Rr==0&&Lev%5==4)
            Dun=min(Dmax,Dun+1),Map(3);
            Gguai=Guai;
        }
        if(Guai==0&&x==0&&Win==0&&Bblood<=0)
        {
            if(Lev!=24)
            {   
                system("color 6E"),Color(5);
                SetPos(2,2),cout<<"You! Win!!!";Sleep(500);
                SetPos(3,2),cout<<"Please point 'y' to Play AGain.",Sleep(1000);
                system("color 0F");Map(1);
            }
            Win++,Lev++;
        }
    }
}
void Fan(int i,int j,int M)
{
    if(M%10==1||M%10==3) m[i][j]=M+4;
    if(M%10==5||M%10==7) m[i][j]=M-4;
    if(M%10==2)
    {
        if(m[i][j+1]!=0||m[i-2][j+1]!=0) m[i][j]=M+6;
        else if(m[i-1][j]!=0||m[i-1][j+2]!=0) m[i][j]=M+2;
        else m[i][j]=M+4;
    }
    if(M%10==4)
    {
        if(m[i+1][j]!=0||m[i+1][j+2]!=0) m[i][j]=M-2;
        else if(m[i][j+1]!=0||m[i+2][j+1]!=0) m[i][j]=M+2;
        else m[i][j]=M+4;
    }
    if(M%10==6)
    {
        if(m[i][j-1]!=0||m[i+2][j-1]!=0) m[i][j]=M-2;
        else if(m[i+1][j]!=0||m[i+1][j-2]!=0) m[i][j]=M+2;
        else m[i][j]=M-4;
    }
    if(M%10==8)
    {
        if(m[i][j-1]!=0||m[i-2][j-1]!=0) m[i][j]=M-6;
        else if(m[i-1][j]!=0||m[i-1][j-2]!=0) m[i][j]=M-2;
        else m[i][j]=M-4;
    }
}
void Light(int i,int j,int M,int x)
{
    if(M%10==1) for(int k=1;CanGo(i-k,j,x);k++)  {if(x==3) m[i-k][j]=84; else m[i-k][j]=4;}
    if(M%10==2) for(int k=1;CanGo(i-k,j+k,x);k++){if(x==3) m[i-k][j+k]=84; else m[i-k][j+k]=4;}
    if(M%10==3) for(int k=1;CanGo(i,j+k,x);k++)  {if(x==3) m[i][j+k]=84; else m[i][j+k]=4;}
    if(M%10==4) for(int k=1;CanGo(i+k,j+k,x);k++){if(x==3) m[i+k][j+k]=84; else m[i+k][j+k]=4;}
    if(M%10==5) for(int k=1;CanGo(i+k,j,x);k++)  {if(x==3) m[i+k][j]=84; else m[i+k][j]=4;}
    if(M%10==6) for(int k=1;CanGo(i+k,j-k,x);k++){if(x==3) m[i+k][j-k]=84; else m[i+k][j-k]=4;}
    if(M%10==7) for(int k=1;CanGo(i,j-k,x);k++)  {if(x==3) m[i][j-k]=84; else m[i][j-k]=4;}
    if(M%10==8) for(int k=1;CanGo(i-k,j-k,x);k++){if(x==3) m[i-k][j-k]=84; else m[i-k][j-k]=4;}
}
void Move()
{
    bool nx[32][32];
    memset(nx,0,sizeof(nx));
    for(int i=2;i<=28;i++)
    for(int j=2;j<=28;j++)
    {
        if(m[i][j]==50&&nx[i][j]==0&&T%2==0)//无脑怪
        {
            int r,I=i,J=j,rr=rand()%5,rrr=rand()%2;
            if(rrr==0) {if(X<i) r=1;if(X>i) r=4;}
            if(rrr==1) {if(Y>j) r=2;if(Y<j) r=3;} if(rr==0) r=rand()%4+1;
            if(r==1) I=i-1,J=j;if(r==2) I=i,J=j+1;if(r==3) I=i,J=j-1;if(r==4) I=i+1,J=j;
            if(CanGo(I,J,1)) m[i][j]=0,m[I][J]=50,SetPos(i,j),cout<<"  ",SetPos(I,J),cout<<"●",nx[I][J]=1;
        }
        if(m[i][j]==51&&nx[i][j]==0)//毒怪
        {
            int R=rand()%10;
            int r,I=i,J=j,rr=rand()%30,rrr=rand()%2,mr=rand()%15;
            if(rrr==0) {if(X<i) r=1;if(X>i) r=4;}
            if(rrr==1) {if(Y>j) r=2;if(Y<j) r=3;} if(rr!=0) r=rand()%4+1;
            if(r==1) I=i-1,J=j;if(r==2) I=i,J=j+1;if(r==3) I=i,J=j-1;if(r==4) I=i+1,J=j;
            if(mr==0) {for(int k=I-2;k<=I+2;k++) for(int l=J-2;l<=J+2;l++) if(k>1&&l>1&&k<=28&&l<=28&&(CanGo(k,l,1)||m[k][l]==1)) m[k][l]=59;}
            if(CanGo(I,J,1)||m[I][J]==1) m[i][j]=59,m[I][J]=51,SetPos(i,j),cout<<"  ",SetPos(I,J),cout<<"●",nx[I][J]=1;
        }
        if(m[i][j]==52&&nx[i][j]==0)//散弹怪 
        {
            int R=rand()%10;
            if(R==0)
            {
                int I,J,r,rn=0;
                int rr=rand()%8,Rn=rand()%3+1;
                Xr:
                rr=rand()%8,rn++;
                if(rr==0) {r=1,I=i-1,J=j;if(CanGo(I,J,6)) m[I][J]=210+r;}
                if(rr==1) {r=3,I=i,J=j+1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                if(rr==2) {r=5,I=i+1,J=j;if(CanGo(I,J,6)) m[I][J]=210+r;}
                if(rr==3) {r=7,I=i,J=j-1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                if(rr==4) {r=2,I=i-1,J=j+1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                if(rr==5) {r=4,I=i+1,J=j+1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                if(rr==6) {r=6,I=i+1,J=j-1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                if(rr==7) {r=8,I=i-1,J=j-1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                if(rr==8) {r=rand()%7+2;I=i+1,J=j;if(m[I][J]!=2) m[I][J]=210+r;}nx[I][J]=1;
                if(rn<Rn) goto Xr;
            }
            else if(R<=2)
            {
                int r=rand()%4+1,Ie,Je;
                if(r==1) Ie=i-1,Je=j;if(r==2) Ie=i,Je=j+1;if(r==3) Ie=i,Je=j-1;if(r==4) Ie=i+1,Je=j;
                if(CanGo(Ie,Je,1)) m[i][j]=0,m[Ie][Je]=52,SetPos(i,j),cout<<"  ",SetPos(Ie,Je),cout<<"●";
            }
        }
        if(m[i][j]==53&&nx[i][j]==0)//瞄准怪 
        {
            int R=rand()%6;
            if(R==0)
            {
                int I,J,r,rr=rand()%5;
                if(X-i<0&&abs(Y-j)<=2) {r=1,I=i-1,J=j;if(CanGo(I,J,6)) m[I][J]=210+r;}
                else if(Y-j>0&&abs(X-i)<=2) {r=3,I=i,J=j+1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                else if(X-i>0&&abs(Y-j)<=2) {r=5,I=i+1,J=j;if(CanGo(I,J,6)) m[I][J]=210+r;}
                else if(Y-j<0&&abs(X-i)<=2) {r=7,I=i,J=j-1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                else if(X-i<0&&Y-j>0&&abs((i-X)-(Y-j))<=2) {r=2,I=i-1,J=j+1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                else if(X-i>0&&Y-j>0&&abs((X-i)-(Y-j))<=2) {r=4,I=i+1,J=j+1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                else if(X-i>0&&j-Y>0&&abs((X-i)-(j-Y))<=2) {r=6,I=i+1,J=j-1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                else if(X-i<0&&Y-j<0&&abs((i-X)-(j-Y))<=2) {r=8,I=i-1,J=j-1;if(CanGo(I,J,6)) m[I][J]=210+r;}
                else if(rr==0) {r=rand()%7+2;I=i+1,J=j;if(CanGo(I,J,6)) m[I][J]=210+r;}
            }
            else if(R==1)
            {
                int r=rand()%4+1,Ie,Je;
                if(r==1) Ie=i-1,Je=j;if(r==2) Ie=i,Je=j+1;if(r==3) Ie=i,Je=j-1;if(r==4) Ie=i+1,Je=j;
                if(CanGo(Ie,Je,1)) m[i][j]=0,m[Ie][Je]=53,SetPos(i,j),cout<<"  ",SetPos(Ie,Je),cout<<"●";
            }
        }
        if(m[i][j]==54&&nx[i][j]==0)//激光怪
        {
            int R=rand()%10;
            if(R==0) {int r=rand()%4; Light(i,j,231+2*r,2);}
            else if(R<=3)
            {
                int r=rand()%4+1,Ie,Je;
                if(r==1) Ie=i-1,Je=j;if(r==2) Ie=i,Je=j+1;if(r==3) Ie=i,Je=j-1;if(r==4) Ie=i+1,Je=j;
                if(CanGo(Ie,Je,1)) m[i][j]=0,m[Ie][Je]=54,SetPos(i,j),cout<<"  ",SetPos(Ie,Je),cout<<"●";
            }
        }
        if(m[i][j]/100==2&&F[3]==1&&T%2==0) nx[i][j]=1;
        if((m[i][j]/100==1||m[i][j]/100==2)&&nx[i][j]==0)//子弹 
        {
            int M=m[i][j],I,J;m[i][j]=0;SetPos(i,j),cout<<"  ";
            if(M%10==1) I=i-1,J=j;if(M%10==2) I=i-1,J=j+1;if(M%10==3) I=i,J=j+1;if(M%10==4) I=i+1,J=j+1;
            if(M%10==5) I=i+1,J=j;if(M%10==6) I=i+1,J=j-1;if(M%10==7) I=i,J=j-1;if(M%10==8) I=i-1,J=j-1;

            if(I==X&&J==Y&&M/100==2) {Jian(2),system("color 4F"),Sleep(30);system("color 0F"),m[i][j]=0;Map(4);}
            else if(I==X&&J==Y&&M/100==1) m[I][J]=0;
            else if(M/100==2&&m[I][J]/100==1) m[i][j]=32;
            else if(M/100==2&&m[I][J]<55&&m[I][J]>=50) m[i][j]=0;
            else if(m[I][J]==2||m[I][J]==3)//石
            {
                if((M%100)/10==0)
                {
                    int rr=rand()%3;
                    if(rr==0) Fan(i,j,M),m[i][j]+=10;
                    else m[i][j]=84;
                }
                if((M%100)/10==1)
                {
                    m[i][j]=84;
                    int rr=rand()%5;
                    if(rr==0&&F[14]==1&&M/100==1)
                    {
                            for(int ii=i-1;ii<=i+1;ii++)
                            for(int jj=j-1;jj<=j+1;jj++)
                            if(m[ii][jj]!=2&&m[ii][jj]!=3&&ii<=28&&jj<=28) m[ii][jj]=84;
                    }
                }
                if((M%100)/10==2)
                {
                    m[i][j]=84;
                    if(m[i-1][j]!=2&&m[i-1][j]!=3)     m[i-1][j]=111;
                    if(m[i-1][j+1]!=2&&m[i-1][j+1]!=3) m[i-1][j+1]=112;
                    if(m[i][j+1]!=2&&m[i][j+1]!=3)     m[i][j+1]=113;
                    if(m[i+1][j+1]!=2&&m[i+1][j+1]!=3) m[i+1][j+1]=114;
                    if(m[i+1][j]!=2&&m[i+1][j]!=3)     m[i+1][j]=115;
                    if(m[i+1][j-1]!=2&&m[i+1][j-1]!=3) m[i+1][j-1]=116;
                    if(m[i][j-1]!=2&&m[i][j-1]!=3)     m[i][j-1]=117;
                    if(m[i-1][j-1]!=2&&m[i-1][j-1]!=3) m[i-1][j-1]=118;
                }
                if((M%100)/10==3) {if(m[I][J]==2&&(I!=1&&J!=1&&I!=29&&J!=29)) m[I][J]=84;else m[i][j]=84;}
                if((M%100)/10==4) m[i][j]=84;
                if((M%100)/10==5)
                {
                    for(int ii=i-2;ii<=i+2;ii++)
                    for(int jj=j-2;jj<=j+2;jj++)
                    if(m[ii][jj]!=2&&m[ii][jj]!=3&&ii<=28&&jj<=28) m[ii][jj]=84;
                }
                if((M%100)/10==6)
                {
                    for(int ii=i-1;ii<=i+1;ii++)
                    for(int jj=j-1;jj<=j+1;jj++)
                    if(m[ii][jj]!=2&&m[ii][jj]!=3&&ii<=28&&jj<=28) m[ii][jj]=9;
                }
                if((M%100)/10>=7&&(M%100)/10<9) Fan(i,j,M),m[i][j]+=(rand()%2)*10;
                if((M%100)/10==9) m[i][j]=84;
            }
            else if(!CanGo(I,J,6))//其他
            {
                if((M%100)/10==0) m[I][J]=84,Fan(i,j,M),m[i][j]+=10;
                if((M%100)/10==1)
                {
                    if(M/100==2&&m[I][J]==50) m[i][j]=0;
                    else m[I][J]=84;
                    if(F[14]==1&&M/100==1)
                    {
                            for(int ii=I-1;ii<=I+1;ii++)
                            for(int jj=J-1;jj<=J+1;jj++)
                            if(m[ii][jj]!=2&&m[ii][jj]!=3&&ii<=28&&jj<=28) m[ii][jj]=84;
                    }
                }
                if((M%100)/10==2)
                {
                    m[I][J]=84;
                    if(m[I-1][J]!=2&&m[I-1][J]!=3)     m[I-1][J]=111;
                    if(m[I-1][J+1]!=2&&m[I-1][J+1]!=3) m[I-1][J+1]=112;
                    if(m[I][J+1]!=2&&m[I][J+1]!=3)     m[I][J+1]=113;
                    if(m[I+1][J+1]!=2&&m[I+1][J+1]!=3) m[I+1][J+1]=114;
                    if(m[I+1][J]!=2&&m[I+1][J]!=3)     m[I+1][J]=115;
                    if(m[I+1][J-1]!=2&&m[I+1][J-1]!=3) m[I+1][J-1]=116;
                    if(m[I][J-1]!=2&&m[I][J-1]!=3)     m[I][J-1]=117;
                    if(m[I-1][J-1]!=2&&m[I-1][J-1]!=3) m[I-1][J-1]=118;
                }
                if((M%100)/10==3) m[I][J]=M,nx[I][J]=1;
                if((M%100)/10==4) Light(i,j,M,3);
                if((M%100)/10==5)
                {
                    for(int ii=I-2;ii<=I+2;ii++)
                    for(int jj=J-2;jj<=J+2;jj++)
                    if(m[ii][jj]!=2&&m[ii][jj]!=3&&ii<=28&&jj<=28) m[ii][jj]=84;
                }
                if((M%100)/10==6)
                {
                    for(int ii=I-1;ii<=I+1;ii++)
                    for(int jj=J-1;jj<=J+1;jj++)
                    if(m[ii][jj]!=2&&m[ii][jj]!=3&&ii<=28&&jj<=28) m[ii][jj]=9;
                }
                if((M%100)/10>=7&&(M%100)/10<9) m[I][J]=84,Fan(i,j,M);
                if((M%100)/10==9) m[I][J]=84;
            }
            else//空地
            {
                if((M%100)/10==6)
                {
                    m[i][j]=9;
                    if(CanGo(i,j-1,5)) m[i][j-1]=9;if(CanGo(i,j+1,5)) m[i][j+1]=9;
                    if(CanGo(i-1,j,5)) m[i-1][j]=9;if(CanGo(i-1,j,5)) m[i+1][j]=9;
                    m[I][J]=M,nx[I][J]=1;
                }
                if((M%100)/10==4) m[i][j]=84,m[I][J]=M,i=2,j=2;
                else m[I][J]=M,nx[I][J]=1;
            }
        }
    }
    if(Bblood>0) Boss();
}
void Bullet()
{
    int I=0,J=0,R=rand()%10,Rr=rand()%3,Rrr,K=0,tg=gunT;
    Hh:Rrr=rand()%20;
    if(gunT==1&&m[X-1][Y]!=2&&m[X-1][Y]!=3) I=X-1,J=Y;
    if(gunT==2&&m[X-1][Y+1]!=2&&m[X-1][Y+1]!=3) I=X-1,J=Y+1;
    if(gunT==3&&m[X][Y+1]!=2&&m[X][Y+1]!=3) I=X,J=Y+1;
    if(gunT==4&&m[X+1][Y+1]!=2&&m[X+1][Y+1]!=3) I=X+1,J=Y+1;
    if(gunT==5&&m[X+1][Y]!=2&&m[X+1][Y]!=3) I=X+1,J=Y;
    if(gunT==6&&m[X+1][Y-1]!=2&&m[X+1][Y-1]!=3) I=X+1,J=Y-1;
    if(gunT==7&&m[X][Y-1]!=2&&m[X][Y-1]!=3) I=X,J=Y-1;
    if(gunT==8&&m[X-1][Y-1]!=2&&m[X-1][Y-1]!=3) I=X-1,J=Y-1;
    if(I!=0&&J!=0) m[I][J]=100+10*gunZ+gunT;
    if(K==1) m[I][J]=110+gunT;
    if(F[2]==1&&gunZ==1) m[I][J]=100+gunT;
    if(F[8]==1&&R==0&&K==0) {gunT=rand()%8+1;K=1;goto Hh;}
    if(F[8]==1&&K!=0&&K<Rr) {gunT=rand()%8+1;K++;goto Hh;} if(K>=Rr) gunT=tg;
    if(Rrr==0&&F[11]==1&&K==0) {m[I][J]=100+10*(rand()%7+1)+gunT;}
    if(gunZ!=1) {G[gunZ]--; if(G[gunZ]<=0) G[gunZ]=0,gunZ=1;Map(3);}
}
void OpenBox(int a)
{
    for(int i=X-1;i<=X+1;i++)
    for(int j=Y-1;j<=Y+1;j++)
    if(m[i][j]==3)
    {
        int r=2;//
        if(a==1) r=rand()%6+2;
        if(F[9]==1) r=rand()%12+2;
        SetPos(i,j);Color(5);
        if(r==2) cout<<"分裂枪！";
        if(r==3) cout<<"穿甲枪！";
        if(r==4) cout<<"激光枪！";
        if(r==5) cout<<"爆炸枪！";
        if(r==6) cout<<"毒气枪！";
        if(r==7) cout<<"弹跳枪！";
        if(r==8) cout<<"生命药水！",Blood=min(Blood+5,Bmax+2),Map(3);
        if(r==9) cout<<"盾牌药水！",Dun=min(Dun+5,Dmax+2),Map(3);
        if(F[9]==1&&r>=8&&r<=13) cout<<"生命药水！",Blood=min(Blood+5,Bmax+2),Map(3);
        Sleep(1000);m[i][j]=84;if(r<=7&&F[6]==0) gunZ=r,G[r]+=10;if(r<=7&&F[6]==1) gunZ=r,G[r]+=20;
        SetPos(i,j); cout<<"         ";Map(0);
    }
}
void Sheng()
{
    memset(m,0,sizeof(m));memset(n,0,sizeof(n));
    int q=0,T=0,II=0,JJ=0;
    Re: q++;
    int r=rand()%15+1;
    if(F[19]==1) r=rand()%20+1;
    if(r==1) {for(int i=5;i<=7;i++)for(int j=5;j<=7;j++) m[i][j]=2;for(int i=23;i<=25;i++)for(int j=5;j<=7;j++) m[i][j]=2;for(int i=5;i<=7;i++)for(int j=23;j<=25;j++) m[i][j]=2;for(int i=23;i<=25;i++)for(int j=23;j<=25;j++) m[i][j]=2;}
    if(r==2) {for(int i=13;i<=17;i++) for(int j=13;j<=17;j++) m[i][j]=1;}
    if(r==3) {for(int i=2;i<=28;i++) m[i][6]=m[i][24]=m[6][i]=m[24][i]=1;}
    if(r==4) {for(int i=2;i<=28;i++) m[i][15]=m[15][i]=1;}
    if(r==5) {for(int i=2;i<=28;i++) if(abs(i-15)>=3) m[i][15]=m[15][i]=2;}
    if(r==6) {for(int i=2;i<=28;i++) for(int j=2;j<=28;j++) if(i==j||i+j==30) m[i][j]=1;}
    if(r==7) {for(int i=2;i<=28;i++) for(int j=2;j<=28;j++) if(abs(i-15)+abs(j-15)==10) m[i][j]=1;}
    if(r==8) {for(int i=5;i<=25;i++) if(abs(i-15)>=2) m[i][10]=m[i][20]=m[10][i]=m[20][i]=2;}
    if(r==9) {for(int i=2;i<=28;i++) for(int j=2;j<=28;j++) {int rr=rand()%20; if(rr==0&&m[i][j]==0) m[i][j]=1;}}
    if(r>=10&&II==0) {T--;int ii=rand()%27+2;int jj=rand()%27+2; for(int i=ii-1;i<=ii+1;i++) for(int j=jj-1;j<=jj+1;j++) if(m[i][j]==0) m[i][j]=1;II=ii,JJ=jj;}
    if(r>=10&&II!=0) goto Re;if(Lev<=5&&q<2) goto Re;
    T++;if(T==1) goto Re;if(II!=0) m[II][JJ]=3;
    r=rand()%15+1;
    if(r==1) {for(int i=5;i<=25;i++) n[i][4]=n[i][9]=n[i][15]=n[i][21]=n[i][26]=31;}
    if(r==2) {for(int i=8;i<=22;i++) n[i][8]=n[i][22]=n[8][i]=n[22][i]=31;}
    if(r==3) {for(int i=1;i<=5;i++) {int ii=rand()%23+4,jj=rand()%23+4;for(int ki=ii-2;ki<=ii+2;ki++)for(int kj=jj-2;kj<=jj+2;kj++) if(abs(ki-X)>2||abs(kj-Y)>2) n[ki][kj]=1;}}
    if(r==4) {for(int i=1;i<=7;i++) {int ii=rand()%23+4,jj=rand()%23+4;for(int ki=ii-1;ki<=ii+1;ki++)for(int kj=jj-1;kj<=jj+1;kj++) n[ki][kj]=11;}}
    if(r==5) {for(int i=1;i<=20;i++) {int ii=rand()%23+4,jj=rand()%13+1;jj*=2;for(int ki=ii-1;ki<=ii+1;ki++) n[jj+1][ki]=31;}}
    if(r==6) {for(int i=2;i<=28;i++) n[i][9]=n[i][10]=n[i][20]=n[i][21]=11;}
    if(r==7) {for(int i=5;i<=25;i++) n[4][i]=n[9][i]=n[15][i]=n[21][i]=n[26][i]=31;}
    if(r==8) {for(int i=7;i<=23;i++) for(int j=7;j<=23;j++) if(i==j||i+j==30) n[i][j]=31;}
    if(r==9) {for(int i=2;i<=28;i++) {if(i!=4&&i!=26&&!(i==Y&&(14<=X&&16>=X))) n[14][i]=n[15][i]=n[16][i]=1; m[14][i]=m[15][i]=m[16][i]=0;}}
    if(r==10) {for(int i=7;i<=23;i++) if(abs(i-15)>1) n[i][7]=n[i][23]=n[7][i]=n[23][i]=1;}
    Kk:
    int k=0,K[35][35]; memset(K,0,sizeof(K));
    if(Lev%5!=4)
    {
        for(int i=2;i<=28;i++)//怪
        for(int j=2;j<=28;j++)
        {
            if(Lev<=1) {int r=rand()%150;if(r==0) K[i][j]=50,k++;}
            else if(Lev<=2) {int r=rand()%200;if(r==0) K[i][j]=50;if(r==1) K[i][j]=51;if(r<=1) k++;}
            else if(Lev<=3) {int r=rand()%300;if(r==0) K[i][j]=50;if(r==1) K[i][j]=51;if(r==2) K[i][j]=52;if(r<=2) k++;}
            else if(Lev<=5) {int r=rand()%400;if(r==0) K[i][j]=50;if(r==1) K[i][j]=51;if(r==2) K[i][j]=52;if(r==3) K[i][j]=53;if(r<=3) k++;}
            else if(Lev<=7) {int r=rand()%350;if(r==0) K[i][j]=50;if(r==1) K[i][j]=51;if(r==2) K[i][j]=52;if(r==3) K[i][j]=53;if(r==4) K[i][j]=54;if(r<=4) k++;}
            else {int r;if(Lev<=10) r=rand()%300;if(Lev<=15) r=rand()%280;if(Lev<=20) r=rand()%250;if(Lev<=25) r=rand()%230;if(r==0) K[i][j]=50;if(r==1) K[i][j]=51;if(r==2) K[i][j]=52;if(r==3) K[i][j]=53;if(r==4) K[i][j]=54;if(r<=4) k++;}
        }if(k<3) goto Kk;if(k>5&&Lev<=3) goto Kk;if(k<5&&Lev>=10) goto Kk;if(k>10&&Lev<=10) goto Kk;if(k>15&&Lev<=15) goto Kk;if(k<10&&Lev>=20) goto Kk;if(k>20&&Lev<=20) goto Kk;
    }
    for(int i=2;i<=28;i++) for(int j=2;j<=28;j++) {if(n[i][j]!=0) m[i][j]=0;if(K[i][j]!=0&&(m[i-1][j]!=2||m[i+1][j]!=2||m[i][j-1]!=2||m[i][j+1]!=2)) m[i][j]=K[i][j];}
    if(Lev%5==4) {int ms;if(Lev==4) ms=3;if(Lev==9) ms=5;if(Lev==14) ms=10;if(Lev==19) ms=15;if(Lev==24) ms=20;Bx=rand()%23+4,By=rand()%23+4;Bblood=ms*12;for(int i=14;i<=16;i++) for(int j=14;j<=16;j++) m[i][j]=n[i][j]=0;}
    for(int i=X-1;i<=X+1;i++) for(int j=Y-1;j<=Y+1;j++) if(i!=1&&i!=29&&j!=1&&j!=29) m[i][j]=0;
    for(int i=1;i<=29;i++) m[1][i]=2,m[29][i]=2; for(int i=1;i<=29;i++) m[i][1]=2,m[i][29]=2;//周围石块
}
void TianFu()
{
    int A[4],ss=0;
    system("cls");
    SetPos(5,5),cout<<"选择一个天赋！（数字键选择）"; 
    Tf:
    int R=rand()%20+1;
    for(int i=1;i<=3;i++) if(R==A[i]) goto Tf;
    if(F[R]==1) goto Tf;
    ss++,A[ss]=R; SetPos(4*ss+5,8),cout<<ss<<"、";
    if(R==1) SetPos(4*ss+5,10),cout<<"盾牌恢复速度增加";
    if(R==2) SetPos(4*ss+5,10),cout<<"普通子弹有概率弹跳";
    if(R==3) SetPos(4*ss+5,10),cout<<"怪物子弹速度变慢";
    if(R==4) SetPos(4*ss+5,10),cout<<"免疫地刺和怪物的毒";
    if(R==5) SetPos(4*ss+5,10),cout<<"开局无敌时间增加";
    if(R==6) SetPos(4*ss+5,10),cout<<"宝箱子弹量增加";
    if(R==7) SetPos(4*ss+5,10),cout<<"盾牌上限增加";
    if(R==8) SetPos(4*ss+5,10),cout<<"有概率发射散弹";
    if(R==9) SetPos(4*ss+5,10),cout<<"宝箱抽出生命水概率增加";
    if(R==10) SetPos(4*ss+5,10),cout<<"每次开局有概率增加生命";
    if(R==11) SetPos(4*ss+5,10),cout<<"有概率发射特殊子弹";
    if(R==12) SetPos(4*ss+5,10),cout<<"激光伤害减半";
    if(R==13) SetPos(4*ss+5,10),cout<<"盾牌爆后无敌一段时间";
    if(R==14) SetPos(4*ss+5,10),cout<<"普通子弹有概率爆炸";
    if(R==15) SetPos(4*ss+5,10),cout<<"杀死怪有几率加盾（BOSS关除外）";
    if(R==16) SetPos(4*ss+5,10),cout<<"出场释放冲击波";
    if(R==17) SetPos(4*ss+5,10),cout<<"盾牌爆后释放冲击波";
    if(R==18) SetPos(4*ss+5,10),cout<<"有概率在身周放毒";
    if(R==19) SetPos(4*ss+5,10),cout<<"刷出宝箱概率增加";
    if(R==20) SetPos(4*ss+5,10),cout<<"每次开局获得一把枪";
    if(ss<3) goto Tf;
    tF:
    char c=_getch();
    if(c>='1'&&c<='3') F[A[c-'0']]=1;
    else goto tF;
    if(A[c-'0']==7) Dmax+=3;
}
void GuaiQuan()
{
    X=3,Y=3;Win=-1;system("cls");Color(0);
    memset(m,0,sizeof(m));memset(n,0,sizeof(n));
    for(int i=1;i<=29;i++) m[1][i]=2,m[29][i]=2;
    for(int i=1;i<=29;i++) m[i][1]=2,m[i][29]=2;//周围石块 
    for(int i=4;i<=12;i++) m[i][4]=m[i][12]=m[4][i]=m[12][i]=m[i][18]=m[i][26]=m[18][i]=m[26][i]=2;
    for(int i=18;i<=26;i++) m[i][4]=m[i][12]=m[4][i]=m[12][i]=m[i][18]=m[i][26]=m[18][i]=m[26][i]=2;
    for(int i=11;i<=19;i++) m[i][11]=m[i][19]=m[11][i]=m[19][i]=2;
    for(int i=6;i<=10;i++) for(int j=13;j<=17;j++) m[i][j]=1; 
    m[8][8]=50;m[8][21]=51;m[15][15]=52;m[21][8]=53;m[21][21]=54;m[16][23]=3;Map(5);
    SetPos(3,5);cout<<"←你";SetPos(4,14);cout<<"木箱↓";SetPos(17,4);cout<<"铁块↓";SetPos(17,21);cout<<"宝箱↑";
    SetPos(13,5);cout<<"无脑小怪↑";SetPos(14,21);cout<<"剧毒小怪↑";
    SetPos(20,13);cout<<"散弹小怪↑";SetPos(27,5);cout<<"狙击小怪↑";SetPos(27,21);cout<<"激光小怪↑";
    while(1)
    {
        if(bu>0) bu--;
        if(GetAsyncKeyState(VK_UP)&0x8000) Map(2),gx--; 
        else if(GetAsyncKeyState(VK_DOWN)&0x8000) Map(2),gx++;
        else if(GetAsyncKeyState(VK_LEFT)&0x8000) Map(2),gy--;
        else if(GetAsyncKeyState(VK_RIGHT)&0x8000) Map(2),gy++;
        if(kbhit())
        {
            char g=_getch();
            if(g=='a') {Map(2); if(gunT!=1) gunT--;else gunT=8;}
            if(g=='d') {Map(2); if(gunT!=8) gunT++;else gunT=1;}
            if(g=='w') OpenBox(1);
            if(g=='s'&&bu<=2) Bullet(),bu+=2;
            if(g==' ') Sleep(100),SetPos(-1,18),sy++,system("pause");
            if(g=='y'&&Win<0) {break;}
        }
        if(sy==1) SetPos(-1,18),cout<<"                           ",sy--;
        Move(); Map(0); Sleep(50);
    }Lev=0;Blood=10,Dun=10,Bmax=10,Dmax=10;
}
void Start()
{
    Color(5);
    SetPos(2,3);cout<<"     ■■■■■■            ■                  ";
    SetPos(3,3);cout<<"                            ■■■■■■■■     ";
    SetPos(4,3);cout<<"                           ■                    ";
    SetPos(5,3);cout<<" ■■■■■■■■■■    ■  ■■■■■■        ";
    SetPos(6,3);cout<<"       ■    ■                                  ";
    SetPos(7,3);cout<<"       ■    ■              ■■■■■■■      ";
    SetPos(8,3);cout<<"      ■     ■  ■                    ■        ";
    SetPos(9,3);cout<<"   ■■       ■■■                  ■        ";
    SetPos(10,3);cout<<"                                      ■    ■  ";
    SetPos(11,3);cout<<"                         小            ■■■■ ";
    SetPos(13,3);cout<<" 2.0版本：                                      ";
    SetPos(14,3);cout<<"                               ■■■     ■    ";
    SetPos(15,3);cout<<" 新增BOSS！Crab-Dave！         ■  ■    ■     ";
    SetPos(16,3);cout<<"                               ■■■  ■    ■ ";
    SetPos(17,3);cout<<" 水,生木块,地刺加入战场！      ■  ■ ■■■■■";
    SetPos(18,3);cout<<"                               ■  ■           ";
    SetPos(19,3);cout<<" 身周不会刷出石和水了！        ■■■  ■■■■ ";
    SetPos(20,3);cout<<"                               ■  ■  ■    ■ ";
    SetPos(21,3);cout<<" BUG修正于小优化！努力通关吧！ ■  ■  ■    ■ ";
    SetPos(22,3);cout<<"                            ■■   ■  ■■■■ ";
    SetPos(25,4);Color(1);cout<<"按 y 开始游戏!";
    SetPos(29,3);Color(3);cout<<"注意！这里 绝对不能是拼音输入法!";
    A:char y=_getch();
    if(y=='y') return;
    else goto A;
}
void Bling()
{
    for(int i=0;i<=3;i++)
    {
        system("color 1A");Sleep(10);
        system("color 2B");Sleep(10);
        system("color 3C");Sleep(10);
        system("color 4D");Sleep(10);
        system("color 5D");Sleep(10);
        system("color 6E");Sleep(10);
        system("color 7F");Sleep(10);
    }system("color 0F");system("cls");
}
void BaoBo(int B)
{
    for(int i=X-B;i<=X+B;i++) if(CanGo(i,Y-B,3)&&i>0&&Y-B>0) m[i][Y-B]=86,m[i][Y-B+1]=8;
    for(int i=X-B;i<=X+B;i++) if(CanGo(i,Y+B,3)&&i>0&&Y+B>0) m[i][Y+B]=86,m[i][Y+B-1]=8;
    for(int j=Y-B;j<=Y+B;j++) if(CanGo(X+B,j,3)&&j>0&&X+B>0) m[X+B][j]=86,m[X+B-1][Y]=8;
    for(int j=Y-B;j<=Y+B;j++) if(CanGo(X-B,j,3)&&j>0&&X-B>0) m[X-B][j]=86,m[X-B+1][Y]=8;
}
void Ci()
{
    for(int i=1;i<=29;i++)
    for(int j=1;j<=29;j++)
    {
        if(n[i][j]>=10&&n[i][j]<50&&n[i][j]!=30) n[i][j]++;
        if(n[i][j]==50) {n[i][j]=31;if(m[i][j]==2) m[i][j]=0;}
        if(n[i][j]==45&&!(m[i][j]>=50&&m[i][j]<55)&&!(abs(Bx-i)<=1&&abs(By-i)<=1)) m[i][j]=2;
        if(n[i][j]>20&&n[i][j]<=30&&m[i][j]==0) n[i][j]=10;
        if(n[i][j]==20&&m[i][j]==0&&!(abs(Bx-i)<=1&&abs(By-i)<=1)) m[i][j]=1;
    }
}
int main()
{
    system("mode con cols=62 lines=34");
    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
    srand((unsigned)time(NULL));
    SSt: 
    Start();Bling();
    X=4,Y=8,gx=gy=0,gunT=1,gunZ=1,Lev=0,T;
    Blood=10,Dun=10,Bmax=10,Dmax=10;
    memset(G,0,sizeof(G)); memset(F,0,sizeof(F));
    GuaiQuan();
    St:
    Win=0;Bo=Boo=0;
    memset(m,0,sizeof(m));
    if(Lev%5==0&&Lev!=0) TianFu();
    Bling();T=0;Sheng();Map(1);int rr=rand()%3;
    if(F[5]==1) WuDi=60;else WuDi=30;
    if(rr==0&&F[10]==1) Blood=min(Blood+1,Bmax);
    if(F[16]==1) Bo=4;
    if(F[20]==1) {int Q=rand()%7+2;gunZ=Q,G[Q]=5;}
    while(Win<=0&&Blood>0&&Lev<25)
    {
        T++;
        if(bu>0) bu--;
        if(WuDi>0) WuDi--;
        if(WuDi==1) WuDi--,Map(4);
        if(Bo>0) BaoBo(5-Bo),Bo--;
        if(Boo>0) BaoBo(4-Boo),Boo--;
        if(F[18]==1)
        {
            int Rrr=rand()%30;
            if(Rrr==0)
            for(int i=X-2;i<=X+2;i++)
            for(int j=Y-2;j<=Y+2;j++) if(CanGo(i,j,5)&&i>0&&j>0) m[i][j]=9;
        }
        if(Dun<Dmax)
        {
            if(F[1]==1&&T%30==0) Dun++,Map(3);
            if(F[1]==0&&T%70==0) Dun++,Map(3);
        }
        if(GetAsyncKeyState(VK_UP)&0x8000) Map(2),gx--; 
        else if(GetAsyncKeyState(VK_DOWN)&0x8000) Map(2),gx++;
        else if(GetAsyncKeyState(VK_LEFT)&0x8000) Map(2),gy--;
        else if(GetAsyncKeyState(VK_RIGHT)&0x8000) Map(2),gy++;
        if(kbhit())
        {
            char g=_getch();
            if(g=='a') {Map(2); if(gunT!=1) gunT--;else gunT=8;}
            if(g=='d') {Map(2); if(gunT!=8) gunT++;else gunT=1;}
            if(g=='w') OpenBox(0);
            if(g=='s'&&bu<=2) Bullet(),bu+=2;
            if(g==' ') Sleep(100),SetPos(-1,18),sy++,system("pause");
        }
        if(sy==1) SetPos(-1,18),cout<<"                           ",sy--;
        if(T%2==0) Ci();
        Move();Map(0);Sleep(50);
    }
    if(Win==0&&Blood<=0&&Lev<25)
    {
        system("color 7F"),Color(4);Lev=0;Blood=Dun=Bmax=Dmax=10;
        Bblood=Bsi=Bjiao=Bdu=Bfang=0;
        memset(G,0,sizeof(G)); memset(F,0,sizeof(F));
        SetPos(2,2);cout<<"You! Die!!!",Sleep(1000);
        SetPos(3,2);cout<<"Please point 'y' to Play AGain.";
    }
    if(Lev<25) { A:char e=_getch();if(e=='y') goto St;else goto A;}
    if(Lev==25)
    {
        system("color 6E"),Color(5);
        SetPos(2,2),cout<<"You! Pass All The Level!!!";Sleep(3000);
        system("color 0F");system("cls");goto SSt;
    }
    return 0;
}
