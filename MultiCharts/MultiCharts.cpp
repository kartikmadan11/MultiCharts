#include "pch.h"
#include "Python.h"
#include "MultiCharts.h"
#include "pyhelper.hpp"
#include "string"

//Creating a Python Instance
CPyInstance pyInstance;

MultiCharts::MultiCharts() { }

MultiCharts::~MultiCharts() { }

/*

		--Member Functions--

*/

void MultiCharts::DisposeMultiCharts()
{
	if ((bool)Py_IsInitialized())
	{
		int _ = Py_FinalizeEx();
		Py_Finalize();
	}

	if (trainingData != NULL)
	{
		delete[] trainingData;
		trainingData = NULL;
	}

	if (dateArrayUNIX != NULL)
	{
		delete[] dateArrayUNIX;
		dateArrayUNIX = NULL;
	}

	if (testingData != NULL)
	{
		delete[] testingData;
		testingData = NULL;
	}

	if (testDateArrayUNIX != NULL)
	{
		delete[] testDateArrayUNIX;
		testDateArrayUNIX = NULL;
	}

	if (fileName != NULL)
	{
		delete[] fileName;
		fileName = NULL;
	}

	if (volumeArray != NULL)
	{
		delete[] volumeArray;
		volumeArray = NULL;
	}

	if (this != NULL)
	{
		delete this;
	}
}

void MultiCharts::InitTrainingData(int size)
{
	this->trainingDataSize = size;
	this->trainingData = new double[size];
}

void MultiCharts::SetTrainingData(double *trainingData)
{
	//this->trainingData = trainingData;
	for (int i = 0; i < trainingDataSize; i++)
	{
		this->trainingData[i] = trainingData[i];
	}
}

void MultiCharts::InitTestingData(int size)
{
	this->testingDataSize = size;
	this->testingData = new double[size];
}

void MultiCharts::SetTestingData(double *testingData)
{
	for (int i = 0; i < testingDataSize; i++)
	{
		this->testingData[i] = testingData[i];
	}
}

void MultiCharts::InitDateArrayUNIX(int size)
{
	this->dateArrayUNIXSize = size;
	this->dateArrayUNIX = new long long[size];
}

void MultiCharts::SetDateArrayUNIX(long long * dateArray)
{
	for (int i = 0; i < dateArrayUNIXSize; i++)
	{
		this->dateArrayUNIX[i] = dateArray[i];
	}
}

void MultiCharts::InitTestDateArrayUNIX(int size)
{
	this->testDateArrayUNIXSize = size;
	this->testDateArrayUNIX = new long long[size];
}

void MultiCharts::SetTestDateArrayUNIX(long long * testDateArray)
{
	for (int i = 0; i < testDateArrayUNIXSize; i++)
	{
		this->testDateArrayUNIX[i] = testDateArray[i];
	}
}

void MultiCharts::InitVolumeArray(int size)
{
	this->volumeArraySize = size;
	this->volumeArray = new long[size];
}

void MultiCharts::SetVolumeArray(long* volume)
{
	this->volumeArray = volume;
	//delete[] volume;
	//volume = NULL;
}

void MultiCharts::InitFileName(int size)
{
	this->fileNameSize = size;
	this->fileName = new char[size];
}

void MultiCharts::SetFileName(char* fileName)
{
	for (int i = 0; i < fileNameSize; i++)
	{
		this->fileName[i] = fileName[i];
	}
	fileName[fileNameSize] = '\0';
}

void MultiCharts::SetLearningRate(double learningRate)
{
	this->learningRate = learningRate;
}

void MultiCharts::SetEpochs(int epochs)
{
	this->epochs = epochs;
}

void MultiCharts::SetScale(int scale)
{
	this->scale = scale;
}

void MultiCharts::SetOptimizer(int optimizer)
{
	this->optimizer = optimizer;
}

void MultiCharts::SetMomentum(double momentum)
{
	this->momentum = momentum;
}

