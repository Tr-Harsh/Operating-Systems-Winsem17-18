#include<bits/stdc++.h>
using namespace std;

struct process
{
    int pid[10];
    int at[10];
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
        cin>>p.pid[i]>>p.at[i]>>p.bt[i];
    }
    int ct[5], tat[5], wt[5] , tempbt[5];
   
    bool visited[5];
    for(int i=0;i<n;i++)
    visited[i] = false;  
    
    for(int i=0;i<n;i++)
    tempbt[i] = p.bt[i];  

    int overhead,sj,finished=0; 
    map<int,int> arrived;
    if(p.at[0]>=0)
        overhead = p.at[0] - 0;  
    
    int temp = overhead;
    
    map<int,int>::iterator it; 
    while(finished!=n)        
    {
        for(int j=0;j<n;j++) 
        {
            if(p.at[j]<=overhead)
            {
                if(visited[j]==false)  
                arrived.insert(make_pair(p.bt[j],p.pid[j]));  /*push remaining burst times of all the process as key and pid as value into 
                											  map.It is the only change we have to make from pre-emptive prioriy 																  scheduling.Since the sorting is done based on remaining burst time. */
            }
        }
        it = arrived.begin();
        sj = it->second;  
        if(p.bt[sj]<=0)  
        {
        	ct[sj] = overhead - finished; 
        	visited[sj] = true;  
        	finished++;  
        }
        p.bt[sj]--; 
        overhead++; 
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
		wt[i] = tat[i] - tempbt[i];
		cout<<p.pid[i]<<" : "<<wt[i]<<endl;
	}       
    return 0;
}
