#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "node.h"

std::map<std::string, std::complex<double>> vars {
	{ "pi", 3.141592653 },
	{ "e", 2.7182818284 },
	{ "tau", 3.141592653*2 },
	{ "phi", 1.61803398874 },
	{ "i", 1i }
};

std::map<std::string, int> funcs {
	{ "cos", COS },
	{ "sin", SIN },
	{ "tan", TAN },
	{ "acos", ACOS },
	{ "asin", ASIN },
	{ "atan", ATAN },
	{ "log", LOG }
};

std::string getUserInput() {
	std::cout << ">>> ";
	std::string inpt;
	std::cin >> inpt;
	return inpt;
}

bool isFloat(std::string s) {
    std::istringstream iss(s);
    float dummy;
    iss >> std::noskipws >> dummy;
    return iss && iss.eof();     // Result converted to bool
}

std::string complexToString(std::complex<double> val) {
	std::stringstream ss;
	double delta = 1.0 / 100000.0;
	if (abs(val.real()) - delta > 0 || delta - abs(val.imag()) > 0) {
		ss << val.real();
		if (abs(val.imag()) - delta > 0) {
			ss << "+";
		}
	}
	if (abs(val.imag()) - delta > 0) {
		if (abs(abs(val.imag()) - 1) < delta) {
			ss << (val.imag() > 0 ? "" : "-") << "i";
		}
		else {
			ss << val.imag() << "i";
		}
	}
	return ss.str();
}

Node* makeTree(std::string inpt) {
	Node* node;
	int depth = 0;
	for (int i = inpt.length()-1; i >= 0; i--) {
		if (inpt[i] == ')') {
			depth++;
		}
		if (inpt[i] == '(') {
			depth--;
		}

		if (inpt[i] == '+' && depth == 0) {
			node = new Node(ADDITION);
			node->isOperator = true;
			node->Child(0) = makeTree(inpt.substr(0,i));
			node->Child(1) = makeTree(inpt.substr(i+1));
			return node;
		}
		if (inpt[i] == '-' && depth == 0) {
			node = new Node(SUBTRACTION);
			node->isOperator = true;
			node->Child(0) = makeTree(inpt.substr(0,i));
			node->Child(1) = makeTree(inpt.substr(i+1));
			return node;
		}
	}

	if (depth != 0) {
		std::cout << "Parens are unbalanced. Killing with fire." << std::endl;
		return new Node(0);
	}

	for (int i = inpt.length()-1; i >= 0; i--) {
		if (inpt[i] == ')') {
			depth++;
		}
		if (inpt[i] == '(') {
			depth--;
		}

		if (inpt[i] == '*' && depth == 0) {
			node = new Node(MULTIPLICATION);
			node->isOperator = true;
			node->Child(0) = makeTree(inpt.substr(0,i));
			node->Child(1) = makeTree(inpt.substr(i+1));
			return node;
		}
		if (inpt[i] == '/' && depth == 0) {
			node = new Node(DIVISION);
			node->isOperator = true;
			node->Child(0) = makeTree(inpt.substr(0,i));
			node->Child(1) = makeTree(inpt.substr(i+1));
			return node;
		}
	}

	for (int i = inpt.length()-1; i >= 0; i--) {
		if (inpt[i] == ')') {
			depth++;
		}
		if (inpt[i] == '(') {
			depth--;
		}

		if (inpt[i] == '^' && depth == 0) {
			node = new Node(EXPONENTIAL);
			node->isOperator = true;
			node->Child(0) = makeTree(inpt.substr(0,i));
			node->Child(1) = makeTree(inpt.substr(i+1));
			return node;
		}
	}

	if (inpt[0] == '(' && inpt[inpt.length()-1] == ')') {
		return makeTree(inpt.substr(1,inpt.length()-2));
	}

	for (int i = 0; i < inpt.length(); i++) {
		if (inpt[i] == '(') {
			node = new Node(funcs[inpt.substr(0, i)]);
			node->isOperator = true;
			node->Child(0) = makeTree(inpt.substr(i+1, inpt.length() - i - 2));
			return node;
		}
	}

	if (isFloat(inpt)) {
		return new Node(std::atof(inpt.c_str()));
	} else {
		return new Node(vars[inpt]);
	}
}

std::string parseInput(std::string inpt) {
	for (int i = 0; i < inpt.length(); i++) {
		if (inpt[i] == '=') {
			std::string name = inpt.substr(0, i);
			std::complex<double> value = makeTree(inpt.substr(i+1))->calculate();
			vars[name] = value;
			return "Set variable " + name + " to " + complexToString(value);
		}
	}
	std::stringstream ss;
	ss << complexToString(makeTree(inpt)->calculate());
	return ss.str();
}

int main() {
	std::cout << "Welcome to the calculator!\nEnter any expression, and I'll evaluate it.\n";
	std::string inpt = "";

	while (1) {
		inpt = getUserInput();
		if (inpt == "exit") break;
		std::cout << parseInput(inpt) << std::endl;
	}
	return 0;
}