/** @name Machine.java
 *  @author William Woodard
 *  @date 3/9/2014
 *  @purpose This class uses the Slot.java class to manage a slot machine
 */

import java.util.Scanner;                                   //Import scanner class for user input

public class Machine
{
   public static void main(String[] args)
   {
      Scanner keyboard = new Scanner(System.in);            //Create new scanner for keyboard input
      
      double totalEarnings = 0,                             //Total earnings counter
             totalAmountEntered = 0,                        //Total amount entered counter
             betAmount;                                     //User Input: amount that user bet
      int playAgain;                                        //Ask if player wants to play again
      
      do                                                       //Do
      {
         System.out.print("\nEnter the amount of money you wish to bet: ");
         betAmount = keyboard.nextDouble();                 //Get bet amount
         Slot slotInstance = new Slot(betAmount);           //Crate a slots class to play the slots game
         totalAmountEntered += betAmount;                   //Increment total amount by bet amount
         
         totalEarnings += slotInstance.play();              //Increment total earnings by amount returned by the slot game
         
         System.out.print("Your total earnings has been: $" + totalEarnings + "\n" +
                           "Do you wish to play again? (Enter 1 for yes or 0 for no): ");
         playAgain = keyboard.nextInt();                    //Get if player wants to play again
      } while (playAgain > 0);                                 //While user wants to play
      
      System.out.print("Your total earnings has been: $" + totalEarnings + "\n" +
                        "You spent on this session: $" + totalAmountEntered + "\n" +
                        "The net amount of this session: $" + (totalEarnings - totalAmountEntered));
   }
}