#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
int Combination(int First_Val, int Second_Val);
void calculating_result(int first_val, int second_val, int &result);
int main()
{
	//all the ways based on catalan number is calculated by (1/(n+1))*(2n!/n!*n!)
	int square = 0, result;
	cin >> square;
	int First_Val, Second_Val;
	Second_Val = square;
	First_Val = 2 * square;
	result = (Combination(First_Val, Second_Val)) / (square + 1);
	cout << result;
	return 0;
}
void calculating_result(int first_val, int second_val, int &result)
{
	//final result is the answer of 2n!/n!*n!
	//for using less stack divide the result by second_val and then return it 
	int next_num, current_num;
	next_num = Combination(first_val, second_val - 1);
	current_num =first_val - second_val;
	current_num = next_num * (current_num+1);
	result=current_num / second_val;
}
int Combination(int First_Val, int Second_Val)
{
	//calculating the 2n!/n!*n!
	int result = 0;
	if (Second_Val <= 0)
		return 1;
	else
		calculating_result(First_Val, Second_Val, result);
	return result;
}