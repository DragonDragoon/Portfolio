/****************************************************************************
*      Program: Problem_1.cpp
*       Author: William Woodard
*  Lab Section: ITCS1212 - L04
*         Date: 10/15/2013
*      Purpose: This program calculates the the bill for a cellphone company
*               depending on the type of service in the plan selected—the
*               regular plan and the premium plan, each with their own methods
*               of calculating the bill. The program will ask for the type of
*               plan, and the amount of minutes used, accounting for the plans
*               and display the final bill to the user.
*
*    Algorithm:
*        Input: 1) Display options: "Regular Plan (R), or Premium Plan (P)?"
*               2) User input plan type -> var char planType
*      Process: 3) If Regular Plan (R), then
*                   a) User input total minutes -> var float totalMinutes
*                   b) If totalMinutes is greater than 200, then
*                       i) totalCost = $20 + $0.15 * (totalMinutes - 200) -> var float
*                      Else,
*                       i) totalCost = $20
*               4) Else If Premium Plan (P), then ask for minutes from 6:00AM-6:00PM,
*                  and ask for minutes from 6:00PM-6:00AM
*                   a) User input minutes A and minutes B -> vars float minutesA, minutesB
*                   b) totalMinutes = minutesA + minutesB
*                   b) If minutesA is greater than 100, then
*                       i) costA = $0.10 * (minutesA - 100) -> var float
*                      Else,
*                       i) costA = $0
*                   c) If minutesB is greater than 300, then
*                       i) costB = $0.05 * (minutesB - 300) -> var float
*                      Else,
*                       i) costB = $0
*                   d) totalCost = $35 + costA + costB
*                  Else,
*               5) Display "Invalid Input"
*       Output: 6) Display results: totalMinutes and totalCost
****************************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    ////Constant Declarations:
    const float REGULAR_BASE_COST = 20.00;          //Base cost of regular plan
    const float REGULAR_COST_PER_MINUTE = 0.15;     //Cost per minute of regular plan
    const int REGULAR_FREE_MINUTES = 200;           //Free minutes for regular plan
    const float PREMIUM_BASE_COST = 35.00;          //Base cost of premium plan
    const float PREMIUM_COST_PER_MINUTE_A = 0.10;   //Cost per minutes of premium plan - first half of day
    const float PREMIUM_COST_PER_MINUTE_B = 0.05;   //Cost per minutes of premium plan - second half of day
    const int PREMIUM_FREE_MINUTES_A = 100;         //Free minutes for premium plan - first half of day
    const int PREMIUM_FREE_MINUTES_B = 300;         //Free minutes for premium plan - second half of day

    ////Variable Declarations:
    char planType;                                  //User input type of plan
    float minutesA;                                 //User input minutes for premium's first half of day
    float minutesB;                                 //User input minutes for premium's second half of day
    float totalMinutes;                             //User input (for regular plan) OR calculated (for premium plan)
    float costA;                                    //Calculated cost for premium plan's first half of day
    float costB;                                    //Calculated cost for premium plan's second half of day
    float totalCost;                                //Calculated total cost of bill

    ////Input:
    cout << "Type 'P' for the Premium Plan, or 'R' for the Regular Plan: ";
    cin  >> planType;                                //User inputs the type of plan

    ////Process:
    switch (planType)
    {
        case 'r':                                   //If lowecase was entered, continue to next case
        case 'R':                                   //If type of plan is premium
        {
            cout << "Enter the total minutes used: ";
            cin  >> totalMinutes;                    //User inputs the total minutes used

            if (totalMinutes > REGULAR_FREE_MINUTES)
            {
                /*Calculate the total cost for regular plan if minutes used is over the free minutes*/
                totalCost = REGULAR_BASE_COST + REGULAR_COST_PER_MINUTE * (totalMinutes - REGULAR_FREE_MINUTES);
            }
            else
            {
                /*Calculate the total cost for regular plan for all other cases*/
                totalCost = REGULAR_BASE_COST;
            }

            break;
        }//End of case Regular Plan 'R'
        case 'p':                                   //If lowercase was entered, continue to next case
        case 'P':                                   //If type of plan is regular
        {
            cout << "Enter the number of minutes used between 6:00AM and 6:00PM: ";
            cin  >> minutesA;                        //User inputs the total minutes used for the first halves for all days
            cout << "Enter the number of minutes used after 6:00PM and before 6:00AM: ";
            cin  >> minutesB;                        //User inputs the total minutes used for the second halves for all days

            if (minutesA > PREMIUM_FREE_MINUTES_A)
            {
                /*Calculate the cost for the minutes used in the first halves of all days if the minutes used is greater
                  than the free minutes for the first half of days for the premium plan*/
                costA = PREMIUM_COST_PER_MINUTE_A * (minutesA - PREMIUM_FREE_MINUTES_A);
            }
            else
            {
                /*Calculate the cost for the minutes used in the first halves of all days for all other cases
                  for the premium plan type*/
                costA = 0;
            }

            if (minutesB > PREMIUM_FREE_MINUTES_B)
            {
                /*Calculate the cost for the minutes used in the second halves of all days if the minutes used is greater
                  than the free minutes for the first half of days for the premium plan*/
                costB = PREMIUM_COST_PER_MINUTE_B * (minutesB - PREMIUM_FREE_MINUTES_B);
            }
            else
            {
                /*Calculate the cost for the minutes used in the second halves of all days for all other cases
                  for the premium plan type*/
                costB = 0;
            }

            /*Calculate the total minutes used for the premium plan*/
            totalMinutes = minutesA + minutesB;
            /*Calculate the total cost of the premium plan*/
            totalCost = PREMIUM_BASE_COST + costA + costB;

            break;
        }//End of Premium Plan 'P'
        default:                                    //If invalid input for type of plan
        {
            cout << "*Invalid Input*" << endl;        //Do not accept invalid characters

            break;
        }//End of case default
    }

    ////Output:
    cout << endl
         /*Display the total minutes for whichever plan chosen*/
         << "Total minutes used: " << totalMinutes << " minutes" << endl
         /*Set significant figures to display two digits after decimal place*/
         << showpoint << fixed << setprecision(2)
         /*Display the total cost for whichever plan chosen*/
         << "Total cost is: $" << totalCost << endl;

    return 0;
}//End of main()
