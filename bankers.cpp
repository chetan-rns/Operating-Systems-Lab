#include<bits/stdc++.h>
using namespace std;
int allocation[100][100],maxm[100][100],need[100][100],n,m,work[100],available[100],safeSeq[100],request[100];
bool finish[100];

bool isSafe(){
	for(int i=0;i<n;i++)
   		for(int j=0;j<m;j++)
   			need[i][j]=maxm[i][j]-allocation[i][j];
   	for (int i = 0; i < n; ++i)
   	{
   		finish[i]=false;
   	}
   	for(int i=0;i<m;i++){
   		work[i]=available[i];
   	}
   	int complete = 0;
   	bool done =false;
   	while(complete<n){
   		done=false;
   		for(int p=0;p<n;p++){
   			if(finish[p]==false){
   				int i=0;
   				for(i=0;i<m;i++)
   					if(need[p][i]>work[i])
   						break;
   				if(i==m){
   					finish[p]=true;
   					safeSeq[complete++]=p;
   					for(int k=0;k<m;k++)
   						work[k]+=allocation[p][k];
   					done=true;
   				}
   			}
   		}
   		if(done==false)return false;
   	}
   	return true;
}
int main(){
   	cout<<"Enter the number of process\n";
   	cin>>n;
   	cout<<"Enter the number of resources\n";
   	cin>>m;
   	cout<<"Enter the alloted resource for each process\n";
   	for(int i=0;i<n;i++)
   		for(int j=0;j<m;j++)
   			cin>>allocation[i][j];
   	cout<<"Enter the max instances of resources required\n";
   	for(int i=0;i<n;i++)
   		for(int j=0;j<m;j++)
   			cin>>maxm[i][j];
   	cout<<"Enter the available instances of resources\n";
   	for (int i = 0; i < m; ++i)
   	{
   		cin>>available[i];
   	}
   	bool flag=isSafe();
   	if(flag){
   		cout<<"Enter the process which is requesting the resource\n";
   		int pNo;
   		cin>>pNo;
   		cout<<"Enter the instances of resources requested\n";
   		for (int i = 0; i < m; ++i)
   		{
   			cin>>request[i];
   		}
   		int i=0;
   		for (i = 0; i < m; ++i)
   		{
   			if(request[i]>need[pNo][i])break;
   		}
   		if(i==m){
   			int i=0;
   			for (i = 0; i < m; ++i)
   			{
   				if(request[i]>available[i])break;
   			}
   			if(i==m){
   				int i=0;
   				for (i = 0; i < m; ++i)
   				{
   					allocation[pNo][i]+=request[i];
   					available[i]-=request[i];
   				}
   				bool flag=isSafe();
   				if(flag){
   					cout<<"Safe sequence is:\n";
   					for (int i = 0; i < n; ++i)
   					{
   						cout<<safeSeq[i]<<" ";
   					}
   				}
   			}
   			else{
   				cout<<"REsources not available\n";
   			}
   		}
   		else{
   			cout<"Process has excluded its maximum claim\n";
   		}

   	}
   	else{
   		cout<<"NO safe sequence\n";
   	}
   	return 0;
}
/*
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2


7 5 3
3 2 2
9 0 2
2 2 2
4 3 3


*/