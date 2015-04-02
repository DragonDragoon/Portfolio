/**
 * @author William Woodard
 * @date   3/28/2015
 * @HW     Topological Ordering Implementation
 * @name   Graph.java
 * @desc   This file contains the graph structure for implementing topological order
 */
package TopologicalOrdering;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * 
 * @author William
 *
 * @param <V> : V is some general object (in the assignment we use a String)
 * @desc  Graph implementation that is the center of the assignment; implements the topological sorting
 *        in this file to keep main driver clean, and because it is relevant to the graph's functionality,
 *        similar to BFS and DFS.
 */
public class Graph<V> {
	//Public declarations because these are important to use outside of the class without doing a deep copy
	public Map<String, List<Edge<Vertex<String>>>> adjacent = new HashMap<String, List<Edge<Vertex<String>>>>();  //Map of all adjacent vertexes
	public Map<String, Integer> inboundEdgesCount = new HashMap<String, Integer>(); //Map of inbound edge counts (in place of using dictionaries)
	public Map<String, Integer> outboundEdgesCount = new HashMap<String, Integer>(); //Map of outbound edge counts (in place of using dictionaries)
	public Map<String, Boolean> visited = new HashMap<String, Boolean>();  //Map of visited vertexes (not needed for assignment, but good for searches)
	
	/**
	 * @name Graph()
	 * @desc Constructor for graph; the graph is made to be populated via 3rd party
	 */
	public Graph() {
	}
	
	/**
	 * @name  addVertex()
	 * @param parent : vertex to add to graph
	 */
	public void addVertex(Vertex<String> parent) {
		if (!adjacent.containsKey(parent.getValue())) {                              //If key does not already exist
			adjacent.put(parent.getValue(), new ArrayList<Edge<Vertex<String>>>());  //Add key to graph
			inboundEdgesCount.put(parent.getValue(), 0);                             //Initialize inbound count
			outboundEdgesCount.put(parent.getValue(), 0);                            //Initialize outbound count
			visited.put(parent.getValue(), false);                                   //Initialize visited boolean
		}
	}
	
	/**
	 * @name  createEdge()
	 * @param parent : parent vertex
	 * @param child : child vertex
	 * @param edge : edge connecting from parent to child
	 */
	public void createEdge(Vertex<String> parent, Vertex<String> child, Edge<Vertex<String>> edge) {
		this.addVertex(parent);                                                                    //Add parent to graph
		outboundEdgesCount.put(parent.getValue(), outboundEdgesCount.get(parent.getValue()) + 1);  //Add one to outbound count
		this.addVertex(child);                                                                     //Add child to graph
		inboundEdgesCount.put(child.getValue(), inboundEdgesCount.get(child.getValue()) + 1);      //Add one to inbound count
		adjacent.get(parent.getValue()).add(edge);                                                 //Add edge to key in graph
	}
	
	/**
	 * @name   contains()
	 * @param v : object that is the key to the list of edges for a certain vertex
	 * @return boolean : whether or not the graph contains the key (and therefore the vertex)
	 */
	public boolean contains(V v) {
		return adjacent.containsKey(v);
	}
	
	/**
	 * @name  inboundEdges()
	 * @param v : object to compare to
	 * @return List<String> : list of keys that make up the inbound edges in the graph
	 * @desc  while making the graph structure, I thought I might need this (but I did not)
	 */
	public List<String> inboundEdges(V v) {
		List<String> list = new ArrayList<String>();
		for (String vertex : adjacent.keySet()) {
			for (Edge<Vertex<String>> edge : adjacent.get(vertex)) {
				if (edge.getParent().equals(v)) {
					list.add(vertex);
				}
			}
		}
		return list;
	}
	
	/**
	 * @name outboundEdges()
	 * @param v : key to parent
	 * @return List<Vertex<String>> : list of vertexes that make up the outbound edges in the graph
	 * @desc  while making the graph structure, I thought I might need this (but I did not)
	 */
	public List<Vertex<String>> outboundEdges(V v) {
		List<Vertex<String>> list = new ArrayList<Vertex<String>>();
		for (Edge<Vertex<String>> edge : adjacent.get(v)) {
			list.add(edge.getChild());
		}
		return list;
	}
	
	/**
	 * @name unvisitNodes()
	 * @desc in case multiple searches are made in the main driver, this can be used to reset the structure
	 *       keeping track of whether or not a node has been visited
	 */
	public void unvisitNodes() {
		for (String key : visited.keySet()) {
			visited.put(key, false);
		}
	}
	
	/**
	 * @name topologicalSort()
	 * @return String : string displaying ordered objects, or if a cycle was found
	 * @desc  the main part of the assignment; searches through using inbound edges (decreasing to 0)
	 */
	public String topologicalSort() {
		String str = "";                                                        //Initialize empty string
		boolean cycle = false;                                                  //Whether or not a cycle is found
		Map<String, Integer> inboundCount = inboundEdgesCount;                  //Copy of inbound count Map
		unvisitNodes();                                                         //Unvisit all nodes
		for (int i = 0; i < inboundCount.size() && !cycle; i++) {               //For inbound edges
			boolean found = false;                                              //Whether or not node was found
			for (int j = 0; j < inboundCount.size() && !found; j++) {           //Decrement inbound edge counts
				String key = (String) inboundCount.keySet().toArray()[i];       //Key to node
				if (inboundCount.get(key) == 0) {                               //If node is 0
					visited.put(key, true);                                     //Visited node
					str += (i != inboundCount.size() - 1) ?  key + "," : key;   //Add to return string
					List<Edge<Vertex<String>>> children = adjacent.get(key);    //Get children
					for (int k = 0; k < children.size(); k++) {                 //For all children
						String child = children.get(k).getChild().getValue();   //Get key of child
						inboundCount.put(child, inboundCount.get(child) - 1);   //Decrement inbound count
					}
					found = true;                                               //Zero found
				}
			}
			if (!found) {                                                       //If no zero inbounds were found
				cycle = true;                                                   //Cycle was found!
				str = "Cycle found! No topological ordering!";                  //Set return string
			}
		}
		return str;                                                             //Return string
	}
	
	/**
	 * @toString()
	 * @desc used for debugging
	 */
	@Override
	public String toString() {
		String str = "";
		for (int i = 0; i < adjacent.size(); i++) {
			str += adjacent.values().toArray()[i] + "\n";
		}
		return str;
	}
}
