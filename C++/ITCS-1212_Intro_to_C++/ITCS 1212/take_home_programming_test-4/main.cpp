/************************************************************************************************************
*      Program: dicegame
*       Author: William Woodard
*  Lab Section: ITCS1212 - L04
*         Date: 11/22/2013
*      Purpose: This program allows a defined number of players to play a (6-sided) dice game.
*
*    Algorithm:
*        Input:  1) Ask user for number of players & winning score & names
*               for each turn and each user, until a user achieves the winning score and the last turn is active
*                2) User rolls dice
*      Process:  3) Random dice generation
*                4) Calculate accumulated score
*        Input:  5) User decides which dice to lock, repeat until all chosen -> repeat 2 - 5 until farkle or done
*      Process:  6) If farkle, user looses accumulated score, and goes to next turn
*                7) If hot dice, user gets an extra turn
*                8) Add accumulated score
*                9) If total score of player is greater than the winning score, last turn activates
*               end of loop
*               10) If another user scores higher than highest score, that user is now selected
*       Output: 11) Display winner, ask if users want to play again
*               12) Repeat entire game if users want to play again
*    Functions:
*               1) int calcPossibleScore(int*, int*, bool)
*                a) Evaluate the occurences of same dice rolls
*                b) Accumulate them
*                c) Display point value messages if wanted
*                d) Return accumulated point values
*
*               2) bool calcHotDice(bool*, int*, int*)
*                a) Evaluate if point values possible from each dice
*                b) If so, that dice is 'hot'
*                c) Evaluate if each dice is 'hot'
*                d) If so, dice are 'hot'
*                e) Return if dice are 'hot' or not
*
*               3) void displayCurrentDice(int*, int*)
*                a) Evaluate values of unlocked dice
*                b) Evaluate values of locked dice
*                c) Display values which are not zero.
************************************************************************************************************/

////Include Libraries:
#include <iostream>                             //cout, cin
#include <string>                               //string
#include <ctime>                                //time()
#include <cstdlib>                              //rand(), srand()
#include <limits>                               //class: numeric_limits
using namespace std;                            //inherit std::

////Global Constant Declarations:
const int NUMBER_OF_DICE = 6;                   //Number of dice to be used in the game
const int NUMBER_OF_SIDES = 6;                  //Number of sides each dice has (Note: Anything above 6 will not be scored)

/* Scorings */
const int SCORE_FOR_EACH_1 = 100;               //Value of each 1 scored that is not a triplet 1
const int SCORE_FOR_EACH_5 = 50;                //Value of each 5 scored that is not a triplet 5
const int SCORE_FOR_THREE_1 = 1000;             //Value of scoring triplet 1s
const int SCORE_FOR_THREE_2 = 200;              //Value of scoring triplet 2s
const int SCORE_FOR_THREE_3 = 300;              //Value of scoring triplet 3s
const int SCORE_FOR_THREE_4 = 400;              //Value of scoring triplet 4s
const int SCORE_FOR_THREE_5 = 500;              //Value of scoring triplet 5s
const int SCORE_FOR_THREE_6 = 600;              //Value of scoring triplet 6s

////Function Prototypes:
int calcPossibleScore(int*, int*, int* ,bool);        //Function to calculate possible scores
bool calcHotDice(bool*, int*, int*);            //Function to calculate whether the user has hot dice
void displayCurrentDice(int*, int*);            //Function to display the current dice

