#include "ex1.h"

int dot(list_t v1, list_t v2){
	// TODO: implement dot function
	int sum = 0;
	while ((!list_isEmpty(v1)) && (!list_isEmpty(v2))) {
		sum = sum + list_first(v1) * list_first(v2);
		v1 = list_rest(v1);
		v2 = list_rest(v2);
	}
	return sum;
}

list_t filter_odd(list_t list){
	// TODO: implement filter_odd function
	list_t result, temp;
	result = list_make();
	temp = list_make();
	while (!list_isEmpty(list)) {
		if (list_first(list) % 2 == 1)
			temp = list_make(list_first(list), temp);
		list = list_rest(list);
	}
	while (!list_isEmpty(temp)) {
		result = list_make(list_first(temp), result);
		temp = list_rest(temp);
	}
	return result;
}

list_t filter(list_t list, bool (*fn)(int)){
	// TODO: implement filter function
	list_t result, temp;
	temp = list_make();
	result = list_make();
	while (!list_isEmpty(list)) {
		if (fn(list_first(list)))
			result = list_make(list_first(list), result);
		list = list_rest(list);
	}
	while (!list_isEmpty(temp)) {
		result = list_make(list_first(temp), result);
		temp = list_rest(temp);
	}
	return result;
}

