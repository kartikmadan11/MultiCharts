#include "pch.h"

constexpr auto DATE_SIZE = 11;

public class MultiCharts
{
public:
	double* trainingData;
	int trainingDataSize;

	double* testingData;
	int testingDataSize;
	
	long long* dateArrayUNIX;
	int dateArrayUNIXSize;
	
	char(*dateArray)[DATE_SIZE];
	int dateArraySize;

	char(*testDateArray)[DATE_SIZE];
	int testDateArraySize;

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

	void InitDateArray(int size);
	void SetDateArray(char *dateArray);

	void InitTestDateArray(int size);
	void SetTestDateArray(char *testDateArray);

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