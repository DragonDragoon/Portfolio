/**
 * @author William Woodard
 * @date   11/19/2014
 * @HW     Project 5a Graphs
 * @name   p5Driver.java
 */
package p5Driver;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

import edu.uncc.cs.bridges.*;

public class p5Driver {
	/**
	 * @description Sets all nodes in graph to not visited and sets them invisible
	 * @param gv -> Graph, editable
	 */
	public static void unvisitNodes(GraphVisualizer<?> gv) {
		for (AbstractVertex<?> a_v : gv.vertices.values()) {  //For every vertex in graph
			Vertex<?> v = (Vertex<?>) a_v;		//Cast against AbstractVertex
        	v.setNotVisited();
        	v.setVisibility(false);
		}
	}
	
	/**
	 * @description Populates graph with data from specified file
	 * @param list_actors -> HashMap of actors in Graph for faster and easier access outside of populate
	 * @param gv -> Graph, editable
	 * @param filename -> Filename of file to parse data from
	 * @throws FileNotFoundException
	 */
	public static void populate(HashMap<Integer,String> list_actors, GraphVisualizer<?> gv, String filename) throws FileNotFoundException {
		String path, line, actor_and_movie[], actor, movie;
		path = p5Driver.class.getResource(filename).getPath();	//Get file path from class files (needs refresh for Eclipse)
		File file = new File(path);					//Get file
		Scanner scanner = new Scanner(file);		//To read each line
		
		int actor_count = 0;						//No actors initially
        while (scanner.hasNextLine()) {				//While there is another line in file
            line = scanner.nextLine();					//Get next line
            actor_and_movie = line.split(" ");			//Split line into array with actor and movie
            actor = actor_and_movie[0];					//Get actor name
            movie = actor_and_movie[1];					//Get movie name
            Vertex<?> v_actor, v_movie;
            if (gv.vertices.containsKey(actor)) {		//If actor already inserted
            	v_actor = (Vertex<?>) gv.vertices.get(actor);	//Get actor vertex (cast from AbstractVertex)
            	v_movie = new Vertex<String>(movie, gv);		//Create new movie vertex
            	v_actor.createEdge(v_movie).setOpacity(0.5);					//Create new edge between actor and vertex
            	//v_movie.createEdge(v_actor);					//Create new edge between actor and vertex
            } else {									//Else actor not inserted
            	v_actor = new Vertex<String>(actor, gv);		//Create new actor vertex
            	v_movie = new Vertex<String>(movie, gv);		//Create new movie vertex
        		v_actor.createEdge(v_movie).setOpacity(0.5);					//Create new edge between actor and vertex
        		//v_movie.createEdge(v_actor);					//Create new edge between actor and vertex
                list_actors.put(actor_count++, actor);			//Add actor to list of actors
            }
        }
        scanner.close();  // Close file
	}
	
	/**
	 * @description Implements Depth-First-Search algorithm to set traversed nodes to visible with color specifying level
	 * @param gv -> Graph, editable
	 * @param s -> Object used to identify vertex (string in this driver)
	 * @param level -> Level to check against and traverse to
	 * 
	 * @NOTE Need to be able to set edge invisible, because it automatically makes the edge appear when both vertices are visible
	 */
	static void DFS(GraphVisualizer<?> gv, Object s, int level) {
		Vertex<?> v = (Vertex<?>) gv.vertices.get(s);				//Get vertex (cast)
		v.setColor(getColor(level));											//Set color of vertex
		v.setVisited();												//Set vertex to visited
		v.setVisibility(true);										//Set vertex to visible
		if (level == 0) {											//If level is zero
			return;														//Stop recursion
		}
	    for (AbstractEdge<?> w : v.outgoing) {						//For every outgoing edge
			Vertex<?> n = (Vertex<?>) w.getDestination();				//Get destination vertex (cast)
	        if (!n.visited) {											//If destination not visited
	        	w.setColor(getColor(level));											//Set color of edge
				DFS(gv, n.getIdentifier(), level - 1);						//Recurse one level more
	        }
			n = (Vertex<?>) w.getSource();								//Get source vertex (cast)
	        if (!n.visited) {											//If source was not visited
	        	w.setColor(getColor(level));											//Set color of edge
				DFS(gv, n.getIdentifier(), level - 1);						//Recurse one level more
	        }
	    }
	}
	
	static String getColor(int col) {
		String rgb = Integer.toHexString(101010 + 000303 * col);	//Calculate some color
		String color = "#" + rgb.substring(2, rgb.length());		//Make into string
		return color;
	}
	
