#include <iostream>
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
	cout << "dice Var : " << D.VAR << endl;



	return 0;
}