//7. Write a program to implement round robin scheduling algorithm.

#include <iostream>
#include <stdlib.h>
using namespace std;

class Process 
{
	int pid;
	float arrivalTime;
	float burstTime;
	float waitingTime;
	float turnAroundTime;
	public:
		friend class round_robin;
};

class round_robin
{
	int n;
	int quantum;
	Process *p;
	void sortAccArrivalTime();
	void sortAccPID();
	void calcTurnAroundTime();
	void calcWaitingTime();
	public:
		round_robin()
		{
			cout<<"Enter no of processes - ";
			cin>>n;
			p=new Process[n];
			cout<<"Enter quantam time - ";
			cin>>quantum;
		}
		void input();
		void printAvgTime();
};

void round_robin::input()
{
	for(int i=0; i<n; ++i)
	{
		p[i].pid = i+1;
		cout << " Enter Arrival Time of Process " << i+1 << ": ";
		cin >> p[i].arrivalTime;
		cout << " Enter Burst Time of Process " << i+1 << ": ";
		cin >> p[i].burstTime;
		cout << endl;
	}
}

void round_robin::sortAccArrivalTime()
{
    for(int i=0,j,least;i<n-1;i++)
	{
		for(j=i+1,least=i;j<n;j++)
		{
			if(p[j].arrivalTime<p[least].arrivalTime)
				least=j;
		}
		Process temp=p[least];
		p[least]=p[i];
		p[i]=temp;
	}
}

void round_robin::sortAccPID()
{
    for(int i=0,j,least;i<n-1;i++)
	{
		for(j=i+1,least=i;j<n;j++)
		{
			if(p[j].pid<p[least].pid)
				least=j;
		}
		Process temp=p[least];
		p[least]=p[i];
		p[i]=temp;
	}
}

void round_robin::calcWaitingTime()
{
	float *remainingTime = new float[n];
	for(int i=0; i<n; ++i)
		remainingTime[i] = p[i].burstTime;

	float temp = 0;
	
	while(true)
	{
		int flag = 1;
		for(int i=0; i<n; ++i)
		{
			if (remainingTime[i] > 0)
			{
				flag = 0;
				if (remainingTime[i] > quantum)
				{
					temp += quantum;
					remainingTime[i] -= quantum;
				}
				else
				{
					temp += remainingTime[i];
					p[i].waitingTime += temp - p[i].arrivalTime - p[i].burstTime;
					remainingTime[i] = 0;	
				}
			}
  		}
		if (flag ==1) break;
  	}
}

void round_robin::calcTurnAroundTime()
{
	for(int i=0; i<n; ++i)
  	{
    	p[i].turnAroundTime = p[i].waitingTime + p[i].burstTime - p[i].arrivalTime;
  	}
}

void round_robin::printAvgTime()
{
	cout<<endl<<endl;
	cout<<"  PID	\t arrival time	\t burst time";
	for(int i=0;i<n;i++)
	{
		cout<<endl;
		cout<<"   "<<p[i].pid<<"\t\t\t";
		cout<<p[i].arrivalTime<<"\t\t\t";
		cout<<p[i].burstTime<<"\t\t\t";
		cout<<endl;
	}
	cout<<endl;
	sortAccArrivalTime();
	calcWaitingTime();
	calcTurnAroundTime();
	sortAccPID();

  	// Printing Process Info
  	cout<<endl<<endl;
	cout << " Round Robin CPU Scheduling" << endl;
	cout << " ------------------------------" << endl;
  	cout<<"  PID\t turnaround time\t waiting time";
	for(int i=0;i<n;i++)
	{
		cout<<endl;
		cout<<"   "<<p[i].pid<<"\t\t";
		cout<<p[i].turnAroundTime<<"\t\t\t";
		cout<<p[i].waitingTime;
		cout<<endl;
	}

  	// Calculating sum of waitingTime and turnAroundTime
  	float sumW = 0.0;
  	float sumT = 0.0;
  	for (int i=0; i<n; ++i)
  	{
    		sumW += p[i].waitingTime;
    		sumT += p[i].turnAroundTime;
  	}

  	// Printing average waitingTime and turnAroundTime
  	cout << "\n Average Waiting Time: " << sumW/n;
  	cout << "\n Average Turn Around Time: " << sumT/n << endl;
}

int main()
{
	round_robin r;
	r.input();
	r.printAvgTime();
	return 0;
}