double MultiCharts::TrainModel()
{	
	// Importing the .py module
	CPyObject pModule = PyImport_ImportModule("build");

	PyGILState_STATE gstate = PyGILState_Ensure();

	if (pModule)
	{
		// Importing the Train Function
		CPyObject pFunc = PyObject_GetAttrString(pModule, "train");
		
		if (pFunc && PyCallable_Check(pFunc))
		{
			// Creating PyObjects Parameters for Train Function

			// Python Lists for Training Data Values and Dates
			CPyObject pTrainingData = PyList_New(0);
			CPyObject pDate = PyList_New(0);

			for (int i = 0; i < trainingDataSize; i++)
			{	
				CPyObject pTrainEle = PyFloat_FromDouble(trainingData[i]);
				CPyObject pDateEle = PyUnicode_FromFormat("%lli", dateArrayUNIX[i]);
				
				PyList_Append(pTrainingData, pTrainEle);
				PyList_Append(pDate, pDateEle);
			}

			std::string fileNameString(fileName, fileNameSize);
			const char* d = fileNameString.c_str();

			CPyObject pLearningRate = PyFloat_FromDouble(learningRate);
			CPyObject pScale = Py_BuildValue("i", scale);
			CPyObject pEpochs = Py_BuildValue("i", epochs);
			CPyObject pMomentum = Py_BuildValue("i", momentum);
			CPyObject pOptimizer = Py_BuildValue("i", optimizer);
			CPyObject pFileName = PyUnicode_FromFormat("%s", d);
			
			if (pTrainingData && pDate && pLearningRate && pScale && pEpochs && pMomentum && pOptimizer && pFileName)
			{
				// Receiving return value from the Train Function
				CPyObject pValue = PyObject_CallFunctionObjArgs(pFunc, pTrainingData, pDate, pLearningRate, pScale, pEpochs, pMomentum, pOptimizer, pFileName, NULL);

				if (pValue)
				{
					double returnVal = PyFloat_AsDouble(pValue);
					PyGILState_Release(gstate);
					return returnVal;
				}
				else
				{
					PyGILState_Release(gstate);
					return 1.01;
				}
			}
			else
			{
				PyGILState_Release(gstate);
				return 2.01;
			}
		}
		else
		{
			PyGILState_Release(gstate);
			return 3.01;
		}
	}
	else
	{
		PyGILState_Release(gstate);
		return 4.01;
	}
}

double MultiCharts::TestModel()
{
	// Importing the .py module
	CPyObject pModule = PyImport_ImportModule("build");

	PyGILState_STATE gstate = PyGILState_Ensure();

	if (pModule)
	{
		// Importing the Test Function
		CPyObject pFunc = PyObject_GetAttrString(pModule, "test");

		if (pFunc && PyCallable_Check(pFunc))
		{
			// Creating PyObjects Parameters for Test Function

			//Python Lists for Test Data Values and Dates
			CPyObject pTestingData = PyList_New(0);
			CPyObject pDate = PyList_New(0);

			for (int i = 0; i < testingDataSize; i++)
			{
				CPyObject pTestEle = PyFloat_FromDouble(testingData[i]);
				CPyObject pDateEle = PyUnicode_FromFormat("%lli", dateArrayUNIX[i]);

				PyList_Append(pTestingData, pTestEle);
				PyList_Append(pDate, pDateEle);
			}

			std::string fileNameString(fileName, fileNameSize);
			const char* d = fileNameString.c_str();

			CPyObject pFileName = PyUnicode_FromFormat("%s", d);

			if (pTestingData && pDate && pFileName)
			{
				// Receiving return value from the Test Function
				CPyObject pValue = PyObject_CallFunctionObjArgs(pFunc, pTestingData, pDate, pFileName, NULL);

				if (pValue)
				{
					double returnVal = PyFloat_AsDouble(pValue);
					PyGILState_Release(gstate);
					return returnVal;
				}
				else
				{
					PyGILState_Release(gstate);
					return 0.01;
				}
			}
			else
			{
				PyGILState_Release(gstate);
				return 0.02;
			}
		}
		else
		{
			PyGILState_Release(gstate);
			return 0.03;
		}
	}
	else
	{
		PyGILState_Release(gstate);
		return 0.04;
	}
}

double* MultiCharts::Predict(int ticks)
{
	// Importing the .py module
	CPyObject pModule = PyImport_ImportModule("build");

	PyGILState_STATE gstate = PyGILState_Ensure();

	if (pModule)
	{
		// Importing the Predict Function
		CPyObject pFunc = PyObject_GetAttrString(pModule, "predict");

		if (pFunc && PyCallable_Check(pFunc))
		{
			// Creating PyObjects Parameters for Predict Function

			std::string fileNameString(fileName, fileNameSize);
			const char* d = fileNameString.c_str();

			CPyObject pFileName = PyUnicode_FromFormat("%s", d);
			CPyObject pTicks = Py_BuildValue("i", ticks);

			if (pFileName && pTicks)
			{
				// Receiving return value from the Predict Function
				CPyObject pValue = PyObject_CallFunctionObjArgs(pFunc, pFileName, pTicks, NULL);

				if (pValue)
				{
					if (PyList_Check(pValue))
					{
						int count = (int)PyList_Size(pValue);

						double* predictions = new double[count];
						CPyObject pTemp;

						for (int i = 0; i < count; i++)
						{
							pTemp = PyList_GetItem(pValue, i);
							predictions[i] = PyFloat_AsDouble(pTemp);
						}

						PyGILState_Release(gstate);

						//double* predictions = new double[ticks]{ 1.1, 2.01, 3.22, 4.1, 5.09 };
						return predictions;
					}
					else
					{
						return NULL;
					}
				}
				else
				{
					return NULL;
				}
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}