/** @name Employees.java
 *  @author William Woodard
 *  @date 4/27/2014
 *  @purpose This class uses the ProductionWorker class to organize txt files and create a new one
 */
 
import java.util.Scanner;              //Scanner
import java.io.*;                      //File I/O
import java.util.StringTokenizer;      //Tokenize Strings (for first and last name)

public class Employees
{
   public static void main(String[] args) throws IOException
   {
      String filenameRead  = "Information.txt",                               //Text document to read from
             filenameWrite = "Department.txt";                                //Text document to write to 
      
      File openFile = new File(filenameRead);                                     //Initialize file opener
      Scanner fileInput = new Scanner(openFile);                              //Initialize new scanner 
      PrintWriter writer = new PrintWriter(filenameWrite, "UTF-8");               //Initialize file writer
      
      do                                                                      //Do
      {
         StringTokenizer st = new StringTokenizer(fileInput.nextLine(), ",");    //Initialize tokenizer with new line
         String name    = st.nextToken().trim(),                                 //Name is first token
                number  = st.nextToken().trim(),                                 //Number is second token
                date    = st.nextToken().trim();                                 //Date is third token
         int    shift   = Integer.parseInt(st.nextToken().trim());               //Shift is fourth token
         double pay     = Double.parseDouble(st.nextToken().trim());             //Pay is fifth token
                
         ProductionWorker worker = new ProductionWorker(name, number, date, shift, pay);  //Create production worker
         
         System.out.println(worker.toString());                                  //Console: To String
         writer.println(worker.toString());                                      //Text file: To String
      } while (fileInput.hasNext());                                          //While another line exists
      
      writer.close();                                                         //Close writer
   }
}