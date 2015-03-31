#include <iostream>

using namespace std;
/*
int smallestIndex(int arr[], int index)
{
    return arr[index];
}

int main()
{
    int empID[7] = {123, 132, 178, 234, 345, 741, 999};
    int hours[7];
    float payRate[7];
    float wages[7];

    for (int i = 0; i < 7; i++)
    {
        cout << "Employee #" << empID[i] << ":" << endl;
        do
        {
            cout << "Enter hours worked: ";
            cin >> hours[i];
        } while (hours[i] < 0);

        do
        {
            cout << "Enter pay rate: ";
            cin >> payRate[i];
        } while (payRate[i] < 6.00);

        wages[i] = hours[i] * payRate[i];

        cout << smallestIndex(hours, i) << endl;
    }

    return 0;
}
*/

const int size2 = 2;

void procedure(int arr[][2])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int arry[2][size2] = {{1,2},{3,4}};
/*
    arry[0][0] = 1;
    arry[0][1] = 2;
    arry[1][0] = 3;
    arry[1][1] = 4;
*/
    procedure(arry);
    return 0;
}
