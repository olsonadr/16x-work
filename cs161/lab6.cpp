#include <iostream>
#include <sys/time.h>
#include <cstdlib>

using std::cout;
using std::endl;

int fib_iter(int n)
{
	int temp1 = 0;
	int temp2 = 1;
	int current;

	if (n == 1)
	{
		return 0;
	}
	else if (n == 2)
	{
		return 1;
	}
	else if (n < 1)
	{
		return -1;
	}

	for (int i = 3; i <= n; i++)
	{
		current = temp1 + temp2;
		temp1 = temp2;
		temp2 = current;
	}

	return current;
}

int fib_recurs(int n)
{
	if (n <= 2)
	{
		return n-1;
	}
	else
	{
		return fib_recurs(n - 2) + fib_recurs(n - 1);
	}
}

int main()
{

      typedef struct timeval time;
      time stop, start;
    //Iterative Timed
	gettimeofday(&start, NULL);
	//Time your iterative or recursive function here.
	std::cout << "1st fib number:  " << fib_iter(1) << std::endl;
	std::cout << "5th fib number:  " << fib_iter(5) << std::endl;
	std::cout << "15th fib number: " << fib_iter(15) << std::endl;
	std::cout << "25th fib number: " << fib_iter(25) << std::endl;
	std::cout << "45th fib number: " << fib_iter(45) << std::endl;
	gettimeofday(&stop, NULL);

	if (stop.tv_sec > start.tv_sec)
	{
		cout << "Iter Seconds: " << stop.tv_sec - start.tv_sec << endl;
	}
	else
	{
		cout << "Iter Micro: " << stop.tv_usec - start.tv_usec << endl;
	}

	//Recursive Timed
	gettimeofday(&start, NULL);
	//Time your iterative or recursive function here.
	std::cout << "1st fib number:  " << fib_recurs(1) << std::endl;
	std::cout << "5th fib number:  " << fib_recurs(5) << std::endl;
	std::cout << "15th fib number: " << fib_recurs(15) << std::endl;
	std::cout << "25th fib number: " << fib_recurs(25) << std::endl;
	std::cout << "45th fib number: " << fib_recurs(45) << std::endl;
	gettimeofday(&stop, NULL);

	if (stop.tv_sec > start.tv_sec)
	{
		cout << "Recurs Seconds: " << stop.tv_sec - start.tv_sec << endl;
	}
	else
	{
		cout << "Recurs Micro: " << stop.tv_usec - start.tv_usec << endl;
	}

	return 0;
}
