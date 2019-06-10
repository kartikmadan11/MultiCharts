#include "pch.h"
#include "iostream"
#include "MultiCharts.h"

using namespace std;

int main()
{
	long long int *unix_dates = new long long[65];
	double *trainingData = new double[65];
	long long init = 1136332800;
	for (int i = 0; i < 65; i++)
	{
		unix_dates[i] = init + (i * 150);
		trainingData[i] = init + (i * 6.32);
	}

	MultiCharts * multiCharts = new MultiCharts();
	
	multiCharts->InitTrainingData(65);
	multiCharts->SetTrainingData(trainingData);

	multiCharts->InitDateArrayUNIX(65);
	multiCharts->SetDateArrayUNIX(unix_dates);

	char* fileName = new char[4]{"abc"};
	multiCharts->InitFileName(4);
	multiCharts->SetFileName(fileName);

	multiCharts->SetEpochs(2);
	multiCharts->SetLearningRate(0.001);
	multiCharts->SetScale(100);
	multiCharts->SetOptimizer(0);
	multiCharts->SetMomentum(10);

	cout << multiCharts->dateArrayUNIX[21] << endl;

	cout << multiCharts->TrainModel();

	multiCharts->DisposeMultiCharts();
	return 0;
}