//9. Write a program to implement non-preemptive priority based scheduling algorithm.

#include <iostream>
#include <stdlib.h>
using namespace std;

class Process 
{
	int pid;
	int priority;
	float arrivalTime;
	float burstTime;
	float completionTime;
	float waitingTime;
	float turnAroundTime;
	public:
		friend class priority_np;
};

class priority_np
{
	int n;
	Process *p;
	void swapProcess(Process *a, Process *b);
	void sortForExec();
	void sortAccArrivalTime();
	void sortAccPID();
	void calcCompletionTime();
	void calcTurnAroundTime();
	void calcWaitingTime();
	public:
		priority_np()
		{
			cout<<"Enter no of processes - ";
			cin>>n;
			p=new Process[n];
		}
		void input();
		void printAvgTime();		
};

void priority_np::input()
{
	for(int i=0; i<n; ++i)
	{
		p[i].pid = i+1;
		cout << " Enter Priority of Process " << i+1 << ": ";
		cin >> p[i].priority;
		cout << " Enter Arrival Time of Process " << i+1 << ": ";
		cin >> p[i].arrivalTime;
		cout << " Enter Burst Time of Process " << i+1 << ": ";
		cin >> p[i].burstTime;
		cout << endl;
	}
}

void priority_np::swapProcess(Process *a, Process *b)
{
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void priority_np::sortForExec()
{
    for(int i=0; i < n-1; ++i)
    {
        if(p[i].arrivalTime > p[i+1].arrivalTime)
        {
            swapProcess(&p[i], &p[i+1]);
        }
        else if(p[i].arrivalTime == p[i+1].arrivalTime)
        {
            if(p[i].priority > p[i+1].priority)
				swapProcess(&p[i], &p[i+1]);
			else if(p[i].priority == p[i+1].priority)
        	{
            	if(p[i].pid > p[i+1].pid)
					swapProcess(&p[i], &p[i+1]);
        	}
        }
    }
}

void priority_np::sortAccPID()
{
    for(int i=0; i < n-1; ++i)
    {
        if(p[i].pid > p[i+1].pid)
        {
            swapProcess(&p[i], &p[i+1]);
        }
    }
}

void priority_np::calcCompletionTime()
{
    p[0].completionTime = p[0].burstTime;
	for(int i=1; i<n; ++i)
	{
		p[i].completionTime = p[i-1].completionTime + p[i].burstTime;
  	}
}

void priority_np::calcTurnAroundTime()
{
	for(int i=0; i<n; ++i)
  	{
    	p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
  	}
}

void priority_np::calcWaitingTime()
{
  	for(int i=0; i<n; ++i)
  	{
    	p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
  	}
}

void priority_np::printAvgTime()
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
	
	sortForExec();
	calcCompletionTime();
    sortAccPID();
	calcTurnAroundTime();
	calcWaitingTime();

  	// Printing Process Info
  	cout<<endl<<endl;
	cout << " Non-preemptive Priority Based CPU Scheduling" << endl;
	cout << " ------------------------------------------------" << endl;
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
	priority_np pr;
	pr.input();
	pr.printAvgTime();
	return 0;
}
