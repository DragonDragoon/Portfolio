/** @name CircleDemo.java
 *  @author William Woodard
 *  @date 2/12/2014
 *  @purpose This program dreates a circle defined by the user and displays properties of the circle
 */

import java.util.Scanner;                                   //Import scanner class for user input

public class CircleDemo
{
   public static void main(String[] args)
   {
      Scanner keyboard = new Scanner(System.in);            //Create new scanner for keyboard input

      System.out.print("Enter the circle's radius: ");
      Circle myCircle = new Circle(keyboard.nextDouble());  //Create new circle with keyboard input for radius

      System.out.print("The Circle's Stats:\n" +
                        "Radius: " + myCircle.getRadius() + "\n" +               //Display radius
                        "Diameter: " + myCircle.getDiameter() + "\n" +           //Display diameter
                        "Circumference: " + myCircle.getCircumference() + "\n" + //Display circumference
                        "Area: " + myCircle.getArea());                          //Display area
   }
}