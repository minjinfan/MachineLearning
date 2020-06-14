#include"Header.h"
#include "BPNet.h"
using namespace std;

inline double getRandom()
{
	return (rand() % (2000) / 1000.0 - 1);
}

inline double sigmoid(double &z)
{
	return 1 / (1 + exp(-z));
}

void BPNet::InputInitW(std::vector<InLayer>& inLayerNode) {
	inLayerNode.resize(InNodeNum + 1);
	srand(time(NULL));
	for (int i = 0; i <= InNodeNum; i++) {  // 0 为偏置的权重；
		for (int j = 0; j < HiddenNodeNum; j++) {
			inLayerNode[i].weight.push_back(getRandom());

		}
	}
}
void BPNet::HiddenInitW(std::vector<HiddenLayer>& hiddenLayerNode) {
	hiddenLayerNode.resize(HiddenNodeNum + 1);
	srand(time(NULL));
	for (int i = 0; i <= HiddenNodeNum; i++) {  // 0 为偏置的权重；
		for (int j = 0; j < OutNodeNum; j++) {
			hiddenLayerNode[i].weight.push_back(getRandom());

		}
	}

}

BPNet::BPNet(std::string& filenamne)
{
	inLayerNode->resize(InNodeNum + 1);
	hiddenLayerNode->resize(HiddenNodeNum + 1);
	outLayerNode->reserve(OutNodeNum + 1);

	InputInitW(*inLayerNode);
	HiddenInitW(*hiddenLayerNode);
	

	ReadInputData();   
}

void BPNet::forwardPropagation()
{
	// input layer to hidden layer
	for (int i = 1; i <= HiddenNodeNum; i++)
	{
		double z = 0.0;
		auto& inNode = *inLayerNode;
		auto& hiddenNode = *hiddenLayerNode;
		int j;
		for (j = 1; j <= InNodeNum; j++)
		{
			z += inNode[j].inputValue * inNode[j].weight[i];
		}
		// 加上偏移量
		z += inNode[0].bias * inNode[0].weight[0];

		double a = sigmoid(z);
		hiddenNode[i].inputValue = z;
		hiddenNode[i].outputValue = a;
	}
	// hidden layer to out layer
	for (int i = 1; i <= OutNodeNum; i++)
	{
		double z = 0.0;
		auto& hiddenNode = *hiddenLayerNode;
		auto& outNode = *outLayerNode;
		int j;
		for (j = 1; j <= HiddenNodeNum; j++) {
			z += hiddenNode[j].outputValue * hiddenNode[j].weight[i];
		}
		z += hiddenNode[0].bias * hiddenNode[0].weight[0];

		double a = sigmoid(z);
		outNode[i].inputValue = z;
		outNode[i].outputValue = a;
	}
} 

void BPNet::BackPropagation()
{
	//输出层误差
	auto& outNode = *outLayerNode;
	for (int i = 1; i <= OutNodeNum; i++)
	{
		double delta = -(outNode[i].label - outNode[i].outputValue) * (1 - outNode[i].outputValue) * outNode[i].outputValue;
		outNode[i].delta = delta;
	}

	//隐藏层误差
	auto& hiddenNode = *hiddenLayerNode;
	for (int i = 1; i <= HiddenNodeNum; i++)
	{
		double delta = 0.0;
		for (int j = 1; j <= OutNodeNum; j++) {
			delta = outNode[j].delta * hiddenNode[i].weight[j];
		}
		delta = delta * hiddenNode[i].outputValue * (1 - hiddenNode[i].outputValue);
		hiddenNode[i].delta = delta;
	}

	//更新权重
	for (int i = 1; i <= HiddenNodeNum; i++)
	{
		double err = 0.0;
		int j;
		for (j = 1; j <= OutNodeNum; j++) {
			err = outNode[j].delta * hiddenNode[i].outputValue;
		}
		hiddenNode[i].weight[j] -= LearnStep * err;
	}

	auto& inNode = *inLayerNode;
	for (int i = i; i <= InNodeNum; i++)
	{
		double err = 0.0;
		int j;
		for (j = 1; j < HiddenNodeNum; j++) {
			err = hiddenNode[j].delta * inNode[i].inputValue;
		}
		inNode[i].weight[j] -= LearnStep * err;
	}
}


void BPNet::ReadInputData() {

}

