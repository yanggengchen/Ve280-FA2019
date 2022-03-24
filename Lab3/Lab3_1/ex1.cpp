/*
 * VE280 Lab 3, SU2020.
 * Written by Guoxin Yin
 */

#include <iostream>

using namespace std;

const int MAXSIZE = 10;

void helper_canWin(int count, int arr_record[], int arr[], int position, int *fg) {
	//EFFECTS: return whether the player can win given the start position and previous records
	if (arr[position] == 280) *fg = 1;
	int temp_arr_record[10] = {};
	for (int i = 0; i < 10; i++)
		temp_arr_record[i] = arr_record[i];
	temp_arr_record[position] = 1;
	if ((position + arr[position] < count) && (position + arr[position] >= 0) && (arr_record[position + arr[position]] == 0))
		helper_canWin(count,temp_arr_record,arr,position + arr[position], fg);
	if (position - arr[position] < count) {
		if (position - arr[position] >= 0) {
			if (arr_record[position - arr[position]] == 0) {
				helper_canWin(count, temp_arr_record, arr, position - arr[position], fg);
			}
		}
	}
}

bool canWin(int count, int arr[], int position) {
	// EFFECTS: return whether the player can win given the start position
	// and the card sequence
	if (arr[position] == 280) return 1;
	int record[10] = {};
	int flag = 0;
	int* fg = &flag;
	helper_canWin(count, record, arr, position, fg);
	return flag;
	// TODO: implement this function
}

int main() {
	int count;
	cin >> count;
	int arr[MAXSIZE];
	for (int i = 0; i < count; ++i) {
		cin >> arr[i];
	}
	int position;
	cin >> position;
	cout << canWin(count, arr, position);
}