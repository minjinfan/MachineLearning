#pragma once
#ifndef OUTPUTLAYER_H
#define OPUTPUTLAYER_H

class OutLayer {
public:

	double inputValue;   // z = sum(weight * x)
	double outputValue;  // a = sigmoid(z)，即预测输出

	double label;        // 训练的标签

	double delta = 0;        // 单个神经元的激活项误差

};

#endif // !INPUTLAYER_H
