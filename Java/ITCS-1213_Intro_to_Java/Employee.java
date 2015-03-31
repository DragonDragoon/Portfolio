/** @name Employee.java
 *  @author William Woodard
 *  @date 4/27/2014
 *  @purpose This class prepares the creation of an employee to be extended to a worker
 */
 
public class Employee
{
   private String name,          //Name
                  number,        //Number
                  date;          //Date hired
                  
   public Employee(String nm, String nmbr, String dte)
   {
      name = nm;
      number = nmbr;
      date = dte;
   }
   
   public String getName()             //Getter: name
   {
      return name;
   }
   
   public String getNumber()           //Getter: number
   {
      return number;
   }
   
   public String getNumberType()       //Getter: number type
   {
      switch (number.charAt(0))        //Select appropriate number type
      {
         case 'A':
            return "Accounting";
         case 'H':
            return "Human Resources";
         case 'P':
            return "Production";
         case 'S':
            return "Shipping";
         default:
            return "Unknown";
      }
   }
   
   public String getDate()             //Getter: date hired
   {
      return date;
   }
   
   public void setName(String nm)      //Setter: name
   {
      name = nm;
   }
   
   public void setNumber(String nmbr)  //Setter: number
   {
      number = nmbr;
   }
   
   public void setDate(String dte)     //Setter: date hired
   {
      date = date;
   }
}