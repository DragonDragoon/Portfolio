/** @name Morse.java
 *  @author William Woodard
 *  @date 3/31/2014
 *  @purpose This class prepares methods to translate data input
 */

import java.util.Scanner;              //Scanner
import java.io.*;                      //File I/O
import java.text.DecimalFormat;        //Currency decimal formatting
import java.util.StringTokenizer;      //Tokenize Strings (for first and last name)

public class Morse
{
   ////Variable Declarations
   private String filename,            //Filename
                  translate,           //Input to be translated
                  translated = "";     //Counter of translated characters
   private int    numOfLines = 0;      //Number of lines in file
   String[]       transChars,          //Parallel: Array of translated characters
                  morseChars;          //Parallel: Array of morse code characters
   
   public Morse(String flnme, String trans)  //Constructor
   {
      filename = flnme;                //Set filename to input
      translate = trans;               //Set string to translate to input
   }
   
   public String translate() throws IOException
   {
      ////Class Initializers
      File openFile = new File(filename);                                  //Initialize file opener      
      
      Scanner fileInput = new Scanner(openFile);                           //Initialize scanner 
      while (fileInput.hasNext())                                          //While there is another line in file
      {
         numOfLines++;                                                        //Increment number of lines counter
         fileInput.nextLine();                                                //Traverse to next line
      }
      
      ////Variable Declarations
      transChars = new String[numOfLines];                                 //Initialize first names array
      morseChars = new String[numOfLines];                                  //Initialize last names array
      
      Scanner fileInput2 = new Scanner(openFile);                          //Initialize new scanner 
      int line = 0;                                                        //Initialize line counter
      do                                                                   //Do
      {
         StringTokenizer st = new StringTokenizer(fileInput2.nextLine());     //Initialize tokenizer with new line
         transChars[line] = st.nextToken();                                   //First name is the first token
         morseChars[line] = st.nextToken();                                    //Last name is the second token
     
         line++;                                                              //Increment line counter
      } while (fileInput2.hasNext());                                      //While another line exists
      
      for (int idx = 0; idx < translate.length(); idx++)                   //For the number of characters to translate
      {
         String strAppend;                                                    //Create a string to append to counter
         
         int pos = -1;                                                        //Start before the first position
         for (int i = 0; i < transChars.length; i++)                          //For the number of characters in translation array
         {
            if (transChars[i].equals(String.valueOf(translate.charAt(idx)).toUpperCase()))   //If character equals the user input
            {
               pos = i;                                                                         //Set position to that character
               break;                                                                           //Stop looping
            }
         }//End for()
         
         if (translate.charAt(idx) == '.')                                    //Special character '.'
         {
            strAppend = "   ";                                                   //Three spaces
         }
         else if (pos == -1)                                                  //Special character (not found)
         {
            strAppend = "";                                                      //Empty character
         }
         else                                                                 //Else this character matched
         {
            strAppend = morseChars[pos] + " ";                                   //Set character to translated characte
         }
         
         translated += strAppend;                                             //Append to total translated string
      }//End for()
      
      return   "\nOriginal Sentence:\n" +
                           translate + "\n" +
               "Translated Sentence:\n" +
                           translated;                                        //Return translated string
   }
}