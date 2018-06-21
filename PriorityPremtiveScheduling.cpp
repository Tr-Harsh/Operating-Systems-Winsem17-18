#include<bits/stdc++.h>
using namespace std;
//processes with lowest priority are given precedence
/*pid needs to be from 0 as if not then to implement that part we have to make a map with key as pid and all other values in array/vector as 
its value which is complicated and slow process*/
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
    int ct[5], tat[5], wt[5] , tempbt[5];
   
    bool visited[5];
    for(int i=0;i<n;i++)
    visited[i] = false;  //make a bool array to note which processes are completed
    
    for(int i=0;i<n;i++)
    tempbt[i] = p.bt[i]; /*copying burst time into temp array as bt will be changed during processing and we need original bt values
						 for calculating Wait time*/    

    int overhead,sj,finished=0; //we need finished variable for our outer loop to stop when all process are completed
    map<int,int> arrived;
    if(p.at[0]>=0)
        overhead = p.at[0] - 0;  //calculate the initial overhead that if first process doesn't arrive at zero seconds   
    int temp = overhead;  
    map<int,int>::iterator it; 
    while(finished!=n)    //checks each time that if all processes are finished executing or not
    {
        for(int j=0;j<n;j++) //for pushing process that have arrived into map. since it is a map it'll sort itself A/C to key
        {
            if(p.at[j]<=overhead)  //push all the process that have arrival time less than current time into map 
            {
                if(visited[j]==false)  //to check if they are not finished execution already
                arrived.insert(make_pair(p.priority[j],p.pid[j]));  //push priority as key and pid as value into map
            }
        }
        it = arrived.begin();
        sj = it->second;  //return the process with lowest priority into sj variable
        if(p.bt[sj]<=0)  //check if process is finished
        {
        	ct[sj] = overhead - finished; //calculate completion time if process is finished
        	visited[sj] = true;  //mark it as finished
        	finished++;  //increment total process which have finished 
        }
        p.bt[sj]--;  //decrement burst time of process if not finished
        overhead++; //increase current time by 1
        arrived.clear(); //clear all map values
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
