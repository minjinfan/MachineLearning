/*    main.cpp    */
#include<iostream>
#include<fstream>
#include<time.h>
#include<sstream>
#include<cstdio>
#include"GD.h"
#define TEST

using namespace std;

bool loadAnswerData(string& awFile, vector<int>& awVec);

int main()
{
	//ofstream outfile("trainData.txt");
	//srand((unsigned)time(NULL));
	//for (int i = 0; i < 2000; i++) {
	//	//原函数 y = 1 + 3x;   创造一个训练集
	//	double x1 = (rand() % (30));
	//	//double x2 = (rand() % (50) + 10);
	//	double y = 1 + 3 * x1;
	//	outfile << 1 <<","<< x1 << ","  << y << endl;
	//}
	//outfile.close();
	//cout << "训练文件已生成 " << endl;

	//ofstream outTestfile("testData.txt");
	//srand((unsigned)time(NULL));
	//for (int i = 0; i < 2000; i++) {
	//	//原函数 y = 1 + 3x;   创造一个训练集
	//	double x1 = (rand() % (50));
	//	//double x2 = (rand() % (50) + 10);
	//	double y = 1 + 3 * x1;
	//	outfile << 1 << "," << x1 << "," << y << endl;
	//}
	//outTestfile.close();
	//cout << "测试文件已生成 " << endl;


	string trainFile = "train_data.txt";
	string testFile = "test_data.txt";
	string predictFile = "result.txt";

	GD gradient(trainFile,testFile,predictFile);

	clock_t start1 = clock();
	printf("start train model ...\n");
	gradient.train();
	clock_t end1 = clock();
	cout << "train model time is " << end1 - start1 << endl;

	printf("training end,ready to store the model ... \n");
	gradient.storeModel();
	//vector<double> theta;
	//for (int i = 0; i < gradient.Weight.size(); i++) {
	//	theta.push_back(gradient.Weight[i]);
	//}
	//cout << "预测的原函数为：y = " << theta[0] << " + " << theta[1] << "x1" << theta[2] << "x2" << endl;    //我知道所以才这么看结果
	
#ifdef TEST
	vector<int> answerVec;
	string answerFile = "answer.txt";
	printf("load answer data ...\n");
	loadAnswerData(answerFile, answerVec);
#endif

	printf("let's prediction test ...\n");
	gradient.predict();

#ifdef TEST
	vector<int> predictVec;
	loadAnswerData(predictFile, predictVec);
	cout << "test data set size is " << predictVec.size() << endl;
	int correctCount = 0;
	for (int j = 0; j < predictVec.size(); j++) {
		if (j < answerVec.size()) {
			if (answerVec[j] == predictVec[j]) {
				correctCount++;
			}
		}
		else {
			cout << "answer size less than the real predicted value" << endl;
		}
	}

	double accurate = ((double)correctCount) / answerVec.size();
	cout << "the prediction accuracy is " << accurate << endl;
#endif
	return 0;
}

bool loadAnswerData(string& awFile, vector<int>&  awVec) {
	ifstream infile(awFile.c_str());
	if (!infile.is_open()) {
		printf("open answer file failure \n");
		exit(0);
	}

	while (!infile.eof()) {
		int aw;
		string line;
		getline(infile, line);
		if (line.size() > 0) {
			stringstream sin(line);
			sin >> aw;
			awVec.push_back(aw);
		}		
	}
	infile.close();
	return true;
}