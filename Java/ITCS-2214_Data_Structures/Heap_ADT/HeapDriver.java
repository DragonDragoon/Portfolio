/**
 * @author William Woodard
 * @date   11/2/2014
 * @HW     Project 4 MaxHeap
 * @name   HeapDriver.java
 */
package Heap_ADT;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.File;
import java.util.Scanner;

public class HeapDriver {
	public static final int MAX_ELEMENTS = 100; // Maximum number of tweets
	public static final int TOP_NUM = 15; // Number of top tweets to display
	public static final String FILENAME = "twitter3.txt";
	
	/** Populate heap with Twitter data from file */
	public static void populate(MaxHeap<Twitter> heap, String filename) throws FileNotFoundException {
		String path = HeapDriver.class.getResource(filename).getPath(); // Get file path
		File file = new File(path);                                     // Open file
		Scanner scanner = new Scanner(file);                            // Initialize scanner with file
		
        while (scanner.hasNextLine()) {          // While there is another line in file
            String line = scanner.nextLine();      // Get new line
            String[] person = line.split("\t");    // Split line into array by \ts
            if (person[0].equals("Name       Followers  Following  Tweets") || person[0].equals("")) {
            	continue;  //Skip first line and whitespace
            }
            String name = person[0];                     // Name is always the first value
            int followers = Integer.parseInt(person[1]); // Followers is always the second value
            int follows = Integer.parseInt(person[2]);   // Follows is always the third value
            int tweets = Integer.parseInt(person[3]);    // Tweets is always the fourth value
            Twitter twitter = new Twitter(name, followers, follows, tweets); // Create new twitter off of data
            heap.insert(twitter);  // Insert twitter object into heap
        }
        scanner.close();  // Close file
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		Twitter[] twitters = new Twitter[MAX_ELEMENTS];  // Initialize Twitter object array
		MaxHeap<Twitter> heap = new MaxHeap<Twitter>(twitters, 0, MAX_ELEMENTS);  // Initialize heap with Twitter array
		populate(heap, FILENAME);  // Populate Twitter heap with "twitter3.txt" file data
		
		int size = heap.heapsize();  // Get heap size before deletion
		//size = 2.0^(height + 1.0) - 1.0  -->  height = (log(size + 1) - log(2.0)) / log(2.0)
		double heightDbl = (Math.log(size + 1) - Math.log(2.0)) / Math.log(2.0);  // Calculate height
		int height = (heightDbl > (int) heightDbl) ? (int) heightDbl + 1 : (int) heightDbl;  // Round upwards (last level does not have to be full)
		
		/** (Part 1) Top 15 */
		String output = "(1) - Top " + TOP_NUM + " Twitters\n" +
		  String.format("%-3s %-18s %-10s %-10s %-10s \n", "No.", "Name", "Followers", "Follows", "Tweets"); // Format output
		for (int i = 0; i < heap.heapsize(); i++) {  // For all the elements in heap
			if (i < TOP_NUM) {
				output += String.format("%-3s %s \n", (i + 1) + ":", heap.remove(0).toString()); // Display top value
			} else {
				heap.remove(0); // Remove top value
			}
		}
		
		/** (Part 2) Average Swaps */
		output += "\n(2) - Average Swaps\n" +
		//(Our data to read from was randomized, so sometimes two swaps were made, at worst)
		          "1: Inserts = " + heap.calcAvgSwapsInsert() + "\n" + // Display average insertion swaps
		//(We always removed the top in this driver, so for every removal, there was only one swap)
		          "2: Removes = " + heap.calcAvgSwapsRemove() + "\n" +  // Display average removal swaps
		/** (Part 3) Heap Height */
		          "\n(3) - Heap Height - Before Removals\n" +
		          "Size: " + size + "\n" +  // Display size of the heap before deletions
		          "Height: " + height;  // Display height of heap before deletions

		String path = HeapDriver.class.getResource(FILENAME).getPath(); // Get file path
		path = path.substring(0, path.length() - FILENAME.length()) + "output.txt"; // Get path for output.txt in same directory
		File file = new File(path);
		PrintWriter writer = new PrintWriter(file); // Initialize PrintWriter
		writer.write(output); // Output to file
		System.out.println("Log: output.txt written to: " + path + "\n"); // Log that file was written to
		writer.close(); // Close opened file
		
		System.out.print(output);
	}
}
