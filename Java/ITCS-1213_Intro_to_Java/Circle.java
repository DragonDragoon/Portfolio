/** @name Circle.java
 *  @author William Woodard
 *  @date 2/12/2014
 *  @purpose This program dreates a class of a circle, where it will manage instances of the circle
 */
 
public class Circle
{
   final double PI = 3.14159;             //Constant: value of pi
   private double radius;                 //User input: radius of circle
   
   public Circle(double rad)              //Constructor: Circle initialize
   {
      radius = rad;                       //Set radius to initial value
   }
   
   public void setRadius(double rad)      //Mutator: Set the radius
   {
      radius = rad;
   }
   
   public double getRadius()              //Accessor: Get the radius
   {
      return radius;
   }
   
   public double getArea()                //Calculator: Return the area
   {
      return PI * radius * radius;        //Area of a circle
   }
   
   public double getDiameter()            //Calculator: Return the diameter
   {
      return 2 * radius;                  //Diameter of a circle
   }
   
   public double getCircumference()       //Calculator: Return the circumference
   {
      return 2 * PI * radius;             //Circumference of a circle
   }
}