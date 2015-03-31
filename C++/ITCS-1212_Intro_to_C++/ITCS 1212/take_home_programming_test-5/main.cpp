/************************************************************************************************************
*      Program: airline.cpp
*       Author: William Woodard
*  Lab Section: ITCS1212 - L04
*         Date: 12/4/2013
*      Purpose: This program keeps track of plane charting statistics, allowing both customer and employee
*                interaction with data and keeping records.
*
*    Algorithm:
*        Input: 1) Ask user for menu choice (customer or employee)
*      Process/Output:
*               2) If customer choice, then display customerMenu()
*                   a) Do until customer doest not want to book any more seats
*               3) If employee choice, then display employeeMenu()
*                   a) Do until employee is done with menu
*               4) Repeat until employee sets the program to end
*    Functions:
*               1) displaySeats()
*               2) customerMenu()
*                   a) Ask user for menu option (book a seat or display stats)
*                   b) If user wants to book a seat, ask user for menu option (enter or let program decide seat)
*                   c) Pick row and column either randomly, or let user decide
*                   d) Update seating chart
*               3) employeeMenu()
*                   a) Ask user for menu option
*                   b) If option 1, display current seating chart displaySeats()
*                   c) If option 2, display available seats
*                   d) If option 3, display available seats per class
*                   e) If option 4, display amount plane has made
*                   f) If option 5, set program to end
************************************************************************************************************/
#include <iostream>
#include <iomanip>                                                      //setw(), fixed, showpoint, setprecision()
#include <limits>                                                       //class: numeric_limits
#include <ctime>                                                        //time()
#include <cstdlib>                                                      //rand(), srand()
#include <string>
using namespace std;

///Global Constant Declarations:
const int   NUMBER_OF_ROWS        = 22;                                 //Number of rows the plane has
const int   NUMBER_OF_COLUMNS     = 7;                                  //Number of seats per row
const int   END_OF_FIRST_CLASS    = 4;                                  //End of first class rows
const int   END_OF_BUSINESS_CLASS = 8;                                  //End of business class rows
const float PRICE_FIRST_CLASS     = 3600.00;                            //Price for a first class ticket
const float PRICE_BUSINESS_CLASS  = 1500.00;                            //Price for a business clsss ticket
const float PRICE_ECONOMY_CLASS   = 550.00;                             //Price for an economy class ticket
const int   TOTAL_NUMBER_OF_SEATS = NUMBER_OF_COLUMNS * NUMBER_OF_ROWS; //Total number of seats in plane

/* Both of these must be changed if one is changed */
const int   NUMBER_OF_EXIT_ROWS            = 4;                         //Number of exit rows in plane
const int   EXIT_ROWS[NUMBER_OF_EXIT_ROWS] = {6, 7, 15, 16};            //The rows that are exit rows

///Function Prototypes:
/* Display the plane seats */
void displaySeats(char seats[][NUMBER_OF_COLUMNS]);
/* Display and run through customer menu */
float customerMenu(char seats[][NUMBER_OF_COLUMNS], int& numOccupiedSeats, int& numOccupiedFirstClass, int& numOccupiedBusinessClass, int& numOccupiedEconomyClass);
/* Display and run through employee menu */
void employeeMenu(char seats[][NUMBER_OF_COLUMNS], int numOccupiedSeats, bool& endProgram, int numOccupiedFirstClass, int numOccupiedBusinessClass, int numOccupiedEconomyClass, float totalEarnedMoney);

