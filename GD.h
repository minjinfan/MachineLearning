/****************   GD.h   **********************/

#pragma once
#include<iostream>
#include<vector>

using namespace std;

struct Data {
	vector<double> feature;
	double label;
	Data(vector<double>f, double l) :feature(f), label(l) {}
};

class GD
{
public:
	GD(string& trainfile, string& testfile, string& predictOutfile);
	void train();
	int storeModel();
	void predict();

	vector<double> Weight;

private:
	vector<Data> testDataSet;
	vector<Data> trainDataSet;
	vector<int> predictVec;

private:
	string trainFile;
	string testFile;
	string predictOutFile;

	int featureNum = 0;
	double alpha = 0.001; //²½³¤
	double epsion = 1e-8;   //Îó²îÏÞ
	int maxIterTimes = 300;
	double predictTrueThresh = 0.5;
	string weightParamFile = "modelweight.txt";

private:
	bool init();
	bool loadTrainData();
	void initWeight();
	double wxCal(Data& data);
	//double lossCalc();
	void UpdateW();
	double gradient(int& index);
	//inline double sigmoidCala(double wx);
	//int storeModel();
	bool loadTestData();
	int storePredict();

	double costCalc();

};
