#pragma once
#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H

#include"Header.h"

class HiddenLayer {
public:
	double bias = 1;  //偏置
	//double biasWeight;

	double inputValue;   // z = sum(weight * x)
	double outputValue;  // a = sigmoid(z)
	
	std::vector<double> weight;   // 隐藏层单个神经元对下一层每个神经元的权重

	double delta = 0;        // 单个神经元的激活项误差
};

#endif // !HIDDENLAYER_H
