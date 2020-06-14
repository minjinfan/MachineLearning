#pragma once
#ifndef INPUTLAYER_H
#define INPUTLAYER_H

#include"Header.h"

class InLayer {
public:
	double bias = 1;              //偏置
	//double biasWeight;

	double inputValue;            // 训练的特征值
	std::vector<double> weight;   // 输入层单个神经元对隐藏层每个神经元的权重

};

#endif // !INPUTLAYER_H