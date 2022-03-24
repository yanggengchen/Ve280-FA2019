#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;

bool triangle_Number(int num)
{
	if ((floor(sqrt(2 * num)) * (floor(sqrt(2 * num)) + 1) == num) || (floor(sqrt(2 * num)) * (floor(sqrt(2 * num)) - 1) == num))
	//take a close integer to the square root of 2*num, and see whether the integer times its adjacent integer gets 2*num, if it does, then the number is triangle number
		return 1;
	else
		return 0;
}

bool palindrome(int num)
{
	int power = 0, num_array[9] = {};
	while (num >= 1)
	{
		num_array[power] = num % 10;
		num = (num - num_array[power]) / 10;
		power++;
	}
	//turn the number into an array digits in the reverse order
	for (int i = 0; i < floor(power / 2); i++)
	{
		if (num_array[i] != num_array[power - i - 1])
			return 0;
		//test whether the value of the digit is equal to that when the number is read on the other way
	}
	return 1;
}

bool power_Number(int num)
{
	double power = 0;
	for (int i = 2; i <= floor(sqrt(num)); i++)
	{
		power = log(num) / log(i);
		//represent num as i^power
		if (power - floor(power) == 0)
		//test whether power is integer
			return 1;
	}
	return 0;
}

bool abundant_Number(int num)
{
	int sum = 1;
	//summation of the number's proper divisor, taking 1 into account
	for (int i = 2; i <= floor(sqrt(num)); i++)
	{
		if (num % i == 0)
			sum = sum + i + num / i;
		//add both the divisors since i <= sqrt(num)
	}
	if (sum > num)
		return 1;
	else
		return 0;
}

int main(){
	int num = 0,situation = 0;
	while ((num <= 0) || (num > 10000000) || (situation <= 0) || (situation >= 5))
	{
		cout << "Please enter the integer and the test number: ";
		cin >> num >> situation;
	}
	switch (situation) {
		case 1:
			cout << triangle_Number(num);
			break;
		case 2:
			cout << palindrome(num);
			break;
		case 3:
			cout << power_Number(num);
			break;
		case 4:
			cout << abundant_Number(num);
			break;
	}
	return 0;
}