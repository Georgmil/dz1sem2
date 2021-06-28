#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
void middel(float a1x,float a1y, float a2x, float a2y,int value);
void dijkstra(int matrica[20][20],int len,float vershina[20][20]);

int main(){

    float b, angle;
    int a,matrica[20][20];
    printf("Enter how many tops do you want:\n");
    scanf("%d",&a);
    b=360/a;

    printf("Zapolnite takuju tablicu kak nizhe: numeratsiju versjin na pervoj stroke i stolbtse ne nado\n");
    for(int i=1;i<=a;i++){
        printf("  %d",i);}
    printf("\n");
    for(int j=1;j<=a;j++){
        printf("%d\n\n",j);}
    for(int i=1;i<=a;i++){
        for(int j=1;j<=a;j++){
            scanf("%d",&matrica[i][j]);
        }
    }
    printf("\n\n");

    int width=1200,height=700;
    int centerw,centerh,radius;
    centerw=width/2;
    centerh=height/2;
    radius=centerw/2;

    initwindow(width,height); // razmer ekrana
    setbkcolor(BLACK);    // tsvet fona
    //cleardevice(); // chtobi fon narisovalsja

    setlinestyle(0,0,1); // tolshina linij
    setcolor(WHITE);//tsvet linij

    // Risuem vershini
    char str[20];
    for(int i=1;i<=a;i++){
        sprintf(str,"%d",i);
        angle=b*i*M_PI/180;
        circle(radius*(cos(angle))+centerw,-radius*(sin(angle))+centerh,25);
        outtextxy(radius*(cos(angle))+centerw,-radius*(sin(angle))+centerh-45,str);
    }
    float vershina[20][20];
    for(int i=1;i<=a;i++){
        for(int j=i;j<=a;j++){
            if (matrica[i][j]!=0){
                float ang2,ang3;
                ang2=b*i*M_PI/180;
                ang3=b*j*M_PI/180;
                line(radius*(cos(ang2))+centerw,-radius*(sin(ang2))+centerh,(radius)*(cos(ang3))+centerw,-(radius)*(sin(ang3))+centerh);
                vershina[i][0]=radius*(cos(ang2))+centerw;
                vershina[i][1]=(-radius*(sin(ang2)))+centerh;
                vershina[j][0]=(radius)*(cos(ang3))+centerw;
                vershina[j][1]=-(radius)*(sin(ang3))+centerh;
                middel(radius*(cos(ang2))+centerw,-radius*(sin(ang2))+centerh,(radius)*(cos(ang3))+centerw,-(radius)*(sin(ang3))+centerh,matrica[i][j]);
                }

        }
    }
    outtext("Nazhimite na ekran i zatem lubuju klavishu, chtobi zaputit algoritm dejikstra");
    getch();
    dijkstra(matrica,a,vershina);
    getch();
    cleardevice();
    closegraph();

return 0;
}


void middel(float a1x,float a1y, float a2x, float a2y,int value){
    float startx=a1x, starty=a1y, endx=a2x,endy=a2y;
    float len=0.5;

    float vektorx=(endx-startx)*len, vektory=(endy-starty)*len;
    float vektorstartx=(endx-startx)-vektorx, vektorstarty=endy-starty-vektory;
    float pointx=startx+vektorstartx, pointy=starty+vektorstarty;
    char str1[10];
    sprintf(str1,"%d",value);
    outtextxy(pointx,pointy,str1);
}
void dijkstra(int matrica[20][20],int len,float vershina[20][20]){
    int cost[20][20];
    int dist[20];
    int pred[20];
    int visited[20];
    int nextnode,shet,mindst,j,i,start=1;

    for(i=1;i<=len;i++){
        for(j=1;j<=len;j++){
            if(matrica[i][j]==0){
                cost[i][j]=99999;}
            else{
                cost[i][j]=matrica[i][j];
            }
        }
    }
    for(i=1;i<=len;i++){
        dist[i]=cost[start][i];
        pred[i]=start;
        visited[i]=0;
    }
    dist[start]=0;
    visited[start]=1;
    shet=2;

    while(shet<len){
        mindst=99999;
        for(int i=1;i<=len;i++){
            if(dist[i]<mindst&&!visited[i]){
                mindst=dist[i];
                nextnode=i;
            }
        }
        visited[nextnode]=1;
        for(int i=1;i<=len;i++){
            if(!visited[i]){
                if((mindst+cost[nextnode][i])<dist[i]){
                    dist[i]=mindst+cost[nextnode][i];
                    pred[i]=nextnode;
                }
            }
        }shet++;

    }
    int zap;
    for(int i=1;i<=len;i++){
        if(i!=start){
            printf("\n Dlina puti do vershini %d = %d", i, dist[i]);
			printf("\nSamij karotkij put do etoj verhini = %d", i);
			j=i;
			do{
                zap=j;
                j=pred[j];
                setlinestyle(0,0,1);
                setcolor(YELLOW);
                line(vershina[j][0],vershina[j][1],vershina[zap][0],vershina[zap][1]);

                printf("<- %d",j);
			}
			while(j!=start);
        }
    }

}


