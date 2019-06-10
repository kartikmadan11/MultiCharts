#include "pch.h"

public class MultiCharts
{
public:
	double* trainingData;
	int trainingDataSize;

	double* testingData;
	int testingDataSize;
	
	long long* dateArrayUNIX;
	int dateArrayUNIXSize;

	long long *testDateArrayUNIX;
	int testDateArrayUNIXSize;
	
	long* volumeArray;
	int volumeArraySize;

	char* fileName;
	int fileNameSize;

	double learningRate;
	int epochs;
	int scale;
	int optimizer;
	int momentum;
	double testingPart;
	double testingWeight;

	MultiCharts();
	~MultiCharts();
	void DisposeMultiCharts();

	void InitTrainingData(int size);
	void SetTrainingData(double* trainingData);

	void InitTestingData(int size);
	void SetTestingData(double* testingData);

	void InitDateArrayUNIX(int size);
	void SetDateArrayUNIX(long long *dateArray);

	void InitTestDateArrayUNIX(int size);
	void SetTestDateArrayUNIX(long long *testDateArray);

	void InitVolumeArray(int size);
	void SetVolumeArray(long* volume);

	void InitFileName(int size);
	void SetFileName(char* fileName);

	void SetLearningRate(double learningRate);
	void SetEpochs(int epochs);
	void SetScale(int scale);
	void SetOptimizer(int optimizer);
	void SetMomentum(int momentum);
	void SetTestingPart(double testingPart);
	void SetTestingWeight(double testingWeight);

	double TrainModel();
	double TestModel();
	double* Predict(int ticks);
};