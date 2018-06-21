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
    int n;
    cout<<"Enter number of process\n";
    cin>>n;
    struct process p;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter process Details\n";
        cin>>p.pid[i]>>p.at[i]>>p.bt[i];
    }
    int ct[5], tat[5], wt[5];
    
    bool visited[5];
    for(int i=0;i<n;i++)
    visited[i] = false;    //make a bool array to store which jobs are completed and which are not
    
    int overhead,sj;
    map<int,int> arrived;
    if(p.at[0]>=0)
        overhead = p.at[0] - 0;  //calculate the initial overhead
    
    map<int,int>::iterator it; 
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(p.at[j]<=overhead)   //all the jobs that have arrived during the time lapsed
            {
                if(visited[j]==false)  //if the job is not completed already
                arrived.insert(make_pair(p.bt[j],p.pid[j]));  //insert the burst time as key and pid as value
            }
        }    
        it = arrived.begin();  //since map are already sorted a/c to key which is BT 
        sj = it->second;      // store the job with shortest BT in variable sj
        ct[sj] =  overhead + p.bt[sj];  //calculate the CT for that job
        overhead = ct[sj];   //increase the time lapsed in execution
        visited[sj] = true;   // mark the job as completed
        arrived.clear();    //clear the map
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
