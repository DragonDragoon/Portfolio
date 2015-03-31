/************************************************************************************************************
*      Program: mortgage.cpp
*       Author: William Woodard
*  Lab Section: ITCS1212 - L04
*         Date: 11/11/2013
*      Purpose: This program creates and displays an amortization table for the user inputted loan amount,
*               interest rate, and number of years of amortization. It allows the user to repeat the creation
*               of a table for as many times as desired.
*
*    Algorithm:
*        Input: 1) Execute validUserInput()
*      Process: 2) Monthly payment = Execute calcMonthlyPayment()
*       Output: 3) do
*                   a) current monthly interest = principleAmount * monthlyInterest -> var double currentMonthlyInterest
*                   b) current monthly payment = monthlyPayment - currentMonthlyInterest -> var double currentMonthlyPayment
*                   c) new balance = principleAmount - currentMonthlyPayment -> var double newBalance
*                   d) Add 1 to payment counter -> var int paymentNum
*                   e) Display calculated row in table
*                  While the new balance is greater than zero to create body of table
*               4) Repeat for as many times as user desires.
*    Functions:
*               1) validUserInput()
*                   a) Ask user for amount borrowed,    -> var float principleAmount
*                      annual interest rate,            -> var float interestRate
*                      and number of years of the loan. -> var int numYears
*               2) calcMonthlyPayment()
*                   a) monthly interest = interestRate / ( 12 * 100 ) -> var float monthlyInterest
*                   b) number of months = numYears * 12 -> var int numMonths
*                   c) Monthly payment = principleAmount * ( monthlyInterest / ( 1 - ( 1 + monthlyInterest ) ^ (-numMonths))) -> var float monthlyPayment
*                   d) return monthlyPayment
************************************************************************************************************/

////Include Libraries:
#include <iostream>
#include <iomanip>                                              //fixed, showpoint, setprecision(), setw()
#include <cmath>                                                //pow()
using namespace std;

////Function Prototypes:
void validUserInput(double&, double&, int&);                    //Gets user input and validates it
double calcMonthlyPayment(double, double&, double, int, int&);  //Calculates the monthly payment to be made

int main()
{
    ////Variable Declarations:
    double principleAmount;                                     //User input: Principle amount of the loan
    double interestRate;                                        //User input: Interest rate of the loan
    int numYears;                                               //User input: Number of years of amortization
    double monthlyInterest;                                     //Calculated: Monthly interest of the interest rate
    int numMonths;                                              //Calculated: Number of months of amortization
    double monthlyPayment;                                      //Calculated: Amount of monthly payments to be made
    double currentMonthlyInterest;                              //Calculated: Amount of interest compounded
    double currentMonthlyPayment;                               //Calculated: Monthly payment to be paid
    double newBalance;                                          //Calculated: Balance after monthly payment
    int paymentNum;                                             //Calculated: Number of monthly payments made
    char doAgain;                                               //User input: While user wants to repeat the process

    /*Allow user to repeat as many times as desired*/
    do
    {
        paymentNum = 0;                                         //Initialize payment counter for every time run

        ////Input:
        /*Ask user for principle, interest rate, and number of years*/
        validUserInput(principleAmount, interestRate, numYears);


        ////Process:
        /*Calculate monthly payment*/
        monthlyPayment = calcMonthlyPayment(principleAmount, monthlyInterest, interestRate, numYears, numMonths);

        /*Create header for table*/
        cout << endl
             << setw(6) << "[ No.]" << " " << setw(7) << "[Interest]"           << " " << setw(8) << "[Principle]"         << " " << setw(12) << "[  Balance ]" << endl;

        /*Create body for table*/
        do
        {
            /*Calculate the current monthly interest*/
            currentMonthlyInterest = principleAmount * monthlyInterest;
            /*Calculate the current monthly payment*/
            currentMonthlyPayment = monthlyPayment - currentMonthlyInterest;
            /*Calculate the new balance*/
            newBalance = principleAmount - currentMonthlyPayment;
            paymentNum++;                                       //Add one to counter

            ////Output:
            /*Display row in body*/
            cout << fixed << showpoint << setprecision(2)
                 << setw(5) << paymentNum << " " << setw(10) << currentMonthlyInterest << " " << setw(11) << currentMonthlyPayment << " " << setw(12) << newBalance + 0.00001 << endl;

            principleAmount = newBalance;                       //Update control, set until

        } while (newBalance > currentMonthlyPayment);//End of doWhile create body for table

        /*Ask user if user wants to repeat*/
        cout << endl
             << "Enter 'y' to check another loan: ";
        cin >> doAgain;

    } while (doAgain == 'y' || doAgain == 'Y');//End of doWhile user wants to check more loans

}

/*****************************************************************************
*    Name: validUserInput()
*   Input: 3 parameters:
*          principleAmount -> reference: the amount of the loan
*          interestRate -> reference: the intest rate of the loan
*          numYears -> reference: the number of years of amortization
* Process: Gets and validates user data.
* Returns: None, void;
*          principleAmount, interestRate, numYears are changed by reference.
*****************************************************************************/
void validUserInput(double& principleAmount, double& interestRate, int& numYears)
{
    do
    {
    cout << "Enter the amount borrowed: ";                      //Ask user for the loan amount
    cin >> principleAmount;                                     //User inputs the loan amount
    } while (principleAmount < 0);                              //doWhile initial amount is less than zero

    do
    {
    cout << "Enter the interest rate: ";                        //Ask user for interest rate
    cin >> interestRate;                                        //User inputs the interest rate
    } while (interestRate < 0);                                 //doWhile interest rate is less than zero

    do
    {
    cout << "Enter the number of years: ";                      //Ask user for number of years of amortization
    cin >> numYears;                                            //User inputs the number of years
    } while (numYears < 0);                                     //doWhile number of years is less than zero
}

/*****************************************************************************
*    Name: calcMonthlyPayment()
*   Input: 5 parameters:
*          principleAmount -> the amount of the loan
*          monthlyInterest -> reference: the compounded monthly interest
*          interestRate -> the intest rate of the loan
*          numYears -> the number of years of amortization
*          numMonths -> reference: the number of months of amortization
* Process: Calculates the monthlyInterest using the interest rate inputted.
*          Calculates the number of months using the number of years inputted.
*          Calculates the monthly payment using the principle amount (principleAmount)
*           monthly interest (monthlyInteres) and number of months (numMonths).
* Returns: monthly payment, double -> to be stored in variable monthlyPayment
*           is the monthly payment amounts to be made.
*          monthlyInterest and numMonths are updated by reference.
*****************************************************************************/
double calcMonthlyPayment(double principleAmount, double& monthlyInterest, double interestRate, int numYears, int& numMonths)
{
    monthlyInterest = interestRate / ( 12 * 100 );              //Calculate the monthly interest rate from given interest rate
    numMonths = numYears * 12;                                  //Calcualte the number of months from given years

    /*Calculate and return the monthly payments to be made*/
    return principleAmount * ( monthlyInterest / ( 1 - pow( 1 + monthlyInterest , -1 * numMonths )));
}
