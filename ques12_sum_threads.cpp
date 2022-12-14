//12. Write a program to calculate sum of n numbers using thread library.

#include <pthread.h>
#include <iostream>
#include <cstdlib>
using namespace std;

int sum;
void *sum_of_n(void *param);

int main(int argc,char* argv[])
{
	pthread_t worker;
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);

	pthread_create(&worker,&attr,sum_of_n,argv[1]);

	pthread_join(worker,NULL);
	
	cout<<"Sum of "<<argv[1]<<" numbers is "<<sum;
	
	return 0;
}

void *sum_of_n(void *param)
{
	int num = atoi((const char *)(param));
	for (int i = 1; i <= num; i++)
		sum += i;
	pthread_exit(0);
}