/*****************************************************************************
*    Name: main()
*   Input: 0 parameters:
           Initial variables declared.
* Process: Runs the game, displays output that does not re-occur.
* Returns: 0 if successful.
*****************************************************************************/
int main()
{
    ////Declarations:
    int numberOfPlayers = 0;                            //User Input: Number of players that will be playing game
    int winningScore;                                   //User Input: The winning score that each player tries to achieve
    char continueGame;                                  //User Input: Y or N if user wants to continue game
    char scoreDice;                                     //User Input: Y or N if user wants to score current dice
    int selectDice;                                     //User Input: Number of dice that user wants to lock
    int highestScore;                                   //Calculated: The current highest score
    bool hasHotDice;                                    //Calculated: Whether or not user has hot dice
    int exemptPlayer;                                   //Calculated: The exempt player on the last turn who does not play
    int countThrows;                                    //Calculated: The number of throws a player has made
    char selectMore;                                    //User Input: Y or N if user wants to select more dice to lock
    int accumulatedScore;                               //Calculated: The user's accumulated score for the turn

/*
    ////Post Declarations:
    string playerNames[numberOfPlayers];                //User Input: The names of each player
    int setDice[NUMBER_OF_DICE] = {0};                  //User Input: The locked dice
    int dice[NUMBER_OF_DICE] = {0};                     //Calculated: The unlocked dice
    int currentNumOfEach[NUMBER_OF_SIDES] = {0};        //Calculated: The multiple occurences of each value
    int currentNumOfThrows[NUMBER_OF_DICE] = {0};       //Calculated: The number of throws each dice has made
    int playerScores[numberOfPlayers];                  //Calculated: The scores of each player
    bool isHotDice[NUMBER_OF_DICE];                     //Calculated: The hot dice
    bool lastTurn = false;                              //Calculated: The last turn of the game
    int firstPlace = 0;                                 //Calculated: The player that is in first place
    int currentNumOfEachSet[NUMBER_OF_SIDES] = {0};     //Calculated: The current occurence of each locked dice
*/
    srand(time(0));                                     //Seed the random generator with the current time

    do                                                  //Do until users do not want to play game
    {
        ////Input:
        cout << "You are playing: Farkle" << endl << endl

        /* Get the number of players */
             << "Enter number of players (two minimum): ";

        while (!(cin >> numberOfPlayers) || numberOfPlayers < 2)        //Get valid input for number of players
        {
            cin.clear();
            cout << endl << numberOfPlayers << " is invalid. You must have two or more players." << endl
                         << "Enter number of players (two minimum): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter the winning score amount (10000 default): ";

        while (!(cin >> winningScore) || winningScore <= 0)             //Get valid input for the winning score
        {
            cin.clear();
            cout << endl << winningScore << " is invalid. The winning score must be greater than zero." << endl
                         << "Enter the winning score amount (10000 default): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        ////Updated Declarations:
        string playerNames[numberOfPlayers];                //User Input: The names of each player
        int playerScores[numberOfPlayers];                  //Calculated: The scores of each player
        bool isHotDice[NUMBER_OF_DICE];                     //Calculated: The hot dice
        bool lastTurn = false;                              //Calculated: The last turn of the game
        int firstPlace = 0;                                 //Calculated: The player that is in first place
        int dice[NUMBER_OF_DICE] = {0};                     //Calculated: The unlocked dice

        for (int activePlayer = 0; activePlayer < numberOfPlayers; activePlayer++)
        {
            /* Initialize variable-size scores array to zero */
            playerScores[activePlayer] = 0;

            cout << "Enter Player " << (activePlayer + 1) << "'s name: ";
            cin.sync();
            getline(cin, playerNames[activePlayer], '\n');                              //Enter the player's name
        }

        ////Process:
        do                                                                              //Do rounds until final round
        {
            for (int activePlayer = 0; activePlayer < numberOfPlayers; activePlayer++)  //Do turns until all turns are finished
            {
                if (activePlayer != exemptPlayer)                                       //Do not let exempt player play on final round
                {
                    do                                                                  //Do turn player again if player has hot dice
                    {
                        ////Initialize updated variables
                        int setDice[NUMBER_OF_DICE] = {0};                              //User Input: The locked dice
                        int currentNumOfEach[NUMBER_OF_SIDES] = {0};                    //Calculated: The multiple occurences of each value
                        int currentNumOfThrows[NUMBER_OF_DICE] = {0};                   //Calculated: The number of throws each dice has made
                        countThrows = 1;                                                //Set throw count to one (User already did one throw)
                        int throwOnSameTurn[NUMBER_OF_DICE] = {0};

                        cout << endl
                             << "Player " << (activePlayer + 1) << " (" << playerNames[activePlayer] << ") turn: " << endl
                             << "Current score: " << playerScores[activePlayer] << endl;
                        cin.sync();
                        cout << "Press the enter key to roll the dice..." << endl;
                        cin.get();                                                      //Let player roll the dice when ready

                        for (int diceNum = 0; diceNum < NUMBER_OF_DICE; diceNum++)      //For each dice
                        {
                            dice[diceNum] = rand() % NUMBER_OF_SIDES + 1;               //Get random dice values in the range of their sides
                            currentNumOfEach[dice[diceNum] - 1]++;                      //Add one to the current occurences of each value
                            isHotDice[diceNum] = false;                                 //Initialize each dice as "not hot"
                            currentNumOfThrows[diceNum] = countThrows;                  //Count the dice that have been thrown (one throw)

                            cout << (diceNum + 1) << ":[" << dice[diceNum] << "] ";     //Display initial dice roll
                        }//End of for
                        cout << endl << endl;

/*                                                                                       //DEBUG: Display current numbers of each side
                        for (int sideNum = 0; sideNum < NUMBER_OF_SIDES; sideNum++)
                        {
                            cout << "[" << currentNumOfEach[sideNum] << "] ";
                        }//End of for
                        cout << endl;
*/                                                                                      //END OF DEBUG

                        /* Calculate possible score */
                        accumulatedScore = calcPossibleScore(currentNumOfEach, currentNumOfThrows, throwOnSameTurn, true);   //Evaluate current roll's score

                        if (accumulatedScore == 0)                                      //If no dice can score, user farkles before being able to lock dice
                        {
                            cout << endl << endl
                                 << "** Player " << (activePlayer + 1) << " (" << playerNames[activePlayer] << ") has Farkled!**" << endl
                                 << "No possible points! Turn is over." << endl;
                            scoreDice = 'Y';
                        }
                        else                                                            //Else, some dice can score, and user can lock any dice to roll again
                        {
                            cout << "Your possible score for this roll is: " << accumulatedScore << endl
                                 << "Do you want to score the dice? (Y or N): ";
                            cin  >> scoreDice;                                          //Get if user wants to score dice
                            cout << endl;
                        }

                        while (scoreDice == 'N' || scoreDice == 'n')                    //While the user does not want to score dice
                        {
                            do                                                          //Do until player farkles
                            {
                                int countDice;

                                do                                                      //Do until user entry would be invalid (all dice cannot be locked)
                                {
                                    countDice = 0;
                                    for (int numDice = 0; numDice < NUMBER_OF_DICE; numDice++)
                                    {
                                        if (dice[numDice] == 0)
                                        {
                                            countDice++;                                //Count the numebr of dice that are locked
                                        }
                                    }

                                    if (countDice >= (NUMBER_OF_DICE - 1))              //Do not allow player to lock all dice
                                    {
                                        cout << endl << endl << countDice << " dice selected. You cannot select any more dice.";
                                    }
                                    else                                                //Else, player can still lock more dice
                                    {
                                        displayCurrentDice(dice, setDice);              //Display the current dice for user

                                        cout << "Which dice would you like to lock? (1 through " << NUMBER_OF_DICE << "):" << endl;
                                        if (!(cin >> selectDice))                       //Do not allow user to make cin go into failed state
                                        {
                                            cin.clear();
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        }
                                    }
                                } while ((!(selectDice >= 1 && selectDice <= NUMBER_OF_DICE))
                                         && cout << endl << "*Invalid Entry*" << endl << endl
                                         && countDice < (NUMBER_OF_DICE - 1)
                                        );                                              //Make user repeat until valid entry is given

                                if (dice[selectDice - 1] != 0 && selectDice != 0)                          //If the current dice value is not zero
                                {
                                    setDice[selectDice - 1] = dice[selectDice - 1];
                                    dice[selectDice - 1] = 0;
                                }                                                       //Do not allow locked dice to become zero

                                displayCurrentDice(dice, setDice);                      //Display the updated locked an unlocked dice

                                cout << endl << " - Another? (Y or N): ";
                                cin  >> selectMore;                                     //Ask if user wants to lock more dice

                                //correction++;
                                //setDice[5] -= correction * correction + correction * correction;
                            } while (selectMore == 'Y' || selectMore == 'y');           //If user does not want to lock more dice, continue with game

                            int currentNumOfEachSet[NUMBER_OF_SIDES] = {0};             //Calculated: The current occurence of each locked dice

                            for (int diceNum = 0; diceNum < NUMBER_OF_DICE; diceNum++)
                            {
                                currentNumOfEachSet[setDice[diceNum] - 1]++;            //Count number of each occurence of dice values
                            }

                            countThrows++;                                              //Count number of throws made

                            cin.sync();
                            cout << "Press the enter key to roll the dice..." << endl;
                            cin.get();                                                  //Allow user to decide when to throw dice

                            /* Set current number of each dice to zero */
                            for (int diceNum = 0; diceNum < NUMBER_OF_DICE; diceNum++)
                            {
                                currentNumOfEach[diceNum] = 0;
                            }

                            cout << endl << endl << "(Note: [X] = unlocked | {X} = locked)" << endl;
                            for (int diceNum = 0; diceNum < NUMBER_OF_DICE; diceNum++)  //Display new dice roll
                            {
                                if (dice[diceNum] != 0)
                                {
                                    dice[diceNum] = rand() % 6 + 1;
                                    currentNumOfEach[dice[diceNum] - 1]++;
                                    currentNumOfThrows[diceNum] = countThrows;
                                    throwOnSameTurn[diceNum] = true;

                                    cout << (diceNum + 1) << ":[" << dice[diceNum] << "] ";
                                }
                                else
                                {
                                    cout << (diceNum + 1) << ":{" << setDice[diceNum] << "} ";
                                }
                            }//End of for
                            cout << endl << endl;
                                                                                        //Calculate new score
                            int newScore = calcPossibleScore(currentNumOfEach, currentNumOfThrows, throwOnSameTurn, true);
                            hasHotDice = calcHotDice(isHotDice, dice, setDice);         //Calculate if player has hot dice

                            if (newScore == 0 && !hasHotDice)                           //If the new score does not have any dice that can score
                            {
                                cout << endl << endl
                                     << "** Player " << (activePlayer + 1) << " (" << playerNames[activePlayer] << ") has Farkled!**" << endl
                                     << "No possible points! Turn is over." << endl << endl;
                                accumulatedScore = newScore;
                                scoreDice = 'Y';
                            }                                                           //Player has farkled, turn ends
                            else                                                        //Else, player can lock more to reroll or score dice
                            {                                                           //Calculate the new accumulated points
                                accumulatedScore = newScore + calcPossibleScore(currentNumOfEachSet, currentNumOfThrows, throwOnSameTurn, true);

                                cout << "Your accumulated score for this turn is: " << accumulatedScore << endl
                                     << "Do you want to score the dice? (Y or N): ";
                                cin  >> scoreDice;                                      //Get if user wants to score dice
                                cout << endl << endl;
                            }
                        }                                                               //User now wants to score dice

                        playerScores[activePlayer] += accumulatedScore;                 //Add to player's score

                        cout << endl                                                    //Display updated score
                             << "Player " << (activePlayer + 1) << " (" << playerNames[activePlayer] << ") current score: " << playerScores[activePlayer] << endl << endl;

                        hasHotDice = calcHotDice(isHotDice, dice, setDice);           //Calculate if player has hot dice

                        if (hasHotDice)                                                 //If player has hot dice, player can go another turn
                        {
                            cout << endl << endl
                                 << "** Player " << (activePlayer + 1) << " (" << playerNames[activePlayer] << ") has Hot Dice!!**" << endl
                                 << "All dice scored! Player gets another turn!" << endl << endl;
                        }
                    } while (hasHotDice);                                               //While player has hot dice
                }
            }//End of for (turn)

            /* Find highest score */
            highestScore = playerScores[0];
            firstPlace = 0;

            for (int activePlayer = 0; activePlayer < numberOfPlayers; activePlayer++)  //Find the player with the highest score
            {
                if (playerScores[activePlayer] > highestScore)
                {
                    highestScore = playerScores[activePlayer];                          //Set the new highest score
                    firstPlace = activePlayer;                                          //Set the player in first place
                }
            }

            if (highestScore >= winningScore && lastTurn != true)                       //If their score is higher than the winning score, but it is not the last turn
            {
                cout << "Player " << (firstPlace + 1) << " (" << playerNames[firstPlace] << ") has over " << winningScore << " points!" << endl
                     << "All remaining players have one final turn try to get over " << highestScore << " points!" << endl;
                exemptPlayer = firstPlace;                                              //Exempt that player from last turn
            }

            if (lastTurn)                                                               //End turns
            {
                lastTurn = false;
            }
            else
            {
                lastTurn = true;
            }
        } while (highestScore < winningScore || lastTurn);                              //Do each round, until the last
                                                                                        //Announce winning player
        cout << "**Player " << (firstPlace + 1) << " (" << playerNames[firstPlace] << ") has won the game!**" << endl
             << "Congratulations " << playerNames[firstPlace] << " for making " << highestScore << " points!" << endl << endl;

        cout << "Do you want to play the game again? (Y or N): ";
        cin  >> continueGame;                                                           //Get if users want to play game again
    } while (continueGame == 'Y' || continueGame == 'y');                               //Continue new games until userse do not want to play again

    return 0;
}//End of main()

/*****************************************************************************
*    Name: calcPossibleScore()
*   Input: 3 parameters:
*           currentNumOfEach[] -> current numbers of each dice values
*            (Could be dice[] or setDice[])
*           currentNumOfThrows[] -> current number of each dice throws
*           showMessages -> Boolean to show messages or not
* Process: Calculates the possible score, and displays what points are gained
*           if program needs to.
* Returns: The possible score, calculated.
*****************************************************************************/
int calcPossibleScore(int currentNumOfEach[], int currentNumOfThrows[], int throwOnSameTurn[], bool showMessages)
{
    int possibleScore = 0;
    int thisScore = 0;
    bool multi1s = showMessages;
    bool multi5s = showMessages;
    int diceToScore1 = currentNumOfEach[0];
    int diceToScore5 = currentNumOfEach[4];

    if (currentNumOfEach[0] > 0 /*&& currentNumOfEach[0] < 3*/)             //Count 1s
    {
        if (diceToScore1 > 3)
        {
            thisScore = (currentNumOfEach[0] - 3) * SCORE_FOR_EACH_1;
            if (showMessages)
            {
                cout << (currentNumOfEach[0] - 3) << " 1s: +" << thisScore << endl;   //Display score gained if wanted
            }
        }
        else if (currentNumOfEach[0] < 3)
        {
            thisScore = (currentNumOfEach[0]) * SCORE_FOR_EACH_1;
            if (showMessages)
            {
                cout << currentNumOfEach[0] << " 1s: +" << thisScore << endl;   //Display score gained if wanted
            }
        }

//        if (throwOnSameTurn[0] == true)
        {
//            multi1s = false;                                                 //Do not allow multiple scorings
            //possibleScore -= thisScore;
        }
//        else
        {
            possibleScore += thisScore;                                         //Score 1s
        }
    }

    if (currentNumOfEach[4] > 0 && currentNumOfEach[4] < 3)             //Count 5s
    {
        if (diceToScore5 > 3)
        {
            thisScore = (currentNumOfEach[4] - 3) * SCORE_FOR_EACH_5;
            if (showMessages)
            {
                cout << (currentNumOfEach[4] - 3) << " 5s: +" << thisScore << endl;   //Display score gained if wanted
            }
        }
        else if (currentNumOfEach[0] < 3)
        {
            thisScore = (currentNumOfEach[4]) * SCORE_FOR_EACH_5;
            if (showMessages)
            {
                cout << currentNumOfEach[4] << " 5s: +" << thisScore << endl;   //Display score gained if wanted
            }
        }
 //       if (throwOnSameTurn[4] == true)
        {
 //           multi5s = false;                                                 //Do not allow multiple scorings
            //possibleScore -= thisScore;
        }
 //       else
        {
            possibleScore += thisScore;                                         //Score 5s
        }
    }

    for (int sideNum = 0; sideNum < NUMBER_OF_SIDES; sideNum++)
    {
        if (currentNumOfEach[sideNum] >= 3)                                 //If there are triplets
        {
            switch (sideNum + 1)                                            //The actual dice value
            {
            case 1:
                if (multi1s)                                               //If it is not on the same dice roll
                {
                    possibleScore += SCORE_FOR_THREE_1;                     //Score triplet 1s, if on the same turn
                }
                break;
            case 2:
                possibleScore += SCORE_FOR_THREE_2;                         //Score triplet 2s
                break;
            case 3:
                possibleScore += SCORE_FOR_THREE_3;                         //Score triplet 3s
                break;
            case 4:
                possibleScore += SCORE_FOR_THREE_4;                         //Score triplet 4s
                break;
            case 5:
                if (multi5s)                                               //If it is not on the same dice roll
                {
                    possibleScore += SCORE_FOR_THREE_5;                     //Score triplet 5s, if on the same turn
                }
                break;
            case 6:
                possibleScore += SCORE_FOR_THREE_6;                         //Score triplet 6s
                break;
            }
        }//End of if

        if (showMessages)                                                   //If program wants to show point values
        {
            if (currentNumOfEach[sideNum] >= 3)                             //If triplets
            {
                switch (sideNum + 1)                                        //Get actual dice values
                {
                case 1:
                    if (multi1s)                                           //If it is not on the same dice roll
                    {
                        cout << "Three 1s: +1000" << endl;                  //Display triplet 1s scoring
                    }
                    break;
                case 2:
                    cout << "Three 2s: +200" << endl;                       //Display triplet 2s scoring
                    break;
                case 3:
                    cout << "Three 3s: +300" << endl;                       //Display triplet 3s scoring
                    break;
                case 4:
                    cout << "Three 4s: +400" << endl;                       //Display triplet 4s scoring
                    break;
                case 5:
                    if (multi5s)                                           //If it is not on the same dice roll
                    {
                        cout << "Three 5s: +500" << endl;                   //Display triplet 5s scoring
                    }
                    break;
                case 6:
                    cout << "Three 6s: +600" << endl;                       //Display triplet 6s scoring
                    break;
                }
            }//End of if (triplets)
        }//End of if (showMessages)
    }//End of for

    return possibleScore;                                                   //Return accumulated scores
}//End of calcPossibleScore()

/*****************************************************************************
*    Name: calcHotDice()
*   Input: 3 parameters:
*           isHotDice[] -> to be updated in the function, for each dice, if 'hot'
*           dice[] -> The values of the current unlocked dice
*           setDice[] -> The values of the current locked dice
* Process: Calculates if a player has hot dice  by setting and
*           checking if each element in isHotDice[] is true.
* Returns: If the user has hot dice or not
*****************************************************************************/
bool calcHotDice(bool isHotDice[], int dice[], int setDice[])
{
    int currentNumOfEach[NUMBER_OF_SIDES] = {0};                            //Counter
    bool hasHotDice = true;                                                 //Assume player has hot dice

    for (int diceNum = 0; diceNum < NUMBER_OF_DICE; diceNum++)              //For each dice
    {
        if (dice[diceNum] != 0)                                             //If unlocked dice is not of value zero
        {
            currentNumOfEach[dice[diceNum] - 1]++;                          //Add to counter
//            cout << "[" << dice[diceNum] << "] ";                             //DEBUG: Display unlocked dice values
        }
        else                                                                //Else, locked dice is not of value zero
        {
            currentNumOfEach[setDice[diceNum] - 1]++;                       //Add to counter
//            cout << "{" << setDice[diceNum] << "} ";                          //DEBUG: Display locked dice values
        }
    }//End of for (each dice)

    for (int sideNum = 0; sideNum < NUMBER_OF_SIDES; sideNum++)             //For each side
    {                                                                       //If dice are 1s or 5s
        if (dice[sideNum] == 1 || dice[sideNum] == 5 || setDice[sideNum] == 1 || setDice[sideNum] == 5)
        {
            isHotDice[sideNum] = true;                                      //Those dice are hot
        }

        if (currentNumOfEach[sideNum] >= 3)                                     //If triplets
        {
            switch (sideNum + 1)                                                //Get actual dice values
            {
            case 2:                                                             //For multiside triplets of 2s
                for (int multiSideNum = 0; multiSideNum < NUMBER_OF_DICE; multiSideNum++)
                {
                    if (dice[multiSideNum] == 2 || setDice[multiSideNum] == 2)  //If values are 2
                    {
                        isHotDice[multiSideNum] = true;                         //All 2s dice are hot
                    }
                }
                break;
            case 3:                                                             //For multiside triplets of 3s
                for (int multiSideNum = 0; multiSideNum < NUMBER_OF_DICE; multiSideNum++)
                {
                    if (dice[multiSideNum] == 3 || setDice[multiSideNum] == 3)  //If values are 3
                    {
                        isHotDice[multiSideNum] = true;                         //All 3s dice are hot
                    }
                }
                break;
            case 4:                                                             //For multiside triplets of 4
                for (int multiSideNum = 0; multiSideNum < NUMBER_OF_DICE; multiSideNum++)
                {
                    if (dice[multiSideNum] == 4 || setDice[multiSideNum] == 4)  //If values are 4
                    {
                        isHotDice[multiSideNum] = true;                         //All 4s dice are hot
                    }
                }
                break;
            case 6:                                                             //For multiside triplets of 6
                for (int multiSideNum = 0; multiSideNum < NUMBER_OF_DICE; multiSideNum++)
                {
                    if (dice[multiSideNum] == 6 || setDice[multiSideNum] == 6)  //If values are 6
                    {
                        isHotDice[multiSideNum] = true;                         //All 6s are hot
                    }
                }
                break;
            }
        }//End of if
    }

    for (int diceNum = 0; diceNum < NUMBER_OF_DICE && hasHotDice; diceNum++)    //For every dice
    {
        if (isHotDice[diceNum] != true)                                         //If the dice is not hot
        {
            hasHotDice = false;                                                 //Player does not have hot dice
        }
    }

/*                                                                                  //DEBUG: Display number of each dice, and if they are hot
    cout << endl;
    for (int diceNum = 0; diceNum < NUMBER_OF_DICE; diceNum++)
    {
        if (dice[diceNum] != 0)
        {
            cout << "[" << currentNumOfEach[diceNum] << "] ";
        }
        else
        {
            cout << "{" << currentNumOfEach[diceNum] << "} ";
        }
    }
    cout << endl;
    for (int diceNum = 0; diceNum < NUMBER_OF_DICE; diceNum++)
    {
        if (dice[diceNum] != 0)
        {
            cout << "[" << isHotDice[diceNum] << "] ";
        }
        else
        {
            cout << "{" << isHotDice[diceNum] << "} ";
        }
    }
    cout << endl << "HasHotDice: " << hasHotDice << endl;
*/                                                                                  //END OF DEBUG
    return hasHotDice;
}//End of calcHotDice()

/*****************************************************************************
*    Name: displayCurrentDice()
*   Input: 2 parameters:
*           dice[] -> The values of the current unlocked dice
*           setDice[] -> The values of the current locked dice
* Process: Goes through the elements of both locked and unlocked dice, and
*           displays them to the screen.
* Returns: None, only displays the dice values of locked and unlocked dice.
*****************************************************************************/
void displayCurrentDice(int dice[], int setDice[])
{
    cout << endl
         << "(Note: [X] = unlocked | {X} = locked)" << endl << endl                 //Display Legend
         << "Current dice:" << endl;                                                //Display current unlocked dice

    for (int diceNum = 0; diceNum < NUMBER_OF_DICE; diceNum++)                      //For each dice
    {
        if (dice[diceNum] != 0)                                                     //If unlocked dice value is not zero
        {
            cout << (diceNum + 1) << ":[" << dice[diceNum] << "] ";                 //Display dice value
        }
        else                                                                        //Else, locked dice is not zero
        {
            cout << (diceNum + 1) << ":[" <<      " "      << "] ";                 //Display Empty space instead of zero
        }
    }

    cout << endl << endl << "Current locked dice:" << endl;                         //Display current locked dice

    for (int diceNum = 0; diceNum < NUMBER_OF_DICE; diceNum++)                      //For each dice
    {
        if (setDice[diceNum] != 0)                                                  //If unlocked dice value is not zero
        {
            cout << (diceNum + 1) << ":{" << setDice[diceNum] << "} ";              //Display dice value
        }
        else                                                                        //Else, locked dice is not zerp
        {
            cout << (diceNum + 1) << ":{" <<       " "        << "} ";              //Display Empty space instead of zero
        }
    }//End of for (display dice)

    cout << endl << endl;
}//End of displayCurrentDice()
