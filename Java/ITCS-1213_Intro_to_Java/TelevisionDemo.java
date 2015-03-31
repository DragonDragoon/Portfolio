/** @name TelevisionDemo.java
 *  @author William Woodard
 *  @date 2/3/2014
 *  @purpose This program creates a television instance and allows the user to modify it
 */

import java.util.Scanner;

public class TelevisionDemo
{
   public static void main(String[] args)
   {
      String tvBrandName;        //The brand name of the television
      double tvScreenSize;       //The screen size of the television
      
      Scanner keyboard = new Scanner(System.in);   //Scanner object for keyboard input
      
      System.out.print("Enter the television's manufacturer: ");
      tvBrandName = keyboard.nextLine();
      
      System.out.print("Enter the television's screen size: ");
      tvScreenSize = keyboard.nextDouble();
      
      Television myTV = new Television(tvBrandName, tvScreenSize);
      myTV.Power();           //Turn television on
      showState(myTV);
      
      System.out.print("Enter the desired channel: ");
      myTV.setChannel(keyboard.nextInt());
      showState(myTV);
      
      System.out.print("Increasing volume by 6...\n");
      myTV.increaseVolume();  //1
      myTV.increaseVolume();  //2
      myTV.increaseVolume();  //3
      myTV.increaseVolume();  //4
      myTV.increaseVolume();  //5
      myTV.increaseVolume();  //6
      showState(myTV);
      
      System.out.print("The volume is too loud! Lowering volume by 2...\n");
      myTV.decreaseVolume();  //1
      myTV.decreaseVolume();  //2
      showState(myTV);
   }
   
   /** @name function showState()
    *  @purpose Passes a television instance and displays its state to the user
    */
   public static void showState(Television myTV)
   {
      System.out.print("The state of the television:\n" +
                       "Manufacturer: " + myTV.getManufacturer() + "\n" +
                       "Screen Size: " + myTV.getScreenSize() + "\n" +
                       "Power State: " + myTV.getPower() + "\n" +
                       "Channel: " + myTV.getChannel() + "\n" +
                       "Volume: " + myTV.getVolume() + "\n\n");
   }
}//End of TelevisionDemo

/** @name Television
 *  @purpose This class is used to create an object of a television for the user to read and modify
 */
class Television
{
   private String manufacturer;                 //The manufacturer of the television
   private double screenSize;                   //The screen size of the television
   private boolean powerOn;                     //The state that the television is in (on or off)
   private int channel,                         //The channel that the television is on
               volume;                          //The volume that the televisions is set (0 to 25)
   
   /** @name constructor Television()
    *  @purpose Create an initialized instance of Television
    */
   public Television(String manu, double scrnSze)
   {
      manufacturer = manu;
      screenSize = scrnSze;
      powerOn = false;
      channel = 2;
      volume = 20;
   }
   
   public void setChannel(int chan)             //Set the channel
   {
      channel = chan;
   }
   
   public void Power()                          //Set the power
   {
      if (!powerOn)   //television is off
      {
         powerOn = true;
      }
      else  //the television is on
      {
         powerOn = false;
      }
   }
   
   public void increaseVolume()                 //Increase the volume by 1
   {
      volume++;
   }
   
   public void decreaseVolume()                 //Decrease the volume by 1
   {
      volume--;
   }
   
   public int getChannel()                      //Get the television's channel
   {
      return channel;
   }
   
   public int getVolume()                       //Get the television's volume
   {
      return volume;
   }
   
   public String getManufacturer()
   {
      return manufacturer;
   }
   
   public double getScreenSize()
   {
      return screenSize;
   }
   
   public boolean getPower()
   {
      return powerOn;
   }
}//end of class RectangleDemo