	static void BFS(GraphVisualizer<?> gv, Object start, Object end) {
		Queue<Object> Q = new Queue<Object>();
		HashMap<Object,Integer> distTo = new HashMap<Object,Integer>();
		HashMap<Object,Object> prev = new HashMap<Object,Object>();
		Boolean end_found = false;

	    Q.enQueue(start);
	    distTo.put(start, 0);
	    
	    while(Q.length() > 0) {			
	    	Vertex<?> v = (Vertex<?>) gv.vertices.get(Q.deQueue().getIdentifier());
        	v.setColor(getColor(distTo.get(v.getIdentifier())));
			v.setVisibility(true);
			v.setVisited();
			//for (AbstractVertex<?> w : v.getNeighbors().keySet()) {
			//	Vertex<?> n = (Vertex<?>) w;
			//System.out.println(v.getNeighbors().keySet().size());
			//System.out.println(v.getNeighboringEdges().keySet().size());
		    for (AbstractEdge<?> w : v.outgoing) {						//For every outgoing edge
				Vertex<?> n = (Vertex<?>) (!(((Vertex<?>) w.getSource()).visited) ? w.getSource() : w.getDestination());
				if (!n.visited) {											//If source was not visited
		        	Q.enQueue(n.getIdentifier());
		        	distTo.put(n.getIdentifier(), distTo.get(v.getIdentifier()) + 1);
		        	w.setColor(getColor(distTo.get(n.getIdentifier())));
		        	prev.put(n.getIdentifier(), v.getIdentifier());
		        }
		    }
	        if (v.getIdentifier().equals(end)) {
	        	System.out.println(end + " found " + distTo.get(end) + " levels away.");
	        	DFS(gv, end, 1);
	        	end_found = true;
	        	break;
	        }
	    }
	    
	    if (!end_found) {
	    	System.out.println(end + " not found.");
	    } else {
	    	Vertex<?> last = (Vertex<?>) gv.vertices.get(end);
	    	while (!last.getIdentifier().equals(start)) {
	    		Vertex<?> v_last = (Vertex<?>) gv.vertices.get(prev.get(last.getIdentifier()));
	    		AbstractEdge<?> e = last.getEdge(v_last);
	    		if (e == null) {
	    			for (AbstractEdge<?> o : v_last.outgoing) {
	    				if (o.getSource().getIdentifier().equals(v_last.getIdentifier()) && o.getDestination().getIdentifier().equals(last.getIdentifier())) {
	    					e = o;
	    				}
	    			}
	    		}
	    		e.setWidth(5);
	    		e.setColor("blue");
	    		last = (Vertex<?>) gv.vertices.get(v_last.getIdentifier());
	    	}
	    }
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		GraphVisualizer<?> gv = new GraphVisualizer<>();						//Initialize graph
		HashMap<Integer,String> list_actors = new HashMap<Integer,String>();	//Initialize actor list
		Bridge.init(11, "1355347875827", gv, "wwoodar1");						//Initialize bridges
		
		populate(list_actors, gv, "imdb-small-Revised.txt");					//Populate graph
		System.out.println("Link to display all vertices in graph: ");
		Bridge.update();														//Display link to total visible graph
		
		Scanner keyboard = new Scanner(System.in);
		/** DFS implementation: 
		System.out.println("\nEnter the number of levels to recurse through for DFS:");
		int level = keyboard.nextInt();											//Get number of levels user wishes to recurse
		
		unvisitNodes(gv);														//Set all nodes to unvisited and invisible
		DFS(gv, list_actors.get(1), level);										//DFS through beginning at Kevin Bacon
		System.out.println("\nLink to display all traversed vertices in graph during DFS: ");
		String DFS_key = "";
		for (int i = 0; i <= level; i++) {										//Display color key
			String rgb = Integer.toHexString(111111 + 121212 * (level - i));
			String color = "#" + rgb.substring(2, rgb.length());
			DFS_key += i + " : " + color + ", ";
		}
		System.out.println("Key: " + DFS_key);
		Bridge.update();														//Complete bridges
		*/
		
		/** BFS implementation: */
		unvisitNodes(gv);														//Set all nodes to unvisited and invisible
		Object start = "Matin_Azizpour";
		Object end = list_actors.get(1);//"Warren_Zevon";//"James_Stewart_(I)";//list_actors.get(12);
		System.out.println("\nBFS: " + start + " -> " + end);
		BFS(gv, start, end);										//DFS through beginning at Kevin Bacon
		System.out.println("Link to display all traversed vertices in graph during BFS: ");
		Bridge.complete();														//Complete bridges
		
		keyboard.close();														//Close keyboard scanner
	}
}
