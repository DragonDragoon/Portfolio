#include <iostream>
using namespace std;
int main( )
{
      const double MIN_SAVINGS =  10000;
      const double MIN_CHECKING = 5000;
      char accountType;         //user input
      int accountNumber;     //user input
      double minBalance;     //user input
      double currentBalance;   //user input
      double serviceCharge;     //a fee assessed if below min balance
      double interestEarned;    //a credit given if above min value
      bool charged;    //set to indicate if a user is below min balance or not

      //initialize some starting values
       serviceCharge = 0;
       interestEarned = 0;
       charged = false;

      //gather user input
      cout << "Please enter your account number: ";
      cin >> accountNumber;
      cout << "Please enter your account type (S for savings, C for checking):  ";
      cin >> accountType;
      cout << "Please enter your current balance: ";
      cin >> currentBalance;
     if(accountType == 'S' || accountType == 's')  //take care of savings account charges
    {
           if(currentBalance < MIN_SAVINGS)  // this means customer must pay a fee
          {
                  serviceCharge = 10;
                  charged = true;
          }
           else  //this means customer has savings acct and has over min in savings
          {
                   interestEarned = .04 * currentBalance;
            }
       } //end of savings account calculations
      else   //this means customer has a checking account
       {
            if(currentBalance < MIN_CHECKING)   //this means customer must pay a fee
             {
                  serviceCharge = 25;
                  charged =true;
             }
            else  //this means the checking acct customer earned interest
            {
                 if ( minBalance  <= currentBalance + 5000)   //customer earns low interest
                 {
                       interestEarned = .015 * currentBalance;
                  }
                 else  //this means customer earns high interest
                  {
                       interestEarned  = currentBalance *  .025;
                  }
            } //end of checking account calculations
       }
        //the current balance is what its value was minus the service charges or plus the interest amounts
        currentBalance  =  currentBalance - serviceCharge + interestEarned;
        cout << "Account number:  " <<  accountNumber  <<  endl;
        cout << "Your account type is:  " <<  accountType  <<  endl;
        cout << "Your current balance is:  $" << currentBalance  <<  endl;
        if(charged)
        {
             cout << "You were charged a fee for going below the minimum balance. \n";
        }
    return 0;
}//end of main ( )
