/*********************************  GD.cpp  **************************************/

#include "GD.h"
#include<fstream>
#include<sstream>
#include<time.h>
#include<string>

using namespace std;

GD::GD(string& trainfile, string& testfile, string& predictOutfile) {
	trainFile = trainfile;
	testFile = testfile;
	predictOutFile = predictOutfile;
	init();
}

//初始化包括：加载训练文件、初始化权重
bool GD::init() {
	trainDataSet.clear();
	clock_t start = clock();
	bool sign = loadTrainData();
	clock_t end = clock();
	cout << "load train file time is " << end - start << endl;
	if (sign == false)
		return false;

	featureNum = trainDataSet[0].feature.size();
	Weight.clear();
	initWeight();

	return true;
}

bool GD::loadTrainData() {
	ifstream infile(trainFile.c_str());
	string line;

	if (!infile.good()) {
		std::cout << "open train file failure" << endl;
		exit(0);
	}
	while (!infile.eof()) {
		getline(infile, line);

		if (line.size() > 0) {
			stringstream strCin(line);

			char ch;
			double data;
			vector<double> feature;

			while (strCin) {
				//char c = strCin.peek();
				//if (int(c) != -1) {
				strCin >> data;
				feature.push_back(data);
				strCin >> ch;
				/*}
				else {
					return false;
				}*/

			}
			double label = feature.back();
			feature.pop_back();
			trainDataSet.push_back(Data(feature, label));
		}

	}
	infile.close();
	//trainDataSet.pop_back();
	return true;
}

void GD::initWeight() {
	for (int i = 0; i < featureNum; i++)
		Weight.push_back(1.0); //先初始化权重全为1
}

void GD::train() {
	//for (int i = 0; i < maxIterTimes; i++) {
	int k = 0;
	double objCost = costCalc();
	UpdateW();
	double newCost = costCalc();
	while (fabs(newCost - objCost) > epsion) {
		objCost = newCost;
		UpdateW();
		newCost = costCalc();
		k++;
		if (k > 2000) break;
	}

	//}
}

double GD::wxCal(Data& data) {
	double h_theta = 0;
	double theta, x;
	for (int i = 0; i < featureNum; i++) {
		theta = Weight[i];
		x = data.feature[i];
		h_theta += theta * x;
	}

	return h_theta;
}

double GD::costCalc() {
	double costV = 0.0;
	for (int i = 0; i < trainDataSet.size(); i++) {
		costV += pow(wxCal(trainDataSet[i]) - trainDataSet[i].label, 2);
	}
	costV = costV / (2.0 * trainDataSet.size());
	return costV;

}

void GD::UpdateW() {
	vector<double> temp = Weight;
	double V = 0;
	for (int i = 0; i < Weight.size(); i++) {
		temp[i] -= alpha * gradient(i);
	}
	Weight = temp;
}
double GD::gradient(int& index) {
	double gV = 0.0;
	for (int i = 0; i < trainDataSet.size(); i++) {
		double h_theta = wxCal(trainDataSet[i]);
		double label = trainDataSet[i].label;
		gV += (h_theta - label) * trainDataSet[i].feature[index];
	}
	gV = gV / trainDataSet.size();
	return gV;
}

int GD::storeModel() {
	clock_t start = clock();

	ofstream outfile(weightParamFile.c_str());
	string line;
	if (!outfile.is_open())  printf("open model file failure \n");
	for (int i = 0; i < featureNum; i++)
		outfile << Weight[i] << " ";
	outfile.close();
	clock_t end = clock();
	cout << "store model time is" << end - start << endl;
	return 0;
}

bool GD::loadTestData() {
	ifstream infile(testFile.c_str());
	string line;
	if (!infile.is_open()) {
		printf("open test file failure \n");
		exit(0);
	}

	while (!infile.eof()) {
		vector<double> feature;
		string line;

		getline(infile, line);
		if (line.size() > 0) {
			stringstream sin(line);
			double data;
			char ch;
			//int i = 0;
			while (sin) {
				sin >> data;
				feature.push_back(data);
				sin >> ch;
				//i++;
			}
			testDataSet.push_back(Data(feature, 0));
		}
	}
	infile.close();
}

int GD::storePredict() {
	//int GD::storePredict(vector<int>& predict) {
	ofstream outfile(predictOutFile.c_str());
	if (!outfile.is_open())
		printf("open predict file failure\n");
	for (int i = 0; i < predictVec.size(); i++) {
		outfile << predictVec[i] << endl;
	}
	outfile.close();
	return 0;
}
void GD::predict() {
	clock_t start = clock();
	loadTestData();
	clock_t end = clock();
	cout << endl << "读测试文件时间 ：" << end - start << endl;
	for (int i = 0; i < testDataSet.size(); i++) {
		//double sigV = sigmoidCala(wxCal(testDataSet[i]));
		double h_theta = wxCal(testDataSet[i]);
		//int predictV = sigV >= predictTrueThresh ? 1 : 0;
		predictVec.push_back(h_theta);
	}

	clock_t start2 = clock();
	storePredict();
	clock_t end2 = clock();
	cout << endl << "保存预测数据时间：" << end2 - start2 << endl;
}
