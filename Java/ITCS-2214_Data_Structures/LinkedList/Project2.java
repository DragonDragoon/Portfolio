/*
 * @name	William Woodard
 * @date	Due 9-19-2014
 * @class	ITCS-2214-001
 * @HW		Project_2_Linked_Lists
 */
public class Project2 {
	public static void main(String[] args) {
		LList<String> s_list = new LList<String>(1);
		s_list.insert("New York, 8.4M");
		s_list.insert("Los Angeles 3.8M");
		s_list.insert("Chicago, 2.7M");
		s_list.insert("Houston, 2.1M");
		s_list.insert("Philadelphia, 1.55M");
		s_list.insert("Phoenix, 1.51M");
		s_list.append("San Antonio, 1.4M");
		s_list.append("San Diego, 1.35M");
		s_list.append("Dallas, 1.25M");
		s_list.append("San Jose, 0.998M");
		s_list.append("Austin, 0.88M");
		s_list.append("Indianapolis, 0.84M");
		s_list.append("Jacksonville, 0.84M");
		s_list.append("San Francisco, 0.83M");
		s_list.append("Columbus, 0.82M");
		s_list.append("Charlotte, 0.79M");

		s_list.print();
		s_list.moveToPos(3);
		s_list.remove();
		s_list.print();
		s_list.moveToEnd();
		s_list.remove();
		s_list.print();
		s_list.moveToStart();
		s_list.remove();
		s_list.remove();
		s_list.print();
		s_list.clear();
		s_list.print();
	}
}