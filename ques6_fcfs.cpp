//6. Write a program to implement FCFS scheduling algorithm.

#include <iostream>
#include <stdlib.h>
using namespace std;

class Process 
{
	int pid;
	float arrivalTime;
	float burstTime;
	float completionTime;
	float waitingTime;
	float turnAroundTime;
	public:
		friend class fcfs;
};

class fcfs
{
	int n;
	Process *p;
	void calcCompletionTime();
	void calcTurnAroundTime();
	void calcWaitingTime();
	public:
		fcfs()
		{
			cout<<"Enter no of processes - ";
			cin>>n;
			p=new Process[n];
		}
		void input();
		void printAvgTime();
};

void fcfs::input()
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

void fcfs::calcCompletionTime()
{
	p[0].completionTime = p[0].burstTime;
	for(int i=1; i<n; ++i)
	{
		p[i].completionTime = p[i-1].completionTime + p[i].burstTime;
	}
}

void fcfs::calcTurnAroundTime()
{
	for(int i=0; i<n; ++i)
	{
    	p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
	}
}

void fcfs::calcWaitingTime()
{
	for(int i=0; i<n; ++i)
	{
    	p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
	}
}

void fcfs::printAvgTime()
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
	calcCompletionTime();
	calcTurnAroundTime();
	calcWaitingTime();

  	// Printing Process Info
  	cout<<endl<<endl;
  	cout << " FCFS CPU Scheduling" << endl;
	cout << " ----------------------------" << endl;
	cout<<"  PID\t turnaround time\t waiting time\t completion time";
	for(int i=0;i<n;i++)
	{
		cout<<endl;
		cout<<"   "<<p[i].pid<<"\t\t";
		cout<<p[i].turnAroundTime<<"\t\t\t";
		cout<<p[i].waitingTime<<"\t\t";
		cout<<p[i].completionTime;
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
	fcfs f;
	f.input();
	f.printAvgTime();
	return 0;
}
