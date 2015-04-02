/**
 * @author William Woodard
 * @date   3/28/2015
 * @HW     Topological Ordering Implementation
 * @name   TopologicalOrdering.java
 * @desc   This file contains the class driver for implementing the data structure from the other files
 */
package TopologicalOrdering;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class TopologicalOrdering {
	
	public static void populate(Graph<Vertex<String>> graph, String filename) throws FileNotFoundException {
		String path, line, parent_and_children[];
		path = TopologicalOrdering.class.getResource(filename).getPath();	//Get file path from class files (needs refresh for Eclipse)
		File file = new File(path);					                        //Get file
		Scanner scanner = new Scanner(file);		                        //To read each line
		
		while (scanner.hasNextLine()) {
            line = scanner.nextLine();					                    //Get next line
            parent_and_children = line.split(",");                          //Split line among commas
            Vertex<String> parent = new Vertex<String>(parent_and_children[0]);  //First will always be the parent
            for (int i = 1; i < parent_and_children.length; i++) {
            	Vertex<String> child = new Vertex<String>(parent_and_children[i]);  //Children will always follow...
            	Edge<Vertex<String>> edge = new Edge<Vertex<String>>(parent, child);  //Create edge between parent and children
            	graph.createEdge(parent, child, edge);                              //Place edge in graph
            }
            
		}
        scanner.close();  // Close file
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		Graph<Vertex<String>> directedGraph = new Graph<Vertex<String>>();               //Initiate graph
		populate(directedGraph, "data.txt");					              //Populate graph (data.txt by default)
		
		System.out.println("The graph appears like: " + directedGraph.adjacent);         //Display graph
		System.out.println("Topological Ordering: " + directedGraph.topologicalSort());  //Display topological sort
	}
}
