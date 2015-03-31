/** @name Sales.java
 *  @author William Woodard
 *  @date 3/27/2014
 *  @purpose This class prepares data from a file that is to be processed for displaying information
 */
 
import java.util.Scanner;              //Scanner
import java.io.*;                      //File I/O
import java.text.DecimalFormat;        //Currency decimal formatting
import java.util.StringTokenizer;      //Tokenize Strings (for first and last name)

public class Sales
{
   ////Variable Declarations
   private String filename,            //Filename
                  aboveAverage = "",   //At or above average salesmen string counter
                  belowAverage = "";   //Below average salesmen string counter
   private int    numOfLines = 0;      //Number of lines in file
   private double total = 0,           //Total monthly sales counter
                  average,             //Average monthly sales
                  lowest,              //Lowest monthly sales
                  highest;             //Highest monthly sales
   private int    numLowest,           //Index of lowest monthly sales
                  numHighest;          //Index of highest monthly sales
   String[]       firstNames,          //Parallel: Array of first names
                  lastNames;           //Parallel: Array of last names
   double[]       monthlySales;        //Parallel: Array of monthly sales
   
   ////Class Initializations
   DecimalFormat formatter = new DecimalFormat("#0.00");                //Initialize decimal formatter
   
   ////Functions
   public Sales()                      //No-Arg constructor
   {
      filename = "Monthly.txt";           //Default filename
   }
   
   public Sales(String flnme)          //User supplied filename constructor
   {
      filename = flnme;                   //User given filename
   }
   
   public void setFilename(String flnme)  //Setter: filename
   {
      filename = flnme;
   }
   
   public int getNumberOfSalesmen()       //Getter: number of salesmen
   {
      return numOfLines;
   }
   
   public String getTotal()               //Getter: Formatted String of total amount of sales
   {
      return formatter.format(total);
   }
   
   public String getAverage()             //Getter: Formatted String of average of monthly sales
   {
      return formatter.format(average);
   }
   
   public String getAboveAverage()        //Getter: String of above average salesmen
   {
      return aboveAverage;
   }
   
   public String getBelowAverage()        //Getter: String of below average salesmen
   {
      return belowAverage;
   }
   
   public String getName(int index)       //Getter: First and last name of specific salesman
   {
      return firstNames[index] + " " + lastNames[index];
   }
   
   public String getMonthlySales(int index)  //Getter: Formatted Monthly sales of specific salesman
   {
      return formatter.format(monthlySales[index - 1]);
   }
   
   public String getHighestSalesman()     //Getter: String of first and last name, and monthly sales of highest salesman
   {
      return firstNames[numHighest] + " " + lastNames[numHighest] + " - $" + formatter.format(highest);
   }
   
   public String getLowestSalesman()      //Getter: String of first and last name, and monthly sales of lowest salesman
   {
      return firstNames[numLowest] + " " + lastNames[numLowest] + " - $" + formatter.format(lowest);
   }
   
   public String calcStats() throws IOException   //Function to calculate stats from filename
   {                                            //(Note: must be run every time filename changes to update private fields in the class)
      ////Class Initializers
      File openFile = new File(filename);                                  //Initialize file opener      
      
      Scanner fileInput = new Scanner(openFile);                           //Initialize scanner 
      while (fileInput.hasNext())                                          //While there is another line in file
      {
         numOfLines++;                                                        //Increment number of lines counter
         fileInput.nextLine();                                                //Traverse to next line
      }
      
      ////Variable Declarations
      String strReturn = "";                                               //Initialize string counter
      firstNames = new String[numOfLines];                                 //Initialize first names array
      lastNames = new String[numOfLines];                                  //Initialize last names array
      monthlySales = new double[numOfLines];                               //Initialize monthly sales array
      
      Scanner fileInput2 = new Scanner(openFile);                          //Initialize new scanner 
      int line = 0;                                                        //Initialize line counter
      do                                                                   //Do
      {
         StringTokenizer st = new StringTokenizer(fileInput2.nextLine());     //Initialize tokenizer with new line
         firstNames[line] = st.nextToken();                                   //First name is the first token
         lastNames[line] = st.nextToken();                                    //Last name is the second token
         monthlySales[line] = Double.parseDouble(st.nextToken());             //Monthly sales is the third token
     
         line++;                                                              //Increment line counter
      } while (fileInput2.hasNext());                                      //While another line exists
      
      lowest = monthlySales[0];                                            //Set lowest amount to collected data
      highest = monthlySales[0];                                           //Set highest amount to collected data
      numLowest = 0;                                                       //Initial index of lowest is the zeroth element
      numHighest = 0;                                                      //Initial index of highest is the zeroth element
      for (int idx = 0; idx < numOfLines; idx++)                           //For the number of lines in the file
      {
         total += monthlySales[idx];                                          //Sum indexed monthly sales
         
         if (lowest > monthlySales[idx])                                      //If indexed monthly sales is lower than current lowest
         {
            lowest = monthlySales[idx];                                          //Set new lowest to indexed monthly sales
            numLowest = idx;                                                     //Set index of lowest to indexed monthly sales index
         }
         
         if (highest < monthlySales[idx])                                     //If indexed monthly sales is higher than the current highest
         {
            highest = monthlySales[idx];                                         //Set new highest to indexed monthly sales
            numHighest = idx;                                                    //Set index of lowest to indexed monthly sales index
         }
      }
      
      average = (double)total / (double)numOfLines;                        //Calculate average      
      
      for (int idx = 0; idx < numOfLines; idx++)                           //For the number of lines in file
      {
         if (monthlySales[idx] >= average)                                    //If the current index is above or at the average monthly sales
            aboveAverage += firstNames[idx] + " " + lastNames[idx] + ", ";       //Concatenate current index to string counter
         if (monthlySales[idx] < average)                                     //If the current index is below the average monthly sales
            belowAverage += firstNames[idx] + " " + lastNames[idx] + ", ";       //Concatenate current index to string counter
      }
      
      //Construct string to return if programmer wishes for a toString() equivalent
      strReturn = "Great Buy Company Monthly Salary Details:\n" +
                  "  Total Sales: $" + this.getTotal() + "\n" +
                  "  Average Sales: $" + this.getAverage() + "\n" +
                  "  Lowest Sales Amount: " + this.getLowestSalesman() + "\n" +
                  "  Highest Sales Amount: " + this.getHighestSalesman() + "\n" +
                  "  Salesmen At or Above Average:\n" +
                  "     " + this.getAboveAverage() + "\n" +
                  "  Salesmen Below Average:\n" +
                  "     " + this.getBelowAverage() + "\n";
      
      return strReturn;
   }
}