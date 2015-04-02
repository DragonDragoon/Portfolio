
public class Project3 {
	public static void main(String args[]){
		LList<String> f_list = new LList<String>(1);
		
		f_list.print();
		f_list.insert("New York, 8.4M");
		f_list.print();
		f_list.remove();
		f_list.print();
		f_list.insert("Los Angeles 3.8M");
		f_list.insert("Chicago, 2.7M");
		f_list.insert("Houston, 2.1M");
		f_list.insert("Philadelphia, 1.55M");
		f_list.insert("San Antonio, 1.4M");
		f_list.insert("San Diego, 1.35M");
		
		f_list.moveToPos(5);
		
		f_list.insert("Phoenix, 1.51M");
		f_list.append("Dallas, 1.25M");
		f_list.append("San Jose, 0.998M");
		f_list.append("Austin, 0.88M");
		f_list.append("Indianapolis, 0.84M");
		f_list.append("Jacksonville, 0.84M");
		f_list.append("San Francisco, 0.83M");
		f_list.append("Columbus, 0.82M");
		f_list.append("Charlotte, 0.79M");

		f_list.print();
				
		f_list.moveToPos(5);
		f_list.remove();
		f_list.print();
		
		f_list.moveToStart();
		f_list.remove();
		f_list.print();
					
		f_list.moveToEnd();
		f_list.remove();
		f_list.print();
				
		f_list.clear();
		f_list.print();
	}
}