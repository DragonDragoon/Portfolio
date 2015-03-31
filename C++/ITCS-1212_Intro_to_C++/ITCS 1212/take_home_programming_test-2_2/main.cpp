/****************************************************************************
*      Program: Problem_2.cpp
*       Author: William Woodard
*  Lab Section: ITCS1212 - L04
*         Date: 10/15/2013
*      Purpose: This program calculates the total bill for a customer depending
*               on the plan selected. The user will input the type of plan and
*               and the channels they have, while the business customer will
*               input an additional number of connections.
*
*    Algorithm:
*        Input: 1) Ask user for customer account number -> var integer customerAccountNum
*               2) Display options: "Residential 'R' or 'r', or Business 'B' or 'b'?"
*               3) User input customer code -> var char customerCode
*      Process: 4) If Residential Code ('R' or 'r'), then
*                   a) Ask user for number of premium channels -> var integer premiumChannels
*                   b) totalBill = calcResidential(premiumChannels) -> var float
*                  Else If Business Code ('B' or 'b'), then
*                   a) Ask user for number of connections -> var integer numConnections
*                   b) Ask user for number of premium channels
*                   c) totalBill = function calcBusiness(premiumChannels, numConnections)
*                  Else,
*                   a) Display "Invalid Entry"
*       Output: 5) Display customerAccountNum and totalBill
*    Functions:
*               1) float calcBusiness(integer numConnections, int premiumChannels)
*                   a) If numConnections >= 10, then
*                       i) return $15.00 + $75.00 + $5.00 * (numConnections - 10) + $50.00 * premiumChannels
*                      Else,
*                       i) return $15.00 + $75.00 + $50.00 * premiumChannels
*               2) float calcResidential(int)
*                   a) return $4.50 + $20.50 + $7.50 * premiumChannels
****************************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

////Global Constant Declarations:
const float RESIDENTIAL_BILL_PROCESSING = 4.50;                 //Residential bill processing fee
const float RESIDENTIAL_BASIC_SERVICE = 20.50;                  //Residential fee for basic service
const float RESIDENTIAL_PER_PREMIUM_CHANNEL = 7.50;             //Residential fee per premium channel
const float BUSINESS_BILL_PROCESSING = 15.00;                   //Business bill processing fee
const int BUSINESS_NUMBER_OF_FIRST_CONNECTIONS = 10;            //Business number of first connections
const float BUSINESS_SERVICE_FIRST_CONNECTIONS = 75.00;         //Business for the first number of connections
const float BUSINESS_SERVICE_PER_ADDITIONAL_CONNECTION = 5.00;  //Business fee per additional connection
const float BUSINESS_PER_PREMIUM_CHANNEL = 50.00;               //Business fee per premium channel

////Function Prototypes:
float calcResidential(int);                                     //Prepare for the residential calculation
float calcBusiness(int, int);                                   //Prepare for the business calculation

int main()
{
    ////Variable Declarations:
    char customerCode;                                          //User input customer code
    int customerAccountNum;                                     //User input customer account number
    int premiumChannels;                                        //User input number of premium channels
    int numConnections;                                         //User input number of connections (for business code)
    float totalBill;                                            //Calculated total bill

    ////Input:
    /*Ask user for customer account number*/
    cout << "Enter the customer's account number: ";
    cin  >> customerAccountNum;                                 //User inputs the customer's accounr number

    ////Process:
    if (!customerAccountNum)                                    //Check for valid customer account number
    {
        cout << "*Invalid customer account number*" << endl;
    }
    else
    {
        ////Input:
        /*Display options*/
        cout << "Enter the customer code:" << endl
             << "(Note: 'R' or 'r' for business, or 'B' or 'b' for residential)" << endl;
        cin  >> customerCode;                                   //User inputs the customer code

        ////Process:
        switch (customerCode)
        {
            case 'r':                                           //If lowercase was entered
            case 'R':                                           //If customer code is residential
            {
                /*Ask user for number of premium channels*/
                cout << "Enter the number of subscribed premium channels: ";
                cin  >> premiumChannels;

                totalBill = calcResidential(premiumChannels);

                break;
            }//End of case Residential Code 'R'
            case 'b':                                           //If lowercase was entered
            case 'B':                                           //If customer code is business
            {
                cout << "Enter the number of connections: ";
                cin  >> numConnections;
                cout << "Enter the number of subscribed premium channels: ";
                cin  >> premiumChannels;

                totalBill = calcBusiness(numConnections, premiumChannels);

                break;
            }//End of case Business Code 'B'
            default:                                            //If invalid input for type of plan
            {
                cout << "*Invalid customer code*" << endl;      //Do not accept invalid characters
                totalBill = 0;                                  //Set total bill to a default

                break;
            }//End of case default
        }//End of switch customer code

        ////Output:
        cout << endl
             /*Display the customer's account number*/
             << "Customer code: " << customerAccountNum << endl
             /*Set significant figures to display two digits after decimal place*/
             << showpoint << fixed << setprecision(2)
             /*Display the total customer bill*/
             << "Total cost is: $" << totalBill << endl;
    }

    return 0;
}//End of main()

/***************************************************************************
*    Name: calcResidential()
*   Input: 1 parameter: integer premiumChannels, which is the number of
*          premium channels the resident is subscribed to.
* Process: Calculate the total bill of a residential customer using
*          the appropriate constants declared initially and
*          the number of premium channels passed by parameter.
* Returns: Returns the float value to be used as the total bill.
***************************************************************************/
float calcResidential(int premiumChannels)
{
    /*Return total bill*/
    return RESIDENTIAL_BILL_PROCESSING + RESIDENTIAL_BASIC_SERVICE + premiumChannels * RESIDENTIAL_PER_PREMIUM_CHANNEL;
}//End of calcResidential()

/***************************************************************************
*    Name: calcBusiness()
*   Input: 2 parametes: Integer premiumChannels, which is the number of
*          premium channels the resident is subscribed to.
*          Integer numConnections, which is the number of connections that
*          the business has.
* Process: Calculate the total bill of a business customer using
*          the appropriate constants declared initially and
*          the number of premium channels and the number
*          of connections passed by parameter.
* Returns: Returns the float value to be used as the total bill.
***************************************************************************/
float calcBusiness(int numConnections, int premiumChannels)
{
    /*Evaluate whether or not the number of connections is over the given number of first connections*/
    if (numConnections >= BUSINESS_NUMBER_OF_FIRST_CONNECTIONS)
    {
        /*Return total bill if the number of connections is over or equivalent*/
        return BUSINESS_BILL_PROCESSING + BUSINESS_SERVICE_FIRST_CONNECTIONS
               + BUSINESS_SERVICE_PER_ADDITIONAL_CONNECTION * (numConnections - BUSINESS_NUMBER_OF_FIRST_CONNECTIONS)
               + BUSINESS_PER_PREMIUM_CHANNEL * premiumChannels;
    }
    else
    {
        /*Return total bill if the number of connections is anything but over (less than)*/
        return BUSINESS_BILL_PROCESSING + BUSINESS_SERVICE_FIRST_CONNECTIONS
               + BUSINESS_PER_PREMIUM_CHANNEL * premiumChannels;
    }
}//End of calcBusiness()
