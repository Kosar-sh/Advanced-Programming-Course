#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;
int to_upper(string input);
int main()
{
    string input;
    while (getline(cin, input))
    {
        input = input + "\n";
        to_upper(input);
    }
    return 0;
}
int to_upper(string input)
{
    char First_char;
    int i = 0;
    if (input == "\n")
    {
        cout << "\n";
        return 0;
    }
    First_char = input[i];
    putchar(toupper(First_char));//print the big case character
    input = input.substr(1);//drop the first character 
    to_upper(input);
    return 1;
}