/************************************************************************************************************
*      Program: distance.cpp
*       Author: William Woodard
*  Lab Section: ITCS1212 - L04
*         Date: 11/11/2013
*      Purpose: This program creates 21 graphical points that are interpreted as coordinates with respect
*               to variables 'x' and 'y'. Each value of 'x' and 'y' can only be from values 1 to 200.
*               It then calculates the distance between the first point produced and the twenty points
*               created after to decide which point is the closest and furthest to the first point.
*
*    Algorithm:
*        Input:
*      Process: 1) Produce 21 random values [1<->200] and store x values -> integer array xArray
*               2) Produce 21 random values [1<->200] and store y values -> integer array yArray
*               --> Each index is interpreted as one point
*               --> xArray[0] and yArray[0] is the set point
*               3) Determine distance from set point for each index after [0] -> float array dArray
*                  -> float calcDistance()
*               4) Find the maximum and minumum values in dArray
*       Output: 5) Display maximum and minimum coordinates to the user
*                   a) Calculate distances from distance-squared
*    Functions:
*               1) float calcDistance(int xArray[], int yArray[], int index)
*                   a) return (xArray[index] - xArray[0])^2 + (yArray[index] - yArray[0])^2
************************************************************************************************************/

////Include Libraries:
#include <iostream>
#include <iomanip>                                      //setw()
#include <ctime>                                        //time()
#include <cstdlib>                                      //rand(), srand()
#include <cmath>                                        //pow()
using namespace std;

////Global Constant Declarations:
const int NUMBER_OF_POINTS = 20;                        //Number of points to generate after set point
const int MIN_VALUE = 1;                                //Minimum value of x and y variables
const int MAX_VALUE = 200;                              //Maximum value of x and y variables

////Function Prototypes:
float calcDistanceSquared(int, int, int, int);          //Calculuate the distance-squared

int main()
{
    ////Variable Declarations:
    int xArray[1 + NUMBER_OF_POINTS];                   //Calculated: the x-coordinates of each point
    int yArray[1 + NUMBER_OF_POINTS];                   //Calculated: the y-coordinates of each point
    float dArray[1 + NUMBER_OF_POINTS];                 //Calculated: the distance-squared from the origin point to each point
    srand(time(0));                                     //Seed random generator with current time

    ////Input:
    //None

    ////Process:
    for (int index = 0; index < 1 + NUMBER_OF_POINTS; index++)
    {
        /*Generate each x-value for each point*/
        xArray[index] = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
        /*Generate each y-value for each point*/
        yArray[index] = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
        /*Calculate the distance for the generated point*/
        dArray[index] = calcDistanceSquared(xArray[index], xArray[0], yArray[index], yArray[0]);
    }

    ////Variable Declarations:
    float maxDistance = dArray[1];                      //The maximum distance initialized to the first point
    int maxIndex = 1;                                   //The corresponding index initialized to the first index
    int xMax = xArray[1];                               //The corresponding x-value initialized to the first point
    int yMax = yArray[1];                               //The corresponding y-value initialized to the first point
    float minDistance = dArray[1];                      //The minimum distance initialized to the first point
    int minIndex = 1;                                   //The corresponding index initialized to the first index
    int xMin = xArray[1];                               //The corresponding x-value initialized to the first point
    int yMin = yArray[1];                               //The corresponding y-value initialized to the first point

    /////Process:
    for (int index = 1; index < 1 + NUMBER_OF_POINTS; index++)
    {
        if (maxDistance < dArray[index])                //If the current distance is greater than the current maximum distance
        {                                               //Then
            maxDistance = dArray[index];                //Set new maximum distance
            maxIndex = index;                           //Set new corresponding index
            xMax = xArray[index];                       //Set new corresponding x-value
            yMax = yArray[index];                       //Set new corresponding y-value
        }

        if (minDistance > dArray[index])                //If the currence distance is less than the current minimum distance
        {                                               //Then
            minDistance = dArray[index];                //Set new minimum distance
            minIndex = index;                           //Set new corresponding index
            xMin = xArray[index];                       //Set new corresponding x-value
            yMin = yArray[index];                       //Set new corresponding y-value
        }
    }

    ////Output:
    /*Display header for table*/
    cout << "[Num]   [x]   [y]   [d^2]" << endl
         << " Set: (" << setw(4) << xArray[0] << ", " << setw(4) << yArray[0] << ")" << endl
         << endl;

    /*Display body of table, generated from each point*/
    for (int index = 1; index < 1 + NUMBER_OF_POINTS; index++)
    {
        cout << setw(4) << index << ": (" << setw(4) << xArray[index] << ", " << setw(4) << yArray[index] << ")  " << dArray[index] << endl;
    }

    /*Display Minimum and maximum in table*/
    cout << endl
         /*Calculate and display distances -> distance = (distance^2)^(1/2)*/
         << "[Num]   [x]   [y]   [d^2]     [d]" << endl
         << "Minimum: " << endl
         << setw(4) << minIndex << ": (" << setw(4) << xMin << ", " << setw(4) << yMin << ")  " << setw(5) << minDistance << "   " << pow( minDistance , 0.5) << endl
         << "Maximum: " << endl
         << setw(4) << maxIndex << ": (" << setw(4) << xMax << ", " << setw(4) << yMax << ")  " << setw(5) << maxDistance << "   " << pow( maxDistance , 0.5) << endl;
}//End of main()

/*****************************************************************************
*    Name: calcDistanceSquared()
*   Input: 4 parameters:
*          integer x2 -> the x-value of the point to compare x1 to.
*          integer x1 -> the x-value of the origin point.
*          integer y2 -> the y-value of the point to compare y1 to.
*          integer y1 -> the y-value of the origin point.
* Process: Calculates the distance squared between two points: (x2, y2) and (x1, y1)
* Returns: Returns the value of the distance squared.
*****************************************************************************/
float calcDistanceSquared(int x2, int x1, int y2, int y1)
{
    return pow( x2 - x1 , 2) + pow( y2 - y1 , 2);       //Calculate distance-squared using given formula
}//End of calcDistanceSquared()
