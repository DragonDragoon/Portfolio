
#include <iostream>

using namespace std;
/*
char validInput();

int main()
{
    char outputChar = validInput();
    cout << "Hello" << endl
         << outputChar;
}

char validInput()
{
    char inputChar;
    do
    {
        cout << "Input 'A', 'B', or 'C': ";
        cin >> inputChar;
    } while(!(inputChar == 'A' || inputChar == 'B' || inputChar == 'C'));
    return inputChar;
}
*/
int main()
{
/*
    float price, total = 0, average;
    for (int index = 1; index <= 50; index++)
    {
        cout << "Enter price " << index << ": ";
        cin >> price;
        total += price;
        cout << endl << total;
    }
    average = total / 50;
    cout << "The average is: " << average << endl;
*/
/*
    for (int index = 2; index <= 100; index += 2)
    {
        cout << index << " ";
    }
*/
/*
int posInt, sum = 0;
    cout << "Enter 10 positive integers:" << endl;
    for (int index = 1; index <= 10; index++)
    {
        do
        {
            cout << "Enter positive integer #" << index << " : ";
            cin >> posInt;
        } while (posInt < 0);
        sum += posInt;
    }
    cout << "The sum is: " << sum;
*/
/*
    int counter = -1;
    char characterEntry;
    while (characterEntry != '?')
    {
        cout << "Enter a character: ";
        cin >> characterEntry;
        counter++;
    }
    cout << "You entered " << counter << " characters before the '?'" << endl;
*/
/*
    int userEntry = 0, maxInt = 0;
    while (userEntry >= 0)
    {
        cout << "Enter a positive integer (enter a negative integer to quit): ";
        cin >> userEntry;
        if (userEntry > maxInt)
        {
            maxInt = userEntry;
        }
    }
    cout << "The maximum integer you entered was: " << maxInt << endl;
*/
/*
    float emplSalary;
    do
    {
        cout << "Enter an employee's salary ($12,000 to $75,000): ";
        cin >> emplSalary;
    } while (emplSalary < 12000 || emplSalary > 750000);
    cout << "The employee's salary is: $" << emplSalary << endl;
*/
/*
    char input;
    do
    {
        cout << "Enter 'A', 'B', or 'C': ";
        cin >> input;
    } while (!(input == 'A' || input == 'B' || input == 'C'));
    cout << "You entered: " << input << endl;
*/
/*
    float itemNum;
    do
    {
        cout << "Enter a valid item #:";
        cin >> itemNum;
    } while (itemNum < 1 || itemNum > 15);
    cout << "The item: " << itemNum;
*/
/*
    char code;
    do
    {
        cout << "Enter your discount code: ";
        cin >> code;
    } while (code != 'P' || code != 'G');
*/
/*
    const int MY_LUCKY_NUMBER = 7;
    const int MAX_NUMBER_OF_TRIES = 5;
    int numTry;

    for (int numTries = 0; numTries < MAX_NUMBER_OF_TRIES; numTries++)
    {
        cout << "What is my lucky number? (" << (MAX_NUMBER_OF_TRIES - numTries) << " tries left): ";
        cin >> numTry;

        if (numTry == MY_LUCKY_NUMBER)
        {
            cout << "CORRECT!" << endl;
            break;
        }
        else if (numTries == MAX_NUMBER_OF_TRIES - 1)
        {
            cout << "Out of guesses! You lose!" << endl;
            cout << "My lucky number is: " << MY_LUCKY_NUMBER << endl;
        }
        else
        {
            cout << "WRONG! Try again." << endl;
        }
    }
*/
/*
bool P = false;
bool Q = true;
bool R = true;
int i = 1;
int j = 0;

cout << "a. " << (P && Q || !P && !Q) << endl
     << "b. " << (P || Q && !P || !Q) << endl
     << "c. " << (P && Q || !P || !Q && 5 - 2 >= i) << endl
     << "d. " << (2 * 4 + 3 > 12) << endl
     << "e. " << (P && (Q || R)) << endl
     << "f. " << (!!P) << endl
     << "g. " << (!j) << endl
     << "h. " << (j=i) << endl
     << "i. " << (i=j) << endl;
     */
     cout << "Hello " "World";
}
