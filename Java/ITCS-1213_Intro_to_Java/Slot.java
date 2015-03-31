/** @name Slot.java
 *  @author William Woodard
 *  @date 3/9/2014
 *  @purpose This class creates an instance of a slot machine
 */

import java.util.Random;               //Random class

public class Slot
{
   Random rand = new Random();         //Initialize random class
   
   final String words[] = { "Cherries", "Oranges", "Plums", "Bells", "Melons", "Bars" };  //Array to hold strings of names
   private double money,               //Amount put into the slot
                  finMoney;            //Amount output of the slot
   private int slotOne,                //Value of slot one
               slotTwo,                //Value of slot two
               slotThree,              //Value of slot three
               matches = 1;            //Initialize matches counter   
   
   public Slot(double mon)             //Initialize constructor with money input
   {
      money = mon;                     //Set money to amount put in
   }
   
   public double play()
   {
      slotOne   = rand.nextInt(6);     //Get random value in Z (mod 7)
      slotTwo   = rand.nextInt(6);     //...
      slotThree = rand.nextInt(6);     //Which is [0,6]
      
      if (slotOne == slotTwo)          //If slot one and two match
      {
         matches++;                    //Increment match counter
      }
      
      if (slotOne == slotThree)        //If slot one and three match
      {
         matches++;                    //Increment counter
      }
      else if (slotTwo == slotThree)   //Else if slow two and three (so that there cannot be an extra match)
      {
         matches++;                    //Increment counter
      }
      
      if (matches < 2) matches = 0;    //If the match counter is less than two, the multiplier is zero
      
      finMoney = money * matches;      //Amount output is the money input multiplied by the multiplier
      
      System.out.print("You rolled:\n" +
                        words[slotOne] + " " + words[slotTwo] + " " + words[slotThree] + "\n" +
                        "There are " + matches + " matches.\n" +
                        "Your winnings are: $" + finMoney + "\n");
                        
      return finMoney;                 //Return the amount after the multiplier
   }
}