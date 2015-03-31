/*
    Program: BoxOffice.cp
    Author: William Woodard
    Lab Section: ITCS1212 - L04
    Date: 9/7/2013
    Purpose: The user inputs the movie name and the number of
             adult and child tickets sold and the program will
             calculate the gross profit and the net profit for
             the box office after applying the percentage cut.
             The program will then display what the user inputted:
                (movie name, adult tickets, and child tickets)
             and display the results of the calculations:
                (gross profit, net profit for box office, and
                 distributor's cut).
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    ////Declarations:
    //Constants:
    const double PERCENTAGE_KEPT = 0.2;
    const double ADULT_PRICE = 6.0;
    const double CHILD_PRICE = 3.0;

    //Variables:
    string movieName;           //User input
    double netProfit;           //Calculated
    double grossProfit;         //Calculated
    double distributor;         //Calculates
    int adultTickets;           //User input
    int childTickets;           //User input

    ////Input:
    cout << "Enter the name of the movie: ";
    getline(cin, movieName);    //User inputs the movie's name

    cout << "Enter the number of adult tickets sold: ";
    cin >> adultTickets;        //User inputs the number of adult tickets sold

    cout << "Enter the number of child tickets sold: ";
    cin >> childTickets;        //User inputs the number of child tickets sold

    ////Process:
    /*Calculate profit margins for both adults and children and add them together*/
    grossProfit = (adultTickets * ADULT_PRICE) + (childTickets * CHILD_PRICE);
    /*Calculate net profit made from the percentage kept*/
    netProfit = PERCENTAGE_KEPT * grossProfit;

    /*Calculate the distributor's cut*/
    distributor = grossProfit - netProfit;

    ////Output:
    cout << "\nRevenue Report\n"
         << "==============\n"

         /*Display movie's name as entered by user*/
         << "Movie Name: "
         << setw(16) << "\"" << movieName << "\"" << endl

         /*Display adult tickets sold as entered by user*/
         << "Adult Tickets Sold:"
         << setw(9) << " " << adultTickets << endl

         /*Display child tickets sold as entered by user*/
         << "Child Tickets Sold:"
         << setw(9) << " " << childTickets << endl

         //Set significant figures to display two after decimal place
         << fixed << showpoint << setprecision(2)

         /*Display gross box office profit as calculated*/
         << "Gross Box Office Profit:"
         << setw(4) << "$" << grossProfit << endl

         /*Display box office's cut of the profit as calculated*/
         << "Net Box Office Profit:"
         << setw(6) << "$" << netProfit << endl

         /*Display the distributor's cut of the profit as calculated*/
         << "Distributor's Cut:"
         << setw(10) << "$" << distributor << endl;

    return 0;
}
