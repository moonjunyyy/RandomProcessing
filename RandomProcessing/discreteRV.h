#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class discreteRV
{
public:

	int N = 0; // number of elements
	int xlow = 0, xhigh = 0; // lowest and highest elements
	double* pdf = nullptr;
	double EX = 0, VAR = 0;

	discreteRV() { }
	discreteRV(int num, int low, int high) {
		init(num, low, high);
	}
	~discreteRV()
	{
		delete[] pdf;
	}

	void init(int num, int low, int high);
	void calculateExVar();
	virtual void experiment(int Ntrial) { };
};

class dice : public discreteRV
{
public:
	dice() {};
	dice(int num, int low, int high)
	{
		init(num, low, high);
		experiment(100000);
	}
	void experiment(int Ntrial);
};

class binomial : public discreteRV
{
public:
	double p_loss;
	binomial() {}
	binomial(int num, double p_loss)
	{
		init(num, p_loss);
	}
	
	void init(int num, double p);
	double factorial(double N);
	void calculateExVar();
	double analyticalBinomial(double n, double k, double p);
	void experiment(int Ntrial);
	void calculate();
};

class poisson : public discreteRV
{
public:
	double P;
	poisson() {}
	poisson(int num, double alpha)
	{
		init(num, alpha);
	}
	void init(int num, double alpha);
	double xpoisson(int x, double alpha);
	double xbinomial(int x, double alpha);

	void experiment(int Ntrial);
	void calcPoisson();
	void calcBinomal();
};