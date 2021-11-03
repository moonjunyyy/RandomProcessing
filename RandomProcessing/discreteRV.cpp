#include "discreteRV.h"
void discreteRV::init(int num, int low, int high)
{
	N = num;
	xlow = low;
	xhigh = high;
	pdf = new float[N];
	EX = VAR = 0;
	for (int i = 0; i < N; i++) pdf[i] = 0.0;
}

void discreteRV::calculateExVar() 
{
	float EX2 = 0.0;
	EX = 0.0;
	for (int i = 0; i < N; i++)
	{
		EX += pdf[i] * (xlow + i);
		EX2 += pdf[i] * (xlow + i) * (xlow + i);
	}
	VAR = EX2 - EX * EX;
}

void dice::experiment(int Ntrial)
{
	for (int i = 0; i < Ntrial; i++)
	{
		int ix = rand() % 6;
		float x = ix + xlow;
		EX += x;
		VAR += x * x;
		pdf[ix]++;
	}
	EX /= Ntrial;
	VAR = VAR / Ntrial - EX * EX;
	for (int i = 0; i < N; i++)
	{
		pdf[i] /= Ntrial;
	}
	return;
}

double binomial::factorial(double N)
{
	double fact = 1;
	for (int i = 1; i < N; i++)	fact *= (i + 1);
	return fact;
}

double binomial::analBinomial(double n, double k, double p)
{
	factorial(n) / factorial(k) / factorial(n - k);
	return 0.0;
}

