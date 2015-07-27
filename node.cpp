#include "node.h"

#include <sstream>
#include <iostream>
#include <cmath>

Node::Node(std::complex<double> val) {
	value = val;
	children[0] = nullptr;
	children[1] = nullptr;
}

Node *&Node::Child(bool dir) { return children[dir]; }
std::complex<double> &Node::Value() { return value; }
std::complex<double> Node::calculate() {
	if (isOperator) {
		switch ((int)value.real()) {
			case MULTIPLICATION:
				return Child(0)->calculate() * Child(1)->calculate();
				break;
			case DIVISION:
				return Child(0)->calculate() / Child(1)->calculate();
				break;
			case ADDITION:
				return Child(0)->calculate() + Child(1)->calculate();
				break;
			case SUBTRACTION:
				return Child(0)->calculate() - Child(1)->calculate();
				break;
			case EXPONENTIAL:
				return std::pow(Child(0)->calculate(), Child(1)->calculate());
				break;
			case LOG:
				return std::log(Child(0)->calculate());
				break;
		}
	} else {
		return value;
	}
}