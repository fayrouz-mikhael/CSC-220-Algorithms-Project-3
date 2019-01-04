#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
using namespace std;

bool BFS (vector <vector<int> > graph , int s , int t ,int n , int patharray[]){
    struct rlimit core_limits;
    core_limits.rlim_cur = core_limits.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);
    
    bool marked[n];
    memset(marked,0,sizeof(marked));
    std :: queue <int> q;
    q.push(s);
    marked[s] = true;
    patharray[s]=-1;
    
    while (!q.empty()){
        int y = q.front();
        q.pop();
        for (int i = 0 ; i < n ; i++){
            if (marked[i]==false &&graph[y][i]) //*(graph + y*n + i) > 0) // *(graph + y*n + i)
            {
                q.push(i);
                patharray[i] = y;
                marked[i] = true;
            }
        }
    }
    
    return (marked[t] == true);
}


void maximum_flow(int n, int s, int t, int *cap, int *flow)
{
    
    struct rlimit core_limits;
    core_limits.rlim_cur = core_limits.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);
    
    vector <vector<int> > ResidualCap;
    vector <vector<int> > currflow;
    vector<int> ResidualCaptmp, currflowtmp;
    int maxflow=0, i, j;
    int path[n];  // new int[n];
    
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            ResidualCaptmp.push_back(0);
            currflowtmp.push_back(  *(cap + i*n + j)  );
        }
        currflow.push_back (ResidualCaptmp) ;
        ResidualCap.push_back (currflowtmp);
        ResidualCaptmp.clear();
        currflowtmp.clear();
        
    }
    
    while( BFS( (ResidualCap), s,t,n,path))
    {
        
        int path_flow = INT_MAX;
        for(j = t; j != s; j= path[j])
        {
            i= path[j];
            path_flow = std::min(path_flow , ResidualCap[i][j]);
        }
        for(j = t; j != s; j= path[j])
        {
            i= path[j];
            ResidualCap[i][j] -= path_flow;
            ResidualCap[j][i] += path_flow;
            currflow[j][i]  += path_flow;
        }
        maxflow += path_flow;
    }
    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            *(flow + i*n + j)= currflow[j][i];
        }
}

/*int main(void)
{  int cap[1000][1000], flow[1000][1000];
    int i,j, flowsum;
    for(i=0; i< 1000; i++)
        for( j =0; j< 1000; j++ )
            cap[i][j] = 0;
    
    for(i=0; i<499; i++)
        for( j=i+1; j<500; j++)
            cap[i][j] = 2;
    for(i=1; i<500; i++)
        cap[i][500 + (i/2)] =4;
    for(i=500; i < 750; i++ )
    { cap[i][i-250]=3;
        cap[i][750] = 1;
        cap[i][751] = 1;
        cap[i][752] = 5;
    }
    cap[751][753] = 5;
    cap[752][753] = 5;
    cap[753][750] = 20;
    for( i=754; i< 999; i++)
    {  cap[753][i]=1;
        cap[i][500]=3;
        cap[i][498]=5;
        cap[i][1] = 100;
    }
    cap[900][999] = 1;
    cap[910][999] = 1;
    cap[920][999] = 1;
    cap[930][999] = 1;
    cap[940][999] = 1;
    cap[950][999] = 1;
    cap[960][999] = 1;
    cap[970][999] = 1;
    cap[980][999] = 1;
    cap[990][999] = 1;
    
    printf("prepared capacity matrix, now executing maxflow code\n");
    
    maximum_flow(1000,0,999,&(cap[0][0]),&(flow[0][0]) );
    
    for(i=0; i<=999; i++)
        for(j=0; j<=999; j++)
        {  if( flow[i][j] > cap[i][j] )
        {  printf("Capacity violated\n"); exit(0);}
        }
    for(i=0; i<=999; i++)
        for(j=0; j<=999; j++)
        {  if( flow[i][j] < 0 )
        {  printf("Flow value negative\n"); exit(0);}
        }
    for(i=1; i<999; i++)
    {  int inflow, outflow;
        inflow = 0;
        for( j=0; j <= 999; j++ )
            inflow += flow[j][i];
        outflow = 0;
        for( j=0; j <= 999; j++ )
            outflow += flow[i][j];
        if( inflow != outflow )
        {  printf("Flow conservation fails at vertex %d\n",i); exit(0);}
    }
    printf("Flow is a valid flow\n");
    flowsum = 0;
    for(i=0; i<=999; i++)
        flowsum += flow[0][i];
    printf("Outflow of  0 is %d, should be 10\n", flowsum);
    flowsum = 0;
    for(i=0; i<=999; i++)
        flowsum += flow[i][999];
    printf("Inflow of 999 is %d, should be 10\n", flowsum);
    
    printf("End Test\n");
    
}*/

