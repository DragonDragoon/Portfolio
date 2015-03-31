/************************************************************************************************************
*      Program: Problem_3.cpp
*       Author: William Woodard
*  Lab Section: ITCS1212 - L04
*         Date: 10/15/2013
*      Purpose: This program reads four test grades, and calculates the
*               average of them. It then converts the average to a character
*               equivalent (A,B,C,D,F), and then displays whether or not the
*               user can take the next course.
*
*    Algorithm:
*        Input: 1) Ask the user for four test grades -> 4 vars float testOne, testTwo, testThree, testFour
*      Process: 2) average = calcAverage() -> var float average
*               3) letterGrade = calcLetterGrade() -> var char letterGrade
*               4) canEnroll = calcCanEnroll() -> var string canEnroll
*       Output: 5) displayMessage()
*    Functions:
*               1) float calcAverage(float testOne, float testTwo, float testThree, float testFour)
*                   a) return (testOne + testTwo + testThree + testFour) / 4
*               2) char calcLetterGrade(float average)
*                   a) If average > 90, then return 'A'
*                   b) Else If average > 80, then return 'B'
*                   c) Else If average > 70, then return 'C'
*                   d) Else If average > 60, then return 'D'
*                   e) Else, return 'F'
*               3) string calcCanEnroll(char letterGrade)
*                   a) If letterGrade = 'A' or 'B' or 'C', then return "You can take the next course."
*                   b) Else, return "You cannot take the next course."
*               4) void displayMessage(float average, char letterGrade, string canEnroll)
*                   a) Display numeric grade, letter grade, and the string of whether or not the
*                      user can take the next course
************************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

////Global Constant Declarations:
const float VALUE_A = 90;                               //Lowest value given for a grade of an A
const float VALUE_B = 80;                               //Lowest value given for a grade of a B
const float VALUE_C = 70;                               //Lowest value given for a grade of a C
const float VALUE_D = 60;                               //Lowest value given for a grade of a D, an F is anything below this

////Function Prototypes:
float calcAverage(float, float, float, float);          //Prepare for the average calculation
char calcLetterGrade(float);                            //Prepare for the letter grade calculation
string calcCanEnroll(char);                             //Prepare for the can enroll string calculation statement
void displayMessage(float, char, string);               //Prepare to display the final message

int main()
{
    ////Variable Declarations:
    float testOne;                                      //User input test one
    float testTwo;                                      //User input test two
    float testThree;                                    //User input test three
    float testFour;                                     //User input test four
    float average;                                      //Calculated average of four tests
    char letterGrade;                                   //Calculated letter grade of the average
    string canEnroll;                                   //Calculated string to display

    ////Input:
    /*Ask user to input the four tests*/
    cout << "Enter the grade for the first test: ";
    cin  >> testOne;                                    //User inputs the test one grade
    cout << "Enter the grade for the second test: ";
    cin  >> testTwo;                                    //User inputs the test two grade
    cout << "Enter the grade for the third test: ";
    cin  >> testThree;                                  //User inputs the test three grade
    cout << "Enter the grade for the fourth test: ";
    cin  >> testFour;                                   //User inputs the test four grade

    /*Check to see if cin has been input with valid values*/
    if (!cin)
    {
        /*Display that the user entered invalid input*/
        cout << endl << "*Invalid input*" << endl;
    }
    else
    {
        /*Continue program if values match variable types*/

        ////Process:
        /*Calculate the average value*/
        average = calcAverage(testOne, testTwo, testThree, testFour);
        /*Calculate the letter grade*/
        letterGrade = calcLetterGrade(average);
        /*Calculate whether or not the user can enroll in the next course*/
        canEnroll = calcCanEnroll(letterGrade);

        ////Output:
        /*Display the final statement*/
        displayMessage(average, letterGrade, canEnroll);
    }

    return 0;
}//End of main()

/*****************************************************************************
*    Name: calcAverage()
*   Input: 4 parameters: float testOne, which is the grade for the first test.
*          float testTwo, which is the grade for the second test.
*          float testThree, which is the grade for the third test.
*          float testFour, which is the grade for the fourth test.
* Process: Calculates the average of the four given test grades.
* Returns: Returns the average value of the four tests.
*****************************************************************************/
float calcAverage(float testOne, float testTwo, float testThree, float testFour)
{
    /*Return average value*/
    return (testOne + testTwo + testThree + testFour) / 4;
}//End of calcAverage()

/******************************************************************************
*    Name: calcLetterGrade()
*   Input: 1 parameter: float average, which is the average of the three tests.
* Process: Calculates the equivalent letter grade that is associated with the
*          average calculated earlier by using the constants given at the
*          beginning of the program and comparing them to the average passed.
* Returns: Returns the equivalent character value of the average.
******************************************************************************/
char calcLetterGrade(float average)
{
    /*Evaluate whether or not the average is A, B, C, D, or F*/
    if (average >= VALUE_A)
    {
        /*Return letter grade if the average is over an A value*/
        return 'A';
    }
    else if (average >= VALUE_B)
    {
        /*Return letter grade if the average is over an B value*/
        return 'B';
    }
    else if (average >= VALUE_C)
    {
        /*Return letter grade if the average is over an C value*/
        return 'C';
    }
    else if (average >= VALUE_D)
    {
        /*Return letter grade if the average is over an D value*/
        return 'D';
    }
    else
    {
        /*Return letter grade if the average is anything but an A, B, C, or D*/
        return 'F';
    }
}//End of calcLetterGrade()

/***************************************************************************
*    Name: calcCanEnroll()
*   Input: 1 parameter: character letterGrade, which is the character value
*          of the average.
* Process: Calculates whether or not the student can take the next course,
*          and gives it a string to display later.
* Returns: Returns the string to display in the final message.
***************************************************************************/
string calcCanEnroll(char letterGrade)
{
    /*Evaluate whether or not the average is A, B, C, D, or F*/
    if (letterGrade == 'A' || letterGrade == 'B' || letterGrade == 'C')
    {
        /*Return string to display if letter grade is an A, B, or C*/
        return "You can take the next course.";
    }
    else
    {
        /*Return string to display if letter grade is not A, B, or C*/
        return "You cannot take the next course.";
    }
}//End of calcCanEnroll()

/*******************************************************************************
*    Name: displayMessage()
*   Input: 3 parameters: float average, which is the average of the three tests.
*          character letterGrade, which is the character value of the average.
*          string canEnroll, which is the string to display that states whether
*          or not the user can take the next course.
* Process: Displays the a statement that includes the average, letter grade, and
*          enroll statement that were passed to it.
* Returns: Returns nothing. This functions just displays a final message.
*******************************************************************************/
void displayMessage(float average, char letterGrade, string canEnroll)
{
    cout << endl
         << "Your average is: " << average << ", which is a(n) " << letterGrade << ". " << canEnroll << endl;
}//End of displayMessage()
