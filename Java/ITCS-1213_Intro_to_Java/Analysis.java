/** @name Analysis.java
 *  @author William Woodard
 *  @date 3/27/2014
 *  @purpose This class prepares data from a file that is to be processed for displaying information
 */
 
import java.util.Scanner;                    //Scanner
import java.io.*;                            //File I/O (throws IOException)

public class Analysis
{
   public static void main(String[] args) throws IOException
   {
      String filename;                                //User Input: Filename
      
      Scanner keyboard = new Scanner(System.in);      //Initialize Scanner <- Keyboard
      
      System.out.println("Enter the filename: ");
      filename = keyboard.nextLine();                 //Get filename
      
      Sales mSales = new Sales(filename);             //Initialize Sales with filename
      mSales.calcStats();                             //Initiate Sales calculate stats
      
      //Output stats
      System.out.print("Great Buy Company Monthly Salary Details:\n" +
                        "  Total Sales: $" + mSales.getTotal() + "\n" +
                        "  Average Sales: $" + mSales.getAverage() + "\n" +
                        "  Lowest Sales Amount: " + mSales.getLowestSalesman() + "\n" +
                        "  Highest Sales Amount: " + mSales.getHighestSalesman() + "\n" +
                        "  Salesmen At or Above Average:\n" +
                        "     " + mSales.getAboveAverage() + "\n" +
                        "  Salesmen Below Average:\n" +
                        "     " + mSales.getBelowAverage() + "\n");
   }
}