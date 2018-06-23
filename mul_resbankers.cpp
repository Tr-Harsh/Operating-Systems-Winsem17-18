#include<bits/stdc++.h>
using namespace std;
    
/*function to check if the available resource can satisfy the need of process															 any process j by substracting the availabe and need and if it is negative then 															it cannot*/
bool check(int j,int m,int available[10],int need[10][10])
{	
	int s=1;
	for(int i=0;i<m;i++)
		if( (available[i] - need[j][i])<0)
			{
				s = 0;
				break;
			}
	if(s==0)
	return false;
	else
	return true;
	
}
int main()
{
	int n,m;
	int res[10][10],max[10][10],need[10][10],available[10],temp[10],free[10],tempava[10],sum=0;
	cout<<"Enter number of process\n";
	cin>>n;
	cout<<"Enter number of resources for each process\n";
	cin>>m;
	
	/*Input for resource for each process*/
	for(int i=0;i<n;i++)
	{
		cout<<"Enter resource for process "<<i<<endl;
		for(int j=0;j<m;j++)
		{
			cin>>res[i][j];	
		}
	}
	/*Input for max resource for each process*/
	for(int i=0;i<n;i++)
	{
		cout<<"Enter max for process "<<i<<endl;
		for(int j=0;j<m;j++)
		{
			cin>>max[i][j];	
		}
	}
	
	/*calculate the need for each process*/
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			need[i][j] = max[i][j] - res[i][j];
	
	/*we need bool array to mark process which are already completed*/	
	bool visited[10];
	for(int i=0;i<n;i++)
	visited[i] = false;
	
	/*Input for available resource*/
	cout<<"Enter Available\n";
	for(int i=0;i<m;i++)
	{
		cin>>available[i];
		tempava[i] = available[i];
	} 
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			{
				/*check the process if the available resource can satisfy its need and its not already completed*/
				if(check(j,m,available,need) && visited[j] == false)
				{
					cout<<"Process selected : "<<j<<endl;
					/* mark it is as completed*/
					visited[j] = true;
					for(int k=0;k<m;k++)
					{
						/*compute the new available resources after the selected process j is completed*/
						temp[k] = available[k] - need[j][k];
						free[k] = res[j][k] + need[j][k];	
						available[k] = free[k] + temp[k];
					}
				}
			}				
	}
	
	/*Check whether the execution of process did not resulted in deadlock by calculating 
	the total resources + available resources before execution and available resource after execution
	that is they should be equal*/
	int count = 0;
	for(int k=0;k<m;k++)
	{	
		sum = 0;
		for(int i=0;i<n;i++)
			{
				sum+=res[i][k];
			}
		if( sum + tempava[k] == available[k])
			count++;		
	}
	if(count == m)
	cout<<"Safe state";
	else
	cout<<"Unsafe state";
	return 0;
}
