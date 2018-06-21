#include<bits/stdc++.h>
using namespace std;

void *fcfs(void* args);
void *sjf(void* args);

double et1;
double et2;
double avgwt1=0.0;
double avgwt2=0.0;
struct process
{
    int pid[10];
    int at[10];
    int bt[10];   
};

int main()
{
	pthread_t p1,p2;
	pthread_create(&p1,NULL,&fcfs,NULL);
	pthread_join(p1,NULL);
	pthread_create(&p2,NULL,&sjf,NULL);
	pthread_join(p2,NULL);	
	
	cout<<"FCFS took: "<<et1<<" and average wait time was "<<avgwt1<<endl;
	cout<<"SJF took: "<<et2<<" and average wait time was "<<avgwt2 <<endl;
	
}

void *fcfs(void *args)
{
	clock_t t1,t2;
	t1 = clock();
    int n;
    cout<<"Enter number of processes in FCFS\n";
    cin>>n;
	struct process p;
	int ct[10],tat[10],wt[10];
	
	for(int i=0;i<n;i++)
	{
		cout<<"Enter process details\n";
		cin>>p.pid[i];
		cin>>p.at[i];
		cin>>p.bt[i];
	}
	int overhead;
	if(p.at[0]!=0)
	{
		overhead = p.at[0] - 0;  //calculate the initial overhead
	}
	for(int i=0;i<n;i++)
	{
		if(p.at[i]<=overhead)    //all the jobs having arrival time less than the time lapsed
		{
		ct[i] = overhead + p.bt[i];  
		overhead = ct[i];        // update the time lapsed 
		}
	}
	for(int i=0;i<n;i++)
	{
		tat[i] = ct[i] - p.at[i];
	}
		
	for(int i=0;i<n;i++)
	{
		wt[i] = tat[i] - p.bt[i];
		avgwt1+=(double)wt[i]/n;
	}
	t2 = clock();
	et1 = (double)(t2-t1)/CLOCKS_PER_SEC;
	cout<<"FCFS Process Exited\n";
	pthread_exit(0);
}

void* sjf(void* args)
{
	clock_t t1,t2;
	t1 = clock();
    int n;
    cout<<"\nEnter number of process in SJF\n";
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

    for(int i=0;i<n;i++)
	{
		tat[i] = ct[i] - p.at[i];
	}
	
	for(int i=0;i<n;i++)
	{
		wt[i] = tat[i] - p.bt[i];
		avgwt2 += (double)wt[i]/n;
	}
	t2 = clock();
	et2 = (double)(t2-t1)/CLOCKS_PER_SEC;
	cout << "SJF Process Exited\n";
	pthread_exit(0);
}

/*

Enter number of processes in FCFS
2
Enter process details
0 2 4
Enter process details
1 3 2
FCFS Process Exited

Enter number of process in SJF
2
Enter process Details
0 2 4
Enter process Details
1 3 2
SJF Process Exited
FCFS took: 0.000422 and average wait time was 1.5
SJF took: 0.000362 and average wait time was 1.5


*/
