#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class discreteRV
{
public:

	int N = 0; // number of elements
	int xlow = 0, xhigh = 0; // lowest and highest elements
	float* pdf = nullptr;
	float EX = 0, VAR = 0;

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
		experiment(10000);
	}
	void experiment(int Ntrial);
};

class binomial : public discreteRV
{
public:
	binomial() {};
	binomial(int num, int low, int high)
	{

	}
	
	double factorial(double N);
	double analBinomial(double n, double k, double p);
	void experiment(int Ntrial);
};