/*****************************************************************************
*    Name: main()
*   Input: None, initialize program.
* Process: Ask user for initial input. Decide which menu to display. Allow
*           processes to repeat.
* Returns: 0 if program executes successfully.
*****************************************************************************/
int main()
{
    ///Variable Declarations:
    srand(time(0));                                                     //Seed random generator with current time
    char seats[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];                      //User Input: The seats in the plane : (rows) x (seats per row)
    char menuChoice;                                                    //User Input: The menu the user chooses
    char customerContinue;                                              //User Input: Whether or not the user wants to continue
    bool endProgram              = false;                               //User Input: Employee ends the program
    float totalCost;                                                    //Calculated: The total cost per customer
    int numOccupiedSeats         = 0;                                   //Calculated: The number of occupied seats throughout the plane
    int numOccupiedFirstClass    = 0;                                   //Calculated: The number of occupied seats throughout First Class
    int numOccupiedBusinessClass = 0;                                   //Calculated: The number of occupied seats throughout Business Class
    int numOccupiedEconomyClass  = 0;                                   //Calculated: The number of occupied seats throughout Economy Class
    float totalEarnedMoney       = 0;                                   //Calculated: The total amount of money earned by the plane

    /* Initialize seats to vacant */
    for (int numRow = 0; numRow < NUMBER_OF_ROWS; numRow++)
    {
        for (int numCol = 0; numCol < NUMBER_OF_COLUMNS; numCol++)
        {
            seats[numRow][numCol] = '*';                                //'*' means vacant, 'X' means occupied
        }
    }

    do
    {
        ///Input:
        cout << "Select menu display:" << endl
             << "(Note: 1 or C for customer - 2 or E for employee)" << endl;
        while (!(cin >> menuChoice)                                     //Get valid input for menu choice
               || (menuChoice != '1' && menuChoice != '2'
               && menuChoice != 'C' && menuChoice != 'c' && menuChoice != 'E' && menuChoice != 'e'))
        {
            cin.clear();
            cout << endl << menuChoice << " is invalid." << endl
                 << "Select menu display:" << endl
                 << "(Note: 1 or C for customer - 2 or E for employee)" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << endl;

        switch (menuChoice)                                             //Display chosen menu choice
        {
        case '1':
        case 'c':
        case 'C':
            totalCost = 0;
            do
            {
                /* Add the customer's bill for the seat type chosen */
                totalCost += customerMenu(seats, numOccupiedSeats, numOccupiedFirstClass, numOccupiedBusinessClass, numOccupiedEconomyClass);

                cout << endl << fixed << showpoint << setprecision(2)
                     << "You total bill is: $" << totalCost << endl
                     << "Do you want to continue? (Y or N): ";
                while (!(cin >> customerContinue))                      //Get valid input for whether or not the customer wants to continue
                {
                    cin.clear();
                    cout << endl << customerContinue << " is invalid." << endl
                         << "Do you want to continue? (Y or N): ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << endl;
            } while (customerContinue != 'N' && customerContinue != 'n');

            totalEarnedMoney += totalCost;                              //Add customer's bill to the earned money for the plane
            break;
        case '2':
        case 'E':
        case 'e':
            /* Display employee menu */
            employeeMenu(seats, numOccupiedSeats, endProgram, numOccupiedFirstClass, numOccupiedBusinessClass, numOccupiedEconomyClass, totalEarnedMoney);
            break;
        }//End of switch
    } while (!endProgram);
    return 0;
}//End of main()

/*****************************************************************************
*    Name: displaySeats()
*   Input: 1 parameter:
*          seats -> The array that stores which seats are taken
* Returns: None, void, only displays to screen.
*****************************************************************************/
void displaySeats(char seats[][NUMBER_OF_COLUMNS])
{
    char headerLetter = 'A';                                            //Initial ASCII value

    cout << "         ";                                                //Display header
    for (int numCol = 0; numCol < NUMBER_OF_COLUMNS; numCol++)
    {
        if (numCol == NUMBER_OF_COLUMNS / 3 || numCol == NUMBER_OF_COLUMNS - NUMBER_OF_COLUMNS / 3)
        {
            cout << " " << headerLetter << " ";
        }
        else
        {
            cout << headerLetter << " ";
        }
        headerLetter++;
    }
    cout << endl;

    for (int numRow = 0; numRow < NUMBER_OF_ROWS; numRow++)             //Display body
    {                                                                   //Add a space to distinguish classes
        if (numRow == END_OF_FIRST_CLASS || numRow == END_OF_BUSINESS_CLASS)
        {
            cout << endl << "ROW " << setw(2) << (numRow + 1) << "   ";
        }
        else
        {
            cout << "ROW " << setw(2) << (numRow + 1) << "   ";
        }

        for (int numCol = 0; numCol < NUMBER_OF_COLUMNS; numCol++)      //Display seats per row
        {                                                               //Add a space to distinguish aisles
            if (numCol == NUMBER_OF_COLUMNS / 3 || numCol == NUMBER_OF_COLUMNS - NUMBER_OF_COLUMNS / 3)
            {
                cout << " " << seats[numRow][numCol] << " ";
            }
            else
            {
                cout << seats[numRow][numCol] << " ";
            }
        }
        cout << endl;
    }
}

/*****************************************************************************
*    Name: customerMenu()
*   Input: 5 parametes:
*          seats -> The array that stores which seats are taken
*          numOccupiedSeats -> The number of occupied seats in the plane
*          numOccupiedFirstClass -> The number of occupied First Class seats
*          numOccupiedBusinessClass -> The number of occupied Business Class seats
*          numOccupiedEconomyClass -> The number of occupied Economy Class seats
* Process: Gets and validates user data.
* Returns: None, void;
*          seats, numOccupiedSeats, numOccupiedFirstClass,
*           numOccupiedBusinessClass, numOccupiedEconomyClass are updated by reference.
*****************************************************************************/
float customerMenu(char seats[][NUMBER_OF_COLUMNS], int& numOccupiedSeats, int& numOccupiedFirstClass, int& numOccupiedBusinessClass, int& numOccupiedEconomyClass)
{
    ///Variable Declarations:
    char pickSeat;                                                      //User Input: If the user wants to pick a seat
    char ticketType;                                                    //User Input: The ticket type
    char acceptCost;                                                    //User Input: If the user accepts the cost
    int userAge = 18;                                                   //User Input: The user's age
    int userOption;                                                     //User Input: The option the user selects
    char pickedColChar;                                                 //User Input: The character of the seat picked by the user
    int pickedRow;                                                      //User Input/Calculated: The row picked by user or program
    int pickedCol;                                                      //User Input/Calculated: The seat picked by user or program
    int maxRow;                                                         //Calculated: The maximum row for the program to pick
    int minRow;                                                         //Calculated: The minimum row for the program to pick
    float seatCost;                                                     //Calculated: The cost of the seat chosen
    char headerLetter = 'A';                                            //Calculated: The letter of the column
    bool eligible;                                                      //Calculated: If the user is eligible for the seat
    int seatCounter;                                                    //Calculated: The number of seats occupied
    bool seatsFull;

    cout << "Select an option:" << endl
         << "1. Select a Seat" << endl
         << "2. Display Charting Statistics" << endl;

    while (!(cin >> userOption))                                        //Get valid input for user option
    {
        cin.clear();
        cout << endl << userOption << " is invalid." << endl
             << "1. Select a Seat" << endl
             << "2. Display Charting Statistics" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (userOption)                                                 //Display chosen menu option
    {
    case 1:                                                             //If option 1
        {
            cout << endl
                 << "Do you want to pick your seat, or have us pick it for you? (Y or N): ";
            while (!(cin >> pickSeat))                                  //Get valid input for the user option for picking a seat
            {
                cin.clear();
                cout << endl << pickSeat << " is invalid." << endl
                     << "Do you want to pick your seat, or have us pick it for you? (Y or N): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << endl;

            if (pickSeat == 'Y' || pickSeat == 'y')                     //If the user wants to pick a seat
            {
                cout << "Current plane chart:" << endl;
                displaySeats(seats);                                    //Display current seating chart
                do                                                      //Do while user wants to keep picking
                {
                    do                                                  //Do while not eligible for seat
                    {
                        eligible = true;
                        cout << endl
                             << "Choose a row: " << endl
                             << "Note:" << endl
                             << "Rows 1-" << END_OF_FIRST_CLASS << " are first class" << endl
                             << "Rows " << END_OF_FIRST_CLASS + 1 << "-" << END_OF_BUSINESS_CLASS << " are business class" << endl
                             << "Rows " << END_OF_BUSINESS_CLASS + 1 << "-" << NUMBER_OF_ROWS << " are economy class" << endl;
                        while (!(cin >> pickedRow))                     //Get valid input for the picked row
                        {
                            cin.clear();
                            cout << endl << pickedRow << " is invalid." << endl
                                 << "Choose a row: " << endl
                                 << "Note:" << endl
                                 << "Rows 1-" << END_OF_FIRST_CLASS << " are first class" << endl
                                 << "Rows " << END_OF_FIRST_CLASS + 1 << "-" << END_OF_BUSINESS_CLASS << " are business class" << endl
                                 << "Rows " << END_OF_BUSINESS_CLASS + 1 << "-" << NUMBER_OF_ROWS << " are economy class" << endl;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cout << endl;

                        for (int rowNum = 0; rowNum < NUMBER_OF_EXIT_ROWS; rowNum++)
                        {                                               //Check for exit rows and validate user's age
                            if (pickedRow == EXIT_ROWS[rowNum])         //If the row picked is an exit row
                            {
                                cout << "The row you have chosen is an exit row." << endl
                                     << "How old are you?: ";
                                while (!(cin >> userAge))               //Get valid input for the age of the user
                                {
                                    cin.clear();
                                    cout << endl << userAge << " is invalid." << endl
                                         << "The row you have chosen is an exit row." << endl
                                         << "How old are you?: ";
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }

                                if (userAge < 18)                       //If they are under 18
                                {
                                    eligible = false;                   //They are ineligible for the seat
                                }
                            }
                        }
                    } while (!eligible &&
                             cout << "You must be over eighteen to choose this exit row. Pick another row." << endl);
                    cout << endl
                         << "Choose a seat (A through " << (char)(headerLetter + NUMBER_OF_COLUMNS - 1) << "): ";
                    while (!(cin >> pickedColChar) ||                   //Get valid input for the character corresponding to the column
                           pickedColChar < headerLetter || pickedColChar > headerLetter + NUMBER_OF_COLUMNS - 1)
                    {
                        cin.clear();
                        cout << endl << pickedColChar << " is invalid." << endl
                             << "Choose a seat (A through " << (char)(headerLetter + NUMBER_OF_COLUMNS - 1) << "): ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cout << endl;

                    pickedCol = pickedColChar - 65;                     //Convert character entered to integer
                    pickedRow--;                                        //Account for the user input -> element index
                } while (seats[pickedRow][pickedCol] == 'X' &&
                         cout << "That seat is taken. Pick another seat:" << endl);
            }//End If
            else                                                        //Else the user wants the program to decide
            {
                cout << "To account for exit rows:" << endl
                     << "How old are you?: ";
                while (!(cin >> userAge))                               //Get valid input for the user's age
                {
                    cin.clear();
                    cout << endl << userAge << " is invalid." << endl
                         << "The row you have chosen is an exit row." << endl
                         << "How old are you?: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                do                                                          //Do while seats are full
                {
                    seatsFull = false;
                    cout << "Select ticket type: " << endl
                         << "(Note: F for first class - B for business - E for economy)" << endl;
                    while (!(cin >> ticketType))                            //Get valid input for the ticket type
                    {
                        cin.clear();
                        cout << endl << ticketType << " is invalid." << endl
                             << "Select ticket type: ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cout << endl;

                    if (ticketType == 'F' || ticketType == 'f')             //If ticket type chosen is first class
                    {
                        minRow = 0;
                        maxRow = END_OF_FIRST_CLASS;

                        if (END_OF_FIRST_CLASS * NUMBER_OF_COLUMNS - numOccupiedFirstClass == 0)
                        {
                            seatsFull = true;
                        }
                    }
                    else if (ticketType == 'B' || ticketType == 'b')        //IF ticket type chosen is business class
                    {
                        minRow = END_OF_FIRST_CLASS;
                        maxRow = END_OF_BUSINESS_CLASS;

                        if ((END_OF_BUSINESS_CLASS - END_OF_FIRST_CLASS) * NUMBER_OF_COLUMNS - numOccupiedBusinessClass == 0)
                        {
                            seatsFull = true;
                        }
                    }
                    else                                                    //Else the ticket type chosen is economy class
                    {
                        minRow = END_OF_BUSINESS_CLASS;
                        maxRow = NUMBER_OF_ROWS;

                        if ((NUMBER_OF_ROWS - END_OF_BUSINESS_CLASS) * NUMBER_OF_COLUMNS - numOccupiedBusinessClass == 0)
                        {
                            seatsFull = true;
                        }
                    }

                } while (seatsFull
                         && cout << "That section is full." << endl);

                do                                                      //Do while ineligible
                {
                    eligible = true;

                    pickedRow = rand() % (maxRow - minRow) + minRow;    //Pick random row with constraints
                    pickedCol = rand() % NUMBER_OF_COLUMNS;             //Pick random column with constraints

                    for (int rowNum = 0; rowNum < NUMBER_OF_EXIT_ROWS; rowNum++)
                    {                                                   //If user is under eighteen and row is an exit row
                        if (pickedRow == (EXIT_ROWS[rowNum] - 1) && userAge < 18)
                        {
                            eligible = false;                           //User is ineligible
                        }
                    }
                } while (seats[pickedRow][pickedCol] == 'X' || !eligible);
            }//End of else

            if (pickedRow >= 0 && pickedRow < END_OF_FIRST_CLASS)       //If picked row is in first class
            {
                seatCost = PRICE_FIRST_CLASS;                           //Seat cost is first class
            }                                                           //Else if picked row is in business class
            else if (pickedRow >= END_OF_FIRST_CLASS && pickedRow < END_OF_BUSINESS_CLASS)
            {
                seatCost = PRICE_BUSINESS_CLASS;                        //Seat cost is business class
            }
            else                                                        //Else picked row is in economy class
            {
                seatCost = PRICE_ECONOMY_CLASS;                         //Seat cost is economy class
            }

            seats[pickedRow][pickedCol] = 'H';                          //Temporary display character

            /* Display single row for user validation */
            cout << "You will be placed here (You are H):" << endl
                 << "         ";
            for (int numCol = 0; numCol < NUMBER_OF_COLUMNS; numCol++)
            {
                if (numCol == NUMBER_OF_COLUMNS / 3 || numCol == NUMBER_OF_COLUMNS - NUMBER_OF_COLUMNS / 3)
                {
                    cout << " " << headerLetter << " ";
                }
                else
                {
                    cout << headerLetter << " ";
                }
                headerLetter++;
            }
            cout << endl
                 << "ROW " << setw(2) << (pickedRow + 1) << "   ";

            for (int numCol = 0; numCol < NUMBER_OF_COLUMNS; numCol++)
            {
                if (numCol == NUMBER_OF_COLUMNS / 3 || numCol == NUMBER_OF_COLUMNS - NUMBER_OF_COLUMNS / 3)
                {
                    cout << " " << seats[pickedRow][numCol] << " ";
                }
                else
                {
                    cout << seats[pickedRow][numCol] << " ";
                }
            }
            cout << endl << fixed << showpoint << setprecision(2)
                 << "The cost will be: $" << seatCost << endl
                 << "Do you accept? (Y or N): ";
            while (!(cin >> acceptCost))                                //Get valid input for accepting cost
            {
                cin.clear();
                cout << endl << acceptCost << " is invalid." << endl
                     << endl << fixed << showpoint << setprecision(2)
                     << "The cost will be: $" << seatCost << endl
                     << "Do you accept? (Y or N): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << endl << endl;

            if (acceptCost == 'Y' || acceptCost == 'y')                 //If user accepted the cost
            {
                seats[pickedRow][pickedCol] = 'X';                      //Set seat as occupied
                numOccupiedSeats++;                                     //Add to number of occupied seats counter

                if (pickedRow >= 0 && pickedRow < END_OF_FIRST_CLASS)   //If first class
                {
                    numOccupiedFirstClass++;                            //Add to first class counter
                }                                                       //Else if business class
                else if (pickedRow >= END_OF_FIRST_CLASS && pickedRow < END_OF_BUSINESS_CLASS)
                {
                    numOccupiedBusinessClass++;                         //Add to business class counter
                }
                else                                                    //Else economy class
                {
                    numOccupiedEconomyClass++;                          //Add to economy class counter
                }
            }
            else                                                        //Else user did not accept cost
            {
                seats[pickedRow][pickedCol] = '*';                      //Set seat back to vacant
                seatCost = 0;                                           //Cost of seat is zero
            }

            cout << "The updated plane chart: " << endl;
            displaySeats(seats);                                        //Display updated seating chart

            break;
        }//End of case 1
    case 2:                                                             //If option 2
        {
            cout << endl << "Seating Statistics:" << endl               //Display number of occupied seats in plane
                 << "The number of seats that have been sold: " << numOccupiedSeats << endl;
            for (int numRow = 0; numRow < NUMBER_OF_ROWS; numRow++)     //Display number of seats available in each row
            {
                seatCounter = 0;
                for (int numCol = 0; numCol < NUMBER_OF_COLUMNS; numCol++)
                {
                    if (seats[numRow][numCol] == '*')
                    {
                        seatCounter++;
                    }
                }
                cout << "Number of seats available in Row " << setw(2) << (numRow + 1) << ": " << seatCounter << endl;
            }                                                           //Display number of available seats in first class
            cout << "Number of seats available in First Class: " << NUMBER_OF_COLUMNS * END_OF_FIRST_CLASS - numOccupiedFirstClass << endl
                                                                        //Display number of available seats in business class
                 << "Number of seats available in Business Class: " << NUMBER_OF_COLUMNS * (END_OF_BUSINESS_CLASS - END_OF_FIRST_CLASS) - numOccupiedBusinessClass << endl
                                                                        //Display number of available seats in economy class
                 << "Number of seats available in Economy Class: " << NUMBER_OF_COLUMNS * (NUMBER_OF_ROWS - END_OF_BUSINESS_CLASS) - numOccupiedEconomyClass << endl
                                                                        //Display number of available seats in the entire plane
                 << "Number of seats available in Entire Plane: " << NUMBER_OF_COLUMNS * NUMBER_OF_ROWS - numOccupiedSeats << endl;
            seatCost = 0;                                               //Cost of seat is zero
            break;
        }//End of case 2
    default:                                                            //Case invalid
        {
            cout << "Invalid entry." << endl;
            seatCost = 0;                                               //Cost of seat is zero
        }
    }

    return seatCost;                                                    //Return the cost of the seat
}//End of customerMenu

/*****************************************************************************
*    Name: employeeMenu()
*   Input: 7 parametes:
*          seats -> The array that stores which seats are taken
*          numOccupiedSeats -> The number of occupied seats in the plane
*          endProgram -> Whether or not the employee wants to end the program
*          numOccupiedFirstClass -> The number of occupied First Class seats
*          numOccupiedBusinessClass -> The number of occupied Business Class seats
*          numOccupiedEconomyClass -> The number of occupied Economy Class seats
*          totalEarnedMoney -> The amount of money earned by the plane
* Returns: None, void;
*          numOccupiedSeats, endProgram are updated by reference.
*****************************************************************************/
void employeeMenu(char seats[][NUMBER_OF_COLUMNS], int numOccupiedSeats, bool& endProgram, int numOccupiedFirstClass, int numOccupiedBusinessClass, int numOccupiedEconomyClass, float totalEarnedMoney)
{
    ///Variable Declarations:
    int optionNum;                                                      //User Input: The option the user picks
    char endMenu;                                                       //User Input: If the user wants to end the employee menu display
    string optionFiveMessage;                                           //Calculated: Display whether or not the program will exit

    do                                                                  //Do while user wants to continue menu
    {
        if (!endProgram)                                                //Display appropriate choice for ending the program (option 5)
        {
            optionFiveMessage = "End Program State (Program will exit once employee menu is ends)";
        }
        else
        {
            optionFiveMessage = "Reactivate Program State (Program will continue once employee menu ends)";
        }

        cout << "Choose an option:" << endl
             << "1. Display Seating Chart" << endl
             << "2. Display Seating Count/Availability" << endl
             << "3. Display Seating Count By Price Level" << endl
             << "4. Display Total Earnings" << endl
             << "5. " << optionFiveMessage << endl;
        while (!(cin >> optionNum))                                     //Get valid input for option number
        {
            cin.clear();
            cout << endl << optionNum << " is invalid." << endl
                 << "Choose an option:" << endl
                 << "1. Display Seating Chart" << endl
                 << "2. Display Seating Count/Availability" << endl
                 << "3. Display Seating Count By Price Level" << endl
                 << "4. Display Total Earnings" << endl
                 << "5. " << optionFiveMessage << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << endl;

        switch (optionNum)                                              //Display appropriate option
        {
        case 1:                                                         //If option 1
            displaySeats(seats);
            break;
        case 2:                                                         //If option 2
                                                                        //Display total number of seats
            cout << "Total number of seats: " << TOTAL_NUMBER_OF_SEATS << endl
                                                                        //Display total numebr of booked seats
                 << "Number of booked seats: " << numOccupiedSeats << endl
                                                                        //Display total number of available seats
                 << "Number of available seats: " << TOTAL_NUMBER_OF_SEATS - numOccupiedSeats << endl;
            break;
        case 3:                                                         //If option 3
            cout << "First Class:" << endl
                                                                        //Display number of seats in first class
                 << "Total number of seats: " << NUMBER_OF_COLUMNS * END_OF_FIRST_CLASS << endl
                                                                        //Display number of booked seats in first class
                 << "Number of booked seats: " << numOccupiedFirstClass << endl
                 << endl;
            cout << "Business Class:" << endl
                                                                        //Display number of seats in business class
                 << "Total number of seats: " << NUMBER_OF_COLUMNS * (END_OF_BUSINESS_CLASS - END_OF_FIRST_CLASS) << endl
                                                                        //Display number of booked seats in business class
                 << "Number of booked seats: " << numOccupiedBusinessClass << endl
                 << endl;
            cout << "Economy Class:" << endl
                                                                        //Display number of seats in economy class
                 << "Total number of seats: " << NUMBER_OF_COLUMNS * (NUMBER_OF_ROWS - END_OF_BUSINESS_CLASS) << endl
                                                                        //Display number of booked seats in economy class
                 << "Number of booked seats: " << numOccupiedEconomyClass << endl;
            break;
        case 4:                                                         //If option 4
            cout << fixed << showpoint << setprecision(2)               //Display total amount earned on plane
                 << "The total earned money of this plane is: $" << totalEarnedMoney << endl;
            break;
        case 5:                                                         //If option 5
            if (!endProgram)                                            //If program is not ending
            {
                endProgram = true;                                      //Program is ending
            }
            else                                                        //Else program is ending
            {
                endProgram = false;                                     //Program is not ending
            }
        }
        cout << endl;

        cout << "End employee menu? (Y or N): ";
        while (!(cin >> endMenu))                                       //Get valid input for end menu option
        {
            cin.clear();
            cout << endl << optionNum << " is invalid." << endl
                 << "End employee menu? (Y or N)";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (endMenu != 'Y' && endMenu != 'y');
}//End of employeeMenu()
