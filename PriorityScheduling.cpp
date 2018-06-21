#include<bits/stdc++.h>
using namespace std;

struct process
{
    int pid[10];
    int at[10];
    int priority[10];
    int bt[10];   
};
int main()
{
    struct process p;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter process Details\n";
        cin>>p.pid[i]>>p.at[i]>>p.bt[i]>>p.priority[i];
    }
    int ct[5], tat[5], wt[5];
   
    bool visited[5];
    for(int i=0;i<n;i++)
    visited[i] = false;
    
    int overhead,sj;
    map<int,int> arrived;
    if(p.at[0]>=0)
        overhead = p.at[0] - 0;
    
    map<int,int>::iterator it; 
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(p.at[j]<=overhead)
            {
                if(visited[j]==false)
                arrived.insert(make_pair(p.priority[j],p.pid[j]));
            }
        }     
        it = arrived.begin();
        sj = it->second;
        ct[sj] =  overhead + p.bt[sj];
        overhead = ct[sj];
        visited[sj] = true;
        arrived.clear();
    }
    
    cout<<"COMPLETION TIME\n";
    for(int i=0;i<n;i++)
        cout<<p.pid[i]<<" : "<<ct[i]<<endl;
    
    cout<<"TURN AROUND TIME\n";
	for(int i=0;i<n;i++)
	{
		tat[i] = ct[i] - p.at[i];
		cout<<p.pid[i]<<" : "<<tat[i]<<endl;
	}
	
	cout<<"WAIT TIME\n";
	for(int i=0;i<n;i++)
	{
		wt[i] = tat[i] - p.bt[i];
		cout<<p.pid[i]<<" : "<<wt[i]<<endl;
	}       
    return 0;
}
