//8. Write a program to implement SJF scheduling algorithm.

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
		friend class sjf_np;
};

class sjf_np
{
	int n;
	Process *p;
	void swapProcess(Process *a, Process *b);
	void sortAccArrivalTime();
	void sortAccPID();
	void calcCompletionTime();
	void calcTurnAroundTime();
	void calcWaitingTime();
	public:
		sjf_np()
		{
			cout<<"Enter no of processes - ";
			cin>>n;
			p=new Process[n];
		}
		void input();
		void printAvgTime();
};

void sjf_np::input()
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

void sjf_np::swapProcess(Process *a, Process *b)
{
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sjf_np::sortAccArrivalTime()
{
    for(int i=0; i < n-1; ++i)
    {
        if(p[i].arrivalTime > p[i+1].arrivalTime)
        {
            swapProcess(&p[i], &p[i+1]);
        }
    }
}

void sjf_np::sortAccPID()
{
    for(int i=0; i < n-1; ++i)
    {
        if(p[i].pid > p[i+1].pid)
        {
            swapProcess(&p[i], &p[i+1]);
        }
    }
}

void sjf_np::calcCompletionTime()
{
    float minBurstTime = p[0].burstTime;
    p[0].completionTime = minBurstTime + p[0].arrivalTime;
    int temp;

    for(int i=1; i < n; ++i)
    {
        temp = i;
        minBurstTime = p[i].burstTime;
        for(int j=i; j < n; j++)
        {
            if(p[i-1].completionTime >= p[j].arrivalTime && minBurstTime > p[j].burstTime)
            {
                minBurstTime = p[j].burstTime;
                temp = j;
            }
        }
        p[temp].completionTime = p[i-1].completionTime + p[temp].burstTime;
        swapProcess(&p[temp], &p[i]);
    }
}

void sjf_np::calcTurnAroundTime()
{
	for(int i=0; i<n; ++i)
  	{
    	p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
  	}
}

void sjf_np::calcWaitingTime()
{
  	for(int i=0; i<n; ++i)
  	{
    	p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
  	}
}

void sjf_np::printAvgTime()
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
	calcCompletionTime();
	calcTurnAroundTime();
	calcWaitingTime();
    sortAccPID();

  	// Printing Process Info
	cout<<endl<<endl;
	cout << " SJF CPU Scheduling" << endl;
	cout << " ------------------------------" << endl;
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
	sjf_np s;
	s.input();
	s.printAvgTime();
	return 0;
}
