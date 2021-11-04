#include "discreteRV.h"

/*
RV Parent Class
*/

void discreteRV::init(int num, int low, int high)
{
	N = num;
	xlow = low;
	xhigh = high;
	pdf = new double[N];
	EX = VAR = 0;
	for (int i = 0; i < N; i++) pdf[i] = 0.0;
}

void discreteRV::calculateExVar() 
{
	double EX2 = 0.0;
	EX = 0.0;
	for (int i = 0; i < N; i++)
	{
		EX += pdf[i] * (xlow + i);
		EX2 += pdf[i] * (xlow + i) * (xlow + i);
	}
	VAR = EX2 - EX * EX;
}

/*
Dice RV Class
*/

void dice::experiment(int Ntrial)
{
	for (int i = 0; i < Ntrial; i++)
	{
		int ix = rand() % 6;
		double x = ix + xlow;
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

/*
Binominal RV Class
*/

void binomial::init(int num, double p)
{
	N = num + 1;
	p_loss = p;
	xlow = 0, xhigh = num;
	pdf = new double[N];
	EX = VAR = 0;
	for (int i = 0; i < N; i++) pdf[i] = 0.0;

	experiment(10000);
}

double binomial::factorial(double N)
{
	double fact = 1;
	for (int i = 2; i <= N; i++) fact *= i;
	return fact;
}

double binomial::analyticalBinomial(double n, double k, double p)
{
	return factorial(n) / factorial(k) / factorial(n - k)
		* pow(p, k) * pow(1. - p, n - k);
}

void binomial::experiment(int Ntrial)
{
	for (int i = 0; i < Ntrial; i++)
	{
		int lost = 0;
		for (int t = 0; t < N; t++)
		{
			if ((rand() / (double)RAND_MAX) < p_loss) lost++;
		}
		pdf[lost]++;
		EX += lost;
		VAR += lost * lost;
	}
	for (int i = 0; i < N; i++) pdf[i] /= (double)Ntrial;
	EX /= (double)Ntrial;
	VAR = VAR / (double)Ntrial - EX * EX;
}

void binomial::calculate()
{
	for (int i = 0; i < N; i++) pdf[i] = analyticalBinomial(xhigh, i, p_loss);
	calculateExVar();
}

/*
Poisson Limit Class
*/

void poisson::init(int num, double p)
{
	N = num + 1;
	this->P = p;
	xlow = 0, xhigh = num;
	pdf = new double[N];
	EX = VAR = 0;
	for (int i = 0; i < N; i++) pdf[i] = 0.0;

	experiment(10000);
}

double poisson::xpoisson(int x, double alpha)
{
	double px = 1.0;
	for (int i = 1; i <= x; i++) px *= (alpha / (float)i);
	return px * exp(-alpha);
}

double poisson::xbinomial(int x, double p)
{
	double px = 1.0;
	for (int i = 1; i < N; i++)
	{
		px *= (double)i / ((i > x) ? (N - i) : i);
	}
	return px * pow(p, x) * pow(1. - p, N - 1 - x);
}

void poisson::experiment(int Ntrial)
{
	for (int i = 0; i < Ntrial; i++)
	{
		int lost = 0;
		for (int t = 0; t < N; t++)
		{
			if ((rand() / (double)RAND_MAX) < P) lost++;
		}
		pdf[lost]++;
		EX += lost;
		VAR += lost * lost;
	}
	for (int i = 0; i < N; i++) pdf[i] /= (double)Ntrial;
	EX /= (double)Ntrial;
	VAR = VAR / (double)Ntrial - EX * EX;
}

void poisson::calcPoisson()
{
	for (int i = 0; i < N; i++) pdf[i] = xpoisson(i, (N - 1) * P);
	calculateExVar();
}

void poisson::calcBinomal()
{
	for (int i = 0; i < N; i++) pdf[i] = xbinomial(i, P);
	calculateExVar();
}

/*
Central Limit Class
*/

void central::init(int num, int low, int high)
{
	N = num;
	xlow = low;
	xhigh = high;
	max = xhigh * N + 1;
	
	mean = 21. / 6.;
	sigma = 91. / 6. - mean * mean;
	mean *= N;
	sigma = sqrt(N * sigma);

	pdf = new double[max];
	EX = VAR = 0;
	for (int i = 0; i < max; i++) pdf[i] = 0.0;
}

void central::experiment(int Ntrial)
{
	for (int t = 0; t < Ntrial; t++)
	{
		int x = 0;
		for (int d = 0; d < N; d++)
		{
			x += (rand() % 6 + 1);
		}
		pdf[x]++;
		EX += x;
		VAR += x * x;
	}
	for (int i = 0; i < max; i++) pdf[i] /= (double)Ntrial;
	EX /= (double)Ntrial;
	VAR = VAR / (double)Ntrial - EX * EX;
}

void central::gaussianRV()
{
	for (int d = 0; d < max; d++)
	{
		pdf[d] = 1 / sqrt(2 * PI * sigma * sigma)
			* exp(- 1. / (2 * sigma * sigma) * (d - mean) * (d - mean));
	}
	calculateExVar();
}


void central::calculateExVar()
{
	double EX2 = 0.0;
	EX = 0.0;
	for (int i = 0; i < max; i++)
	{
		EX += pdf[i] * i;
		EX2 += pdf[i] * i * i;
	}
	VAR = EX2 - EX * EX;
}