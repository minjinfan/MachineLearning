//#include<iostream>
//#include<sstream>
//#include<string.h>
//#include<fstream>
//#include<vector>
//#include<time.h>
//#include<chrono>
//#include<thread>
//#include<mutex>
//#include<future>
//
//using namespace std;
//std::mutex m;
//
//const int threads = 3;
//string testFile = "test_data.txt";
//
//struct Data {
//	vector<double> feature;
//	double label;
//	Data(vector<double> f,double l):feature(f),label(l)
//	{}
//};
//
//vector<Data>testDataSet;
//
//vector<pair<long long, long long>> get_read_point() {
//	ifstream is(testFile);
//	if (!is) {
//		printf("open test file failure \n");
//		exit(1);
//	}
//	is.seekg(0, is.end);
//	long long length = is.tellg();
//
//	vector < pair<long long, long long>> res(threads);
//
//	res[0].first = 0;
//	for (int i = 1; i < threads; i++) {
//		is.seekg(length / threads * i);
//		{
//			string tmp;
//			getline(is, tmp);
//		}
//		res[i].first = is.tellg();
//		res[i - 1].second = res[i].first - res[i - 1].first;
//	}
//	res.back().second = length - res.back().first;
//
//	is.close();
//	return res;
//}
//
//void thread_read_file(int id, long long start__point, long long volume) {
//	m.lock(); 
//	//std::lock_guard<std::mutex> lockg(m);
//	ifstream is(testFile);
//	is.seekg(start__point);
//	if (!is) {
//		printf("open test file failure\n");
//		exit(1);
//	}
//	string line;
//	while (volume > 0 && getline(is, line)) {
//		//do something
//		vector<double> feature;
//		if (line.size() > 0) {
//			stringstream sin(line);
//			double data;
//			char ch;
//			//int i = 0;
//			while (sin) {
//				sin >> data;
//				feature.push_back(data);
//				sin >> ch;
//				//i++;
//			}
//			testDataSet.push_back(Data(feature, 0));
//		}
//
//		volume -= line.size() + 1.0;
//
//		if ((volume & 1048575) == 1048575)
//			printf("%d %lld\n", id, volume);
//		
//	}
//	m.unlock();
//}
//
//int main()
//{
//	//clock_t start = clock();
//
//	//int featureNum = 1000;
//	//vector<Data>testDataSet;
//	//
//
//	//ifstream infile(testFile.c_str());
//	//string line;
//	//if (!infile.is_open()) {
//	//	printf("open test file failure \n");
//	//	exit(0);
//	//}
//
//	//vector<double> feature;
//	//string buffer;
//	//buffer.assign(istreambuf_iterator<char>(infile), istreambuf_iterator<char>());
//	//stringstream strSin(buffer);
//	//clock_t end1 = clock();
//	//cout << "读进字符串时间：" << end1 - start << endl;
//	//
//	//while (getline(strSin, line)) {
//	//	if (line.size() > 0) {
//	//		stringstream sin(line);
//	//		double data;
//	//		char ch;
//	//		//int i = 0;
//	//		while (sin) {
//	//			sin >> data;
//	//			feature.push_back(data);
//	//			sin >> ch;
//	//			//i++;
//	//			
//	//		}
//	//		testDataSet.push_back(Data(feature, 0));
//	//	}
//	//}
//	//
//	//infile.close();
//	//clock_t end2 = clock();
//	//cout << endl << "读测试文件时间为：" << end2 - start << endl;
//
//	using namespace std::chrono;
//	steady_clock::time_point t1 = steady_clock::now();
//	vector<pair<long long, long long>> read_point = get_read_point();
//	double t2 = duration_cast<duration<double>>(steady_clock::now() - t1).count();
//
//	printf("get_read_point time_cost = %.2fs\n", t2);
//
//
//	vector<std::thread> vec_thread;
//	for (int i = 0; i < threads; ++i) {
//		/*promise<int> my_promise;
//		future<int> my_future = my_promise.get_future();
//		thread th(thread_read_file, i, read_point[i].first, read_point[i].second,move(my_promise));*/
//		//auto my_future = async(launch::async, thread_read_file, i, read_point[i].first, read_point[i].second);
//		//my_future.wait();
//		thread th(thread_read_file, i, read_point[i].first, read_point[i].second);		
//		vec_thread.push_back(move(th));
//	}
//	for (auto& th : vec_thread)
//		th.join();
//
//	double t = duration_cast<duration<double>>(steady_clock::now() - t1).count();
//
//	printf("time_cost = %.2fs\n", t);
//
//	return 0;
//}

#include<iostream>
#include<fstream>
#include<time.h>
#include<sstream>
#include<cstdio>
#include"GD.h"
//#define TEST

using namespace std;

bool loadAnswerData(string& awFile, vector<int>& awVec);

int main()
{
	ofstream outfile("trainData.txt");
	srand((unsigned)time(NULL));
	for (int i = 0; i < 2000; i++) {
		//原函数 y = 1 + 3x;   创造一个训练集
		double x1 = (rand() % (30));
		//double x2 = (rand() % (50) + 10);
		double y = 1 + 3 * x1;
		outfile << 1 << "," << x1 << "," << y << endl;
	}
	outfile.close();
	cout << "训练文件已生成 " << endl;

	ofstream outTestfile("testData.txt");
	ofstream outAnswerfile("testData.txt");
	srand((unsigned)time(NULL));
	for (int i = 0; i < 2000; i++) {
		//原函数 y = 1 + 3x;   创造一个训练集
		double x1 = rand();
		//double x2 = (rand() % (50) + 10);
		double y = 1 + 3 * x1;
		outTestfile << 1 << "," << x1  << endl;
		outAnswerfile << y << endl;
	}
	outTestfile.close();
	outAnswerfile.close();
	cout << "测试文件、答案文件已生成 " << endl;


	string trainFile = "trainData.txt";
	string testFile = "testData.txt";
	string predictFile = "result.txt";

	GD gradient(trainFile, testFile, predictFile);

	clock_t start1 = clock();
	printf("start train model ...\n");
	gradient.train();
	clock_t end1 = clock();
	cout << "train model time is " << end1 - start1 << endl;

	printf("training end,ready to store the model ... \n");
	gradient.storeModel();

	vector<double> theta;
	for (int i = 0; i < gradient.Weight.size(); i++) {
		theta.push_back(gradient.Weight[i]);
	}
	cout << "预测的原函数为：y = " << theta[0] << " + " << theta[1] << "x1"  << endl;    //我知道所以才这么看结果

#ifdef TEST
	vector<int> answerVec;
	string answerFile = "answer.txt";
	printf("load answer data ...\n");
	loadAnswerData(answerFile, answerVec);
#endif

#ifdef TEST
	printf("let's prediction test ...\n");
	gradient.predict();
#endif
	
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

bool loadAnswerData(string& awFile, vector<int>& awVec) {
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