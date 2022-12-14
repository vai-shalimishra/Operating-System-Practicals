//13. Write a program to implement first-fit, best-fit and worst-fit allocation strategies.

#include <cstring>
#include <iostream>
using namespace std;

void firstFit(int blockSize[], int m, int processSize[], int n);
void bestFit(int blockSize[], int m, int processSize[], int n);
void worstFit(int blockSize[], int m, int processSize[], int n);

int main()
{
  int blocks, processes;

  cout << "\nEnter Number of Blocks: ";
  cin >> blocks;
  cout << "Enter Number of Processes: ";
  cin >> processes;
  
  int blockSizes[blocks], processSizes[processes];

  for (int i = 0; i < blocks; i++)
  {
    cout << "Enter Size of Block " << (i + 1) << ": ";
    cin >> blockSizes[i];
  }

  for (int i = 0; i < processes; i++)
  {
    cout << "Enter Size of Process " << (i + 1) << ": ";
    cin >> processSizes[i];
  }
  
  int ch;
  do
  {
  	cout<<"\nChoose any of the following alloaction strategies to apply - ";
  	cout<<"\n1. FIRST-FIT";
  	cout<<"\n2. BEST-FIT";
  	cout<<"\n3. WORST-FIT";
  	cout<<"\n4. EXIT";
  	cout<<"\n Enter your choice - ";
  	cin>>ch;
  	switch(ch)
  	{
  		case 1: firstFit(blockSizes, blocks, processSizes, processes);
  				break;
  		case 2: bestFit(blockSizes, blocks, processSizes, processes);
  				break;
  		case 3: worstFit(blockSizes, blocks, processSizes, processes);
  				break;
  		case 4: cout<<"\nExiting ..... Thankyou !!";
  				break;
  		default: cout<<"\nEnter a valid option";
  				 break;
	}
  } while(ch!=4);
  return 0;
}

void bestFit(int blockSize[], int m, int processSize[], int n)
{
  int allocation[n];

  for (int i = 0; i < n; i++)
    allocation[i] = -1;

  for (int i = 0; i < n; i++)
  {
    int bestIdx = -1;
    for (int j = 0; j < m; j++)
    {
      if (blockSize[j] >= processSize[i])
      {
        if (bestIdx == -1)
          bestIdx = j;
        else if (blockSize[bestIdx] > blockSize[j])
          bestIdx = j;
      }
    }

    if (bestIdx != -1)
    {
      allocation[i] = bestIdx;
      blockSize[bestIdx] -= processSize[i];
    }
  }

  cout << "\nBest-Fit Allocation Strategy\n";
  cout << "=========================================\n";
  cout << "Process No.\tProcess Size\tBlock No.\n";
  cout << "=========================================\n";
  for (int i = 0; i < n; i++)
  {
    cout << "   " << i + 1 << "\t\t" << processSize[i] << "\t\t";
    if (allocation[i] != -1)
      cout << allocation[i] + 1;
    else
      cout << "Not Allocated";
    cout << endl;
  }
}

void firstFit(int blockSize[], int m, int processSize[], int n)
{
  int allocation[n];

  for (int i = 0; i < n; i++)
    allocation[i] = -1;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (blockSize[j] >= processSize[i])
      {
        allocation[i] = j;
        blockSize[j] -= processSize[i];
        break;
      }
    }
  }

  cout << "\nFirst-Fit Allocation Strategy\n";
  cout << "=========================================\n";
  cout << "\nProcess No.\tProcess Size\tBlock No.\n";
  cout << "=========================================\n";
  for (int i = 0; i < n; i++)
  {
    cout << " " << i + 1 << "\t\t"
         << processSize[i] << "\t\t";
    if (allocation[i] != -1)
      cout << allocation[i] + 1;
    else
      cout << "Not Allocated";
    cout << endl;
  }
}

void worstFit(int blockSize[], int m, int processSize[], int n)
{
  int allocation[n];

  for (int i = 0; i < n; i++)
    allocation[i] = -1;

  for (int i = 0; i < n; i++)
  {
    int wstIdx = -1;
    for (int j = 0; j < m; j++)
    {
      if (blockSize[j] >= processSize[i])
      {
        if (wstIdx == -1)
          wstIdx = j;
        else if (blockSize[wstIdx] < blockSize[j])
          wstIdx = j;
      }
    }

    if (wstIdx != -1)
    {
      allocation[i] = wstIdx;
      blockSize[wstIdx] -= processSize[i];
    }
  }

  cout << "\nWorst-Fit Allocation Strategy\n";
  cout << "=========================================\n";
  cout << "Process No.\tProcess Size\tBlock No.\n";
  cout << "=========================================\n";
  for (int i = 0; i < n; i++)
  {
    cout << "   " << i + 1 << "\t\t" << processSize[i] << "\t\t";
    if (allocation[i] != -1)
      cout << allocation[i] + 1;
    else
      cout << "Not Allocated";
    cout << endl;
  }
}
