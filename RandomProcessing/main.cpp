#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include "discreteRV.h"

int main()
{
	dice D(6, 1, 6);
	cout << "dice Ex  : " << D.EX  << endl;
	cout << "dice Var : " << D.VAR << endl;

	cout << "P[x]     : ";
	for (int i = 0; i < D.N; i++)
	{
		cout << D.pdf[i] << "  ";
	}
	cout << endl << endl;

	D.calculateExVar();
	cout << "dice Ex  : " << D.EX << endl;
	cout << "dice Var : " << D.VAR << endl << endl;

	binomial B(40, 0.01);
	cout << "Loss Ex  : " << B.EX << endl;
	cout << "Loss Var : " << B.VAR << endl;
	cout << "P[x]     : " << endl;
	for (int i = 0; i < B.N; i++)
	{
		cout << B.pdf[i] << endl;
	}
	cout << endl << endl;

	B.calculate();
	cout << "Loss Ex  : " << B.EX << endl;
	cout << "Loss Var : " << B.VAR << endl;
	cout << "P[x]     : " << endl;
	for (int i = 0; i < B.N; i++)
	{
		cout << B.pdf[i] << endl;
	}
	cout << endl << endl;

	poisson P(10, 0.1),
		Q(1E2, 0.1),
		R(1E3, 0.1);
	
	P.experiment(10000);
	cout << "Loss Ex  : " << P.EX << endl;
	cout << "Loss Var : " << P.VAR << endl;
	cout << "P[x]     : " << endl;
	for (int i = 0; i < P.N; i++)
	{
		cout << P.pdf[i] << endl;
	}
	cout << endl << endl;
	P.calcBinomal();
	cout << "Loss Ex  : " << P.EX << endl;
	cout << "Loss Var : " << P.VAR << endl;
	cout << "P[x]     : " << endl;
	for (int i = 0; i < P.N; i++)
	{
		cout << P.pdf[i] << endl;
	}
	cout << endl << endl;
	P.calcPoisson();
	cout << "Loss Ex  : " << P.EX << endl;
	cout << "Loss Var : " << P.VAR << endl;
	cout << "P[x]     : " << endl;
	for (int i = 0; i < P.N; i++)
	{
		cout << P.pdf[i] << endl;
	}
	cout << endl << endl;

	Q.experiment(10000);
	cout << "Experiment" << endl;
	cout << "Loss Ex  : " << Q.EX << endl;
	cout << "Loss Var : " << Q.VAR << endl;
	Q.calcBinomal();
	cout << "Binomal" << endl;
	cout << "Loss Ex  : " << Q.EX << endl;
	cout << "Loss Var : " << Q.VAR << endl;
	Q.calcPoisson();
	cout << "Poisson Limit" << endl;
	cout << "Loss Ex  : " << Q.EX << endl;
	cout << "Loss Var : " << Q.VAR << endl;
	cout << endl << endl;

	R.experiment(10000);
	cout << "Experiment" << endl;
	cout << "Loss Ex  : " << R.EX << endl;
	cout << "Loss Var : " << R.VAR << endl;
	R.calcBinomal();
	cout << "Binomal" << endl;
	cout << "Loss Ex  : " << R.EX << endl;
	cout << "Loss Var : " << R.VAR << endl;
	R.calcPoisson();
	cout << "Poisson Limit" << endl;
	cout << "Loss Ex  : " << R.EX << endl;
	cout << "Loss Var : " << R.VAR << endl;
	cout << endl << endl;

	fstream fio("DicePoisson5.csv", ios::out);

	poisson DiceGame(5, 1. / 6.);
	DiceGame.calcBinomal();
	for (int i = 0; i < DiceGame.N; i++)
	{
		fio << i << ", " << DiceGame.pdf[i] << endl;
	}
	fio << endl;
	DiceGame.calcPoisson();
	for (int i = 0; i < DiceGame.N; i++)
	{
		fio << i << ", " << DiceGame.pdf[i] << endl;
	}
	fio.close();
	
	fio.open("DicePoisson100.csv", ios::out);
	DiceGame.init(100, 1. / 6.);
	DiceGame.calcBinomal();
	for (int i = 0; i < DiceGame.N; i++)
	{
		fio << i << ", " << DiceGame.pdf[i] << endl;
	}
	fio << endl;
	DiceGame.calcPoisson();
	for (int i = 0; i < DiceGame.N; i++)
	{
		fio << i << ", " << DiceGame.pdf[i] << endl;
	}
	fio.close();

	fio.open("DicePoisson200.csv", ios::out);
	DiceGame.init(200, 1. / 6.);
	DiceGame.calcBinomal();
	for (int i = 0; i < DiceGame.N; i++)
	{
		fio << i << ", " << DiceGame.pdf[i] << endl;
	}
	fio << endl;
	DiceGame.calcPoisson();
	for (int i = 0; i < DiceGame.N; i++)
	{
		fio << i << ", " << DiceGame.pdf[i] << endl;
	}
	fio << endl;
	fio.close();


	central DC(5, 1, 6);
	DC.experiment(100000);
	cout << DC.N << ", " << DC.xhigh << endl;
	cout << DC.mean << ", " << DC.sigma << endl;
	for (int i = 0; i < DC.max; i++)
	{
		cout << i << ":\t" << DC.pdf[i] << endl;
	}
	cout << endl << endl;
	DC.gaussianRV();
	for (int i = 0; i < DC.max; i++)
	{
		cout << i << ":\t" << DC.pdf[i] << endl;
	}
	cout << endl << endl;

	return 0;
}