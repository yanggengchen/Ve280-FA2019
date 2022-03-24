//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include "factoredForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in){
	a = a_in;
	float delta = b_in * b_in - 4 * a * c_in;
	if (delta > 0) {
		r1.imaginary = 0;
		r2.imaginary = 0;
		r1.real = (-b_in - sqrt(delta)) / (2 * a);
		r2.real = (-b_in + sqrt(delta)) / (2 * a);
	}
	else if (delta == 0) {
		r1.imaginary = 0;
		r2.imaginary = 0;
		r1.real = (-b_in) / (2 * a);
		r2.real = (-b_in) / (2 * a);
	}
	else {
		r1.imaginary = -sqrt(-delta) / (2 * a);
		r2.imaginary = sqrt(-delta) / (2 * a);
		r1.real = (-b_in) / (2 * a);
		r2.real = (-b_in) / (2 * a);
	}
}
// TODO: implement this constructor

float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    // TODO: implement this function
	return a * (-r1.real - r2.real);
}

float quadraticFunction::getC() const {
    // TODO: implement this function
	return a * (-r2.imaginary * r1.imaginary + r1.real * r2.real);
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
	return a * x* x + getB() * x + getC();
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
	root result;
	result.roots[0] = r1;
	result.roots[1] = r2;
	if (r1.imaginary == 0) {
		if (r1.real == r2.real) {
			result.realRootNum = 1;
		}
		else result.realRootNum = 2;
	}
	else result.realRootNum = 0;
	return result;
}

int quadraticFunction::intersect(quadraticFunction g) {
    // TODO: implement this function
	if (a == g.a) return 1;
	else if ((getB() - g.getB()) * (getB() - g.getB()) - 4 * (a - g.a) * (getC() - g.getC()) >= 0) return 1;
	else return 0;
}