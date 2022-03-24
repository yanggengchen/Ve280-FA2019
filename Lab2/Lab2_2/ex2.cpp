/*
 * Lab2 Ex2 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <cstdlib>
#include <iostream>


using namespace std;

typedef struct {
	// TODO: complete struct
	//string name;
	char stu_name[10] = {};
	int chinese_score;
	int math_score;
	int english_score;
} Student;

int compare(const void* p1, const void* p2) {
	// TODO: complete compare function for qsort()
	Student* temp1 = (Student*)p1;
	Student* temp2 = (Student*)p2;
	if ((temp1->chinese_score + temp1->english_score + temp1->math_score) > (temp2->chinese_score + temp2->english_score + temp2->math_score))
		return -1;
	else
		return 1;
	//range from large to small
}

int main() {
	// TODO: read input
	int number = 0;
	cin >> number;
	//number of total students
	Student rank[10] = {};
	int pos = 0;
	//position of current students
	while (number > 0) { 
		cin >> rank[pos].stu_name >> rank[pos].chinese_score >> rank[pos].math_score >> rank[pos].english_score;

		number--;
		pos++;
	}
	// TODO: sort array with qsort()
	qsort(rank, pos, sizeof(Student), compare);
	// TODO: print result
	while (number < pos) {
		int i = 0;
		while (rank[number].stu_name[i] != '\0') {
			cout << rank[number].stu_name[i];
			i++;
		}
		cout << ' '<< rank[number].chinese_score << ' ' << rank[number].math_score << ' ' << rank[number].english_score << endl;
		number++;
	}
	return 0;
}