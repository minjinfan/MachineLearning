#pragma once
#include"Header.h"
#include"InLayer.h"
#include"HiddenLayer.h"
#include"OutLayer.h"

#define InNodeNum 2		// 输入层节点数
#define HiddenNodeNum 4    // 隐藏层节点数 
#define OutNodeNum 1		// 输出层节点数
#define TotalLayer 3

typedef struct sample {
	std::vector<double> inputData;
	std::vector<double> outputData;
}Sample;


class BPNet
{
public:
	BPNet() {};
	BPNet(std::string &filenamne);   //构造函数，初始化 权重
	void forwardPropagation();
	void BackPropagation();
	void train(std::vector<Sample> sampleGroup);
	void prediction(std::vector<Sample> testGroup);
	~BPNet(){}
private:
	double error; //误差率
	double LearnStep = 0.1;   // 学习率
	std::vector<InLayer>* inLayerNode;
	std::vector<HiddenLayer>* hiddenLayerNode;   // 一个隐藏层，多个隐藏层就用矩阵arma::mat
	std::vector<OutLayer>* outLayerNode;

private:
	void InputInitW(std::vector<InLayer> &inLayer);
	void HiddenInitW(std::vector<HiddenLayer>& hiddenLayer);

	void ReadInputData();
};

