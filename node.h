#ifndef NODE_H
#define NODE_H

#include <string>
#include <complex>

const int ADDITION = 0, SUBTRACTION = 1, MULTIPLICATION = 2, DIVISION = 3,
	EXPONENTIAL = 4, LOG = 5, SIN = 6, COS = 7, TAN = 8, ASIN = 9,
	ACOS = 10, ATAN = 11;

class Node {
public:
	Node(std::complex<double> val);
	Node *&Child(bool dir);
	std::complex<double> &Value();
	bool isOperator = false;
	std::complex<double> calculate();
protected:
	std::complex<double> value;
	Node *children[2];
};
#endif
