#include <iostream>

using namespace std;

char validInput()
{
    char inputChar;
    do
    {
        cout << "Input 'A', 'B', or 'C': ";
        cin >> inputChar;
    } while(inputChar != 'A' || inputChar != 'B' || inputChar != 'C');
    return inputChar;
}
int main()
{
    //cout << "Hello" << endl
    //     << validInput();
}
