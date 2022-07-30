#include <iostream>
#include <math.h>
using namespace std;
#define PI 3.14159265

class Distribution


{
private:
	double* pract1;
	double koef;
	int* count;
	double* fi, * Fi;
	double* ort;
	double sum;
	double* pract;

public:

	Distribution(int n)
	{
		sum = 0;
		koef = 0;
		pract1 = new double[n];
		count = new int[n];
		fi = new double[n];
		ort = new double[n];
		Fi = new double[n];
		pract = new double[n];


	}



	void FI(int n)
	{
		double dx, x;
		double sum_m = 0;
		double stop = 5, start = 0;
		dx = (stop - start) / n;
		x = 0;
		for (int i = 0; i < n; i++)
		{
			double arc = atan(x);

			Fi[i] = 0.5 + arc / PI;
			sum_m += Fi[i];



			printf("i=  %i F[i]=%f\t %f \n", i, Fi[i], x);
			x += dx;
		}
		koef = 1 / sum_m;

	}


	void new_Fi()
	{
		for (int i = 0; i < 50; i++)
			Fi[i] = Fi[i] * koef;
	}
	void fill_ort()
	{
		ort[0] = Fi[0];
		for (int i = 1; i < 50; i++)
		{
			ort[i] = Fi[i] + ort[i - 1];
		}
	}

	int  random(int n)
	{

		double  rand_x;
		int result = 0;
		rand_x = ((double)rand()) / (RAND_MAX);

		for (int i = 0; i < n; i++)
		{
			if (ort[i] >= rand_x)
			{
				result = i;
				break;
			}
		}

		return result;

	}

	void null_pract()
	{
		for (int i = 0; i < 50; i++)
		{
			pract[i] = 0;
			count[i] = 0;
		}
	}


	void start(int n)
	{
		srand(time(NULL));
		int result;
		for (int i = 0; i < 1000; i++)
		{
			result = random(50);
			pract[result] = Fi[result];
			count[result]++;
			pract[result] = pract[result] / koef;
		}


	}

	void do_pract()
	{
		for (int i = 0; i < 50 - 1; i++)
		{
			pract1[i] = (pract[i] + pract[i + 1]) / 2;
		}
		pract1[49] = pract[49];

	}

	void print_pract()
	{
		printf("Середина интревала\tКоличество раз выпало\t Номер интервала ");
		for (int i = 0; i < 50; i++)
		{
			printf("\n          %6.5f   \t%d                       \t%d", pract1[i], count[i], i + 1);

		}

	}
};


int main()
{
	setlocale(LC_ALL, "russian");
	Distribution MY(50);
	MY.FI(50);
	MY.new_Fi();
	MY.fill_ort();
	MY.null_pract();
	MY.start(1000);
	MY.do_pract();
	MY.print_pract();


}
