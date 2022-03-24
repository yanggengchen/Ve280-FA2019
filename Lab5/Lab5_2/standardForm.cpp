//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include <cmath>
#include "standardForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in):a(a_in), b(b_in), c(c_in){}
// TODO: implement this constructor

float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    return b;
}

float quadraticFunction::getC() const {
    return c;
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
	return a * x * x + b * x + c;
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
	root fun_root;
	float delta = b * b - 4 * a * c;
	if (delta > 0) {
		fun_root.realRootNum = 2;
		fun_root.roots[0].imaginary = 0;
		fun_root.roots[1].imaginary = 0;
		fun_root.roots[0].real = (-b - sqrt(delta)) / (2 * a);
		fun_root.roots[1].real = (-b + sqrt(delta)) / (2 * a);
	}
	else if (delta == 0) {
		fun_root.realRootNum = 1;
		fun_root.roots[0].imaginary = 0;
		fun_root.roots[1].imaginary = 0;
		fun_root.roots[0].real = (-b) / (2 * a);
		fun_root.roots[1].real = (-b) / (2 * a);
	}
	else {
		fun_root.realRootNum = 0;
		fun_root.roots[0].imaginary = -sqrt(-delta) / (2 * a);
		fun_root.roots[1].imaginary = sqrt(-delta) / (2 * a);
		fun_root.roots[0].real = (-b) / (2 * a);
		fun_root.roots[1].real = (-b) / (2 * a);
	}
	return fun_root;
}

int quadraticFunction::intersect(quadraticFunction g){
    // TODO: implement this function
	if (a == g.a) return 1;
	else if ((b - g.b) * (b - g.b) - 4 * (a - g.a) * (c - g.c) >= 0) return 1;
	else return 0;
}