#include <iostream>

using namespace std;

void tryMe(int);

int main()
{
    int x = 8;
    for (int count = 0; count < 5; count++)
    {
        tryMe(x);
    }
}
void tryMe(int v)
{
    int num = 2;

    if (v % 2 == 0)
    {
        num++;
        v = v + 3;
    }
    else
    {
        num--;
        v = v + 5;
    }
    cout << v << ", " << num << endl;
}

