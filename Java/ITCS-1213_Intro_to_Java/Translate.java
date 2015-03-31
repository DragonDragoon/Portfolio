/** @name Translate.java
 *  @author William Woodard
 *  @date 3/31/2014
 *  @purpose This class prepares sentences to be translated
 */
 
import java.util.Scanner;                    //Scanner
import java.io.*;                            //File I/O (throws IOException)

public class Translate
{
   public static void main(String[] args) throws IOException
   {
      String filename = "Morse.txt",               //Morse code translation document
             sentence,                             //Sentence to add to total
             translate = "";                       //Sentences to translate
      boolean sentValue = true;                    //Check for sentinal character existing
      
      Scanner keyboard = new Scanner(System.in);   //Initialize Scanner <- Keyboard
      System.out.println("Enter sentences to translate (0 to end)");
      while (sentValue)                            //While sentinal character has not stopped loop
      {
         sentence = keyboard.nextLine() + " ";        //Get user input by line, add a space for delimeter
         translate += sentence;                       //Add sentence to total for translation
         
         if (sentence.contains("0"))                  //If sentinal character exists
            sentValue = false;                           //Stop appending sentences
         else                                         //Else keep going
            System.out.println("Enter sentences to translate (0 to end)");
      }
      
      Morse mCode = new Morse(filename, translate);   //Initialize Sales with filename
      System.out.print(mCode.translate());            //Translate sentences
   }
}