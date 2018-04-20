//revised from http://blog.sina.com.cn/s/blog_6bb1b4b001016pt0.html
#include "bits/stdc++.h"
#include<time.h>
#define NumberOfAnts 30
#define N 34//number of cities
#define NcMax 200 //number of iteration
#define InitPheronone 2
#define MAX 0x7fffffff

struct cityNode
{
    char cityName[15];
    int x;
    int y;
}city[N];
double adjacentGraph[N][N];
double phe[N][N];
double add[N][N];
double yita[N][N];//h function,yita[i][j]=1/adjacentGraph[i][j]
double doubleRand,pro,psum;
double alpha,beta,rou,Q;
double bestsolution=MAX;
double solution[NumberOfAnts];
int visit[NumberOfAnts][N];
int antMap[NumberOfAnts][N];
int bestway[N];
int NC=0;
int s;
int cityRand;


void Init()
{
    alpha=2;
    beta=4;
    rou=0.6;
    Q=500;
    return;
}

void InputCityFile(FILE *fp)
{
    int i;
    int number;
    if(fp==NULL)
    {
        printf("File not exist\n");
        exit(1);
    }
    else
    {
        for(i=0; i<N; ++i)
        {
            fscanf(fp,"%d,%d,%d,%s",&number,&city[i].x,&city[i].y,city[i].cityName);
        }
    }
}

void CreateAdjacentGraph( )
{
    double disSquare;
    for(int i=0; i<N-1; ++i)
    {
        adjacentGraph[i][i]=MAX;
        for(int j=i+1; j<N; ++j)
        {
            disSquare=(double)((city[i].x-city[j].x)*(city[i].x-city[j].x)+(city[i].y-city[j].y)*(city[i].y-city[j].y));
            adjacentGraph[j][i]=adjacentGraph[i][j]=sqrt(disSquare);
        }
    }
    adjacentGraph[N-1][N-1]=MAX;
    return;
}

double Distance(int *p)
{
    double distance=0;
    int i;
    for(i=0; i<N-1; ++i)
    {
        distance+=adjacentGraph[*(p+i)][*(p+i+1)];
    }
    distance+=adjacentGraph[*(p+i)][*(p)];
    return distance;
}

void Result1()
{
    FILE *fl;
    fl = fopen("result.txt","a");
    fprintf(fl,"%s %.4lf\n","The best length:",bestsolution);
    fprintf(fl,"%s\n","The best way:");
    for(int i=0; i<N; ++i)
        fprintf(fl,"%d ",bestway[i]);
    fprintf(fl,"%d",bestway[0]);
    fprintf(fl,"\n\n");
    fclose(fl);
    std::cout << "result has been stored into the result.txt" << std::endl;
    return;
}

void Result2()
{
    FILE *fl;
    fl = fopen("out.txt","a");
    for(int i=0; i<N; ++i)
        fprintf(fl,"%d ",bestway[i]);
    fprintf(fl,"%d",bestway[0]);
    fprintf(fl,"\n");
    fclose(fl);
    return;
}

void Result3()
{
    FILE *fl1;
    fl1 = fopen("outmap.txt","a");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fprintf(fl1, "%.4f ", phe[i][j]);
        }
        fputc('\n', fl1);
    }
    fprintf(fl1,"\n\n\n");
    fclose(fl1);
}

void Result4()
{
    std::cout << "The best length:" << bestsolution << std::endl;
    std::cout << "The best way:" << std::endl;
    for(int i=0; i<N; ++i)
        std::cout << bestway[i] << ' ';
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "The city name:" << std::endl;
    for(int i=0; i<N; ++i)
        std::cout << city[bestway[i]].cityName << ' ';
    std::cout << std::endl;
    std::cout << std::endl;
}

void AntColonyAlgo()
{
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            phe[i][j]=InitPheronone;
            if(i!=j)
            yita[i][j]=100.0/adjacentGraph[i][j];
        }
    }
    memset(antMap,-1,sizeof(antMap));
    memset(visit,0,sizeof(visit));
    srand(time(NULL));
    while(NC++ < NcMax)
    {
        for(int k=0; k<NumberOfAnts; ++k)
        {
            cityRand=rand();
            antMap[k][0]=(cityRand)%N;
            visit[k][antMap[k][0]]=1;
        }
        s=1;
        while(s<N)
        {
            for(int k=0; k<NumberOfAnts; ++k)
            {
                psum=0;
                for(int j=0; j<N; ++j)
                {
                    if(visit[k][j]==0)
                    {
                        psum = psum + pow(yita[antMap[k][s-1]][j],beta) * pow(phe[antMap[k][s-1]][j],alpha);
                    }
                }
                doubleRand=(double)(rand()%5000);
                doubleRand/=5000.0;
                pro=0;
                int j;
                for(j=0; j<N; ++j)
                {
                    if(visit[k][j]==0)
                    {
                        pro = pro + pow(yita[antMap[k][s - 1]][j],beta) * pow(phe[antMap[k][s - 1]][j],alpha) / psum;
                    }
                    if(pro>doubleRand)
                    break;
                }
                visit[k][j]=1;
                antMap[k][s]=j;
            }
            s++;
        }
        memset(add,0,sizeof(add));
        for(int k=0; k<NumberOfAnts; ++k)
        {
            solution[k]=Distance(antMap[k]);
            if(solution[k]<bestsolution)
            {
                bestsolution=solution[k];
                for(int i=0; i<N; ++i)
                    bestway[i]=antMap[k][i];//record the best way
            }
        }
        for(int k=0; k<NumberOfAnts; ++k)
        {
            for(int j=0; j<N-1; ++j)
            {
                add[antMap[k][j]][antMap[k][j+1]]+=Q/solution[k];
            }
            add[N-1][0]+=Q/solution[k];
        }
        for(int i=0; i<N; ++i)
        {
            for(int j=0; j<N; ++j)
            {
                phe[i][j]=phe[i][j] * rou+add[i][j];//update the phe gain
                if(phe[i][j]<0.0001)//lower bound
                    phe[i][j]=0.0001;
                else if(phe[i][j]>2)//upper bound
                    phe[i][j]=2;
            }
        }
        // if(NC%10 == 0){
        //     Result3();
        // }
        // if(NC%1000 == 0 || NC<100) {
        //     Result2();
        //     std::cout << 1;
        // }

        memset(visit,0,sizeof(visit));
        memset(antMap,-1,sizeof(antMap));
    }
}

int main()
{
    clock_t startTime,endTime;
    startTime = clock();
    FILE *fp;
    Init();
    fp = fopen("china_cities_pos_province.csv","r+");
    InputCityFile(fp);
    CreateAdjacentGraph();
    fclose(fp);
    AntColonyAlgo();
    Result4();
    Result1();
    std::cout << "Totle Time: " <<(double)(endTime - startTime) / 1000000 << "s" << std::endl;
    return 0;
}
