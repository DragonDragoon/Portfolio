/** @name ProductionWorker.java
 *  @author William Woodard
 *  @date 4/27/2014
 *  @purpose This class extends the employee class to create a production worker object
 */

import java.util.Formatter;                  //String.format()

public class ProductionWorker extends Employee
{
   private int    shift;                     //Shift number
   private double pay;                       //Pay rate
   private final String shifts[] = {"Morning Shift", "Swing Shift", "Night Shift"}; //Shift types
                  
   public ProductionWorker(String nm, String nmbr, String dte, int shft, double py)
   {
      super(nm, nmbr, dte);                  //Create employee
      
      shift = shft;
      pay = py;
   }
   
   public String getShift()                  //Getter: shift type
   {
      try
      {
         return shifts[shift - 1];
      }
      catch (Exception except)               //Catch possible unknown shift type
      {
         return "Unknown";
      }
   }
   
   public int getShiftNum()                  //Getter: shift number
   {
      return shift;
   }
   
   public double getPay()                    //Getter: payrate
   {
      return pay;
   }
   
   public void setShift(int shft)            //Setter: shift
   {
      shift = shft;
   }
   
   public void setPay(double py)             //Setter: payrate
   {
      pay = py;
   }
   
   public String toString()
   {
      return String.format("%-17s %-5s %-15s %-10s %-13s $%.2f", this.getName(), this.getNumber(), this.getNumberType(),
                              this.getDate(), this.getShift(), this.getPay());   //Format string for proper output
   }
}