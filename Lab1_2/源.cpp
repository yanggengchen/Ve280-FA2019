/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[]) {
	// TODO: Implement this function.
	bool alphabetic = 0;
	//satisfy first requirement
	bool numerial = 0;
	//satisfy second requirement
	bool non_alphanumeric = 0;
	//satisfy third requirement
	while (*password != '\0')
	{
		if (*password >= 48 && *password <= 57)
			numerial = 1;
		//satisfy requirement 2
		else if ((*password >= 65 && *password <= 90) || (*password >= 97 && *password <= 122))
			alphabetic = 1;
		//satisfy requirement 1
		else
			non_alphanumeric = 1;
		//satisfy requirement 3
		if (alphabetic == 1 && numerial == 1 && non_alphanumeric == 1)
			return 1;
		//satisfy all the conditions
		password++;
	}
	return 0;
}


int main() {
	char password[50] = {};
	cin >> password;
	cout << isValidPassword(password) << endl;
}
