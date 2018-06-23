#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	int res[10],max[10],need[10],available,temp,free,tempava,sum=0;
	cout<<"Enter number of process\n";
	cin>>n;
	
	/* Input for allocated and max resource for each process*/
	for(int i=0;i<n;i++)
		{
			cout<<"Enter resource and max for process"<<i<<endl;
			cin>>res[i]>>max[i];	
		}
	
	/* calculation of need for each process*/
	for(int i=0;i<n;i++)
		need[i] = max[i] - res[i];
	
	/*bool array to keep record of process that are completed*/	
	bool visited[10];
	for(int i=0;i<n;i++)
	visited[i] = false;
	
	/*Input for avalibale resource*/
	cout<<"Enter Available\n";
	cin>>available;
	tempava = available;
	 
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			{
				/*check if availble resource can satisfy the process selected and the proces
				is not already completed*/
				if(need[j]<available && visited[j] == false)
				{
					/*calculate the new available and mark the process as visted*/
					temp = available - need[j];
					free = res[j] + need[j];	
					available = free + temp;
					visited[j] = true;
				}
			}				
	}
	
	/*Check for correctnes
	if the sum of total allocated and available resource 
	is equal to new available after excution 
	then no deadlock*/
	for(int i=0;i<n;i++)
	sum+=res[i];
		
	if(sum+tempava == available)
	cout<<"Safe state";
	else
	cout<<"Unsafe state";
	return 0;
}
